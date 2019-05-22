#include "stdafx.h"
#include "mfcviewer.h"
#include <OpenThreads\ScopedLock>
#include <osgViewer\ViewerEventHandlers>
#include <osgViewer\api\win32\GraphicsWindowWin32>
#include <osgGA\StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osg\ComputeBoundsVisitor>
#include <osgDB/ReadFile>
#include <OpenThreads/Thread>
#include <OpenThreads/Block>

class RenderThread : public OpenThreads::Thread
{
private:

	MFCViewer* _viewer;
	OpenThreads::Block _block;

public:
	RenderThread::RenderThread(MFCViewer* viewer) : _viewer(viewer)
	{

	}

	RenderThread::~RenderThread()
	{
		if (isRunning())
		{
			cancel();
			join();
		}
	}

	void pause(bool bPause)
	{
		_block.set(!bPause);
	}

	void RenderThread::run()
	{
		while (!testCancel() && _viewer &&
			_viewer->getViewer() && 
			!_viewer->getViewer()->done())
		{
			_block.block();
			//double minFrameTime = 1.0;
			//osg::Timer_t startFrameTick = osg::Timer::instance()->tick();
			_viewer->getViewer()->frame();
			//OpenThreads::Thread::microSleep(100);
			//osg::Timer_t endFrameTick = osg::Timer::instance()->tick();
			//double frameTime = osg::Timer::instance()->delta_s(startFrameTick, endFrameTick);
			//if (frameTime < minFrameTime) OpenThreads::Thread::microSleep(static_cast<unsigned int>(1000000.0*(minFrameTime-frameTime)));
		}
	}
};



MFCViewer::MFCViewer(HWND hWnd) : _hWnd(hWnd),_viewer(NULL),_renderthread(NULL)
{

}

MFCViewer::~MFCViewer()
{
	if(_viewer)
		_viewer->setDone(true);
	if (_renderthread != NULL)
	{
		((RenderThread*)(_renderthread))->pause(false);
		// 停止渲染线程
		while(((RenderThread*)(_renderthread))->isRunning())
		{
			continue;
		}
		delete (RenderThread*)(_renderthread);
		_renderthread = NULL;
	}

	if (_viewer)
	{
		delete _viewer;
		_viewer = NULL;
	}
}

void MFCViewer::Pause()
{
	if (_renderthread)
	{
		((RenderThread*)(_renderthread))->pause(true);
	}
}

void MFCViewer::Resume()
{
	if (_renderthread)
	{
		((RenderThread*)(_renderthread))->pause(false);
	}
}

void MFCViewer::InitOSG()
{
	InitSceneGraph();
	InitCameraConfig();

	//启动渲染线程
	RenderThread* rt = new RenderThread(this);
	rt->start();
	rt->pause(false);
	_renderthread = (void*)(rt);
}

void MFCViewer::frame()
{
	if (!_viewer || _viewer->done())
		return;

	_viewer->frame();
}

void MFCViewer::clearScene()
{
	if (!_realroot)
		return;

	_realroot->removeChildren(0, _realroot->getNumChildren());
}

void MFCViewer::InitSceneGraph(void)
{
	_sceneroot = new osg::Group;
	_realroot = new osg::Group;
	_realroot->setDataVariance(osg::Object::DYNAMIC);
	_asisroot = new osg::Group;
	_sceneroot->addChild(_realroot);
	_sceneroot->addChild(_asisroot);
}

void MFCViewer::setClearColor(const osg::Vec4& color)
{
	_viewer->getCamera()->setClearColor(color);
}

const osg::Vec4& MFCViewer::getClearColor() const
{
	return _viewer->getCamera()->getClearColor();
}

void MFCViewer::InitCameraConfig(void)
{
	RECT rect;

	// Create the viewer for this window
	_viewer = new osgViewer::Viewer();

	// Add a Stats Handler to the viewer
	_viewer->addEventHandler(new osgViewer::StatsHandler);

	// Get the current window size
	::GetWindowRect(_hWnd, &rect);

	// Init the GraphicsContext Traits
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

	// Init the Windata Variable that holds the handle for the Window to display OSG in.
	osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(_hWnd);

	// Setup the traits parameters
	traits->x = 0;
	traits->y = 0;
	traits->width = rect.right - rect.left;
	traits->height = rect.bottom - rect.top;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->setInheritedWindowPixelFormat = true;
	traits->inheritedWindowData = windata;

	// Create the Graphics Context
	osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits.get());

	// Init a new Camera (Master for this View)
	osg::ref_ptr<osg::Camera> camera = _viewer->getCamera();

	// Assign Graphics Context to the Camera
	camera->setGraphicsContext(gc);

	// Set the viewport for the Camera
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));

	// Set projection matrix and camera attribtues
	camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	camera->setProjectionMatrixAsPerspective(
		30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 1000.0);

	camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.2f, 1.0f));

	// Add the Camera to the Viewer
	//mViewer->addSlave(camera.get());
	_viewer->setCamera(camera.get());

	_viewer->getCamera()->setCullingMode(_viewer->getCamera()->getCullingMode() & ~osg::CullSettings::SMALL_FEATURE_CULLING);

	// Set the Scene Data
	_viewer->setSceneData(_sceneroot.get());

	// Add the Camera Manipulator to the Viewer
	_viewer->setCameraManipulator(new osgGA::TrackballManipulator());

	_viewer->addEventHandler(new osgViewer::StatsHandler());
	_viewer->addEventHandler(new osgGA::StateSetManipulator(camera->getOrCreateStateSet()));

	_viewer->setKeyEventSetsDone(0);

	osg::Light *pLight = _viewer->getLight();

	_viewer->setLightingMode(osg::View::HEADLIGHT);
	pLight->setAmbient(osg::Vec4(0.32, 0.32, 0.32, 1.0));
	pLight->setDiffuse(osg::Vec4(0.35, 0.35, 0.35, 1.0));
	pLight->setSpecular(osg::Vec4(0.6, 0.6, 0.6, 1.0));

	// Realize the Viewer
	_viewer->realize();
}
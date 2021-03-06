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
#include <osgEarthUtil/EarthManipulator>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class RenderThread : public OpenThreads::Thread
{
private:

	MFCViewer* _viewer;
	OpenThreads::Block _block;
	OpenThreads::Mutex _mutex;

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
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
	}

	void RenderThread::run()
	{
		while (!testCancel() && _viewer &&
			_viewer->getViewer() && 
			!_viewer->getViewer()->done())
		{
			_block.block();

			{
				OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
				_viewer->getViewer()->frame();
			}
			
			//OpenThreads::Thread::microSleep(100);
		}
	}
};



MFCViewer::MFCViewer(HWND hWnd) : _hWnd(hWnd),_viewer(NULL),_renderthread(NULL), _mapnode(NULL)
{

}

MFCViewer::~MFCViewer()
{
	if(_viewer)
		_viewer->setDone(true);
	if (_renderthread != NULL)
	{
		((RenderThread*)(_renderthread))->pause(false);
		// ֹͣ��Ⱦ�߳�
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

void MFCViewer::start()
{
	if (_renderthread)
		return;
	//������Ⱦ�߳�
	RenderThread* rt = new RenderThread(this);
	rt->start();
	rt->pause(false);
	_renderthread = (void*)(rt);
}

void MFCViewer::pause()
{
	if (_renderthread)
	{
		((RenderThread*)(_renderthread))->pause(true);
	}
}

void MFCViewer::resume()
{
	if (_renderthread)
	{
		((RenderThread*)(_renderthread))->pause(false);
	}
}

void MFCViewer::init()
{
	if (_viewer != NULL)
		return;

	InitCameraConfig();
}

bool MFCViewer::open(const std::string& file)
{
	osg::Node* node = osgDB::readNodeFile(file);
	if (!node)
		return false;

	osgEarth::MapNode* mapnode = osgEarth::MapNode::get(node);
	if (!mapnode)
		return false;
	_mapnode = mapnode;

	pause();
	_root->removeChildren(0, _root->getNumChildren());
	_root->addChild(node);
	resume();
	_url = file;
	return true;
}

void MFCViewer::clear()
{
	pause();
	_root->removeChildren(0, _root->getNumChildren());
	_url = "";
	resume();
}

void MFCViewer::frame()
{
	if (!_viewer || _viewer->done())
		return;

	_viewer->frame();
}

void MFCViewer::setClearColor(const osg::Vec4& color)
{
	_viewer->getCamera()->setClearColor(color);
}

const osg::Vec4& MFCViewer::getClearColor() const
{
	return _viewer->getCamera()->getClearColor();
}

void MFCViewer::InitCameraConfig()
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
	_root = new osg::Group();
	_root->setDataVariance(osg::Object::DYNAMIC);
	_viewer->setSceneData(_root);

	_viewer->getDatabasePager()->setUnrefImageDataAfterApplyPolicy(true, false);

	// thread-safe initialization of the OSG wrapper manager. Calling this here
	// prevents the "unsupported wrapper" messages from OSG
	osgDB::Registry::instance()->getObjectWrapperManager()->findWrapper("osg::Image");

	// install our default manipulator (do this before calling load)
	_viewer->setCameraManipulator(new osgEarth::Util::EarthManipulator());

	// disable the small-feature culling
	_viewer->getCamera()->setSmallFeatureCullingPixelSize(-1.0f);

	// set a near/far ratio that is smaller than the default. This allows us to get
	// closer to the ground without near clipping. If you need more, use --logdepth
	_viewer->getCamera()->setNearFarRatio(0.0001);

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
#pragma once

#include <osgViewer/Viewer>
#include <osg/Group>
#include <windows.h>

/** 渲染窗口*/
class MFCViewer
{
public:

	MFCViewer(HWND hWnd);
	~MFCViewer();

public:

	/** 初始化*/
	void InitOSG();

	/** 暂停渲染，在暂停渲染后可以对场景进行修改*/
	void Pause();

	/** 恢复渲染*/
	void Resume();

	/** 获取osg视窗*/
	osgViewer::Viewer* getViewer() const { return _viewer; }

	/** 获取显示根节点*/
	osg::Group* getRoot() const { return _realroot; }

	/** 获取辅助显示根节点，用于显示编辑状态等*/
	osg::Group* getAsisRoot() const { return _asisroot; }

	/** 设置背景色*/
	void setClearColor(const osg::Vec4& color);

	/** 获取背景色*/
	const osg::Vec4& getClearColor() const;

public:

	/** 清空显示节点*/
	void clearScene();

protected:

	void InitSceneGraph(void);
	void InitCameraConfig(void);
	void frame();

private:

	HWND _hWnd;
	osgViewer::Viewer* _viewer;
	osg::ref_ptr<osg::Group> _sceneroot;
	osg::ref_ptr<osg::Group> _realroot;
	osg::ref_ptr<osg::Group> _asisroot;
	osg::Vec3d _scenecenter;
	float _scenezscale;
	void* _renderthread;
};
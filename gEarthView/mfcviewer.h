#pragma once

#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgEarth/MapNode>
#include <windows.h>

/** 渲染窗口*/
class MFCViewer
{
public:

	MFCViewer(HWND hWnd);
	~MFCViewer();

public:

	/** 初始化*/
	void init();

	/** 打开节点*/
	bool open(const std::string& file);

	/** 开始渲染*/
	void start();

	/** 暂停渲染，在暂停渲染后可以对场景进行修改*/
	void pause();

	/** 恢复渲染*/
	void resume();

	/** 获取osg视窗*/
	osgViewer::Viewer* getViewer() const { return _viewer; }

	/** 获取根节点*/
	osg::Group* getRoot() const { return _root; }

	/** 获取MapNode*/
	osg::Group* getMapNode() const { return _mapnode; }

	/** 设置背景色*/
	void setClearColor(const osg::Vec4& color);

	/** 获取背景色*/
	const osg::Vec4& getClearColor() const;

protected:

	void InitCameraConfig();
	void frame();

private:

	HWND _hWnd;
	osgViewer::Viewer* _viewer;
	osgEarth::MapNode* _mapnode;
	osg::Group* _root;
	void* _renderthread;
};
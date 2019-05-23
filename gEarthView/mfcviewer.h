#pragma once

#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgEarth/MapNode>
#include <windows.h>

/** ��Ⱦ����*/
class MFCViewer
{
public:

	MFCViewer(HWND hWnd);
	~MFCViewer();

public:

	/** ��ʼ��*/
	void init();

	/** �򿪽ڵ�*/
	bool open(const std::string& file);

	/** ��ʼ��Ⱦ*/
	void start();

	/** ��ͣ��Ⱦ������ͣ��Ⱦ����ԶԳ��������޸�*/
	void pause();

	/** �ָ���Ⱦ*/
	void resume();

	/** ��ȡosg�Ӵ�*/
	osgViewer::Viewer* getViewer() const { return _viewer; }

	/** ��ȡ���ڵ�*/
	osg::Group* getRoot() const { return _root; }

	/** ��ȡMapNode*/
	osg::Group* getMapNode() const { return _mapnode; }

	/** ���ñ���ɫ*/
	void setClearColor(const osg::Vec4& color);

	/** ��ȡ����ɫ*/
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
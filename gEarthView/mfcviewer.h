#pragma once

#include <osgViewer/Viewer>
#include <osg/Group>
#include <windows.h>

/** ��Ⱦ����*/
class MFCViewer
{
public:

	MFCViewer(HWND hWnd);
	~MFCViewer();

public:

	/** ��ʼ��*/
	void InitOSG();

	/** ��ͣ��Ⱦ������ͣ��Ⱦ����ԶԳ��������޸�*/
	void Pause();

	/** �ָ���Ⱦ*/
	void Resume();

	/** ��ȡosg�Ӵ�*/
	osgViewer::Viewer* getViewer() const { return _viewer; }

	/** ��ȡ��ʾ���ڵ�*/
	osg::Group* getRoot() const { return _realroot; }

	/** ��ȡ������ʾ���ڵ㣬������ʾ�༭״̬��*/
	osg::Group* getAsisRoot() const { return _asisroot; }

	/** ���ñ���ɫ*/
	void setClearColor(const osg::Vec4& color);

	/** ��ȡ����ɫ*/
	const osg::Vec4& getClearColor() const;

public:

	/** �����ʾ�ڵ�*/
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
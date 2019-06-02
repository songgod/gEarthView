#pragma once
#include "mfcviewer.h"

// gEarthViewCtrl.h : CgEarthViewCtrl ActiveX �ؼ����������


// CgEarthViewCtrl : �й�ʵ�ֵ���Ϣ������� gEarthViewCtrl.cpp��

class CgEarthViewCtrl : public COleControl
{
	DECLARE_DYNCREATE(CgEarthViewCtrl)

// ���캯��
public:
	CgEarthViewCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

protected:

	MFCViewer *m_Viewer;

// ʵ��
protected:
	~CgEarthViewCtrl();

	DECLARE_OLECREATE_EX(CgEarthViewCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CgEarthViewCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CgEarthViewCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CgEarthViewCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

// ���Ⱥ��¼� ID
public:
	enum {
		dispidSaveAs = 6L,
		dispidSave = 5L,
		dispidClose = 4L,
		dispidOpen = 3L,
		dispidFlyto = 2L
	};
protected:
	void Flyto(DOUBLE lat, DOUBLE lng, DOUBLE alt);
	LONG Open(LPCTSTR url);
	void Close();
	LONG Save();
	LONG SaveAs(LPCTSTR url);
};


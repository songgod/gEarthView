#pragma once
#include "mfcviewer.h"

// gEarthViewCtrl.h : CgEarthViewCtrl ActiveX 控件类的声明。


// CgEarthViewCtrl : 有关实现的信息，请参阅 gEarthViewCtrl.cpp。

class CgEarthViewCtrl : public COleControl
{
	DECLARE_DYNCREATE(CgEarthViewCtrl)

// 构造函数
public:
	CgEarthViewCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

protected:

	MFCViewer *m_Viewer;

// 实现
protected:
	~CgEarthViewCtrl();

	DECLARE_OLECREATE_EX(CgEarthViewCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CgEarthViewCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CgEarthViewCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CgEarthViewCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

// 调度和事件 ID
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


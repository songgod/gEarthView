#pragma once

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

// ���Ⱥ��¼� ID
public:
	enum {
		dispidFlyto = 4L,
		dispidUrl = 3,
		dispidClose = 2L,
		dispidOpen = 1L
	};
protected:
	LONG Open(LPCTSTR url);
	void Close();
	void OnUrlChanged();
	CString m_Url;
	void Flyto(DOUBLE lat, DOUBLE lng, DOUBLE alt);
};


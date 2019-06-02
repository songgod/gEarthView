// gEarthViewCtrl.cpp : CgEarthViewCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "gEarthView.h"
#include "gEarthViewCtrl.h"
#include "gEarthViewPropPage.h"
#include "afxdialogex.h"
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CgEarthViewCtrl, COleControl)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CgEarthViewCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// ����ӳ��

BEGIN_DISPATCH_MAP(CgEarthViewCtrl, COleControl)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "Flyto", dispidFlyto, Flyto, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "Open", dispidOpen, Open, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "Close", dispidClose, Close, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "Save", dispidSave, Save, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "SaveAs", dispidSaveAs, SaveAs, VT_I4, VTS_BSTR)
END_DISPATCH_MAP()

// �¼�ӳ��

BEGIN_EVENT_MAP(CgEarthViewCtrl, COleControl)
END_EVENT_MAP()

// ����ҳ

// TODO: ������Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CgEarthViewCtrl, 1)
	PROPPAGEID(CgEarthViewPropPage::guid)
END_PROPPAGEIDS(CgEarthViewCtrl)

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CgEarthViewCtrl, "GEARTHVIEW.gEarthViewCtrl.1",
	0xf7a56a10, 0xd364, 0x43b3, 0x85, 0x16, 0x5a, 0x4d, 0x8e, 0x9c, 0x84, 0x7b)

// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CgEarthViewCtrl, _tlid, _wVerMajor, _wVerMinor)

// �ӿ� ID

const IID IID_DgEarthView = { 0xC8C4DA98, 0xAC80, 0x497D, { 0x90, 0x4F, 0xB3, 0x64, 0x29, 0x9, 0x89, 0x42 } };
const IID IID_DgEarthViewEvents = { 0x71F9046B, 0x9962, 0x41E5, { 0xAF, 0xE2, 0xA1, 0xC6, 0xBB, 0xB9, 0x35, 0x17 } };

// �ؼ�������Ϣ

static const DWORD _dwgEarthViewOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CgEarthViewCtrl, IDS_GEARTHVIEW, _dwgEarthViewOleMisc)

// CgEarthViewCtrl::CgEarthViewCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CgEarthViewCtrl ��ϵͳע�����

BOOL CgEarthViewCtrl::CgEarthViewCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_GEARTHVIEW,
			IDB_GEARTHVIEW,
			afxRegApartmentThreading,
			_dwgEarthViewOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CgEarthViewCtrl::CgEarthViewCtrl - ���캯��

CgEarthViewCtrl::CgEarthViewCtrl():m_Viewer(NULL)
{
	InitializeIIDs(&IID_DgEarthView, &IID_DgEarthViewEvents);
	// TODO:  �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}

// CgEarthViewCtrl::~CgEarthViewCtrl - ��������

CgEarthViewCtrl::~CgEarthViewCtrl()
{
	// TODO:  �ڴ�����ؼ���ʵ�����ݡ�
	if (m_Viewer)
	{
		delete m_Viewer;
		m_Viewer = NULL;
	}
}

// CgEarthViewCtrl::OnDraw - ��ͼ����

void CgEarthViewCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	if(!m_Viewer)
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
}

// CgEarthViewCtrl::DoPropExchange - �־���֧��

void CgEarthViewCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}


// CgEarthViewCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CgEarthViewCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO:  �ڴ��������������ؼ�״̬��
}


// CgEarthViewCtrl::AboutBox - ���û���ʾ�����ڡ���

void CgEarthViewCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GEARTHVIEW);
	dlgAbout.DoModal();
}


// CgEarthViewCtrl ��Ϣ�������


void CgEarthViewCtrl::Flyto(DOUBLE lat, DOUBLE lng, DOUBLE alt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
}


BOOL CgEarthViewCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (!m_Viewer)
		return COleControl::OnEraseBkgnd(pDC);

	return TRUE;
}


void CgEarthViewCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

}


int CgEarthViewCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_Viewer = new MFCViewer(m_hWnd);
	m_Viewer->init();
	m_Viewer->start();
	return 0;
}


LONG CgEarthViewCtrl::Open(LPCTSTR url)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	if (!m_Viewer->open(url))
		return -1;

	return 0;
}


void CgEarthViewCtrl::Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	m_Viewer->clear();
}


LONG CgEarthViewCtrl::Save()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	osgEarth::MapNode* mapNode = m_Viewer->getMapNode();
	if (!mapNode)
		return -1;

	if (!osgDB::writeNodeFile(*mapNode, m_Viewer->getUrl()))
		return -1;

	return 0;
}


LONG CgEarthViewCtrl::SaveAs(LPCTSTR url)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	osgEarth::MapNode* mapNode = m_Viewer->getMapNode();
	if (!mapNode)
		return -1;

	if (!osgDB::writeNodeFile(*mapNode, url))
		return -1;

	return 0;
}

// gEarthViewCtrl.cpp : CgEarthViewCtrl ActiveX 控件类的实现。

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

// 消息映射

BEGIN_MESSAGE_MAP(CgEarthViewCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CgEarthViewCtrl, COleControl)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "Flyto", dispidFlyto, Flyto, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "Open", dispidOpen, Open, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "Close", dispidClose, Close, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "Save", dispidSave, Save, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CgEarthViewCtrl, "SaveAs", dispidSaveAs, SaveAs, VT_I4, VTS_BSTR)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CgEarthViewCtrl, COleControl)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CgEarthViewCtrl, 1)
	PROPPAGEID(CgEarthViewPropPage::guid)
END_PROPPAGEIDS(CgEarthViewCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CgEarthViewCtrl, "GEARTHVIEW.gEarthViewCtrl.1",
	0xf7a56a10, 0xd364, 0x43b3, 0x85, 0x16, 0x5a, 0x4d, 0x8e, 0x9c, 0x84, 0x7b)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CgEarthViewCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DgEarthView = { 0xC8C4DA98, 0xAC80, 0x497D, { 0x90, 0x4F, 0xB3, 0x64, 0x29, 0x9, 0x89, 0x42 } };
const IID IID_DgEarthViewEvents = { 0x71F9046B, 0x9962, 0x41E5, { 0xAF, 0xE2, 0xA1, 0xC6, 0xBB, 0xB9, 0x35, 0x17 } };

// 控件类型信息

static const DWORD _dwgEarthViewOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CgEarthViewCtrl, IDS_GEARTHVIEW, _dwgEarthViewOleMisc)

// CgEarthViewCtrl::CgEarthViewCtrlFactory::UpdateRegistry -
// 添加或移除 CgEarthViewCtrl 的系统注册表项

BOOL CgEarthViewCtrl::CgEarthViewCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

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


// CgEarthViewCtrl::CgEarthViewCtrl - 构造函数

CgEarthViewCtrl::CgEarthViewCtrl():m_Viewer(NULL)
{
	InitializeIIDs(&IID_DgEarthView, &IID_DgEarthViewEvents);
	// TODO:  在此初始化控件的实例数据。
}

// CgEarthViewCtrl::~CgEarthViewCtrl - 析构函数

CgEarthViewCtrl::~CgEarthViewCtrl()
{
	// TODO:  在此清理控件的实例数据。
	if (m_Viewer)
	{
		delete m_Viewer;
		m_Viewer = NULL;
	}
}

// CgEarthViewCtrl::OnDraw - 绘图函数

void CgEarthViewCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	if(!m_Viewer)
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
}

// CgEarthViewCtrl::DoPropExchange - 持久性支持

void CgEarthViewCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CgEarthViewCtrl::OnResetState - 将控件重置为默认状态

void CgEarthViewCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CgEarthViewCtrl::AboutBox - 向用户显示“关于”框

void CgEarthViewCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GEARTHVIEW);
	dlgAbout.DoModal();
}


// CgEarthViewCtrl 消息处理程序


void CgEarthViewCtrl::Flyto(DOUBLE lat, DOUBLE lng, DOUBLE alt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
}


BOOL CgEarthViewCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (!m_Viewer)
		return COleControl::OnEraseBkgnd(pDC);

	return TRUE;
}


void CgEarthViewCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

}


int CgEarthViewCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_Viewer = new MFCViewer(m_hWnd);
	m_Viewer->init();
	m_Viewer->start();
	return 0;
}


LONG CgEarthViewCtrl::Open(LPCTSTR url)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
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

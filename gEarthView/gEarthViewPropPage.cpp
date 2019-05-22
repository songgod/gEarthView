// gEarthViewPropPage.cpp : CgEarthViewPropPage 属性页类的实现。

#include "stdafx.h"
#include "gEarthView.h"
#include "gEarthViewPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CgEarthViewPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CgEarthViewPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CgEarthViewPropPage, "GEARTHVIEW.gEarthViewPropPage.1",
	0xb4d7f16f, 0xace3, 0x476c, 0x97, 0x73, 0x1b, 0x6, 0xf9, 0xe7, 0xe5, 0x5a)

// CgEarthViewPropPage::CgEarthViewPropPageFactory::UpdateRegistry -
// 添加或移除 CgEarthViewPropPage 的系统注册表项

BOOL CgEarthViewPropPage::CgEarthViewPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GEARTHVIEW_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CgEarthViewPropPage::CgEarthViewPropPage - 构造函数

CgEarthViewPropPage::CgEarthViewPropPage() :
	COlePropertyPage(IDD, IDS_GEARTHVIEW_PPG_CAPTION)
{
}

// CgEarthViewPropPage::DoDataExchange - 在页和属性间移动数据

void CgEarthViewPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CgEarthViewPropPage 消息处理程序

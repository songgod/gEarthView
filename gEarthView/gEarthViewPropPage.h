#pragma once

// gEarthViewPropPage.h : CgEarthViewPropPage 属性页类的声明。


// CgEarthViewPropPage : 有关实现的信息，请参阅 gEarthViewPropPage.cpp。

class CgEarthViewPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CgEarthViewPropPage)
	DECLARE_OLECREATE_EX(CgEarthViewPropPage)

// 构造函数
public:
	CgEarthViewPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_GEARTHVIEW };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};


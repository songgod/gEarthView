#pragma once

// gEarthViewPropPage.h : CgEarthViewPropPage ����ҳ���������


// CgEarthViewPropPage : �й�ʵ�ֵ���Ϣ������� gEarthViewPropPage.cpp��

class CgEarthViewPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CgEarthViewPropPage)
	DECLARE_OLECREATE_EX(CgEarthViewPropPage)

// ���캯��
public:
	CgEarthViewPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_GEARTHVIEW };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};


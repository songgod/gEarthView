#pragma once

// gEarthView.h : gEarthView.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// CgEarthViewApp : �й�ʵ�ֵ���Ϣ������� gEarthView.cpp��

class CgEarthViewApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();

public:

	CString GetOcxPath();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;


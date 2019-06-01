#pragma once

// gEarthView.h : gEarthView.DLL 的主头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号


// CgEarthViewApp : 有关实现的信息，请参阅 gEarthView.cpp。

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


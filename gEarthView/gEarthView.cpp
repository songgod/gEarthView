// gEarthView.cpp : CgEarthViewApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "gEarthView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CgEarthViewApp theApp;

const GUID CDECL _tlid = { 0x16DA3DA1, 0x53F5, 0x44D6, { 0x97, 0xD3, 0xCF, 0x61, 0x4A, 0x79, 0xCA, 0x80 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CgEarthViewApp::InitInstance - DLL ��ʼ��

BOOL CgEarthViewApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CgEarthViewApp::ExitInstance - DLL ��ֹ

int CgEarthViewApp::ExitInstance()
{
	// TODO:  �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}

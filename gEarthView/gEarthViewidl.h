

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed May 22 11:25:16 2019
 */
/* Compiler settings for gEarthView.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __gEarthViewidl_h__
#define __gEarthViewidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DgEarthView_FWD_DEFINED__
#define ___DgEarthView_FWD_DEFINED__
typedef interface _DgEarthView _DgEarthView;

#endif 	/* ___DgEarthView_FWD_DEFINED__ */


#ifndef ___DgEarthViewEvents_FWD_DEFINED__
#define ___DgEarthViewEvents_FWD_DEFINED__
typedef interface _DgEarthViewEvents _DgEarthViewEvents;

#endif 	/* ___DgEarthViewEvents_FWD_DEFINED__ */


#ifndef __gEarthView_FWD_DEFINED__
#define __gEarthView_FWD_DEFINED__

#ifdef __cplusplus
typedef class gEarthView gEarthView;
#else
typedef struct gEarthView gEarthView;
#endif /* __cplusplus */

#endif 	/* __gEarthView_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_gEarthView_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_gEarthView_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_gEarthView_0000_0000_v0_0_s_ifspec;


#ifndef __gEarthViewLib_LIBRARY_DEFINED__
#define __gEarthViewLib_LIBRARY_DEFINED__

/* library gEarthViewLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_gEarthViewLib;

#ifndef ___DgEarthView_DISPINTERFACE_DEFINED__
#define ___DgEarthView_DISPINTERFACE_DEFINED__

/* dispinterface _DgEarthView */
/* [uuid] */ 


EXTERN_C const IID DIID__DgEarthView;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C8C4DA98-AC80-497D-904F-B36429098942")
    _DgEarthView : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DgEarthViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DgEarthView * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DgEarthView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DgEarthView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DgEarthView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DgEarthView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DgEarthView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DgEarthView * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DgEarthViewVtbl;

    interface _DgEarthView
    {
        CONST_VTBL struct _DgEarthViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DgEarthView_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DgEarthView_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DgEarthView_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DgEarthView_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DgEarthView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DgEarthView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DgEarthView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DgEarthView_DISPINTERFACE_DEFINED__ */


#ifndef ___DgEarthViewEvents_DISPINTERFACE_DEFINED__
#define ___DgEarthViewEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DgEarthViewEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DgEarthViewEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("71F9046B-9962-41E5-AFE2-A1C6BBB93517")
    _DgEarthViewEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DgEarthViewEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DgEarthViewEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DgEarthViewEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DgEarthViewEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DgEarthViewEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DgEarthViewEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DgEarthViewEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DgEarthViewEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DgEarthViewEventsVtbl;

    interface _DgEarthViewEvents
    {
        CONST_VTBL struct _DgEarthViewEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DgEarthViewEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DgEarthViewEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DgEarthViewEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DgEarthViewEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DgEarthViewEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DgEarthViewEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DgEarthViewEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DgEarthViewEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_gEarthView;

#ifdef __cplusplus

class DECLSPEC_UUID("F7A56A10-D364-43B3-8516-5A4D8E9C847B")
gEarthView;
#endif
#endif /* __gEarthViewLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



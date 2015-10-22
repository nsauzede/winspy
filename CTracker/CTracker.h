#if !defined(AFX_CTRACKER_H__A4D782B4_D4C8_11D4_8270_00C0F057D251__INCLUDED_)
#define AFX_CTRACKER_H__A4D782B4_D4C8_11D4_8270_00C0F057D251__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CTracker.h : main header file for CTRACKER.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCTrackerApp : See CTracker.cpp for implementation.

class CCTrackerApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRACKER_H__A4D782B4_D4C8_11D4_8270_00C0F057D251__INCLUDED)

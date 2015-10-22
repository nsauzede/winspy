// winspy.h : main header file for the WINSPY application
//

#if !defined(AFX_WINSPY_H__8D8BA565_CF62_11D4_8268_00C0F057D251__INCLUDED_)
#define AFX_WINSPY_H__8D8BA565_CF62_11D4_8268_00C0F057D251__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinspyApp:
// See winspy.cpp for the implementation of this class
//

class CWinspyApp : public CWinApp
{
public:
	CWinspyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinspyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinspyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSPY_H__8D8BA565_CF62_11D4_8268_00C0F057D251__INCLUDED_)

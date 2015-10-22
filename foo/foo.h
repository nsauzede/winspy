// foo.h : main header file for the FOO application
//

#if !defined(AFX_FOO_H__D5EC85E8_D00D_11D4_8269_00C0F057D251__INCLUDED_)
#define AFX_FOO_H__D5EC85E8_D00D_11D4_8269_00C0F057D251__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFooApp:
// See foo.cpp for the implementation of this class
//

class CFooApp : public CWinApp
{
public:
	CFooApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFooApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFooApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOO_H__D5EC85E8_D00D_11D4_8269_00C0F057D251__INCLUDED_)

// Track.h : main header file for the TRACK application
//

#if !defined(AFX_TRACK_H__7FD34A59_D11D_11D4_826B_00C0F057D251__INCLUDED_)
#define AFX_TRACK_H__7FD34A59_D11D_11D4_826B_00C0F057D251__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTrackApp:
// See Track.cpp for the implementation of this class
//

class CTrackApp : public CWinApp
{
public:
	CTrackApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTrackApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACK_H__7FD34A59_D11D_11D4_826B_00C0F057D251__INCLUDED_)

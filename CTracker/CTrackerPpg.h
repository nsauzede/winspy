#if !defined(AFX_CTRACKERPPG_H__A4D782BE_D4C8_11D4_8270_00C0F057D251__INCLUDED_)
#define AFX_CTRACKERPPG_H__A4D782BE_D4C8_11D4_8270_00C0F057D251__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CTrackerPpg.h : Declaration of the CCTrackerPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CCTrackerPropPage : See CTrackerPpg.cpp.cpp for implementation.

class CCTrackerPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCTrackerPropPage)
	DECLARE_OLECREATE_EX(CCTrackerPropPage)

// Constructor
public:
	CCTrackerPropPage();

// Dialog Data
	//{{AFX_DATA(CCTrackerPropPage)
	enum { IDD = IDD_PROPPAGE_CTRACKER };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CCTrackerPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRACKERPPG_H__A4D782BE_D4C8_11D4_8270_00C0F057D251__INCLUDED)

#if !defined(AFX_CTRACKERCTL_H__A4D782BC_D4C8_11D4_8270_00C0F057D251__INCLUDED_)
#define AFX_CTRACKERCTL_H__A4D782BC_D4C8_11D4_8270_00C0F057D251__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CTrackerCtl.h : Declaration of the CCTrackerCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl : See CTrackerCtl.cpp for implementation.

class CCTrackerCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCTrackerCtrl)

// Constructor
public:
	CCTrackerCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTrackerCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CCTrackerCtrl();

	DECLARE_OLECREATE_EX(CCTrackerCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CCTrackerCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCTrackerCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CCTrackerCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CCTrackerCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CCTrackerCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CCTrackerCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CCTrackerCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRACKERCTL_H__A4D782BC_D4C8_11D4_8270_00C0F057D251__INCLUDED)

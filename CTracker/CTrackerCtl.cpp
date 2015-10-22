// CTrackerCtl.cpp : Implementation of the CCTrackerCtrl ActiveX Control class.

#include "stdafx.h"
#include "CTracker.h"
#include "CTrackerCtl.h"
#include "CTrackerPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCTrackerCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCTrackerCtrl, COleControl)
	//{{AFX_MSG_MAP(CCTrackerCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CCTrackerCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CCTrackerCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CCTrackerCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CCTrackerCtrl, COleControl)
	//{{AFX_EVENT_MAP(CCTrackerCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CCTrackerCtrl, 1)
	PROPPAGEID(CCTrackerPropPage::guid)
END_PROPPAGEIDS(CCTrackerCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCTrackerCtrl, "CTRACKER.CTrackerCtrl.1",
	0xa4d782ae, 0xd4c8, 0x11d4, 0x82, 0x70, 0, 0xc0, 0xf0, 0x57, 0xd2, 0x51)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CCTrackerCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DCTracker =
		{ 0xa4d782ac, 0xd4c8, 0x11d4, { 0x82, 0x70, 0, 0xc0, 0xf0, 0x57, 0xd2, 0x51 } };
const IID BASED_CODE IID_DCTrackerEvents =
		{ 0xa4d782ad, 0xd4c8, 0x11d4, { 0x82, 0x70, 0, 0xc0, 0xf0, 0x57, 0xd2, 0x51 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwCTrackerOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCTrackerCtrl, IDS_CTRACKER, _dwCTrackerOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::CCTrackerCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CCTrackerCtrl

BOOL CCTrackerCtrl::CCTrackerCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CTRACKER,
			IDB_CTRACKER,
			afxRegApartmentThreading,
			_dwCTrackerOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::CCTrackerCtrl - Constructor

CCTrackerCtrl::CCTrackerCtrl()
{
	InitializeIIDs(&IID_DCTracker, &IID_DCTrackerEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::~CCTrackerCtrl - Destructor

CCTrackerCtrl::~CCTrackerCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::OnDraw - Drawing function

void CCTrackerCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DoSuperclassPaint(pdc, rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::DoPropExchange - Persistence support

void CCTrackerCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::OnResetState - Reset control to default state

void CCTrackerCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::AboutBox - Display an "About" box to the user

void CCTrackerCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_CTRACKER);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CCTrackerCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("BUTTON");
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::IsSubclassedControl - This is a subclassed control

BOOL CCTrackerCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl::OnOcmCommand - Handle command messages

LRESULT CCTrackerCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerCtrl message handlers

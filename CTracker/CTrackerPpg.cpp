// CTrackerPpg.cpp : Implementation of the CCTrackerPropPage property page class.

#include "stdafx.h"
#include "CTracker.h"
#include "CTrackerPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCTrackerPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCTrackerPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CCTrackerPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCTrackerPropPage, "CTRACKER.CTrackerPropPage.1",
	0xa4d782af, 0xd4c8, 0x11d4, 0x82, 0x70, 0, 0xc0, 0xf0, 0x57, 0xd2, 0x51)


/////////////////////////////////////////////////////////////////////////////
// CCTrackerPropPage::CCTrackerPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCTrackerPropPage

BOOL CCTrackerPropPage::CCTrackerPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CTRACKER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerPropPage::CCTrackerPropPage - Constructor

CCTrackerPropPage::CCTrackerPropPage() :
	COlePropertyPage(IDD, IDS_CTRACKER_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CCTrackerPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerPropPage::DoDataExchange - Moves data between page and properties

void CCTrackerPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CCTrackerPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CCTrackerPropPage message handlers

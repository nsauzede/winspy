// winspyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winspy.h"
#include "winspyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	void ShortDisp( CString s);
	enum { TIMER_WIPE_ID = 1, TIMER_WIPE_PERIOD = 1000 };
	int m_nTimerWipe;
	HICON m_eggIcon;
	bool m_eggFound;
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CAnimateCtrl	m_eggAnim;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_eggIcon = AfxGetApp()->LoadIcon( IDI_EGG);
	m_eggFound = false;
	m_nTimerWipe = 0;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ANIMATE1, m_eggAnim);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinspyDlg dialog

CWinspyDlg::CWinspyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinspyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinspyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_parentWindow = NULL;
	m_trackCursor = AfxGetApp()->LoadCursor( IDC_TRACK);
	m_trackIconDisabled = AfxGetApp()->LoadIcon( IDI_TRACK_ZONE2);
	m_trackIconEnabled = AfxGetApp()->LoadIcon( IDI_TRACK_ZONE1);
	m_isCapturing = false;
	m_captureWindow = this;
	m_hOldWnd = 0;
	m_nHiliteTimer = 0;
}

void CWinspyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinspyDlg)
	DDX_Control(pDX, IDC_LIST_WS_EX, m_WsExStyleList);
	DDX_Control(pDX, IDC_LIST_WS, m_WsStyleList);
	DDX_Control(pDX, IDC_WINDOW_LIST, m_WndList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinspyDlg, CDialog)
	//{{AFX_MSG_MAP(CWinspyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_WINDOW_LIST, OnItemchangedWindowList)
	ON_BN_CLICKED(IDC_SET_WS, OnSetWs)
	ON_BN_CLICKED(IDC_UPDATE_STATUS, OnUpdateStatus)
	ON_EN_SETFOCUS(IDC_SEARCH_WINDOW, OnSetfocusSearchString)
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	ON_BN_CLICKED(IDC_HIDE, OnHide)
	ON_EN_KILLFOCUS(IDC_SEARCH_WINDOW, OnKillfocusSearchWindow)
	ON_EN_KILLFOCUS(IDC_SEARCH_CLASS, OnKillfocusSearchClass)
	ON_EN_SETFOCUS(IDC_SEARCH_CLASS, OnSetfocusSearchClass)
	ON_EN_KILLFOCUS(IDC_WS, OnKillfocusWs)
	ON_EN_SETFOCUS(IDC_WS, OnSetfocusWs)
	ON_EN_KILLFOCUS(IDC_WS_EX, OnKillfocusWsEx)
	ON_EN_SETFOCUS(IDC_WS_EX, OnSetfocusWsEx)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_SHOW_CHILDS, OnShowChilds)
	ON_BN_CLICKED(IDC_SHOW_PARENTS, OnShowParents)
	ON_BN_CLICKED(IDC_HILITE, OnHilite)
	ON_BN_CLICKED(IDC_SHOW_EMPTY_TITLES, OnShowEmptyTitles)
	ON_BN_CLICKED(IDC_SHOW_NULL_RECTS, OnShowNullRects)
	ON_BN_CLICKED(IDC_SHOW_NON_VISIBLES, OnShowVisibles)
	ON_BN_CLICKED(IDC_REPAINT, OnRepaint)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinspyDlg message handlers

BOOL CWinspyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int col = 0;
	m_WndList.InsertColumn( ColHwndSub = col++, "Hwnd", LVCFMT_LEFT, 55);
	m_WndList.InsertColumn( ColWinSub = col++, "Name", LVCFMT_LEFT, 200);
	m_WndList.InsertColumn( ColClassSub = col++, "Class", LVCFMT_LEFT, 180);

	col = 0;
	m_WsStyleList.InsertColumn( ColHwndSub = col++, "Style", LVCFMT_LEFT, 150);

	col = 0;
	m_WsExStyleList.InsertColumn( ColHwndSub = col++, "Extended style", LVCFMT_LEFT, 150);

	m_old_def = 0;

	CString s;
	s.Format( "Feeling groovy");
	SetDlgItemText( IDC_STATUS, s);

	CButton * pButton = (CButton *)GetDlgItem( IDC_SHOW_NULL_RECTS);
	if (pButton)
		pButton->SetCheck( 1);
/*
	CWnd * pWnd;
	pWnd = GetDlgItem( IDC_WS);
	if (pWnd)
		pWnd->EnableWindow( FALSE);
	pWnd = GetDlgItem( IDC_WS_EX);
	if (pWnd)
		pWnd->EnableWindow( FALSE);
	pWnd = GetDlgItem( IDC_SET_WS);
	if (pWnd)
		pWnd->EnableWindow( FALSE);
	pWnd = GetDlgItem( IDC_SHOW);
	if (pWnd)
		pWnd->EnableWindow( FALSE);
	pWnd = GetDlgItem( IDC_HIDE);
	if (pWnd)
		pWnd->EnableWindow( FALSE);
	pWnd = GetDlgItem( IDC_CLOSE);
	if (pWnd)
		pWnd->EnableWindow( FALSE);
*/

	OnRefresh();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinspyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinspyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinspyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
typedef struct _LV_ITEM { 
    UINT   mask; 
    int    iItem; 
    int    iSubItem; 
    UINT   state; 
    UINT   stateMask; 
    LPTSTR  pszText; 
    int    cchTextMax; 
    int    iImage;       // index of the list view item’s icon 
    LPARAM lParam;       // 32-bit value to associate with item 
} LV_ITEM; 
*/

void CWinspyDlg::OnSearch() 
{
	CString sHwnd, sFoundHwnd, sWin, sClass, sFoundWin, sFoundClass;
	int result = -1, partial = -1;

	GetDlgItemText( IDC_SEARCH_HWND, sHwnd);
	GetDlgItemText( IDC_SEARCH_WINDOW, sWin);
	GetDlgItemText( IDC_SEARCH_CLASS, sClass);

	int nItem = m_WndList.GetItemCount();
	int i;

	int start = m_WndList.GetNextItem( -1, LVNI_ALL | LVNI_FOCUSED);
	if (start == -1)
		start = 0;
	else
	{
		start++;
	}
	for (i = start; i < nItem; i++)
	{
		int ok1 = 0, ok2 = 0;

		if (sHwnd != "")
		{
			sFoundHwnd = m_WndList.GetItemText( i, ColHwndSub);
			if (sFoundHwnd == sHwnd)
			{
				result = i;
				break;
			}
		}
		if (sWin != "")
		{
			sFoundWin = m_WndList.GetItemText( i, ColWinSub);
			if (sFoundWin.Find( sWin) >= 0)
				ok1 = 1;
		}
		if (sClass != "")
		{
			sFoundClass = m_WndList.GetItemText( i, ColClassSub);
			if (sFoundClass.Find( sClass) >= 0)
				ok2 = 1;
		}
		if (ok1 || !ok1 && ok2)
		{
			result = i;
			break;
		}
		if ((partial < 0) && (ok1 || ok2))
			partial = i;
	}
	if ((start > 0) && (start < nItem) && (result < 0))
	{
		for (i = 0; i < start; i++)
		{
			int ok1 = 0, ok2 = 0;

			if (sWin != "")
			{
				sFoundWin = m_WndList.GetItemText( i, ColWinSub);
				if (sFoundWin.Find( sWin) >= 0)
					ok1 = 1;
			}
			if (sClass != "")
			{
				sFoundClass = m_WndList.GetItemText( i, ColClassSub);
				if (sFoundClass.Find( sClass) >= 0)
					ok2 = 1;
			}
			if (ok1 || !ok1 && ok2)
			{
				result = i;
				break;
			}
			if ((partial < 0) && (ok1 || ok2))
				partial = i;
		}
	}

	if (result < 0)
		if (partial >= 0)
			result = partial;

	CString status;
	if (result < 0)
		status.Format( "Failed start=%d", start);
	else
	{
		LV_ITEM lvi;
		lvi.mask = LVIF_STATE;
		lvi.iItem = result;
//		lvi.iSubItem = sub;
		lvi.iSubItem = 0;
		m_WndList.GetItem( &lvi);
		lvi.state |= LVIS_FOCUSED | LVIS_SELECTED;
		lvi.stateMask |= LVIS_FOCUSED | LVIS_SELECTED;
		m_WndList.SetItem( &lvi);
		m_WndList.EnsureVisible( i, false);
		status.Format( "Success !! (i=%d) start=%d", i, start);
	}
	SetDlgItemText( IDC_STATUS, status);

/*
	CString sWin, sClass, sFoundWin, sFoundClass;
	HTREEITEM result = NULL, partial = NULL;

	GetDlgItemText( IDC_SEARCH_WINDOW, sWin);
	GetDlgItemText( IDC_SEARCH_CLASS, sClass);

	UINT nItem = m_WndTree.GetCount();
	HTREEITEM i;

	HTREEITEM start = m_WndTree.GetNextItem( TVI_ROOT, TVGN_CARET);
	if (start == NULL)
		start = TVI_ROOT;
	else
	{
		start = m_WndTree.GetNextItem( start, TVGN_NEXT);
	}
	for (i = start; i != NULL; i = m_WndTree.GetNextItem( i, TVGN_NEXT))
	{
		int ok1 = 0, ok2 = 0;

		if (sWin != "")
		{
			sFoundWin = m_WndTree.GetItemText( i);
			if (sFoundWin.Find( sWin) >= 0)
				ok1 = 1;
		}
		if (sClass != "")
		{
			sFoundClass = m_WndTree.GetItemText( i);
			if (sFoundClass.Find( sClass) >= 0)
				ok2 = 1;
		}
		if (ok1 || !ok1 && ok2)
		{
			result = i;
			break;
		}
		if ((partial < 0) && (ok1 || ok2))
			partial = i;
	}
	if ((start != NULL) && (result != NULL))
	{
		for (i = TVI_ROOT; i != start; i = m_WndTree.GetNextItem( i, TVGN_NEXT))
		{
			int ok1 = 0, ok2 = 0;

			if (sWin != "")
			{
				sFoundWin = m_WndTree.GetItemText( i);
				if (sFoundWin.Find( sWin) >= 0)
					ok1 = 1;
			}
			if (sClass != "")
			{
				sFoundClass = m_WndTree.GetItemText( i);
				if (sFoundClass.Find( sClass) >= 0)
					ok2 = 1;
			}
			if (ok1 || !ok1 && ok2)
			{
				result = i;
				break;
			}
			if ((partial < 0) && (ok1 || ok2))
				partial = i;
		}
	}

	if (result == NULL)
		if (partial != NULL)
			result = partial;

	CString status;
	if (result == NULL)
		status.Format( "Failed start=%d", start);
	else
	{
		m_WndTree.SelectItem( result);
		status.Format( "Success !! (i=%d) start=%d", i, start);
	}
	SetDlgItemText( IDC_STATUS, status);
*/
}

#define BUF_SIZE 1024

#define ENUM_CMD_COUNT_CHILDS		((WORD)74)
#define ENUM_CMD_POPULATE			((WORD)66)

#define ENUM_MSK_SHOW_EMPTY_TITLES		((WORD)1)
#define ENUM_MSK_SHOW_NULL_RECTS			((WORD)2)
#define ENUM_MSK_SHOW_NON_VISIBLES		((WORD)4)
#define ENUM_MSK_FULL						((WORD)~0)
int nHwnd;
int called;
int childs;
#define MAX_HWND 256
HWND HwndTab[MAX_HWND] = {0};
int selected = -1;

#define TO_ENUM(c,m) ((DWORD)((((WORD)c) << 16) | (WORD)m))
#define ENUM_CMD(c) HIWORD(c)
#define ENUM_MSK(c) LOWORD(c)

bool IsNullRect( CRect& rect)
{
	return (rect.Width() == 0 && rect.Height() == 0);
}

BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam)
{
	BOOL result = false;
	char buf[BUF_SIZE+1] = {0};
	CRect rect;

	called++;

	if (ENUM_CMD(lParam) == ENUM_CMD_COUNT_CHILDS)
	{
		if (hwnd)
		{
			::GetWindowText( hwnd, buf, BUF_SIZE);
			buf[BUF_SIZE] = 0;
			if ((strlen(buf) != 0) || (ENUM_MSK(lParam) & ENUM_MSK_SHOW_EMPTY_TITLES))
			{
				if (::GetWindowRect( hwnd, &rect))
				{
					if (!IsNullRect( rect) || (ENUM_MSK(lParam) & ENUM_MSK_SHOW_NULL_RECTS))
					{
						LONG l = ::GetWindowLong( hwnd, GWL_STYLE);
						if (l != 0)
						{
							if ((l & WS_VISIBLE) || (ENUM_MSK(lParam) & ENUM_MSK_SHOW_NON_VISIBLES))
							{
								childs++;
							}
						}
					}
				}
			}
			result = true;
		}
	}
	else if (ENUM_CMD(lParam) == ENUM_CMD_POPULATE)
	{
		if (nHwnd < MAX_HWND)
		{
			if (hwnd)
			{
				::GetWindowText( hwnd, buf, BUF_SIZE);
				buf[BUF_SIZE] = 0;
				if ((strlen(buf) != 0) || (ENUM_MSK(lParam) & ENUM_MSK_SHOW_EMPTY_TITLES))
				{
					if (::GetWindowRect( hwnd, &rect))
					{
						if (!IsNullRect( rect) || (ENUM_MSK(lParam) & ENUM_MSK_SHOW_NULL_RECTS))
						{
							LONG l = ::GetWindowLong( hwnd, GWL_STYLE);
							if (l != 0)
							{
								if ((l & WS_VISIBLE) || (ENUM_MSK(lParam) & ENUM_MSK_SHOW_NON_VISIBLES))
								{
									HwndTab[nHwnd++] = hwnd;
								}
							}
						}
					}
				}
				result = true;
			}
		}
	}

	return result;
}
 
void CWinspyDlg::OnRefresh() 
{
	CString s;
	BOOL enable = FALSE;

	m_WndList.DeleteAllItems();

	WORD msk = 0;
	CButton * pButton = (CButton *)GetDlgItem( IDC_SHOW_EMPTY_TITLES);
	if (pButton)
		if (pButton->GetCheck())
			msk |= ENUM_MSK_SHOW_EMPTY_TITLES;
	pButton = (CButton *)GetDlgItem( IDC_SHOW_NULL_RECTS);
	if (pButton)
		if (pButton->GetCheck())
			msk |= ENUM_MSK_SHOW_NULL_RECTS;
	pButton = (CButton *)GetDlgItem( IDC_SHOW_NON_VISIBLES);
	if (pButton)
		if (pButton->GetCheck())
			msk |= ENUM_MSK_SHOW_NON_VISIBLES;

	nHwnd = 0;
	called = 0;
	if (m_parentWindow)
	{
		EnumChildWindows( m_parentWindow, EnumWindowsProc, TO_ENUM( ENUM_CMD_POPULATE, msk));
		CString title;
		CWnd * pWnd = FromHandle( m_parentWindow);
		if (pWnd)
			pWnd->GetWindowText( title);
		char buf[MAX_BUF];
		::GetClassName( pWnd->m_hWnd, buf, MAX_BUF);
		s.Format( "%08lx \"%s\" %s", m_parentWindow, title, buf);
	}
	else
	{
		s.Format( "<no parent>");
		EnumWindows( EnumWindowsProc, TO_ENUM( ENUM_CMD_POPULATE, msk));
	}
	SetDlgItemText( IDC_PARENT_STATUS, s);

	int item = 0;
	int i, newItem;
	char buf[BUF_SIZE+1] = {0};
	for (i = 0; i < nHwnd; i++)
	{
		CString label = "";

		s.Format( "%d", item);
		newItem = m_WndList.InsertItem( item, s);
		if (newItem == -1)
			break;
		m_WndList.SetItemData( newItem, (DWORD)i);

		s.Format( "%08x", HwndTab[i]);
		m_WndList.SetItemText( newItem, ColHwndSub, s);

		::GetWindowText( HwndTab[i], buf, BUF_SIZE);
		buf[BUF_SIZE] = 0;
		s.Format( "%s", buf);
		label += "\"" + s + "\"";
		m_WndList.SetItemText( newItem, ColWinSub, s);

		::GetClassName( HwndTab[i], buf, BUF_SIZE);
		buf[BUF_SIZE] = 0;
		s.Format( "%s", buf);
		label += " " + s;
		m_WndList.SetItemText( newItem, ColClassSub, s);

		item++;

/*
		//if ()
		{
			HTREEITEM item;
			item = m_WndTree.InsertItem( label);
			m_WndTree.SetItemData( item, (DWORD)i);
		}
*/
	}
	LV_ITEM lvi;
	lvi.mask = LVIF_STATE;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	m_WndList.GetItem( &lvi);
	lvi.state |= LVIS_FOCUSED | LVIS_SELECTED;
	lvi.stateMask |= LVIS_FOCUSED | LVIS_SELECTED;
	m_WndList.SetItem( &lvi);
	m_WndList.EnsureVisible( 0, false);

	enable = FALSE;
/*
	HWND parent = ::GetParent( HwndTab[i]);
	if (parent != NULL)
	{
		parent = ::GetParent( parent);
		if (parent != NULL)
		{
			m_showParentsParentWindow = parent;
			enable = TRUE;
		}
	}
*/
	enable = FALSE;
	if (m_parentWindow != NULL)
	{
		m_showParentsParentWindow = ::GetParent( m_parentWindow);
		enable = TRUE;
	}
	CWnd * pWnd = GetDlgItem( IDC_SHOW_PARENTS);
	if (pWnd)
		pWnd->EnableWindow( enable);

	pWnd = GetDlgItem( IDC_SEARCH_WINDOW);
	if (pWnd)
		pWnd->SetFocus();
}

/*
typedef struct tagNM_LISTVIEW { 
    NMHDR hdr; 
    int   iItem; 
    int   iSubItem; 
    UINT  uNewState; 
    UINT  uOldState; 
    UINT  uChanged; 
    POINT ptAction; 
    LPARAM lParam; 
} NM_LISTVIEW; 
*/

void CWinspyDlg::OnItemchangedWindowList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView)
	{
		int item = (int)(pNMListView->lParam);
		CString s;
		UINT state = m_WndList.GetItemState( item, LVIS_SELECTED | LVIS_FOCUSED);
		s.Format( "cur=%u new=%u old=%u", state, pNMListView->uNewState, pNMListView->uOldState);
		SetDlgItemText( IDC_STATUS, s);
		BOOL enable = FALSE;
		if (state && LVIS_SELECTED)
		{
			selected = item;

			Refresh( HwndTab[selected]);
			enable = TRUE;
		}

		CWnd * pWnd;
		pWnd = GetDlgItem( IDC_WS);
		if (pWnd)
			pWnd->EnableWindow( enable);
		pWnd = GetDlgItem( IDC_WS_EX);
		if (pWnd)
			pWnd->EnableWindow( enable);
		pWnd = GetDlgItem( IDC_SET_WS);
		if (pWnd)
			pWnd->EnableWindow( enable);
		pWnd = GetDlgItem( IDC_SHOW);
		if (pWnd)
			pWnd->EnableWindow( enable);
		pWnd = GetDlgItem( IDC_HIDE);
		if (pWnd)
			pWnd->EnableWindow( enable);
		pWnd = GetDlgItem( IDC_CLOSE);
		if (pWnd)
			pWnd->EnableWindow( enable);
	}

	*pResult = 0;
}

void CWinspyDlg::Refresh( HWND hwnd)
{
	CString s;

	BOOL enable = false;
	CWnd * pWnd;

	if (hwnd)
	{
		enable = TRUE;

		int width, height, x, y;
		CRect rect;
		if (!::GetWindowRect( hwnd, &rect))
			s.Format( "Can't get WindowRect");
		else
		{
			width = rect.Width();
			height = rect.Height();
			x = rect.TopLeft().x;
			y = rect.TopLeft().y;
//			if (IsNullRect( rect))
//				s.Format( "Null WindowRect");
//			else
				s.Format( "width=%d height=%d x=%d y=%d", width, height, x, y);
		}
		SetDlgItemText( IDC_WIN_INFO, s);

		int visible = 0;
		int item;
		LONG l;
		l = ::GetWindowLong( hwnd, GWL_STYLE);
		if (l != 0)
		{
			CString s;
			s.Format( "%08lx", l);
			SetDlgItemText( IDC_WS, s);
			if (l & WS_VISIBLE)
				visible = 1;

			item = 0;
			m_WsStyleList.DeleteAllItems();
			if (l & WS_BORDER)
				m_WsStyleList.InsertItem( item++, "WS_BORDER");
			if (l & WS_CAPTION)
				m_WsStyleList.InsertItem( item++, "WS_CAPTION");
			if (l & WS_CHILD)
				m_WsStyleList.InsertItem( item++, "WS_CHILD");
			if (l & WS_CHILDWINDOW)
				m_WsStyleList.InsertItem( item++, "WS_CHILDWINDOW");
			if (l & WS_CLIPCHILDREN)
				m_WsStyleList.InsertItem( item++, "WS_CLIPCHILDREN");
			if (l & WS_CLIPSIBLINGS)
				m_WsStyleList.InsertItem( item++, "WS_CLIPSIBLINGS");
			if (l & WS_DISABLED)
				m_WsStyleList.InsertItem( item++, "WS_DISABLED");
			if (l & WS_DLGFRAME)
				m_WsStyleList.InsertItem( item++, "WS_DLGFRAME");
			if (l & WS_GROUP)
				m_WsStyleList.InsertItem( item++, "WS_GROUP");
			if (l & WS_HSCROLL)
				m_WsStyleList.InsertItem( item++, "WS_HSCROLL");
			if (l & WS_ICONIC)
				m_WsStyleList.InsertItem( item++, "WS_ICONIC");
			if (l & WS_MAXIMIZE)
				m_WsStyleList.InsertItem( item++, "WS_MAXIMIZE");
			if (l & WS_MAXIMIZEBOX)
				m_WsStyleList.InsertItem( item++, "WS_MAXIMIZEBOX");
			if (l & WS_MINIMIZE)
				m_WsStyleList.InsertItem( item++, "WS_MINIMIZE");
			if (l & WS_MINIMIZEBOX)
				m_WsStyleList.InsertItem( item++, "WS_MINIMIZEBOX");
			if (l & WS_OVERLAPPED)
				m_WsStyleList.InsertItem( item++, "WS_OVERLAPPED");
			if (l & WS_OVERLAPPEDWINDOW)
				m_WsStyleList.InsertItem( item++, "WS_OVERLAPPEDWINDOW");
			if (l & WS_POPUP)
				m_WsStyleList.InsertItem( item++, "WS_POPUP");
			if (l & WS_POPUPWINDOW)
				m_WsStyleList.InsertItem( item++, "WS_POPUPWINDOW");
			if (l & WS_SIZEBOX)
				m_WsStyleList.InsertItem( item++, "WS_SIZEBOX");
			if (l & WS_SYSMENU)
				m_WsStyleList.InsertItem( item++, "WS_SYSMENU");
			if (l & WS_TABSTOP)
				m_WsStyleList.InsertItem( item++, "WS_TABSTOP");
			if (l & WS_THICKFRAME)
				m_WsStyleList.InsertItem( item++, "WS_THICKFRAME");
			if (l & WS_TILED)
				m_WsStyleList.InsertItem( item++, "WS_TILED");
			if (l & WS_TILEDWINDOW)
				m_WsStyleList.InsertItem( item++, "WS_TILEDWINDOW");
			if (l & WS_VISIBLE)
				m_WsStyleList.InsertItem( item++, "WS_VISIBLE");
			if (l & WS_VSCROLL)
				m_WsStyleList.InsertItem( item++, "WS_VSCROLL");
		}
		l = ::GetWindowLong( hwnd, GWL_EXSTYLE);
		if (l != 0)
		{
			CString s;
			s.Format( "%08lx", l);
			SetDlgItemText( IDC_WS_EX, s);

			item = 0;
			m_WsExStyleList.DeleteAllItems();
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_ACCEPTFILES");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_APPWINDOW");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_CLIENTEDGE");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_CONTEXTHELP");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_CONTROLPARENT");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_DLGMODALFRAME");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_LEFT");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_LEFTSCROLLBAR");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_LTRREADING");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_MDICHILD");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_NOPARENTNOTIFY");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_OVERLAPPEDWINDOW");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_PALETTEWINDOW");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_RIGHT");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_RIGHTSCROLLBAR");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_RTLREADING");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_STATICEDGE");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_TOOLWINDOW");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_TOPMOST");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_TRANSPARENT");
			if (l & WS_EX_TOPMOST)
				m_WsExStyleList.InsertItem( item++, "WS_EX_WINDOWEDGE");
		}

	//		s = m_WndList.GetItemText( i, ColWinSub);
//		s.Format( "i=%d", i);
//		s.Format( "%s", visible?"visible":"non visible");
		CString wintitle;
		CWnd * pWnd = FromHandle( hwnd);
		if (pWnd)
			pWnd->GetWindowText( wintitle);
		char buf[MAX_BUF];
		::GetClassName( hwnd, buf, MAX_BUF);
		s.Format( "%08lx \"%s\" %s", hwnd, wintitle, buf);
	}
	else
		s.Format( "");
	
	pWnd = GetDlgItem( IDC_WS);
	if (pWnd)
		pWnd->EnableWindow( enable);
	pWnd = GetDlgItem( IDC_WS_EX);
	if (pWnd)
		pWnd->EnableWindow( enable);
	pWnd = GetDlgItem( IDC_SET_WS);
	if (pWnd)
		pWnd->EnableWindow( enable);
	pWnd = GetDlgItem( IDC_SHOW);
	if (pWnd)
		pWnd->EnableWindow( enable);
	pWnd = GetDlgItem( IDC_HIDE);
	if (pWnd)
		pWnd->EnableWindow( enable);
	pWnd = GetDlgItem( IDC_CLOSE);
	if (pWnd)
		pWnd->EnableWindow( enable);
	pWnd = GetDlgItem( IDC_HILITE);
	if (pWnd)
		pWnd->EnableWindow( enable);

	SetDlgItemText( IDC_STATUS, s);

	WORD msk = 0;
	CButton * pButton = (CButton *)GetDlgItem( IDC_SHOW_EMPTY_TITLES);
	if (pButton)
		if (pButton->GetCheck())
			msk |= ENUM_MSK_SHOW_EMPTY_TITLES;
	pButton = (CButton *)GetDlgItem( IDC_SHOW_NULL_RECTS);
	if (pButton)
		if (pButton->GetCheck())
			msk |= ENUM_MSK_SHOW_NULL_RECTS;

	enable = FALSE;
	childs = 0;
	EnumChildWindows( hwnd, EnumWindowsProc, TO_ENUM( ENUM_CMD_COUNT_CHILDS, ENUM_MSK_FULL));
	if (childs > 0)
	{
		m_showChildsParentWindow = hwnd;
		enable = TRUE;
	}
	s.Format( "(%d childs)", m_parentWindow, childs);

	pWnd = GetDlgItem( IDC_SHOW_CHILDS);
	if (pWnd)
		pWnd->EnableWindow( enable);
}

void CWinspyDlg::OnSetWs() 
{
	// TODO: Add your control notification handler code here
	
	LONG l = 0;
#define MAX_SBUF 70
	char sbuf[MAX_SBUF+1] = {0};
	
	int i;

	i = selected;

	if (i < 0)
		return;

	CString s;
	if (GetDlgItemText( IDC_WS, sbuf, MAX_SBUF) != 0)
	{
		if (sscanf( sbuf, "%lx", &l) == 1)
		{
			if (::SetWindowLong( HwndTab[i], GWL_STYLE, l) == 0)
			{
				CWnd * pWnd = GetDlgItem(IDC_WS);
				if (pWnd)
					pWnd->EnableWindow( false);
			}
		}
	}
	if (GetDlgItemText( IDC_WS_EX, sbuf, MAX_SBUF) != 0)
	{
		if (sscanf( sbuf, "%lx", &l) == 1)
			::SetWindowLong( HwndTab[i], GWL_EXSTYLE, l);
	}
}

void CWinspyDlg::OnUpdateStatus() 
{
	// TODO: Add your control notification handler code here
	Refresh( HwndTab[selected]);
}

void CWinspyDlg::OnSetfocusSearchString() 
{
	DWORD old = GetDefID();

	if (HIWORD(old) & DC_HASDEFID)
		m_old_def = LOWORD(old);
	else
		m_old_def = 0;

	SetDefID(IDC_SEARCH);
}

void CWinspyDlg::OnShow() 
{
	int i;

	i = selected;

	if (i < 0)
		return;

	LRESULT res = ::SendMessage( HwndTab[i], WM_SHOWWINDOW, TRUE, SW_PARENTCLOSING);
	
	DWORD dw = res;
	CString s;
	s.Format( "result=%lx", dw);
	
	SetDlgItemText( IDC_STATUS, s);
}

void CWinspyDlg::OnHide() 
{
	int i;

	i = selected;

	if (i < 0)
		return;

	LRESULT res = ::SendMessage( HwndTab[i], WM_SHOWWINDOW, TRUE, SW_PARENTCLOSING);
	
	DWORD dw = res;
	CString s;
	s.Format( "result=%lx", dw);
	
	SetDlgItemText( IDC_STATUS, s);
}

void CWinspyDlg::OnKillfocusSearchWindow() 
{
	if (m_old_def != 0)
		SetDefID( m_old_def);	
}

void CWinspyDlg::OnKillfocusSearchClass() 
{
	if (m_old_def != 0)
		SetDefID( m_old_def);	
}

void CWinspyDlg::OnSetfocusSearchClass() 
{
	DWORD old = GetDefID();

	if (HIWORD(old) & DC_HASDEFID)
		m_old_def = LOWORD(old);
	else
		m_old_def = 0;

	SetDefID(IDC_SEARCH);
}

void CWinspyDlg::OnKillfocusWs() 
{
	if (m_old_def != 0)
		SetDefID( m_old_def);	
}

void CWinspyDlg::OnSetfocusWs() 
{
	DWORD old = GetDefID();

	if (HIWORD(old) & DC_HASDEFID)
		m_old_def = LOWORD(old);
	else
		m_old_def = 0;

	SetDefID(IDC_SET_WS);
}

void CWinspyDlg::OnKillfocusWsEx() 
{
	if (m_old_def != 0)
		SetDefID( m_old_def);	
}

void CWinspyDlg::OnSetfocusWsEx() 
{
	DWORD old = GetDefID();

	if (HIWORD(old) & DC_HASDEFID)
		m_old_def = LOWORD(old);
	else
		m_old_def = 0;

	SetDefID(IDC_SET_WS);
}

void CWinspyDlg::OnClose() 
{
	if ((selected >= 0) && (selected < MAX_HWND))
		::SendMessage( HwndTab[selected], WM_CLOSE, 0, 0);
}

/*
typedef struct _NM_TREEVIEW {  nmtv 
    NMHDR    hdr; 
    UINT     action; 
    TV_ITEM  itemOld; 
    TV_ITEM  itemNew; 
    POINT    ptDrag; 
} NM_TREEVIEW; 
typedef NM_TREEVIEW FAR *LPNM_TREEVIEW;
typedef struct _TV_ITEM {  tvi 
    UINT       mask; 
    HTREEITEM  hItem; 
    UINT       state; 
    UINT       stateMask; 
    LPSTR      pszText; 
    int        cchTextMax; 
    int        iImage; 
    int        iSelectedImage; 
    int        cChildren; 
    LPARAM     lParam; 
} TV_ITEM, FAR *LPTV_ITEM; 
*/

void CWinspyDlg::OnShowChilds() 
{
	m_parentWindow = m_showChildsParentWindow;
	OnRefresh();
}

void CWinspyDlg::OnShowParents() 
{
	m_parentWindow = m_showParentsParentWindow;
	OnRefresh();
}

void MySleep( int ms)
{
	int waste = 10000;
	for (;ms > 0; ms--)
	{
		Sleep( 1);
//		for (int n = 0; n < waste; n++);
	}
}

void CWinspyDlg::OnHilite() 
{
	CWnd * pWnd;

	pWnd = GetDesktopWindow();
//	pWnd = this;
	if (pWnd)
	{
		CDC * pDc;
		pDc = pWnd->GetWindowDC();
		if (pDc)
		{
			CRect rect;
			if ((selected < 0) || (selected >= MAX_HWND))
				return;
			::GetWindowRect( HwndTab[selected], &rect);
//			pWnd->GetWindowRect( &rect);
//			pWnd->ClientToScreen( rect);

//			rect.InflateRect( 1, 1);
			CBrush blackBrush, whiteBrush, redBrush, * oldBrush;

			if ((blackBrush.CreateSolidBrush( RGB(0, 0, 0)) != 0) &&
				(whiteBrush.CreateSolidBrush( RGB(255, 255, 255)) != 0) &&
				(redBrush.CreateSolidBrush( RGB(255, 0, 0)) != 0))
			{
				CString s;
				int delay = 1000;
				s.Format( "Entering blink section.. (delay=%d)", delay);
				SetDlgItemText( IDC_STATUS, s);

//				MySleep( delay);
				s.Format( "in blink section.. (delay=%d)", delay);
				SetDlgItemText( IDC_STATUS, s);

				pDc->FrameRect( &rect, &redBrush);
				oldBrush = pDc->SelectObject( &redBrush);
				if (oldBrush != NULL)
				{
					//pDc->Rectangle( &rect);
//					pDc->FillRect( &rect, &redBrush);
					pDc->SelectObject( oldBrush);
				}

/*				for (int n = 0; n < 5; n++)
				{
					s.Format( "Blink section.. (delay=%d) step=%d", delay, n);
					SetDlgItemText( IDC_STATUS, s);
					MySleep( delay);
//					pDc->FrameRect( &rect, &blackBrush);
					MySleep( delay);
//					pDc->FrameRect( &rect, &whiteBrush);
				}
*/				s.Format( "Leaved blink section. (delay=%d)", delay);
				SetDlgItemText( IDC_STATUS, s);
			}
		}
	}
}

void CWinspyDlg::OnShowEmptyTitles() 
{
	OnRefresh();
}

void CWinspyDlg::OnShowNullRects() 
{
	OnRefresh();
}

void CWinspyDlg::OnShowVisibles() 
{
	OnRefresh();
}

void CWinspyDlg::OnRepaint() 
{
	if ((selected >= 0) && (selected < MAX_HWND))
	{
//		::SendMessage( HwndTab[selected], WM_PAINT, 0, 0);
		::InvalidateRect( HwndTab[selected], NULL, TRUE);
//		CWnd * pWnd = FromHandle( HwndTab[selected]);
//		if (pWnd)
//			pWnd->OnPaint();
	}
}

void CAboutDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CWnd * pWnd = GetDlgItem( IDC_EASTER_EGG);
	if (pWnd)
	{
		CRect rect;
		pWnd->GetWindowRect( &rect);
		ScreenToClient( &rect);
		if (rect.PtInRect(point))
		{
			if (!m_eggFound)
				ShortDisp( "Ah non Krap, trop facile !! Cherche mieux !");
			else
				ShortDisp( "L'oeuf est DEJA trouvé ! Alors, heureux ?? ;-)");
		}
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CWinspyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CString s;
	CWnd * pWnd = GetDlgItem( IDC_TRACK);
	if (pWnd)
	{
		CRect rect;

		pWnd->GetWindowRect( &rect);

		LONG x1 = rect.left;
		LONG y1 = rect.top;
		LONG x2 = rect.right;
		LONG y2 = rect.bottom;

		int px, py;

		px = (x1 + x2) / 2;
		py = (y1 + y2) / 2;

		ScreenToClient( &rect);

		x1 = rect.left;
		y1 = rect.top;
		x2 = rect.right;
		y2 = rect.bottom;

		LONG x = point.x;
		LONG y = point.y;

		s.Format( "x=%ld y=%ld left=%ld top=%ld right=%ld bottom=%ld", x, y, x1, y1, x2, y2);
//		SetDlgItemText( IDC_STATUS, s);

		s.Format( "left=%ld top=%ld right=%ld bottom=%ld", x1, y1, x2, y2);
//		SetDlgItemText( IDC_TRK_RECT, s);

		if ((x >= x1) && (x <= x2) &&
			(y >= y1) && (y <= y2))
		{
			if (!m_isCapturing)
			{
				if (GetCapture() == NULL)
				{
					if (m_captureWindow)
					{
						CStatic * pWnd = (CStatic *)GetDlgItem( IDC_TRACK);
						if (pWnd)
							pWnd->SetIcon( m_trackIconDisabled);
						m_captureWindow->SetCapture();
						m_isCapturing = true;
						s.Format( "Capturing Mouse..");
						SetDlgItemText( IDC_STATUS, s);
						m_oldCursor = GetCursor();
						GetCursorPos( &m_oldCursorPos);
						SetCursorPos( px, py);
						SetCursor( m_trackCursor);
						CButton * pButton = (CButton *)GetDlgItem( IDC_HIDE_MYSELF);
						if (pButton)
							if (pButton->GetCheck())
								HideMyself( 1);
					}
				}
			}
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CWinspyDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_isCapturing)
	{
		if (GetCapture() == m_captureWindow)
		{
			if (ReleaseCapture())
			{
				m_isCapturing = 0;
				CString s;

				ClientToScreen( &point);

				CDC dc;

//				dc.DrawIcon( point, m_trackIcon);

				CStatic * pWnd = (CStatic *)GetDlgItem( IDC_TRACK);
				if (pWnd)
					pWnd->SetIcon( m_trackIconEnabled);

//				SetCursorPos( m_oldCursorPos.x, m_oldCursorPos.y);
				SetCursor( m_oldCursor);

				DropInfo( point);
				CButton * pButton = (CButton *)GetDlgItem( IDC_HIDE_MYSELF);
				if (pButton)
					if (pButton->GetCheck())
						HideMyself( 0);
			}
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CWinspyDlg::DropInfo(CPoint & point)
{
	CString s;

	CWnd * pWnd = CWnd::WindowFromPoint( point);
	if (pWnd)
	{
		s.Format( "Yep! xDrop=%ld yDrop=%ld HWND=%08lx", point.x, point.y, pWnd->m_hWnd);
		if (pWnd->m_hWnd)
		{
			Hilite( pWnd->m_hWnd);
		}
		HWND parent = ::GetParent( pWnd->m_hWnd);
		m_parentWindow = parent;
		CButton * pButton = (CButton *)GetDlgItem( IDC_SHOW_EMPTY_TITLES);
		if (pButton)
			pButton->SetCheck( 1);
		pButton = (CButton *)GetDlgItem( IDC_SHOW_NON_VISIBLES);
		if (pButton)
			pButton->SetCheck( 1);
		OnRefresh();
		CString sHwnd;
		sHwnd.Format( "%08lx", pWnd->m_hWnd);
		SetDlgItemText( IDC_SEARCH_HWND, sHwnd);
		OnSearch();
//		SetDlgItemText( IDC_SEARCH_HWND, "");
	}
	else
		s.Format( "Yop! xDrop=%ld yDrop=%ld", point.x, point.y);
//	SetDlgItemText( IDC_STATUS, s);
}

void CWinspyDlg::Hilite(HWND & hwnd)
{
	static HWND oldhwnd = 0;

	CWnd * pWnd = FromHandle( hwnd);
	if (pWnd)
	{
		CDC * pDc = pWnd->GetDC();
		if (pDc)
		{
			CRect rect;
			pWnd->GetWindowRect( &rect);
			pWnd->ScreenToClient( &rect);
			if (oldhwnd == hwnd)
			{
				if (m_nHiliteTimer)
				{
					KillTimer( m_nHiliteTimer);
					m_nHiliteTimer = 0;
				}
				pWnd->Invalidate();
			}
			else
			{
				if (!m_nHiliteTimer)
				{
					m_nHiliteTimer = SetTimer( TIMER_HILITE_ID, TIMER_HILITE_PERIOD, NULL);
				}
				COLORREF color;
				color = RGB(255, 0, 0);
				CBrush brush( color);
				pDc->FrameRect( &rect, &brush);
				rect.DeflateRect( 1, 1);
				pDc->FrameRect( &rect, &brush);
				rect.DeflateRect( 1, 1);
				pDc->FrameRect( &rect, &brush);
				oldhwnd = hwnd;
			}
		}
	}
}

void CWinspyDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString s;

	ClientToScreen( &point);
	LONG x = point.x;
	LONG y = point.y;

	if (m_isCapturing)
	{
		CWnd * pWnd = CWnd::WindowFromPoint( point);
		if (pWnd)
		{
			if (m_hOldWnd != pWnd->m_hWnd)
			{
				CString title;
				pWnd->GetWindowText( title);
				s.Format( "%s", title);
//				SetDlgItemText( IDC_WIN_TITLE, s);
				char buf[MAX_BUF];
				::GetClassName( pWnd->m_hWnd, buf, MAX_BUF);
				s.Format( "%s", buf);
//				SetDlgItemText( IDC_CLASS_NAME, s);

	//			pWnd->FlashWindow( TRUE);
				
				if (m_hOldWnd)
					Hilite( m_hOldWnd);
				Hilite( pWnd->m_hWnd);

				s.Format( "HWND=%08lx", pWnd->m_hWnd);
				SetDlgItemText( IDC_STATUS, s);

				m_hOldWnd = pWnd->m_hWnd;
				Refresh( pWnd->m_hWnd);
			}
		}
		else
			Refresh( 0);
	}

	s.Format( "x=%ld y=%ld", x, y);
//	SetDlgItemText( IDC_COORDS, s);

	CDialog::OnMouseMove(nFlags, point);
}

void CWinspyDlg::OnAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CWinspyDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

CRect oldRect;

void CWinspyDlg::HideMyself(int hide)
{
	CWnd * pWnd = GetDlgItem( IDC_TRACK);
	if (pWnd)
	{
		if (hide)
		{
			CRect rect1, rect2;
			GetWindowRect( &rect1);
			oldRect = rect1;
			pWnd->GetWindowRect( &rect2);
			SetWindowPos( NULL, rect2.TopLeft().x, rect2.TopLeft().y, rect2.Width(), rect2.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
		}
		else
		{
			SetWindowPos( NULL, oldRect.TopLeft().x, oldRect.TopLeft().y, oldRect.Width(), oldRect.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
		}
	}
}

void CAboutDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == TIMER_WIPE_ID)
	{
		if (m_nTimerWipe)
			KillTimer( m_nTimerWipe);
		SetDlgItemText( IDC_EASTER_TEXT, "");
	}

	CDialog::OnTimer(nIDEvent);
}

void CAboutDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CStatic * pWnd = (CStatic *)GetDlgItem( IDC_EASTER_EGG);
	if (pWnd)
	{
		CStatic * pWnd2 = (CStatic *)GetDlgItem( IDC_EASTER_ZONE);
		if (pWnd2)
		{
			CRect rect;
			pWnd2->GetWindowRect( &rect);
			ScreenToClient( &rect);
			if (rect.PtInRect(point))
			{
				pWnd->SetIcon( m_eggIcon);
				ShortDisp( "Héhé, bien joué.. (bon ça gave un peu à la fin ces EasterEgg :)");
				CRect rect;

				m_eggAnim.Create( WS_CHILD, rect, this, 1);
				m_eggFound = true;
			}
		}
	}
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CAboutDlg::ShortDisp(CString s)
{
	SetDlgItemText( IDC_EASTER_TEXT, s);
	if (m_nTimerWipe)
		KillTimer( m_nTimerWipe);
	m_nTimerWipe = SetTimer( TIMER_WIPE_ID, TIMER_WIPE_PERIOD, NULL);
}

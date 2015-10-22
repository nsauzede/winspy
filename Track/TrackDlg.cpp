// TrackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Track.h"
#include "TrackDlg.h"

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
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackDlg dialog

CTrackDlg::CTrackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrackDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_trackCursor = AfxGetApp()->LoadCursor( IDC_TRACK);
	m_trackIconDisabled = AfxGetApp()->LoadIcon( IDI_TRACK_ZONE2);
	m_trackIconEnabled = AfxGetApp()->LoadIcon( IDI_TRACK_ZONE1);
}

void CTrackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrackDlg, CDialog)
	//{{AFX_MSG_MAP(CTrackDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackDlg message handlers

BOOL CTrackDlg::OnInitDialog()
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
	m_isCapturing = false;
	m_captureWindow = this;
	m_hOldWnd = 0;
	SetDlgItemText( IDC_STATUS, "Feeling groovy.");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrackDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTrackDlg::OnPaint() 
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
HCURSOR CTrackDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTrackDlg::OnLButtonUp(UINT nFlags, CPoint point) 
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
			}
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CTrackDlg::Refresh()
{
	CString s;

	s.Format( "%s", (m_isCapturing)?"capturing":"not capturing");
	SetDlgItemText( IDC_STATUS, s);
}

void CTrackDlg::OnLButtonDown(UINT nFlags, CPoint point) 
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
		SetDlgItemText( IDC_TRK_RECT, s);

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
					}
				}
			}
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CTrackDlg::OnMouseMove(UINT nFlags, CPoint point) 
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
				SetDlgItemText( IDC_WIN_TITLE, s);
#define MAX_BUF 1024
				char buf[MAX_BUF];
				::GetClassName( pWnd->m_hWnd, buf, MAX_BUF);
				s.Format( "%s", buf);
				SetDlgItemText( IDC_CLASS_NAME, s);

	//			pWnd->FlashWindow( TRUE);
				
				if (m_hOldWnd)
					Hilite( m_hOldWnd);
				Hilite( pWnd->m_hWnd);

				s.Format( "HWND=%08lx", pWnd->m_hWnd);
				SetDlgItemText( IDC_STATUS, s);

				m_hOldWnd = pWnd->m_hWnd;
			}
		}
		else
			Refresh();
	}

	s.Format( "x=%ld y=%ld", x, y);
	SetDlgItemText( IDC_COORDS, s);

	CDialog::OnMouseMove(nFlags, point);
}

void CTrackDlg::DropInfo(CPoint & point)
{
	CString s;

	CWnd * pWnd = CWnd::WindowFromPoint( point);
	if (pWnd)
	{
		s.Format( "Yep! xDrop=%ld yDrop=%ld HWND=%08lx", point.x, point.y, pWnd->m_hWnd);
		if (pWnd->m_hWnd)
			Hilite( pWnd->m_hWnd);
	}
	else
		s.Format( "Yop! xDrop=%ld yDrop=%ld", point.x, point.y);
	SetDlgItemText( IDC_STATUS, s);
}

void CTrackDlg::Hilite(HWND& hwnd)
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
			COLORREF color;
			if (oldhwnd == hwnd)
			{
				color = RGB(0, 0, 255);
				pWnd->Invalidate();
			}
			else
			{
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

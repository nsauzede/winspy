// GlowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Glow.h"
#include "GlowDlg.h"

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
// CGlowDlg dialog

CGlowDlg::CGlowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGlowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGlowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGlowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGlowDlg, CDialog)
	//{{AFX_MSG_MAP(CGlowDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlowDlg message handlers

BOOL CGlowDlg::OnInitDialog()
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
	CButton * pButton = (CButton *)GetDlgItem( IDC_ALLOW_GLOW);
	if (pButton)
		pButton->SetCheck( 1);

	m_nGlowStep = 0;
	m_nGlowTimer = SetTimer( TIMER_GLOW_ID, TIMER_GLOW_PERIOD, NULL);	// NULL => timer events must be handled in WM_TIMER's handler

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGlowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGlowDlg::OnPaint() 
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

//		CPaintDC dc(this); // device context for painting
		CDC * pDc = GetWindowDC();
		if (pDc)
		{
			CDC& dc = *pDc;
			CRect rect;

			//GetClientRect( &rect);
			//ClientToScreen( &rect);

			GetWindowRect( &rect);
			ScreenToClient( &rect);
	/*
			CPoint point = rect.CenterPoint();

			rect.SetRect( 0, 0, 50, 50);

			rect.OffsetRect( point - rect.CenterPoint());
	*/
	#define LEN 3
	#define USR_STYLE_LEN1 2
	#define USR_STYLE_LEN2 3
			DWORD UsrStyle1[USR_STYLE_LEN1] = { LEN, LEN };
			DWORD UsrStyle2[USR_STYLE_LEN2] = { 0, LEN, LEN };
			int UsrStyleLen;
			DWORD * UsrStyle;

			if (1)
			{
				UsrStyleLen = USR_STYLE_LEN1;
				UsrStyle = UsrStyle1;
			}
			else
			{
				UsrStyleLen = USR_STYLE_LEN2;
				UsrStyle = UsrStyle2;
			}
	//		COLORREF color = ((m_nGlowStep % 1)?RGB(255,0,0):RGB(0,0,255));
			COLORREF color;
			
			if ((m_nGlowStep & 1) )
				color = RGB(255,0,0);
			else
				color = RGB(0,0,255);
	#define PEN_WIDTH 1
			LOGBRUSH logbrush;
			CBrush brush( color);
			CBrush * pBrush = dc.SelectObject( &brush);
			brush.GetLogBrush( &logbrush);
	//		CPen pen( PS_USERSTYLE, PEN_WIDTH, &logbrush, UsrStyleLen, UsrStyle);
			CPen pen( PS_SOLID, PEN_WIDTH, color);
			CPen * pPen = dc.SelectObject( &pen);
			if (pPen)
			{
				dc.Rectangle( &rect);
				dc.SelectObject( pPen);
			}
				if (pBrush)
					dc.SelectObject( pBrush);
			ReleaseDC( pDc);
		}
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGlowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGlowDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TIMER_GLOW_ID)
	{
		CButton * pButton = (CButton *)GetDlgItem( IDC_ALLOW_GLOW);
		if (pButton)
		{
			if (pButton->GetCheck())
			{
				Invalidate( FALSE);
				CString s;
				s.Format( "Glow step : %d", m_nGlowStep);
				SetDlgItemText( IDC_STATUS, s);
				m_nGlowStep++;
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}

UINT CGlowDlg::OnNcHitTest( CPoint point)
{
	UINT def = CDialog::OnNcHitTest(point);
	return (def==HTCLIENT) ? HTCAPTION:def;
}
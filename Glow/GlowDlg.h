// GlowDlg.h : header file
//

#if !defined(AFX_GLOWDLG_H__A4D782C6_D4C8_11D4_8270_00C0F057D251__INCLUDED_)
#define AFX_GLOWDLG_H__A4D782C6_D4C8_11D4_8270_00C0F057D251__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CGlowDlg dialog

class CGlowDlg : public CDialog
{
// Construction
public:
	int m_nGlowStep;
	CGlowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGlowDlg)
	enum { IDD = IDD_GLOW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum { TIMER_GLOW_ID=1, TIMER_GLOW_PERIOD=1000 } TimerConsts;
	UINT m_nGlowTimer;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGlowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg UINT OnNcHitTest( CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOWDLG_H__A4D782C6_D4C8_11D4_8270_00C0F057D251__INCLUDED_)

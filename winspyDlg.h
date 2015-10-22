// winspyDlg.h : header file
//

#if !defined(AFX_WINSPYDLG_H__8D8BA567_CF62_11D4_8268_00C0F057D251__INCLUDED_)
#define AFX_WINSPYDLG_H__8D8BA567_CF62_11D4_8268_00C0F057D251__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CWinspyDlg dialog

class CWinspyDlg : public CDialog
{
// Construction
public:
	void HideMyself( int hide);
	UINT m_nHiliteTimer;
	enum {	MAX_BUF = 1024,
				TIMER_HILITE_ID = 1, TIMER_HILITE_PERIOD = 200,
	};
	void Hilite(HWND& hwnd);
	void DropInfo(CPoint & point);
	HWND m_parentWindow;
	HWND m_showChildsParentWindow;
	HWND m_showParentsParentWindow;
	UINT m_old_def;
	int ColHwndSub;
	int ColWinSub;
	int ColClassSub;
	void Refresh( HWND hwnd);
	CWnd * m_captureWindow;
	bool m_isCapturing;
	HWND m_hOldWnd;
	HCURSOR m_trackCursor;
	HCURSOR m_oldCursor;
	HICON m_trackIconDisabled;
	HICON m_trackIconEnabled;
	POINT m_oldCursorPos;
	CWinspyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinspyDlg)
	enum { IDD = IDD_WINSPY_DIALOG };
	CListCtrl	m_WsExStyleList;
	CListCtrl	m_WsStyleList;
	CListCtrl	m_WndList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinspyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinspyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSearch();
	afx_msg void OnRefresh();
	afx_msg void OnItemchangedWindowList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetWs();
	afx_msg void OnUpdateStatus();
	afx_msg void OnSetfocusSearchString();
	afx_msg void OnShow();
	afx_msg void OnHide();
	afx_msg void OnKillfocusSearchWindow();
	afx_msg void OnKillfocusSearchClass();
	afx_msg void OnSetfocusSearchClass();
	afx_msg void OnKillfocusWs();
	afx_msg void OnSetfocusWs();
	afx_msg void OnKillfocusWsEx();
	afx_msg void OnSetfocusWsEx();
	afx_msg void OnClose();
	afx_msg void OnShowChilds();
	afx_msg void OnShowParents();
	afx_msg void OnHilite();
	afx_msg void OnShowEmptyTitles();
	afx_msg void OnShowNullRects();
	afx_msg void OnShowVisibles();
	afx_msg void OnRepaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnAbout();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSPYDLG_H__8D8BA567_CF62_11D4_8268_00C0F057D251__INCLUDED_)

#if !defined(AFX_NSWAPDIALOG_H__43028A21_2535_11D2_85D3_444553540000__INCLUDED_)
#define AFX_NSWAPDIALOG_H__43028A21_2535_11D2_85D3_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NSwapDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNSwapDialog dialog

class CNSwapDialog : public CDialog
{
// Construction
public:
	CNSwapDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNSwapDialog)
	enum { IDD = IDD_N_SWAP_DIALOG };
	int		m_swap_number;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNSwapDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNSwapDialog)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NSWAPDIALOG_H__43028A21_2535_11D2_85D3_444553540000__INCLUDED_)

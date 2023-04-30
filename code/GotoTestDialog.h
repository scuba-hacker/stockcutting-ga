#if !defined(AFX_GOTOTESTDIALOG_H__F7C6ED41_0B89_11D2_85D3_444553540000__INCLUDED_)
#define AFX_GOTOTESTDIALOG_H__F7C6ED41_0B89_11D2_85D3_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GotoTestDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGotoTestDialog dialog

class CGotoTestDialog : public CDialog
{
// Construction
public:
	CGotoTestDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGotoTestDialog)
	enum { IDD = IDD_GOTO_TEST_DIALOG };
	int		m_test_number;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGotoTestDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGotoTestDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTOTESTDIALOG_H__F7C6ED41_0B89_11D2_85D3_444553540000__INCLUDED_)

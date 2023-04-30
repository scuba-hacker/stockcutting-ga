#if !defined(AFX_BATCHDIALOG_H__D717EBA4_475F_11D2_85D3_ECC902C10000__INCLUDED_)
#define AFX_BATCHDIALOG_H__D717EBA4_475F_11D2_85D3_ECC902C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BatchDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBatchDialog dialog

class CBatchDialog : public CDialog
{
// Construction
public:
	CBatchDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBatchDialog)
	enum { IDD = IDD_BATCH_SETTINGS };
	UINT	m_experiment_count;
	UINT	m_layout_count;
	CString	m_prefix;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatchDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBatchDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHDIALOG_H__D717EBA4_475F_11D2_85D3_ECC902C10000__INCLUDED_)

#if !defined(AFX_ORDERDIALOG_H__C9419B21_110E_11D2_85D3_444553540000__INCLUDED_)
#define AFX_ORDERDIALOG_H__C9419B21_110E_11D2_85D3_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OrderDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrderDialog dialog
#include <strstream>
#include "define_vars.h"

class COrderDialog : public CDialog
{
// Construction
public:
	COrderDialog(CWnd* pParent = NULL);   // standard constructor
	sequence_size chromosome_length;

// Dialog Data
	//{{AFX_DATA(COrderDialog)
	enum { IDD = IDD_ORDER_DIALOG };
	CString	m_gene_order;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrderDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDERDIALOG_H__C9419B21_110E_11D2_85D3_444553540000__INCLUDED_)

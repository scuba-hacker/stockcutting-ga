#if !defined(AFX_SETREGIMEDIALOG_H__D4FAE6C4_3D95_11D2_85D3_ECC902C10000__INCLUDED_)
#define AFX_SETREGIMEDIALOG_H__D4FAE6C4_3D95_11D2_85D3_ECC902C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SetRegimeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetRegimeDialog dialog

class CSetRegimeDialog : public CDialog
{
// Construction
public:
	CSetRegimeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetRegimeDialog)
	enum { IDD = IDD_SET_REGIME_DIALOG };
	int		m_regime_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRegimeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetRegimeDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETREGIMEDIALOG_H__D4FAE6C4_3D95_11D2_85D3_ECC902C10000__INCLUDED_)

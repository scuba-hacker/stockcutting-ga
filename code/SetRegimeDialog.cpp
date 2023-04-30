// SetRegimeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GA.h"
#include "SetRegimeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetRegimeDialog dialog


CSetRegimeDialog::CSetRegimeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetRegimeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRegimeDialog)
	m_regime_radio = -1;
	//}}AFX_DATA_INIT
}


void CSetRegimeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRegimeDialog)
	DDX_Radio(pDX, IDC_LEFTMOST, m_regime_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetRegimeDialog, CDialog)
	//{{AFX_MSG_MAP(CSetRegimeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetRegimeDialog message handlers

BOOL CSetRegimeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

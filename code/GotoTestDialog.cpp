// GotoTestDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GA.h"
#include "GotoTestDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoTestDialog dialog


CGotoTestDialog::CGotoTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoTestDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoTestDialog)
	m_test_number = 0;
	//}}AFX_DATA_INIT
}


void CGotoTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoTestDialog)
	DDX_Text(pDX, IDC_TEST_NUMBER, m_test_number);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoTestDialog, CDialog)
	//{{AFX_MSG_MAP(CGotoTestDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoTestDialog message handlers

void CGotoTestDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CGotoTestDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

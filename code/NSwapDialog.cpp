// NSwapDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GA.h"
#include "NSwapDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNSwapDialog dialog


CNSwapDialog::CNSwapDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNSwapDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNSwapDialog)
	m_swap_number = 0;
	//}}AFX_DATA_INIT
}


void CNSwapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNSwapDialog)
	DDX_Text(pDX, IDC_SWAP_NUMBER, m_swap_number);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNSwapDialog, CDialog)
	//{{AFX_MSG_MAP(CNSwapDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNSwapDialog message handlers

void CNSwapDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CNSwapDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

// OrderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GA.h"
#include "OrderDialog.h"
#include "define_vars.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrderDialog dialog


COrderDialog::COrderDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COrderDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COrderDialog)
	m_gene_order = _T("");
	//}}AFX_DATA_INIT
}


void COrderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrderDialog)
	DDX_Text(pDX, IDC_GENE_ORDER, m_gene_order);
	DDV_MaxChars(pDX, m_gene_order, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrderDialog, CDialog)
	//{{AFX_MSG_MAP(COrderDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// COrderDialog message handlers

void COrderDialog::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();

}


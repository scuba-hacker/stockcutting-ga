// BatchDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GA.h"
#include "BatchDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatchDialog dialog


CBatchDialog::CBatchDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBatchDialog)
	m_experiment_count = 0;
	m_layout_count = 0;
	m_prefix = _T("");
	//}}AFX_DATA_INIT
}


void CBatchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatchDialog)
	DDX_Text(pDX, IDC_EXPERIMENT_COUNT, m_experiment_count);
	DDX_Text(pDX, IDC_LAYOUT_COUNT, m_layout_count);
	DDX_Text(pDX, IDC_PREFIX, m_prefix);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBatchDialog, CDialog)
	//{{AFX_MSG_MAP(CBatchDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatchDialog message handlers

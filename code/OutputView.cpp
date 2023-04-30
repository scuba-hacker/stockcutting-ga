// OutputView.cpp : implementation file
//

#include "stdafx.h"
#include "GA.h"
#include "OutputView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OutputView

IMPLEMENT_DYNCREATE(OutputView, CScrollView)

OutputView::OutputView()
{
}

OutputView::~OutputView()
{
}


BEGIN_MESSAGE_MAP(OutputView, CScrollView)
	//{{AFX_MSG_MAP(OutputView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OutputView drawing

void OutputView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void OutputView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	//char sheet_text[1000];
	//sprintf (sheet_text, "%d",rand());
	pDC->TextOut(10,10,"Text Output Window");

}

/////////////////////////////////////////////////////////////////////////////
// OutputView diagnostics

#ifdef _DEBUG
void OutputView::AssertValid() const
{
	CScrollView::AssertValid();
}

void OutputView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// OutputView message handlers

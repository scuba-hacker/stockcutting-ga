// GAView.cpp : implementation of the CGAView class
//

#include "stdafx.h"
#include "GA.h"

#include "GADoc.h"
#include "GAView.h"
#include "string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGAView

IMPLEMENT_DYNCREATE(CGAView, CScrollView)

BEGIN_MESSAGE_MAP(CGAView, CScrollView)
	//{{AFX_MSG_MAP(CGAView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGAView construction/destruction

CGAView::CGAView()
{
	// TODO: add construction code here

}

CGAView::~CGAView()
{
}

BOOL CGAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGAView drawing

void CGAView::OnDraw(CDC* pDC)
{
	CGADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CPen* oldPen=pDC->GetCurrentPen();
	CFont* oldFont=pDC->GetCurrentFont();
	CBrush* oldBrush=pDC->GetCurrentBrush();

	LDA_e* test_bed=&pDoc->test_bed;

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(1,1);

	int pen1, pen2, pen3, pen4, font1, brush1;
	int viewport_x=10;
	int viewport_y=10;

	CPen medium_pen, light_pen, thick_pen, dark_pen;
	if (pDC->IsPrinting())
	{
		pDC->SetViewportExt(30,30);

		pen1=medium_pen.CreatePen (PS_SOLID,0,RGB(50,50,50));
		pen2=light_pen.CreatePen (PS_SOLID,0,RGB(50,50,50));
		pDC->SetWindowOrg(-7,-10);
	}
	else
	{
		pDC->SetViewportExt(viewport_x,viewport_y);
		pen1=medium_pen.CreatePen (PS_SOLID,0,RGB(150,150,150));
		pen2=light_pen.CreatePen (PS_SOLID,0,RGB(200,200,200));
		pDC->SetWindowOrg(-1,-1);
	}
	


	pen3=thick_pen.CreatePen (PS_SOLID,0,RGB(0,0,255));
	pen4=dark_pen.CreatePen (PS_SOLID,0,RGB(50,50,50));


	unsigned int rows=test_bed->get_y_size();
	unsigned int cols=test_bed->get_x_size();

	SIZE Size = {(cols+16)*viewport_x, (rows+10)*viewport_y};
	SetScrollSizes (MM_TEXT, Size);

	for (unsigned int i=0; i<=rows; i++)
	{
		if (i % 10==0)
			pDC->SelectObject(&dark_pen);
		else
			if (i % 5==0)
				pDC->SelectObject(&medium_pen);
			else
				pDC->SelectObject(&light_pen);
			
		
		pDC->MoveTo(0,i);
		pDC->LineTo(cols,i);
	}

	for (i=0; i<=cols; i++)
	{
		if (i % 10==0)
			pDC->SelectObject(&dark_pen);
		else
			if (i % 5==0)
				pDC->SelectObject(&medium_pen);
			else
				pDC->SelectObject(&light_pen);

		pDC->MoveTo(i,0);
		pDC->LineTo(i,rows);
	}
	// TODO: add draw code for native data here

	CFont shape_label;
	font1=shape_label.CreatePointFont(9,"Terminal");
	pDC->SelectObject(&shape_label);
	char sheet_text[100];
	char rule_string[100];
	switch (test_bed->get_rule_regime())
	{
		case LEFTMOST:
			strcpy(rule_string,"Leftmost");
			break;	
		case ILEFTMOST:
			strcpy(rule_string,"Inner-Leftmost");
			break;	
		case TOPMOST:
			strcpy(rule_string,"Topmost");
			break;	
		case ITOPMOST:
			strcpy(rule_string,"Inner-Topmost");
			break;	
		case FLIP_LEFT:
			strcpy(rule_string,"Flip left/top, left starts");
			break;
		case FLIP_TOP:
			strcpy(rule_string,"Flip top/left, top starts");
			break;
		case DYNAMIC:
			strcpy(rule_string,"GA Dynamic");		
			break;

		default:
			strcpy(rule_string,"Invalid setting");
			break;			
	}
	sprintf (sheet_text, "Total Sheet Area = %d x %d", cols,rows);
	pDC->TextOut(0,rows+4,sheet_text);
	
	sprintf (sheet_text, "Placement Regime is %s", rule_string);
	pDC->TextOut(0,rows+5,sheet_text);

	sprintf (sheet_text, "Displaying test %d of %d",
						pDoc->tests.current+1, pDoc->tests.length);
	pDC->TextOut(0,rows+6,sheet_text);

	sprintf (sheet_text, "%s) %s",pDoc->tests.get_current().id,pDoc->tests.get_current().description);
	pDC->TextOut(0,rows+7,sheet_text);

	char edge_string[1000]="\0";
	strstream output_edges(edge_string,1000,ios::ate);
	output_edges << pDoc->test_bed;
	output_edges << "\nSheet " << pDoc->current_sheet+1 << " of " << pDoc->test_bed._ftable->sheet_count;
	CRect edge_text(pDoc->test_bed.get_x_size()+2,1,pDoc->test_bed.get_x_size()+12,50);
	pDC->DrawText(edge_string,-1,edge_text,DT_LEFT | DT_WORDBREAK | DT_NOCLIP);


	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&thick_pen);
	CBrush shape_brush;
	brush1=shape_brush.CreateSolidBrush(RGB(50,255,200));
	pDC->SelectObject(shape_brush);

	// set gene_offset to point to first gene to be displayed
	array_index gene_start_offset=0;
	array_index search_sheet=pDoc->current_sheet;
	do
	{
		while (test_bed->layout[gene_start_offset].new_sheet_needed==s_NO)
			gene_start_offset++;

		if (search_sheet--==0)
			break;
		else
			gene_start_offset++;
	}
	while (true);

	if (pDoc->current_sheet>0)
	{
		cout << "!";
	}

	array_index gene_end_offset=gene_start_offset+1;
	while (test_bed->layout[gene_end_offset].new_sheet_needed==s_NO &&
					gene_end_offset<LDA_c::LDA_length)
		gene_end_offset++;

	char placement_heuristic;
	bool flipping=false;
	switch (test_bed->get_rule_regime())
	{
		case LEFTMOST:
			placement_heuristic='L';
			break;

		case ILEFTMOST:
			placement_heuristic='l';
			break;

		case FLIP_LEFT:
			if (gene_start_offset%2 == 0)
				placement_heuristic='L';
			else
				placement_heuristic='T';
			flipping=true;
			break;

		case TOPMOST:
			placement_heuristic='T';
			break;

		case ITOPMOST:
			placement_heuristic='t';
			break;

		case FLIP_TOP:
			if (gene_start_offset%2 == 0)
				placement_heuristic='T';
			else
				placement_heuristic='L';
			flipping=true;
			break;

		case DYNAMIC:
			break;

		default:
			break;
	}
	char angle_string[10];

	for (i=gene_start_offset; i<gene_end_offset; i++)
	{
		shape_g_l *s=&test_bed->layout[i].piece;

		CRect text_box(s->left(),s->top(), s->right(), s->bot());
		pDC->Rectangle(text_box);

		char output[100];


		if (test_bed->get_rule_regime()==DYNAMIC)
		{
			switch (s->get_heuristic())
			{
				case LEFTMOST:
					placement_heuristic='L';
					break;
				case ILEFTMOST:
					placement_heuristic='l';
					break;
				case TOPMOST:
					placement_heuristic='T';
					break;
				case ITOPMOST:
					placement_heuristic='t';
					break;
				default:
					placement_heuristic='X';
					break;
			}
		}

		str_out_angle(angle_string, s->get_orientation());

		sprintf (output, "%d) %d,%d %dx%d %s %c",i,s->left(),s->top(),s->width(),s->height(),
			angle_string, placement_heuristic);

		CRect smaller_box=text_box;
		smaller_box.DeflateRect(1,1);
		pDC->DrawText(output,-1,smaller_box,DT_LEFT | DT_WORDBREAK | DT_NOCLIP);

		if (flipping)
		{
			if (placement_heuristic=='L')
				placement_heuristic='T';
			else
				placement_heuristic='L';
		}
	}
	pDC->SetBkMode(OPAQUE);

	if (pen1==0 || pen2==0 || pen3==0 || pen4==0 || font1==0 || brush1==0)
	{
		#ifdef _DEBUG
		afxDump << "LOW ON RESOURCES!!\n";
			#endif
	}

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldBrush);

}

/////////////////////////////////////////////////////////////////////////////
// CGAView printing

BOOL CGAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGAView diagnostics

#ifdef _DEBUG
void CGAView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGAView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGADoc* CGAView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGADoc)));
	return (CGADoc*)m_pDocument;
}
#endif //_DEBUG


void CGAView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();

	CGADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// TODO: Add your specialized code here and/or call the base class
	SIZE Size = {100, 100};
	SetScrollSizes (MM_TEXT, Size);


	// Note this line sends a command to refresh the screen when the app first loads
	// Prevents OnDraw from trying to display before refresh has been called once.
	// ie loads in all data before OnDraw displays anything
	SendMessage(WM_COMMAND, ID_VIEW_REFRESH, 0);
	SendMessage(WM_COMMAND, ID_VIEW_GOTO_TEST, 0);
}

#if !defined(AFX_OUTPUTVIEW_H__E4F0F644_45C0_11D2_85D3_ECC902C10000__INCLUDED_)
#define AFX_OUTPUTVIEW_H__E4F0F644_45C0_11D2_85D3_ECC902C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutputView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OutputView view

class OutputView : public CScrollView
{
protected:
	OutputView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(OutputView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OutputView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~OutputView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(OutputView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTVIEW_H__E4F0F644_45C0_11D2_85D3_ECC902C10000__INCLUDED_)

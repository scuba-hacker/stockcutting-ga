// GAView.h : interface of the CGAView class
//
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <strstrea.h>
#include "gene.h"

#if !defined(AFX_GAVIEW_H__2C73104D_03E8_11D2_85D3_444553540000__INCLUDED_)
#define AFX_GAVIEW_H__2C73104D_03E8_11D2_85D3_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGAView : public CScrollView
{
protected: // create from serialization only
	CGAView();
	DECLARE_DYNCREATE(CGAView)

// Attributes
public:
	CGADoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGAView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGAView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GAView.cpp
inline CGADoc* CGAView::GetDocument()
   { return (CGADoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAVIEW_H__2C73104D_03E8_11D2_85D3_444553540000__INCLUDED_)

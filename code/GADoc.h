// GADoc.h : interface of the CGADoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GADOC_H__2C73104B_03E8_11D2_85D3_444553540000__INCLUDED_)
#define AFX_GADOC_H__2C73104B_03E8_11D2_85D3_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "gene.h"
#include "GA_parts.h"
#include "GASettingsDialog.h"

class CGADoc : public CDocument
{
protected: // create from serialization only
	CGADoc();
	DECLARE_DYNCREATE(CGADoc)

// Attributes
public:
	test_set_group tests;
	LDA_new test_bed;
//	CMemoryState msOld, msNew, msDif;
	LDA_c *latest;
	char _permutation[10000];
	array_index current_sheet;
	CGASettingsDialog GAsettings;

	CArray<CString, CString&> output_text;
//	void GAThread();


private:
	void Update(update_t choice, array_index* gene_order=NULL);
	void LayoutUpdateView();
	void OutputUpdateView();
	void RunGA();
	int m_detailed_output;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGADoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGADoc)
	afx_msg void OnViewRefresh();
	afx_msg void OnViewNexttest();
	afx_msg void OnViewPrevtest();
	afx_msg void OnViewNext10test();
	afx_msg void OnViewPrev10test();
	afx_msg void OnViewGotoTest();
	afx_msg void OnViewMemorytest();
	afx_msg void OnViewDiagnose();
	afx_msg void OnViewSetcheckpoint();
	afx_msg void OnViewSetCheck1();
	afx_msg void OnViewSetCheck2();
	afx_msg void OnViewShuffle();
	afx_msg void OnViewNormalise();
	afx_msg void OnViewOrder();
	afx_msg void OnOperatorsOrder();
	afx_msg void OnOperatorsInvert();
	afx_msg void OnOperatorsPosition();
	afx_msg void OnOperatorsShunt();
	afx_msg void OnOperatorsSwap();
	afx_msg void OnViewNextSheet();
	afx_msg void OnViewPrevSheet();
	afx_msg void OnOperatorsHuxp();
	afx_msg void OnOperatorsNswap();
	afx_msg void OnGaSettings();
	afx_msg void OnSetRegime();
	afx_msg void OnRunGa();
	afx_msg void OnExportCurrent();
	afx_msg void OnBatchProcess();
	afx_msg void OnDetailedOutput();
	afx_msg void OnUpdateDetailedOutput(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GADOC_H__2C73104B_03E8_11D2_85D3_444553540000__INCLUDED_)

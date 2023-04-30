#if !defined(AFX_GASETTINGSDIALOG_H__F7DE24E2_3A93_11D2_85D3_ECC902C10000__INCLUDED_)
#define AFX_GASETTINGSDIALOG_H__F7DE24E2_3A93_11D2_85D3_ECC902C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GASettingsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGASettingsDialog dialog

#include <afxtempl.h>

class CGASettingsDialog;

class DialogSettings : public CObject
{
	public:
		BOOL	_half_uniform;
		BOOL	_heuristic_flip;
		BOOL	_heuristic_n_point;
		BOOL	_inversion;
		BOOL	_multi_swap;
		BOOL	_orientation_flip;
		BOOL	_orientation_n_point;
		BOOL	_position;
		BOOL	_shunt;
		BOOL	_single_swap;
		CString	_removal_selection;
		CString	_operator_adaptor;
		double	_mutation_rate;
		CString	_generation_model;
		CString	_breed_selection;
		double	_similarities_index;
		BOOL	_order;
		BOOL	_cataclysms_active;
		UINT	_cataclysm_trigger;
		UINT	_generation_epoch;
		CString	_population_size;
		CString	_report_every;
		double	_cooling_ratio;
		double	_end_temp;
		double	_neighbourhood;
		UINT	_restart_threshold;
		double	_start_temp;
		BOOL	_edge_recombination;
		BOOL	_seg_position_based;
		BOOL	_seg_order_based;
		UINT	_max_segment_length;
		UINT	_min_segment_length;
		UINT	_multi_swap_size;
		UINT	_n_point_size;
		BOOL	_segment_restrictions;
		UINT	_tournament_size;
		UINT	_flip_size;
		long	_cobra_iterations;

	public:
		CString _name;
		DialogSettings()
		{
			_name="";
		}
		void read_settings_from(const CGASettingsDialog &s);
		void write_settings_to(CGASettingsDialog &s) const;

		DialogSettings& operator=(const DialogSettings &s);
		
		virtual void Serialize(CArchive& ar);

		DECLARE_SERIAL(DialogSettings);
};


class CGASettingsDialog : public CDialog
{
// Construction
public:
	CGASettingsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGASettingsDialog)
	enum { IDD = IDD_GA_SETTINGS };
	CComboBox	m_population_size_control;
	CComboBox	m_setting_control;
	CButton	m_heuristic_flip_control;
	CButton	m_orientation_flip_control;
	CComboBox	m_operator_adaptor_control;
	CEdit	m_flip_size_control;
	CEdit	m_cobra_iterations_control;
	CButton	m_cataclysmic_mutation;
	CButton	m_position_control;
	CButton	m_order_control;
	CButton	m_half_uniform_control;
	CButton	m_edge_recombination_control;
	CButton	m_crossover_operators;
	CComboBox	m_removal_selection_control;
	CEdit	m_cooling_ratio_control;
	CEdit	m_end_temp_control;
	CEdit	m_start_temp_control;
	CEdit	m_restart_threshold_control;
	CEdit	m_neighbourhood_control;
	CButton	m_segment_settings;
	CButton	m_simulated_annealing_settings;
	CButton	m_hill_climbing_settings;
	CComboBox	m_generation_model_control;
	CButton	m_heuristic_n_point_control;
	CButton	m_orientation_n_point_control;
	CEdit	m_n_point_size_control;
	CEdit	m_multi_swap_size_control;
	CButton	m_multi_swap_control;
	CComboBox	m_breed_selection_control;
	CEdit	m_tournament_size_control;
	CButton	m_seg_position_based_control;
	CButton	m_seg_order_based_control;
	CEdit	m_max_segment_length_control;
	CEdit	m_min_segment_length_control;
	CButton	m_segment_restrictions_control;
	CEdit	m_mutation_rate_control;
	CEdit	m_cataclysm_trigger_control;
	CButton	m_cataclysms_active_control;
	CEdit	m_similarities_index_control;
	BOOL	m_half_uniform;
	BOOL	m_heuristic_flip;
	BOOL	m_heuristic_n_point;
	BOOL	m_inversion;
	BOOL	m_multi_swap;
	BOOL	m_orientation_flip;
	BOOL	m_orientation_n_point;
	BOOL	m_position;
	BOOL	m_shunt;
	BOOL	m_single_swap;
	CString	m_removal_selection;
	CString	m_operator_adaptor;
	double	m_mutation_rate;
	CString	m_generation_model;
	CString	m_breed_selection;
	double	m_similarities_index;
	BOOL	m_order;
	BOOL	m_cataclysms_active;
	UINT	m_cataclysm_trigger;
	UINT	m_generation_epoch;
	CString	m_population_size;
	CString	m_report_every;
	double	m_cooling_ratio;
	double	m_end_temp;
	double	m_neighbourhood;
	UINT	m_restart_threshold;
	double	m_start_temp;
	BOOL	m_edge_recombination;
	BOOL	m_seg_position_based;
	BOOL	m_seg_order_based;
	UINT	m_max_segment_length;
	UINT	m_min_segment_length;
	UINT	m_multi_swap_size;
	UINT	m_n_point_size;
	BOOL	m_segment_restrictions;
	UINT	m_tournament_size;
	UINT	m_flip_size;
	long	m_cobra_iterations;
	CString	m_setting_name;
	//}}AFX_DATA
	DialogSettings set;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGASettingsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void custom_init();

	void segment_restrictions_update();
	void order_segment_restrictions_update();
	void position_segment_restrictions_update();
	void cataclysms_active_update();
	void breed_selection_update();
	void multi_swap_update();
	void n_point_update();
	void generation_update();
	void operator_adaptor_update();
	void flip_size_update();
	void flip_update();

	void load_all_data();
	void save_all_data();


public:

	CArray<DialogSettings, DialogSettings&> all_settings;
	char latest_setting[100];
	bool RemoteChangeSettings(CString set_to);


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGASettingsDialog)
	afx_msg void OnCataclysmsActive();
	virtual BOOL OnInitDialog();
	afx_msg void OnSegOrderBased();
	afx_msg void OnSegPositionBased();
	afx_msg void OnSegmentRestrictions();
	afx_msg void OnSelchangeBreedSelection();
	afx_msg void OnMultiSwapCheck();
	afx_msg void OnHeuristicNPointCheck();
	afx_msg void OnOrientationNPointCheck();
	afx_msg void OnSelchangeGenerationModel();
	afx_msg void OnSelchangeOperatorAdaptor();
	afx_msg void OnHeuristicFlipCheck();
	afx_msg void OnOrientationFlipCheck();
	afx_msg void OnStore();
	afx_msg void OnSelchangeSettings();
	virtual void OnOK();
	afx_msg void OnRemoveFromSetups();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

template <> void AFXAPI SerializeElements <DialogSettings> ( CArchive& ar, DialogSettings* pNew, int nCount );


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GASETTINGSDIALOG_H__F7DE24E2_3A93_11D2_85D3_ECC902C10000__INCLUDED_)

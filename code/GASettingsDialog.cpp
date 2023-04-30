// GASettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GA.h"
#include "GASettingsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGASettingsDialog dialog


CGASettingsDialog::CGASettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGASettingsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGASettingsDialog)
	m_half_uniform = TRUE;
	m_heuristic_flip = FALSE;
	m_heuristic_n_point = FALSE;
	m_inversion = TRUE;
	m_multi_swap = TRUE;
	m_orientation_flip = FALSE;
	m_orientation_n_point = FALSE;
	m_position = TRUE;
	m_shunt = TRUE;
	m_single_swap = TRUE;
	m_removal_selection = _T("Least-Fit");
	m_operator_adaptor = _T("COBRA");
	m_mutation_rate = 0.35;
	m_generation_model = _T("Steady-State");
	m_breed_selection = _T("Rank");
	m_similarities_index = 0.01;
	m_order = TRUE;
	m_cataclysms_active = TRUE;
	m_cataclysm_trigger = 25;
	m_generation_epoch = 1010;
	m_population_size = _T("100");
	m_report_every = _T("100");
	m_cooling_ratio = 0.99;
	m_end_temp = 0.001;
	m_neighbourhood = 0.1;
	m_restart_threshold = 100;
	m_start_temp = 10000;
	m_edge_recombination = TRUE;
	m_seg_position_based = TRUE;
	m_seg_order_based = TRUE;
	m_max_segment_length = 5;
	m_min_segment_length = 3;
	m_multi_swap_size = 2;
	m_n_point_size = 1;
	m_segment_restrictions = FALSE;
	m_tournament_size = 2;
	m_flip_size = 1;
	m_cobra_iterations = 1000;
	m_setting_name = _T("");
	//}}AFX_DATA_INIT

	all_settings.SetSize(0,100);
	latest_setting[0]='\0';
}


void CGASettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGASettingsDialog)
	DDX_Control(pDX, IDC_POPULATION_SIZE, m_population_size_control);
	DDX_Control(pDX, IDC_SETTINGS, m_setting_control);
	DDX_Control(pDX, IDC_HEURISTIC_FLIP_CHECK, m_heuristic_flip_control);
	DDX_Control(pDX, IDC_ORIENTATION_FLIP_CHECK, m_orientation_flip_control);
	DDX_Control(pDX, IDC_OPERATOR_ADAPTOR, m_operator_adaptor_control);
	DDX_Control(pDX, IDC_FLIP_SIZE, m_flip_size_control);
	DDX_Control(pDX, IDC_COBRA_ITERATIONS, m_cobra_iterations_control);
	DDX_Control(pDX, IDC_CATACLYSMIC_MUTATION, m_cataclysmic_mutation);
	DDX_Control(pDX, IDC_POSITION_CHECK, m_position_control);
	DDX_Control(pDX, IDC_ORDER_CHECK, m_order_control);
	DDX_Control(pDX, IDC_HALF_UNIFORM_CHECK, m_half_uniform_control);
	DDX_Control(pDX, IDC_EDGE_RECOMBINATION, m_edge_recombination_control);
	DDX_Control(pDX, IDC_CROSSOVER_OPERATORS, m_crossover_operators);
	DDX_Control(pDX, IDC_REMOVAL_SELECTION, m_removal_selection_control);
	DDX_Control(pDX, IDC_COOLING_RATIO, m_cooling_ratio_control);
	DDX_Control(pDX, IDC_END_TEMP, m_end_temp_control);
	DDX_Control(pDX, IDC_START_TEMP, m_start_temp_control);
	DDX_Control(pDX, IDC_RESTART_THRESHOLD, m_restart_threshold_control);
	DDX_Control(pDX, IDC_NEIGHBOURHOOD, m_neighbourhood_control);
	DDX_Control(pDX, IDC_SEGMENT_SETTINGS, m_segment_settings);
	DDX_Control(pDX, IDC_SIMULATED_ANNEALING_SETTINGS, m_simulated_annealing_settings);
	DDX_Control(pDX, IDC_HILL_CLIMBING_SETTINGS, m_hill_climbing_settings);
	DDX_Control(pDX, IDC_GENERATION_MODEL, m_generation_model_control);
	DDX_Control(pDX, IDC_HEURISTIC_N_POINT_CHECK, m_heuristic_n_point_control);
	DDX_Control(pDX, IDC_ORIENTATION_N_POINT_CHECK, m_orientation_n_point_control);
	DDX_Control(pDX, IDC_N_POINT_SIZE, m_n_point_size_control);
	DDX_Control(pDX, IDC_MULTI_SWAP_SIZE, m_multi_swap_size_control);
	DDX_Control(pDX, IDC_MULTI_SWAP_CHECK, m_multi_swap_control);
	DDX_Control(pDX, IDC_BREED_SELECTION, m_breed_selection_control);
	DDX_Control(pDX, IDC_TOURNAMENT_SIZE, m_tournament_size_control);
	DDX_Control(pDX, IDC_SEG_POSITION_BASED, m_seg_position_based_control);
	DDX_Control(pDX, IDC_SEG_ORDER_BASED, m_seg_order_based_control);
	DDX_Control(pDX, IDC_MAX_SEGMENT_LENGTH, m_max_segment_length_control);
	DDX_Control(pDX, IDC_MIN_SEGMENT_LENGTH, m_min_segment_length_control);
	DDX_Control(pDX, IDC_SEGMENT_RESTRICTIONS, m_segment_restrictions_control);
	DDX_Control(pDX, IDC_MUTATION_RATE, m_mutation_rate_control);
	DDX_Control(pDX, IDC_CATACLYSM_TRIGGER, m_cataclysm_trigger_control);
	DDX_Control(pDX, IDC_CATACLYSMS_ACTIVE, m_cataclysms_active_control);
	DDX_Control(pDX, IDC_SIMILARITIES_INDEX, m_similarities_index_control);
	DDX_Check(pDX, IDC_HALF_UNIFORM_CHECK, m_half_uniform);
	DDX_Check(pDX, IDC_HEURISTIC_FLIP_CHECK, m_heuristic_flip);
	DDX_Check(pDX, IDC_HEURISTIC_N_POINT_CHECK, m_heuristic_n_point);
	DDX_Check(pDX, IDC_INVERSION_CHECK, m_inversion);
	DDX_Check(pDX, IDC_MULTI_SWAP_CHECK, m_multi_swap);
	DDX_Check(pDX, IDC_ORIENTATION_FLIP_CHECK, m_orientation_flip);
	DDX_Check(pDX, IDC_ORIENTATION_N_POINT_CHECK, m_orientation_n_point);
	DDX_Check(pDX, IDC_POSITION_CHECK, m_position);
	DDX_Check(pDX, IDC_SHUNT_CHECK, m_shunt);
	DDX_Check(pDX, IDC_SINGLE_SWAP_CHECK, m_single_swap);
	DDX_CBString(pDX, IDC_REMOVAL_SELECTION, m_removal_selection);
	DDX_CBString(pDX, IDC_OPERATOR_ADAPTOR, m_operator_adaptor);
	DDX_Text(pDX, IDC_MUTATION_RATE, m_mutation_rate);
	DDV_MinMaxDouble(pDX, m_mutation_rate, 0., 1.);
	DDX_CBString(pDX, IDC_GENERATION_MODEL, m_generation_model);
	DDX_CBString(pDX, IDC_BREED_SELECTION, m_breed_selection);
	DDX_Text(pDX, IDC_SIMILARITIES_INDEX, m_similarities_index);
	DDV_MinMaxDouble(pDX, m_similarities_index, 0., 1.);
	DDX_Check(pDX, IDC_ORDER_CHECK, m_order);
	DDX_Check(pDX, IDC_CATACLYSMS_ACTIVE, m_cataclysms_active);
	DDX_Text(pDX, IDC_CATACLYSM_TRIGGER, m_cataclysm_trigger);
	DDX_Text(pDX, IDC_GENERATION_EPOCH, m_generation_epoch);
	DDX_CBString(pDX, IDC_POPULATION_SIZE, m_population_size);
	DDX_CBString(pDX, IDC_REPORT_EVERY, m_report_every);
	DDX_Text(pDX, IDC_COOLING_RATIO, m_cooling_ratio);
	DDV_MinMaxDouble(pDX, m_cooling_ratio, 0., 1.);
	DDX_Text(pDX, IDC_END_TEMP, m_end_temp);
	DDV_MinMaxDouble(pDX, m_end_temp, 0., 1000.);
	DDX_Text(pDX, IDC_NEIGHBOURHOOD, m_neighbourhood);
	DDX_Text(pDX, IDC_RESTART_THRESHOLD, m_restart_threshold);
	DDX_Text(pDX, IDC_START_TEMP, m_start_temp);
	DDX_Check(pDX, IDC_EDGE_RECOMBINATION, m_edge_recombination);
	DDX_Check(pDX, IDC_SEG_POSITION_BASED, m_seg_position_based);
	DDX_Check(pDX, IDC_SEG_ORDER_BASED, m_seg_order_based);
	DDX_Text(pDX, IDC_MAX_SEGMENT_LENGTH, m_max_segment_length);
	DDX_Text(pDX, IDC_MIN_SEGMENT_LENGTH, m_min_segment_length);
	DDX_Text(pDX, IDC_MULTI_SWAP_SIZE, m_multi_swap_size);
	DDX_Text(pDX, IDC_N_POINT_SIZE, m_n_point_size);
	DDX_Check(pDX, IDC_SEGMENT_RESTRICTIONS, m_segment_restrictions);
	DDX_Text(pDX, IDC_TOURNAMENT_SIZE, m_tournament_size);
	DDX_Text(pDX, IDC_FLIP_SIZE, m_flip_size);
	DDX_Text(pDX, IDC_COBRA_ITERATIONS, m_cobra_iterations);
	DDX_CBString(pDX, IDC_SETTINGS, m_setting_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGASettingsDialog, CDialog)
	//{{AFX_MSG_MAP(CGASettingsDialog)
	ON_BN_CLICKED(IDC_CATACLYSMS_ACTIVE, OnCataclysmsActive)
	ON_BN_CLICKED(IDC_SEG_ORDER_BASED, OnSegOrderBased)
	ON_BN_CLICKED(IDC_SEG_POSITION_BASED, OnSegPositionBased)
	ON_BN_CLICKED(IDC_SEGMENT_RESTRICTIONS, OnSegmentRestrictions)
	ON_CBN_SELCHANGE(IDC_BREED_SELECTION, OnSelchangeBreedSelection)
	ON_BN_CLICKED(IDC_MULTI_SWAP_CHECK, OnMultiSwapCheck)
	ON_BN_CLICKED(IDC_HEURISTIC_N_POINT_CHECK, OnHeuristicNPointCheck)
	ON_BN_CLICKED(IDC_ORIENTATION_N_POINT_CHECK, OnOrientationNPointCheck)
	ON_CBN_SELCHANGE(IDC_GENERATION_MODEL, OnSelchangeGenerationModel)
	ON_CBN_SELCHANGE(IDC_OPERATOR_ADAPTOR, OnSelchangeOperatorAdaptor)
	ON_BN_CLICKED(IDC_HEURISTIC_FLIP_CHECK, OnHeuristicFlipCheck)
	ON_BN_CLICKED(IDC_ORIENTATION_FLIP_CHECK, OnOrientationFlipCheck)
	ON_BN_CLICKED(IDC_STORE, OnStore)
	ON_CBN_SELCHANGE(IDC_SETTINGS, OnSelchangeSettings)
	ON_BN_CLICKED(IDC_REMOVE_FROM_SETUPS, OnRemoveFromSetups)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGASettingsDialog message handlers


template <> void AFXAPI SerializeElements <DialogSettings> ( CArchive& ar, DialogSettings* pNew, int nCount )
{    
	for ( int i = 0; i < nCount; i++, pNew++ )   
	{
		// Serialize each CPerson object        
		pNew->Serialize( ar );
	}
}


BOOL CGASettingsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	load_all_data();
	// restore to latest setting
	for (long i=0; i<all_settings.GetSize(); i++)
	{
		if (strcmp(all_settings[i]._name,latest_setting)==0)
		{
			all_settings[i].write_settings_to(*this);
			break;
		}
	}

	UpdateData(FALSE);
	custom_init();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGASettingsDialog::custom_init()
{
	generation_update();
	cataclysms_active_update();
	order_segment_restrictions_update();
	position_segment_restrictions_update();
	breed_selection_update();
	multi_swap_update();
	n_point_update();
	operator_adaptor_update();
	flip_update();
}

void CGASettingsDialog::OnCataclysmsActive() 
{	cataclysms_active_update();}
void CGASettingsDialog::OnSegOrderBased() 
{	order_segment_restrictions_update();}
void CGASettingsDialog::OnSegPositionBased() 
{	position_segment_restrictions_update();}
void CGASettingsDialog::OnSegmentRestrictions() 
{	segment_restrictions_update();}
void CGASettingsDialog::OnSelchangeBreedSelection() 
{	breed_selection_update();}
void CGASettingsDialog::OnMultiSwapCheck() 
{	multi_swap_update(); }
void CGASettingsDialog::OnHeuristicNPointCheck() 
{	n_point_update(); }
void CGASettingsDialog::OnOrientationNPointCheck() 
{	n_point_update(); }
void CGASettingsDialog::OnSelchangeGenerationModel() 
{	generation_update();}
void CGASettingsDialog::OnSelchangeOperatorAdaptor() 
{	operator_adaptor_update();}
void CGASettingsDialog::OnHeuristicFlipCheck() 
{	flip_update(); }
void CGASettingsDialog::OnOrientationFlipCheck() 
{ flip_update();}



void CGASettingsDialog::cataclysms_active_update()
{
	bool setting=m_cataclysms_active_control.GetCheck();
	if (!m_cataclysmic_mutation.IsWindowEnabled())
	{
		setting=false;
		m_cataclysms_active_control.EnableWindow(false);
	}
	else
		m_cataclysms_active_control.EnableWindow(true);

	m_similarities_index_control.EnableWindow(setting);
	m_cataclysm_trigger_control.EnableWindow(setting);
	m_mutation_rate_control.EnableWindow(setting);
}

void CGASettingsDialog::order_segment_restrictions_update()
{
	if (!m_seg_order_based_control.GetCheck())
		if (!m_seg_position_based_control.GetCheck())
		{
			m_segment_restrictions_control.EnableWindow(false);
			m_segment_settings.EnableWindow(false);
			segment_restrictions_update();
		}
		else
		{
			// do nothing
		}
	else
	{
		m_segment_restrictions_control.EnableWindow(true);
		m_segment_settings.EnableWindow(true);
		segment_restrictions_update();
	}
}

void CGASettingsDialog::position_segment_restrictions_update()
{
	if (!m_seg_position_based_control.GetCheck())
		if (!m_seg_order_based_control.GetCheck())
		{
			m_segment_restrictions_control.EnableWindow(false);
			m_segment_settings.EnableWindow(false);
			segment_restrictions_update();
		}
		else
		{
			// do nothing
		}
	else
	{
		m_segment_restrictions_control.EnableWindow(true);
		m_segment_settings.EnableWindow(true);
		segment_restrictions_update();
	}
}

void CGASettingsDialog::segment_restrictions_update()
{
	bool setting=m_segment_restrictions_control.GetCheck();
	bool overall=m_segment_settings.IsWindowEnabled();
	if (overall==false)
	{
		setting=false;
		m_segment_restrictions_control.EnableWindow(false);
	}


	m_min_segment_length_control.EnableWindow(setting);
	m_max_segment_length_control.EnableWindow(setting);
}

void CGASettingsDialog::breed_selection_update()
{
	int i=m_breed_selection_control.GetCurSel();
	CString current;
	m_breed_selection_control.GetLBText(i,current);
	if (current=="Tournament")
		m_tournament_size_control.EnableWindow(true);
	else
		m_tournament_size_control.EnableWindow(false);
}

void CGASettingsDialog::multi_swap_update()
{
	m_multi_swap_size_control.
		EnableWindow(m_multi_swap_control.GetCheck());
}


void CGASettingsDialog::n_point_update() 
{
	if (m_orientation_n_point_control.GetCheck() ||
		  m_heuristic_n_point_control.GetCheck())
		m_n_point_size_control.EnableWindow(true);
	else
		m_n_point_size_control.EnableWindow(false);
}

void CGASettingsDialog::generation_update()
{
	int i=m_generation_model_control.GetCurSel();
	CString current;
	m_generation_model_control.GetLBText(i,current);

	if (current=="Steady-State")
	{
		m_operator_adaptor_control.EnableWindow(true);
		operator_adaptor_update();
		m_population_size_control.EnableWindow(true);
	}
	else
		m_population_size_control.EnableWindow(false);

	if (current=="Hill Climbing" || current=="SA Hill Climbing" ||
			current=="Simulated Annealing" || current=="Random")
	{
		m_removal_selection_control.EnableWindow(false);
		m_breed_selection_control.EnableWindow(false);
		
	
		int i=m_operator_adaptor_control.GetCurSel();
		CString current_adaptor;
		m_operator_adaptor_control.GetLBText(i,current_adaptor);
		
		if (current_adaptor=="Adaptive Mutation" ||
				current_adaptor=="Fixed Rate")
			m_operator_adaptor_control.SetCurSel(1);		// Set to COBRA

		if (m_operator_adaptor_control.GetCount()==4)
		{
			// delete Adaptive Mutation and Fixed Rate from adaptors
			int i_a=m_operator_adaptor_control.FindStringExact(-1,"Adaptive Mutation");
			m_operator_adaptor_control.DeleteString(i_a);
			int i_f=m_operator_adaptor_control.FindStringExact(-1,"Fixed Rate");
			m_operator_adaptor_control.DeleteString(i_f);
		}

		// turn off crossover operators
		m_crossover_operators.EnableWindow(false);
		m_edge_recombination_control.EnableWindow(false);
		m_position_control.EnableWindow(false);
		m_order_control.EnableWindow(false);
		m_half_uniform_control.EnableWindow(false);
		m_seg_position_based_control.EnableWindow(false);
		m_seg_order_based_control.EnableWindow(false);
		m_orientation_n_point_control.EnableWindow(false);
		m_heuristic_n_point_control.EnableWindow(false);

		m_segment_settings.EnableWindow(false);
		m_n_point_size_control.EnableWindow(false);
		m_cataclysmic_mutation.EnableWindow(false);

		segment_restrictions_update();
		cataclysms_active_update();
	}
	else
	{
		m_removal_selection_control.EnableWindow(true);
		m_breed_selection_control.EnableWindow(true);

		if (m_operator_adaptor_control.GetCount()==2)
		{
			m_operator_adaptor_control.InsertString(0,"Adaptive Mutation");
			m_operator_adaptor_control.InsertString(2,"Fixed Rate");
		}


		m_crossover_operators.EnableWindow(true);
		m_edge_recombination_control.EnableWindow(true);
		m_position_control.EnableWindow(true);
		m_order_control.EnableWindow(true);
		m_half_uniform_control.EnableWindow(true);
		m_seg_position_based_control.EnableWindow(true);
		m_seg_order_based_control.EnableWindow(true);
		m_orientation_n_point_control.EnableWindow(true);
		m_heuristic_n_point_control.EnableWindow(true);

		m_segment_settings.EnableWindow(true);
		m_cataclysmic_mutation.EnableWindow(true);

		order_segment_restrictions_update();
		position_segment_restrictions_update();
		n_point_update();
		cataclysms_active_update();
	}

	if (current=="Hill Climbing" || current=="SA Hill Climbing")
	{
		m_hill_climbing_settings.EnableWindow(true);
		m_restart_threshold_control.EnableWindow(true);

		if (current=="SA Hill Climbing")
		{
			m_neighbourhood_control.EnableWindow(true);
			m_operator_adaptor_control.EnableWindow(false);
			operator_adaptor_update();
		}
		else
		{
			m_neighbourhood_control.EnableWindow(false);
			m_operator_adaptor_control.EnableWindow(true);
			operator_adaptor_update();
		}
	}
	else
	{
		m_hill_climbing_settings.EnableWindow(false);
		m_restart_threshold_control.EnableWindow(false);
		m_neighbourhood_control.EnableWindow(false);
	}

	if (current=="Simulated Annealing")
	{
		m_simulated_annealing_settings.EnableWindow(true);
		m_start_temp_control.EnableWindow(true);
		m_end_temp_control.EnableWindow(true);
		m_cooling_ratio_control.EnableWindow(true);
		m_operator_adaptor_control.EnableWindow(true);
		operator_adaptor_update();
	}
	else
	{
		m_simulated_annealing_settings.EnableWindow(false);
		m_start_temp_control.EnableWindow(false);
		m_end_temp_control.EnableWindow(false);
		m_cooling_ratio_control.EnableWindow(false);
	}

}

void CGASettingsDialog::operator_adaptor_update()
{

	int i=m_operator_adaptor_control.GetCurSel();
	CString current;
	m_operator_adaptor_control.GetLBText(i,current);

	if (current=="COBRA" && m_operator_adaptor_control.IsWindowEnabled())
		m_cobra_iterations_control.EnableWindow(true);
	else
		m_cobra_iterations_control.EnableWindow(false);
}


void CGASettingsDialog::flip_update()
{
	if (m_orientation_flip_control.GetCheck() ||
			m_heuristic_flip_control.GetCheck())
			m_flip_size_control.EnableWindow(true);
	else
			m_flip_size_control.EnableWindow(false);
}

IMPLEMENT_SERIAL(DialogSettings, CObject, 1);

void CGASettingsDialog::save_all_data()
{
	CFile theFile;
	theFile.Open("settings.bin", CFile::modeCreate | CFile::modeWrite );
	CArchive archive(&theFile, CArchive::store);
	all_settings.Serialize(archive);
	archive.Close();
	theFile.Close();
}

void CGASettingsDialog::load_all_data()
{
	all_settings.RemoveAll();
	CFile theFile;
	theFile.Open("settings.bin", CFile::modeRead);
	CArchive archive(&theFile, CArchive::load);
	all_settings.Serialize(archive);
	archive.Close();
	theFile.Close();

	// clear all select items in m_settings_control
	m_setting_control.ResetContent();
	// add all names in order to m_settings_control
	for (long i=0; i<all_settings.GetSize(); i++)
	{
		CString t=all_settings[i]._name;
		m_setting_control.InsertString(0,t);
	}

	if (all_settings.GetSize()>0)
		all_settings[0].write_settings_to(*this);

	UpdateData(FALSE);
	custom_init();
}

void DialogSettings::read_settings_from(const CGASettingsDialog &s)
{
	_name=s.m_setting_name;
	_half_uniform =s.m_half_uniform;
	_heuristic_flip =s.m_heuristic_flip;
	_heuristic_n_point =s.m_heuristic_n_point;
	_inversion =s.m_inversion;
	_multi_swap =s.m_multi_swap;
	_orientation_flip =s.m_orientation_flip;
	_orientation_n_point =s.m_orientation_n_point;
	_position =s.m_position;
	_shunt =s.m_shunt;
	_single_swap=s.m_single_swap;
	_removal_selection=s.m_removal_selection;
	_operator_adaptor=s.m_operator_adaptor;
	_mutation_rate=s.m_mutation_rate;
	_generation_model=s.m_generation_model;
	_breed_selection=s.m_breed_selection;
	_similarities_index=s.m_similarities_index;
	_order=s.m_order;
	_cataclysms_active=s.m_cataclysms_active;
	_cataclysm_trigger=s.m_cataclysm_trigger;
	_generation_epoch=s.m_generation_epoch;
	_population_size=s.m_population_size;
	_report_every=s.m_report_every;
	_cooling_ratio=s.m_cooling_ratio;
	_end_temp=s.m_end_temp;
	_neighbourhood=s.m_neighbourhood;
	_restart_threshold=s.m_restart_threshold;
	_start_temp=s.m_start_temp;
	_edge_recombination=s.m_edge_recombination;
	_seg_position_based=s.m_seg_position_based;
	_seg_order_based=s.m_seg_order_based;
	_max_segment_length=s.m_max_segment_length;
	_min_segment_length=s.m_min_segment_length;
	_multi_swap_size=s.m_multi_swap_size;
	_n_point_size=s.m_n_point_size;
	_segment_restrictions=s.m_segment_restrictions;
	_tournament_size=s.m_tournament_size;
	_flip_size=s.m_flip_size;
	_cobra_iterations=s.m_cobra_iterations;
}

void DialogSettings::write_settings_to(CGASettingsDialog &s) const
{
//	s.SetDlgItemText(IDC_SETTINGS,_name);
//	int i=s.m_setting_name.FindStringExact(0,_name);
//	s.m_setting_control.SetCurSel(i);
	s.m_setting_name=_name;

	s.m_half_uniform=_half_uniform;
	s.m_heuristic_flip=_heuristic_flip;
	s.m_heuristic_n_point=_heuristic_n_point;
	s.m_inversion=_inversion;
	s.m_multi_swap=_multi_swap;
	s.m_orientation_flip=_orientation_flip;
	s.m_orientation_n_point=_orientation_n_point;
	s.m_position=_position;
	s.m_shunt=_shunt;
	s.m_single_swap=_single_swap;
	s.m_removal_selection=_removal_selection;
	s.m_operator_adaptor=_operator_adaptor;
	s.m_mutation_rate=_mutation_rate;
	s.m_generation_model=_generation_model;
	s.m_breed_selection=_breed_selection;
	s.m_similarities_index=_similarities_index;
	s.m_order=_order;
	s.m_cataclysms_active=_cataclysms_active;
	s.m_cataclysm_trigger=_cataclysm_trigger;
	s.m_generation_epoch=_generation_epoch;
	s.m_population_size=_population_size;
	s.m_report_every=_report_every;
	s.m_cooling_ratio=_cooling_ratio;
	s.m_end_temp=_end_temp;
	s.m_neighbourhood=_neighbourhood;
	s.m_restart_threshold=_restart_threshold;
	s.m_start_temp=_start_temp;
	s.m_edge_recombination=_edge_recombination;
	s.m_seg_position_based=_seg_position_based;
	s.m_seg_order_based=_seg_order_based;
	s.m_max_segment_length=_max_segment_length;
	s.m_min_segment_length=_min_segment_length;
	s.m_multi_swap_size=_multi_swap_size;
	s.m_n_point_size=_n_point_size;
	s.m_segment_restrictions=_segment_restrictions;
	s.m_tournament_size=_tournament_size;
	s.m_flip_size=_flip_size;
	s.m_cobra_iterations=_cobra_iterations;
}

void DialogSettings::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
			ar << _name <<
				_half_uniform  <<
				_heuristic_flip  <<
				_heuristic_n_point  <<
				_inversion  <<
				_multi_swap <<
				_orientation_flip  <<
				_orientation_n_point <<
				_position  <<
				_shunt  <<
				_single_swap <<
				_removal_selection <<
				_operator_adaptor <<
				_mutation_rate <<
				_generation_model <<
				_breed_selection <<
				_similarities_index <<
				_order <<
				_cataclysms_active <<
				_cataclysm_trigger <<
				_generation_epoch <<
				_population_size <<
				_report_every <<
				_cooling_ratio <<
				_end_temp <<
				_neighbourhood <<
				_restart_threshold <<
				_start_temp <<
				_edge_recombination <<
				_seg_position_based <<
				_seg_order_based <<
				_max_segment_length <<
				_min_segment_length <<
				_multi_swap_size <<
				_n_point_size <<
				_segment_restrictions <<
				_tournament_size <<
				_flip_size <<
				_cobra_iterations;

    }
    else
    {
			ar >> _name >>
				_half_uniform  >>
				_heuristic_flip  >>
				_heuristic_n_point  >>
				_inversion  >>
				_multi_swap >>
				_orientation_flip  >>
				_orientation_n_point >>
				_position  >>
				_shunt  >>
				_single_swap >>
				_removal_selection >>
				_operator_adaptor >>
				_mutation_rate >>
				_generation_model >>
				_breed_selection >>
				_similarities_index >>
				_order >>
				_cataclysms_active >>
				_cataclysm_trigger >>
				_generation_epoch >>
				_population_size >>
				_report_every >>
				_cooling_ratio >>
				_end_temp >>
				_neighbourhood >>
				_restart_threshold >>
				_start_temp >>
				_edge_recombination >>
				_seg_position_based >>
				_seg_order_based >>
				_max_segment_length >>
				_min_segment_length >>
				_multi_swap_size >>
				_n_point_size >>
				_segment_restrictions >>
				_tournament_size >>
				_flip_size >>
				_cobra_iterations;
    }
}
DialogSettings& DialogSettings::operator=(const DialogSettings &s)
{	
	_name=s._name;

	_half_uniform=s._half_uniform;
	_heuristic_flip=s._heuristic_flip;
	_heuristic_n_point=s._heuristic_n_point;
	_inversion=s._inversion;
	_multi_swap=s._multi_swap;
	_orientation_flip=s._orientation_flip;
	_orientation_n_point=s._orientation_n_point;
	_position=s._position;
	_shunt=s._shunt;
	_single_swap=s._single_swap;
	_removal_selection=s._removal_selection;
	_operator_adaptor=s._operator_adaptor;
	_mutation_rate=s._mutation_rate;
	_generation_model=s._generation_model;
	_breed_selection=s._breed_selection;
	_similarities_index=s._similarities_index;
	_order=s._order;
	_cataclysms_active=s._cataclysms_active;
	_cataclysm_trigger=s._cataclysm_trigger;
	_generation_epoch=s._generation_epoch;
	_population_size=s._population_size;
	_report_every=s._report_every;
	_cooling_ratio=s._cooling_ratio;
	_end_temp=s._end_temp;
	_neighbourhood=s._neighbourhood;
	_restart_threshold=s._restart_threshold;
	_start_temp=s._start_temp;
	_edge_recombination=s._edge_recombination;
	_seg_position_based=s._seg_position_based;
	_seg_order_based=s._seg_order_based;
	_max_segment_length=s._max_segment_length;
	_min_segment_length=s._min_segment_length;
	_multi_swap_size=s._multi_swap_size;
	_n_point_size=s._n_point_size;
	_segment_restrictions=s._segment_restrictions;
	_tournament_size=s._tournament_size;
	_flip_size=s._flip_size;
	_cobra_iterations=s._cobra_iterations;
	return *this;
}

void CGASettingsDialog::OnStore()
{
	UpdateData(TRUE);
	set.read_settings_from(*this);
	// Check to prevent name duplication
	for (long i=0; i<all_settings.GetSize(); i++)
	{
		if (all_settings[i]._name==set._name)
		{
			CString replace="Replace the '"+set._name+"' setup with the current setup?";

			int response=MessageBox(replace,"Name Conflict",MB_YESNO | MB_ICONQUESTION);
			if (response==IDYES)
				all_settings[i]=set;

			return;
		}
	}

	int index=all_settings.Add(set);
	m_setting_control.InsertString(0,set._name);
}

bool CGASettingsDialog::RemoteChangeSettings(CString set_to)
{
	for (long i=0; i<all_settings.GetSize(); i++)
	{
		if (all_settings[i]._name==set_to)
		{
//			afxDump << "\nRemotely Selected GA Settings... " << set_to << "\n";
			all_settings[i].write_settings_to(*this);
			return true;
		}
	}
	return false;
}

void CGASettingsDialog::OnSelchangeSettings() 
{
	int index=m_setting_control.GetCurSel();
	CString current;
	m_setting_control.GetLBText(index,current);
	// search for matching name in all_settings
	for (long i=0; i<all_settings.GetSize(); i++)
	{
		if (all_settings[i]._name==current)
		{
			all_settings[i].write_settings_to(*this);
			UpdateData(FALSE);
			custom_init();
			return;
		}
	}
	CString replace="Setup '"+current+"' does not exist!";
	MessageBox(replace,"Setup Not Found",MB_OK | MB_ICONEXCLAMATION);
}

void CGASettingsDialog::OnOK()
{
	int index=m_setting_control.GetCurSel();
	m_setting_control.GetLBText(index,latest_setting);
	CDialog::OnOK();
	save_all_data();
}

void CGASettingsDialog::OnRemoveFromSetups() 
{
	CString remove_string;
	GetDlgItemText(IDC_SETTINGS,remove_string);
	// search for matching name in all_settings
	for (long i=0; i<all_settings.GetSize(); i++)
	{
		if (all_settings[i]._name==remove_string)
		{
			CString remove="Remove '"+remove_string+"' Setup?";
			if (MessageBox(remove,"Removing Setup", MB_OKCANCEL)==IDOK)
			{
				all_settings[i]=all_settings[all_settings.GetUpperBound()];
				if (all_settings.GetUpperBound()>0)
				{
					all_settings.SetSize(all_settings.GetUpperBound());
					int index=m_setting_control.GetCurSel();
					m_setting_control.DeleteString(index);
				}
				all_settings[0].write_settings_to(*this);
				UpdateData(FALSE);
				custom_init();
				return;
			}
			else
				return;
		}
	}
	MessageBox("No Such Setup.", MB_OK);
}

// GADoc.cpp : implementation of the CGADoc class
//

#include "stdafx.h"
#include "GA.h"

#include "GADoc.h"
#include "GotoTestDialog.h"
#include "NSwapDialog.h"
#include "OrderDialog.h"
#include "GASettingsDialog.h"
#include "SetRegimeDialog.h"
#include "BatchDialog.h"
#include "bitstream.h"
#include "time.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

array_index GLOBAL_MIN_SEGMENT_LENGTH;
array_index GLOBAL_MAX_SEGMENT_LENGTH;


/////////////////////////////////////////////////////////////////////////////
// CGADoc

IMPLEMENT_DYNCREATE(CGADoc, CDocument)

BEGIN_MESSAGE_MAP(CGADoc, CDocument)
	//{{AFX_MSG_MAP(CGADoc)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_VIEW_NEXTTEST, OnViewNexttest)
	ON_COMMAND(ID_VIEW_PREVTEST, OnViewPrevtest)
	ON_COMMAND(ID_VIEW_NEXT10TEST, OnViewNext10test)
	ON_COMMAND(ID_VIEW_PREV10TEST, OnViewPrev10test)
	ON_COMMAND(ID_VIEW_GOTO_TEST, OnViewGotoTest)
	ON_COMMAND(ID_VIEW_DIAGNOSE, OnViewDiagnose)
	ON_COMMAND(ID_VIEW_SET_CHECK1, OnViewSetCheck1)
	ON_COMMAND(ID_VIEW_SET_CHECK2, OnViewSetCheck2)
	ON_COMMAND(ID_VIEW_SHUFFLE, OnViewShuffle)
	ON_COMMAND(ID_VIEW_NORMALISE, OnViewNormalise)
	ON_COMMAND(ID_VIEW_ORDER, OnViewOrder)
	ON_COMMAND(ID_OPERATORS_ORDER, OnOperatorsOrder)
	ON_COMMAND(ID_OPERATORS_INVERT, OnOperatorsInvert)
	ON_COMMAND(ID_OPERATORS_POSITION, OnOperatorsPosition)
	ON_COMMAND(ID_OPERATORS_SHUNT, OnOperatorsShunt)
	ON_COMMAND(ID_OPERATORS_SWAP, OnOperatorsSwap)
	ON_COMMAND(ID_VIEW_NEXT_SHEET, OnViewNextSheet)
	ON_COMMAND(ID_VIEW_PREV_SHEET, OnViewPrevSheet)
	ON_COMMAND(ID_OPERATORS_HUXP, OnOperatorsHuxp)
	ON_COMMAND(ID_OPERATORS_NSWAP, OnOperatorsNswap)
	ON_COMMAND(ID_GA_SETTINGS, OnGaSettings)
	ON_COMMAND(ID_SET_REGIME, OnSetRegime)
	ON_COMMAND(ID_RUN_GA, OnRunGa)
	ON_COMMAND(ID_EXPORT_CURRENT, OnExportCurrent)
	ON_COMMAND(ID_BATCH_PROCESS, OnBatchProcess)
	ON_COMMAND(ID_DETAILED_OUTPUT, OnDetailedOutput)
	ON_UPDATE_COMMAND_UI(ID_DETAILED_OUTPUT, OnUpdateDetailedOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGADoc construction/destruction

CGADoc::CGADoc()
{
	// TODO: add one-time construction code here
	LDA_c::_environment=&test_bed;
	_permutation[0]='\0';

	current_sheet=0;
	m_detailed_output=true;
	seed_random_new();
}

CGADoc::~CGADoc()
{
}

BOOL CGADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGADoc serialization

void CGADoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGADoc diagnostics

#ifdef _DEBUG
void CGADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGADoc commands

void CGADoc::LayoutUpdateView()
{
	POSITION pos = GetFirstViewPosition();
	CView *first=GetNextView(pos);
	CView *second=GetNextView(pos);

	// Update the layout view only
	UpdateAllViews(second);
}

void CGADoc::OutputUpdateView()
{
	POSITION pos = GetFirstViewPosition();
	CView *first=GetNextView(pos);

	// Update the layout view only
	UpdateAllViews(first);
}

void CGADoc::Update(update_t choice, array_index* gene_order)
{
	test_bed.set_size(tests.get_current().sheet_width,
										tests.get_current().sheet_height);
	test_bed.set_rule_regime(tests.get_current().rule);
	LDA_c test_chromo;
	switch (choice)
	{
		case u_CURRENT:
			test_chromo.init_chromosome();
			break;
		case u_RANDOM:
			test_chromo.random_chromosome();
			break;
		case u_ORDER:
			test_chromo.ordered_chromosome(gene_order);
		default:
			break;
	}

	test_chromo.get_permutation_char(_permutation);
	strncpy_s(test_bed._permutation,_permutation, maxPermutatationLength);
	current_sheet=0;
	test_chromo.fitness();
	LayoutUpdateView();
}

void CGADoc::OnViewOrder() 
{
	sequence_size chromosome_length=LDA_c::LDA_length;
	do
	{
		COrderDialog dialog;
		dialog.m_gene_order=_permutation;
		if (dialog.DoModal()==IDCANCEL)
			return;

		std::istringstream order_string;
		order_string.str(dialog.m_gene_order.GetBuffer(1));
		array_index i=0, number=0;

		array_index* test=new array_index [chromosome_length];

		while (i<chromosome_length && order_string >> test[i])
			i++;

		// skipping whitespace to end of file or to next non-space char, not including non-space char.
		while (true)
		{
			if (!order_string.eof() || !std::isspace(order_string.get()))
			{
				order_string.unget();
				break;
			}
		}

		if (i==chromosome_length && order_string.eof() &&
				check_permutation(chromosome_length, test)==SUCCESS)
		{
			Update(u_ORDER, test);

			delete[] test;
			return;
		}
		else
		{
			delete[] test;
			MessageBox(NULL, "Invalid Permutation", "Input Error...", 
									MB_OK | MB_ICONSTOP | MB_APPLMODAL);
		}
	}
	while (true);
}

void CGADoc::OnViewRefresh() 
{
	char input_file[]="shapes.txt";
	std::ifstream input_stream(input_file, std::ios::in | std::ios::binary);
	input_stream >> tests;		// read in all test data
	input_stream.close();

	// initialise test_bed to calculate current test

	test_bed.provide_shapes(&tests.get_current().shapes);
	Update(u_CURRENT);
}

void CGADoc::OnViewNexttest() 
{
	test_bed.provide_shapes(&tests.next_current().shapes);
	Update(u_CURRENT);
}

void CGADoc::OnViewPrevtest() 
{
	test_bed.provide_shapes(&tests.prev_current().shapes);
	Update(u_CURRENT);
}

void CGADoc::OnViewNext10test()
{
	for (unsigned int i=0; i<9;i++)
		tests.next_current();
	OnViewNexttest();
}

void CGADoc::OnViewPrev10test() 
{
	for (unsigned int i=0; i<9;i++)
		tests.prev_current();
	OnViewPrevtest();
}

void CGADoc::OnViewGotoTest() 
{
	CGotoTestDialog dialog;
	dialog.DoModal();
	test_bed.provide_shapes(&tests.set_current(dialog.m_test_number).shapes);
	Update(u_CURRENT);
}

void CGADoc::OnViewDiagnose() 
{
//	msDif.Difference( msOld, msNew );
//	msDif.DumpStatistics();
}

void CGADoc::OnViewSetCheck1() 
{
//		msOld.Checkpoint();
//		afxDump << "Snapshot stored in old\n";
//		msOld.DumpStatistics();
}

void CGADoc::OnViewSetCheck2() 
{
//		msNew.Checkpoint();
//		afxDump << "Snapshot stored in new\n";
//		msNew.DumpStatistics();
}

void CGADoc::OnViewShuffle() 
{
	Update(u_RANDOM);
}

void CGADoc::OnViewNormalise() 
{
	Update(u_CURRENT);
}

void CGADoc::OnOperatorsOrder() 
{
	LDA_c parent1, parent2, child;
	parent1.random_chromosome();
	parent2.random_chromosome();

	order_c o;
	o.cross(&parent1,&parent2,&child);
	
	char output[1000];
	child.get_permutation_char(output);
//	afxDump << output << "\n\n";
}


void CGADoc::OnOperatorsPosition() 
{
	// TODO: Add your command handler code here
	LDA_c parent1, parent2, child;
	parent1.random_chromosome();
	parent2.random_chromosome();


	char output[1000];
	parent1.get_permutation_char(output);
//	afxDump << output << " p1\n";
	parent2.get_permutation_char(output);
//	afxDump << output << " p2\n";

	position_c o;
	o.cross(&parent1,&parent2,&child);
	
	child.get_permutation_char(output);
//	afxDump << output << " c\n\n";
}

void CGADoc::OnOperatorsHuxp()
{
	LDA_c parent1, parent2, child;
	parent1.random_chromosome();
	parent2.random_chromosome();

//	afxDump << "\n" << parent1.distance(parent2) << "=DISTANCE\n";

	HUX_position_c o;
	o.cross(&parent1,&parent2,&child);
	
	char output[1000];
	child.get_permutation_char(output);
//	afxDump << output << "\n\n";
}


void CGADoc::OnOperatorsSwap() 
{
	LDA_c parent, child;
	parent.random_chromosome();
	
	swap_m m;
	m.mutate(&parent, &child);

	char output[1000];
	child.get_permutation_char(output);
//	afxDump << output << "\n";
}


void CGADoc::OnOperatorsNswap() 
{
	LDA_c parent, child;
	parent.random_chromosome();
	
	CNSwapDialog dialog;
	dialog.DoModal();

	multiple_swap_m m;
	m.set_swap_count(dialog.m_swap_number);

	m.mutate(&parent, &child);

	char output[1000];
	child.get_permutation_char(output);
//	afxDump << output << "\n";
}


void CGADoc::OnOperatorsInvert() 
{
	LDA_c parent, child;
	parent.random_chromosome();
	
	invert_m m;
	m.mutate(&parent, &child);

	char output[1000];
	child.get_permutation_char(output);
//	afxDump << output << "\n";
}

void CGADoc::OnOperatorsShunt()
{
	LDA_c parent, child;
	parent.random_chromosome();
	
	shunt_m m;
	m.mutate(&parent, &child);

	char output[1000];
	child.get_permutation_char(output);
//	afxDump << output << "\n";
}


void CGADoc::OnViewNextSheet() 
{
	if (current_sheet<test_bed._ftable->sheet_count-1)
	{
		current_sheet++;
		LayoutUpdateView();
	}
}

void CGADoc::OnViewPrevSheet()
{
	if (current_sheet>0)
	{
		current_sheet--;
		LayoutUpdateView();
	}
}


void CGADoc::OnGaSettings() 
{
	// TODO: Add your command handler code here
	GAsettings.DoModal();
}



void CGADoc::OnSetRegime() 
{
	// TODO: Add your command handler code here

	CSetRegimeDialog d;

	switch (tests.get_current().rule)
	{
		case LEFTMOST:
			d.m_regime_radio=0;
			break;
		case TOPMOST:
			d.m_regime_radio=2;
			break;
		case ITOPMOST:
			d.m_regime_radio=1;
			break;
		case DYNAMIC:
			d.m_regime_radio=3;
			break;
		case ILEFTMOST:
			d.m_regime_radio=4;
		default:
			break;
	}

	d.DoModal();

	switch (d.m_regime_radio)
	{
		case 0:
			tests.get_current().rule=LEFTMOST;
			break;
		case 1:
			tests.get_current().rule=ITOPMOST;
			break;
		case 2:
			tests.get_current().rule=TOPMOST;
			break;
		case 3:
			tests.get_current().rule=DYNAMIC;
			break;
		case 4:
			tests.get_current().rule=ILEFTMOST;
			break;
		default:
			break;
	}

	Update(u_CURRENT);
}

void CGADoc::RunGA()
{
		// Create and initialise the population
	LDA_c test_chromo;
	sequence_size pop_size;
	bool randomize_orientation=false;
	bool randomize_heuristic=false;

#ifdef _DEBUG
	afxDump << "Beginning Evolution for... Test " << tests.current+1 << "\n";
#endif
	sequence_size report_every=atoi(GAsettings.m_report_every);

	if (strcmp(GAsettings.m_generation_model,"Hill Climbing")==0 ||
			strcmp(GAsettings.m_generation_model,"SA Hill Climbing")==0 ||
			strcmp(GAsettings.m_generation_model,"Simulated Annealing")==0 ||
			strcmp(GAsettings.m_generation_model,"Random")==0)
		pop_size=1;
	else
		pop_size=atoi(GAsettings.m_population_size);

	population pop(&test_chromo, pop_size);

	selector *breed_selector, *removal_selector;
	adaptor *rate_adaptor;
	generation_model *model;
	
	if (strcmp(GAsettings.m_generation_model,"Steady-State")==0)
	{
		// Create breed selector required
		if (strcmp(GAsettings.m_breed_selection,"Rank")==0)
		{
			#ifdef _DEBUG
				afxDump << "rank selection\n";
			#endif
			breed_selector=new rank_s(&pop);
		}
		else
			if (strcmp(GAsettings.m_breed_selection,"Tournament")==0)
			{
			#ifdef _DEBUG
				afxDump << "tournament selection\n";
			#endif
				breed_selector=new tournament_s(&pop, GAsettings.m_tournament_size);
			}
	}
	else
		breed_selector=new best_s(&pop);

	// Create Removal selector
	if (strcmp(GAsettings.m_removal_selection,"Least-Fit")==0)
	{
			#ifdef _DEBUG
		afxDump << "least-fit selection\n";
			#endif
		removal_selector=new worst_s(&pop);
	}
	else
		if (strcmp(GAsettings.m_removal_selection,"Inverted Rank")==0)
		{
			#ifdef _DEBUG
			afxDump << "inverted rank selection\n";
			#endif
			removal_selector=new worst_rank_s(&pop);
		}

	// Create best and worst selectors
	best_s best_select(&pop);
	worst_s worst_select(&pop);

	// Create Operator Rate Adaptor
	if (strcmp(GAsettings.m_operator_adaptor,"Fixed Rate")==0)
	{
			#ifdef _DEBUG
		afxDump << "Fixed Rate Adaptor\n";
			#endif
		rate_adaptor=new fixed_rate_a(*breed_selector);
	}
	else
		if (strcmp(GAsettings.m_operator_adaptor,"Adaptive Mutation")==0)
		{
			#ifdef _DEBUG
			afxDump << "Adaptive Mutation Rate Adaptor\n";
			#endif
			rate_adaptor=new adaptive_mutation_a(*breed_selector);
		}
		else
			if (strcmp(GAsettings.m_operator_adaptor,"COBRA")==0)
			{
			#ifdef _DEBUG
				afxDump << "COBRA Rate Adaptor\n";
			#endif
				rate_adaptor=new COBRA_a(*breed_selector,GAsettings.m_cobra_iterations);
			}
			else
				if (strcmp(GAsettings.m_operator_adaptor,"Random")==0)
				{
			#ifdef _DEBUG
					afxDump << "Random Rate Adaptor\n";
			#endif
					rate_adaptor=new random_a(*breed_selector);
				}


	// Give operator rate adaptor examples of the crossover operators required
	// Only add crossovers if doing a non-stochastic experiment, ie only GA
	if (GAsettings.m_generation_model=="Steady-State")
	{
		if (GAsettings.m_edge_recombination) 
			{ edge_recombination_c cross; rate_adaptor->add_crossor(cross); }
		if (GAsettings.m_order) 
			{ order_c cross; rate_adaptor->add_crossor(cross); }
		if (GAsettings.m_seg_order_based) 
			{ seg_order_c cross; rate_adaptor->add_crossor(cross); }
		if (GAsettings.m_position) 
			{ position_c cross; rate_adaptor->add_crossor(cross); }
		if (GAsettings.m_seg_position_based) 
			{ seg_position_c cross; rate_adaptor->add_crossor(cross); }
		if (GAsettings.m_half_uniform) 
			{ HUX_position_c cross; rate_adaptor->add_crossor(cross); }
		if (GAsettings.m_orientation_n_point) 
			{ n_point_c cross; cross.n_point=GAsettings.m_n_point_size; cross.copier=&gene::copy_feature_1; 
				cross.name="orient_c";  rate_adaptor->add_crossor(cross); 
				randomize_orientation=true;}
		if (GAsettings.m_heuristic_n_point) 
			{ n_point_c cross; cross.n_point=GAsettings.m_n_point_size; cross.copier=&gene::copy_feature_2; 
				cross.name="heuristic_c"; rate_adaptor->add_crossor(cross); 
				randomize_heuristic=true;}
	}

	// Give operator rate adaptor examples of the mutation operators required
	if (GAsettings.m_single_swap)
		{ swap_m mutate; rate_adaptor->add_mutator(mutate); }
	if (GAsettings.m_multi_swap) 
		{ multiple_swap_m mutate; mutate.set_swap_count(GAsettings.m_multi_swap_size); mutate.set_swap_count(2); rate_adaptor->add_mutator(mutate); }
	if (GAsettings.m_shunt) 
		{ shunt_m mutate; rate_adaptor->add_mutator(mutate); }
	if (GAsettings.m_inversion) 
		{ invert_m mutate; rate_adaptor->add_mutator(mutate); }
	if (GAsettings.m_orientation_flip) 
		{ standard_m mutate; mutate.randomizer=&gene::randomize_feature_1; 
			mutate.name="orient_flip"; mutate.set_gene_count(GAsettings.m_flip_size);
			rate_adaptor->add_mutator(mutate);
			randomize_orientation=true;}
	if (GAsettings.m_heuristic_flip) 
		{ standard_m mutate; mutate.randomizer=&gene::randomize_feature_2; 
			mutate.name="heuristic_flip"; mutate.set_gene_count(GAsettings.m_flip_size);
			rate_adaptor->add_mutator(mutate);
			randomize_heuristic=true;}

	test_bed.mutate_orientation=randomize_orientation;
	test_bed.mutate_heuristic=randomize_heuristic;


	pop.randomize();


	// Create Generational Model
	if (strcmp(GAsettings.m_generation_model,"Steady-State")==0)
	{
			#ifdef _DEBUG
		afxDump << "State-State Model\n";
			#endif
		model=new steady_state(rate_adaptor, removal_selector);
	}
	else
		if (strcmp(GAsettings.m_generation_model,"Hill Climbing")==0)
		{
			#ifdef _DEBUG
			afxDump << "Hill Climbing Model\n";
			#endif
			hc_m mutate(rate_adaptor);
			mutate.threshold=GAsettings.m_restart_threshold;
			model=new stochastic(&mutate, &pop, rate_adaptor);
		}
		else
			if (strcmp(GAsettings.m_generation_model,"SA Hill Climbing")==0)
			{
			#ifdef _DEBUG
				afxDump << "SA Hill Climbing Model\n";
			#endif
				sahc_m mutate;
				mutate.threshold=GAsettings.m_restart_threshold;
				mutate.sample_rate=GAsettings.m_neighbourhood;
				model=new stochastic(&mutate, &pop, rate_adaptor);
			}
			else
				if (strcmp(GAsettings.m_generation_model,"Simulated Annealing")==0)
				{
			#ifdef _DEBUG
					afxDump << "Simulated Annealing Model\n";
			#endif
					anneal_m mutate(rate_adaptor);
					mutate.start_temp=GAsettings.m_start_temp;
					mutate.end_temp=GAsettings.m_end_temp;
					mutate.cooling_ratio=GAsettings.m_cooling_ratio;
					model=new stochastic(&mutate, &pop, rate_adaptor);
				}
				else
					if (strcmp(GAsettings.m_generation_model,"Random")==0)
					{
				#ifdef _DEBUG
						afxDump << "Random Model\n";
				#endif
						random_m mutate;
						model=new stochastic(&mutate, &pop, rate_adaptor);
					}


	if (GAsettings.m_segment_restrictions) 
	{ 
		GLOBAL_MIN_SEGMENT_LENGTH=GAsettings.m_min_segment_length;
		GLOBAL_MAX_SEGMENT_LENGTH=GAsettings.m_max_segment_length;

		if (GLOBAL_MAX_SEGMENT_LENGTH<GLOBAL_MAX_SEGMENT_LENGTH || 
				GLOBAL_MAX_SEGMENT_LENGTH<2 || GLOBAL_MAX_SEGMENT_LENGTH>
				LDA_c::LDA_length-2)
			GLOBAL_MAX_SEGMENT_LENGTH=0;
	}
	else
		GLOBAL_MAX_SEGMENT_LENGTH=0;

	cataclysmic_m cata;
	if (randomize_heuristic || randomize_orientation)
	{
		cata.mutate_features=true;
		if (randomize_heuristic && randomize_orientation)
			cata.feature_mut.randomizer=&gene::randomize_all_features;
		else
			if (randomize_heuristic && !randomize_orientation)
				cata.feature_mut.randomizer=&gene::randomize_feature_2;
			else if (!randomize_heuristic && randomize_orientation)
				cata.feature_mut.randomizer=&gene::randomize_feature_1;
	}
	else
		cata.mutate_features=false;

	fitness_score best_fit, worst;
	candidate* best_candidate;
	sequence_size i=0;
	sequence_size duplicate_count;

	do
	{
		model->finished=false;
		bool restart_flag=model->evolve_once();
		if (model->finished==true)
			break;

		i++;
		if (i%report_every==0)
		{
			if (strcmp(GAsettings.m_generation_model,"Steady-State")==0)
				best_fit=best_select.select_candidate()->fitness();
			else
				best_fit=model->best_so_far->fitness();

			worst=worst_select.select_candidate()->fitness();

			duplicate_count=0;
			for (array_index j=0; j<pop_size; j++)
			{
				if (pop.get_candidate(j)->fitness()+GAsettings.m_similarities_index>=best_fit)
					duplicate_count++;
			}
			#ifdef _DEBUG
			if (m_detailed_output)
				afxDump << "\n" << i << "\t" << best_fit << "\t" << worst << "\t" << duplicate_count;
			#endif

			if (GAsettings.m_cataclysms_active)
			{
				if (duplicate_count>GAsettings.m_cataclysm_trigger)
				{
			#ifdef _DEBUG
				if (m_detailed_output)
					afxDump << " CM";
			#endif
					cata.global_mutate(&pop, GAsettings.m_mutation_rate);
				}
			}
			if (best_fit+0.01>=1)
				break;
		}
			#ifdef _DEBUG
		if (restart_flag && m_detailed_output)
			afxDump << "\tR";
			#endif
	}
	while (i<GAsettings.m_generation_epoch);
	model->terminate();
	worst=worst_select.select_candidate()->fitness();

	if (strcmp(GAsettings.m_generation_model, "Steady-State") == 0)
		best_candidate = best_select.select_candidate();
	else
		best_candidate=model->best_so_far;

	best_candidate->invalidate_fitness();
	best_fit=best_candidate->fitness();

	best_candidate->get_permutation_char(_permutation);
	strncpy_s(test_bed._permutation, _permutation, maxPermutatationLength);

	#ifdef _DEBUG
	afxDump << "\n" << i << "\t" << best_fit << "\t" << worst << "\n";
	afxDump << "----------------------------------------------------------\n";
			#endif
	LayoutUpdateView();

	delete breed_selector;
	delete removal_selector;
	delete rate_adaptor;
	delete model;
}


void CGADoc::OnRunGa()
{
	RunGA();
}

void CGADoc::OnExportCurrent() 
{
	char output_file[]="layout.txt";
	std::ofstream out(output_file, std::ios::out);

	static const int time_date_size = 100;
	char current_time[time_date_size];
	char current_date[time_date_size];
	_strdate_s(current_date, time_date_size);
	_strtime_s(current_time, time_date_size);

	out << "Test performed: " << current_date << " " << current_time << "\n";


	out << "Test " << tests.current+1 << " of " << 
		tests.length << "\n";
	out << "Test Description: " << tests.get_current().id <<
		") " << tests.get_current().description << "\n";

	out << "Sheet Size = " << test_bed.get_x_size() << "x" << 
	  test_bed.get_y_size() << "\n";
	out << "Number of Sheets Used = " << test_bed._ftable->sheet_count << "\n";


	out << "\nFitness Report:\n";
	array_index i = 0;
	for (i=0; i<test_bed._ftable->sheet_count; i++)
	{
		xy_size_t width=test_bed._ftable->sheet_fitness[i].x_span;
		xy_size_t height=test_bed._ftable->sheet_fitness[i].y_span;
		out << "Sheet " << i << ": Area Used = " << width << "x" << height << "\n";
	}
	out << "\nOverall Fitness Of Layout: " << test_bed._fitness << "\n";

	out << "\n\n";
	out << "Formatted Output: \n";
	out << "Col 1: S=New Sheet, -=No New Sheet\n";
	out << "Col 2: Shape ID\n";
	out << "Col 3: Rotation=0 or 90 Degrees\n";
	out << "Col 4: Shape Size: (X-size x Y-size)\n";
	out << "Col 5: Location: (X , Y)\n";
	out << "\n\n";
	for (i=0; i<LDA_c::LDA_length; i++)
		out << test_bed.layout[i];

	out.close();
}

void CGADoc::OnBatchProcess()
{
	bool result;
	const int current_setting_size = 10;
	char current_setting[10];

	const int current_time_size = 100;
	char current_time[current_time_size];

	const int current_date_size = 100;
	char current_date[current_date_size];

	CBatchDialog b;
	b.m_prefix="set";
	b.DoModal();

	for (array_index k=0; k<b.m_layout_count; k++)
	{
		int i=1;
		do
		{
			snprintf(current_setting, current_setting_size, "%s %i",b.m_prefix.GetBuffer(),i);
			i++;
			result=GAsettings.RemoteChangeSettings(current_setting);
			if (!result)
				break;
			else
			{
				for (array_index j=0; j<b.m_experiment_count; j++)
				{
					_strdate_s(current_date, current_date_size);
					_strtime_s(current_time, current_date_size);

#ifdef _DEBUG
					afxDump << "\n" << current_setting << ": no. " << j <<
						"\t" << current_date << " " << current_time << "\n";
#endif
					RunGA();
				}
			}
		}
		while (true);
		OnViewNexttest();
	}
}

void CGADoc::OnDetailedOutput() 
{
	// TODO: Add your command handler code here
	m_detailed_output=!m_detailed_output;

}

void CGADoc::OnUpdateDetailedOutput(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_detailed_output == 1 ? 1 : 0);
}

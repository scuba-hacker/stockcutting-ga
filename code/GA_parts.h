#ifndef _GA_parts_h
#define _GA_parts_h
#include "gene.h"
#include <math.h>

struct pair { array_index i; array_index j; };
void _get_segment_limits(array_index &start_point, 
												array_index &end_point,
												const array_index &length);

class selector : virtual public CObject
{
	DECLARE_DYNAMIC(selector);
	protected:
		population* pool;
		sequence_size pop_size;
	
	public:
		selector(population *pop);
		virtual ~selector();
		virtual array_index select_index()=0;
		virtual candidate* select_candidate()=0;
		virtual candidate* make_child();
		virtual selector* clone()=0;
		virtual void reset_selector();
		sequence_size get_population_size();
		population* get_population();
};

class worst_s : public selector
{
	public:
		worst_s(population *pop);
		virtual ~worst_s();
		virtual array_index select_index();
		virtual candidate* select_candidate();
		virtual selector* clone();
};

class best_s : public selector
{
	public:
		best_s(population *pop);
		virtual ~best_s();
		virtual array_index select_index();
		virtual candidate* select_candidate();
		virtual selector* clone();
};

class rank_s : public selector
{
	DECLARE_DYNAMIC(rank_s);
	private:
		unsigned long *rank_wheel;
		sequence_size wheel_size;

	protected:
		fitness_pair *fitness_ranking;
		bool best_selected;
		virtual array_index look_up_index(const array_index &rank_number);
	public:
		rank_s(population *pop);
		virtual ~rank_s();
		virtual array_index select_index();
		virtual candidate* select_candidate();
		virtual selector* clone();
};

class worst_rank_s : public rank_s
{
	public:
		worst_rank_s(population *pop);
		virtual array_index look_up_index(const array_index &rank_number);
};


class tournament_s : public selector
{
	DECLARE_DYNAMIC(tournament_s);
	private:
		sequence_size pick_size;

	public:
		tournament_s(population *pop, sequence_size n=2);
		virtual ~tournament_s();
		virtual array_index select_index();
		virtual candidate* select_candidate();
		virtual selector* clone();
};

class heterogeneous_s : public selector
{
	DECLARE_DYNAMIC(heterogeneous_s);
	private:
		sequence_size min_distance;
		sequence_size stagnate_iteration;
		array_index parent1_index;
		candidate* parent1;
	
	public:
		heterogeneous_s(population *pop, sequence_size min_d=1, 
										sequence_size iteration=50);
		virtual ~heterogeneous_s();
		virtual array_index select_index();
		virtual candidate* select_candidate();
		virtual selector* clone();
		virtual void reset_selector();
};

class crossover : public CObject
{
	DECLARE_DYNAMIC(crossover);
		CString name;
		virtual ~crossover();
		virtual void cross(candidate *p1, candidate *p2, candidate *c)=0;
		virtual crossover* clone()=0;
};

class order_c : public crossover
{
	DECLARE_DYNAMIC(order_c);
	private:
		virtual void generate_index_mask(const array_index &chromo_length, 
																	const array_index &mask_word_length, 
																	bitstream &index_mask);

	public:
		order_c();
		void cross(candidate *p1, candidate *p2, candidate *c);
		virtual crossover* clone();
};

class seg_order_c : public order_c
{
	DECLARE_DYNAMIC(seg_order_c);
	private:
		virtual void generate_index_mask(const array_index &chromo_length, 
																	const array_index &mask_word_length, 
																	bitstream &index_mask);

	public:
		seg_order_c();
		virtual crossover* clone();	
};


class position_c : public crossover
{
	DECLARE_DYNAMIC(position_c);
	public:
		position_c();
		void cross(candidate *p1, candidate *p2, candidate *c);
		virtual crossover* clone();
};

class HUX_position_c : public crossover
{
	DECLARE_DYNAMIC(HUX_position_c);
	private:
		virtual void get_segment_limits(array_index &start_point, 
																		array_index &end_point,
																		const array_index &length);

	public:
		HUX_position_c();
		void cross(candidate *p1, candidate *p2, candidate *c);
		virtual crossover* clone();
};

class seg_position_c : public HUX_position_c
{
	DECLARE_DYNAMIC(seg_position_c);
	private:
		virtual void get_segment_limits(array_index &start_point, 
																		array_index &end_point,
																		const array_index &length);

	public:
		seg_position_c();
		virtual crossover* clone();
};

class n_point_c : public crossover
{
	DECLARE_DYNAMIC(n_point_c);
	public:
		sequence_size n_point;
		void (gene::*copier)(gene *source);

		n_point_c();
		void cross(candidate *p1, candidate *p2, candidate *c);
		virtual crossover* clone();
};

class mutation : public CObject
{
	DECLARE_DYNAMIC(mutation);
	protected:
		bool in_situ_mutation;

	public:
		bool finished;
		bool restart_flag;
		CString name;
		mutation();
		virtual ~mutation();
		virtual void mutate(candidate *p, candidate *c)=0;
		virtual mutation* clone()=0;
		void set_in_situ_mutation(const bool &new_val);
		virtual void reset_mutator();
};

class standard_m : public mutation
{
	DECLARE_DYNAMIC(standard_m);
	private:
		sequence_size gene_count;

	public:
		void (gene::*randomizer)();
		standard_m();
		void mutate(candidate *p, candidate *c);
		virtual mutation* clone();
		void set_gene_count(const sequence_size &new_count);
};

class swap_m : public mutation
{
	DECLARE_DYNAMIC(swap_m);
	public:
		swap_m();
		void mutate(candidate *p, candidate *c);
		void mutate_choice(candidate *p, candidate *c, pair choice);
		virtual mutation* clone();
};

class multiple_swap_m : public mutation
{
	private:
		sequence_size swap_count;

	DECLARE_DYNAMIC(multiple_swap_m);
	public:
		multiple_swap_m();
		void mutate(candidate *p, candidate *c);
		virtual mutation* clone();
		void set_swap_count(const sequence_size &new_count);
};

class invert_m : public mutation
{
	DECLARE_DYNAMIC(invert_m);
	public:
		invert_m();
		void mutate(candidate *p, candidate *c);
		virtual mutation* clone();
};

class shunt_m : public mutation
{
	DECLARE_DYNAMIC(shunt_m);
	public:
		shunt_m();
		void mutate(candidate *p, candidate *c);
		virtual mutation* clone();
};

class cataclysmic_m : public mutation
{
	DECLARE_DYNAMIC(cataclysmic_m);
	private:
		multiple_swap_m swapper;

	public:
		bool mutate_features;
		standard_m feature_mut;

		cataclysmic_m();
		void mutate(candidate *p, candidate *c);
		void global_mutate(population *pool, double percentage_change);
		virtual mutation* clone();
};

class adaptor;

class hc_m : public mutation
{
	DECLARE_DYNAMIC(hc_m);
	private:
		adaptor *operator_adaptor;
		sequence_size iteration;
	public:
		sequence_size threshold;
		hc_m();
		hc_m(adaptor *a);
		void mutate(candidate *p, candidate *c);
		virtual mutation* clone();
};

class sahc_m : public mutation
{
	DECLARE_DYNAMIC(sahc_m);
	private:
		swap_m swapper;
		sequence_size iteration;
		pair *pairings;
		sequence_size pairs_length;
		void generate_pairs();

	public:
		double sample_rate;
		sequence_size threshold;
		sahc_m();
		virtual ~sahc_m();
		void mutate(candidate *p, candidate *c);
		virtual mutation* clone();
};

class anneal_m : public mutation
{
	DECLARE_DYNAMIC(anneal_m);
	private:
		adaptor *operator_adaptor;
	public:
		double start_temp;
		double current_temp;
		double end_temp;
		double cooling_ratio;
		anneal_m();
		anneal_m(adaptor *a);
		void mutate(candidate *p, candidate *c);
		virtual mutation* clone();
		virtual void reset_mutator();
};

class random_m : public mutation
{
	DECLARE_DYNAMIC(random_m);
	public:
		random_m();
		random_m(adaptor *a);
		void mutate(candidate *p, candidate *c);
		virtual mutation* clone();
};

class adaptor : public CObject
{
	DECLARE_DYNAMIC(adaptor);

	protected:
		crossover* cross[100];
		mutation* mut[100];
		selector* select;

		sequence_size cross_count;
		sequence_size mut_count;

	public:
		bool finished;
		adaptor();
		adaptor(selector &s);
		~adaptor();
		void add_mutator(mutation &mu);
		void add_crossor(crossover &cr);
		void set_selector(selector &s);
		population* get_population();

		virtual candidate *apply_operator()=0;
};

class COBRA_a : public adaptor
{
	DECLARE_DYNAMIC(COBRA_a);

	private:
		bool wheel_in_use;
		sequence_size *operator_wheel;
		fitness_pair  *operator_ranking;
		sequence_size wheel_size;
		sequence_size number_of_operators;
		sequence_size iteration_point;
		sequence_size current_iteration;
	
	private:
		void generate_weighted_wheel();
		status update_operator_count();
		void initialise_operator_ranking();

	public:
		COBRA_a(selector &s);
		COBRA_a(selector &s, long &iteration);
		~COBRA_a();
		virtual candidate *apply_operator();
		void set_iteration_point(sequence_size &new_point);
};

class fixed_rate_a : public adaptor
{
	DECLARE_DYNAMIC(fixed_rate_a);
	private:
		double rate;

	public:
		fixed_rate_a(selector &s);
		void set_rate(double new_rate);
		double get_rate();
		virtual candidate *apply_operator();
};

class random_a : public adaptor
{
	DECLARE_DYNAMIC(random_a);
	public:
		random_a(selector &a);
		virtual candidate *apply_operator();
};

class adaptive_mutation_a : public adaptor
{
	DECLARE_DYNAMIC(adaptive_mutation_a);
	public:
		adaptive_mutation_a(selector &s);
		virtual candidate *apply_operator();
};

class generation_model : public CObject
{
	public:
		population *pool;
		adaptor *operator_adaptor;
		selector *removal_select;
		chromosome *best_so_far;
		bool finished;

		generation_model(adaptor *adapt, selector *remover);
		virtual ~generation_model();
		virtual bool evolve_once()=0;
		virtual void terminate();
};

class steady_state : public generation_model
{
	public:
		steady_state(adaptor *a, selector *r);
		bool evolve_once();
};


class stochastic : public generation_model
{
	private:
		mutation *mut;
	public:
		bool best_active;
		stochastic(mutation *m, population *p, adaptor *a); 
		virtual ~stochastic();
		bool evolve_once();
		virtual void terminate();
};


class generational : public generation_model
{
	public:
		generational(adaptor *a, selector *r);
		bool evolve_once();
};

const array_index MAX_EDGES=4;

class allele_map : public CObject
{
	DECLARE_DYNAMIC(allele_map);
	private:
		array_index edges[MAX_EDGES];
		sequence_size edge_count;

	public:
		allele_map();
		bool add_edge(const array_index &i);
		bool remove_edge(const array_index &i);
		sequence_size get_edge_count();
		void clear();
	friend class edge_map;
};

class edge_map : public CObject
{
	DECLARE_DYNAMIC(edge_map);
	private:
		allele_map *alleles;
		array_index *chosen_alleles;
		sequence_size map_length;
	public:
		edge_map();
		virtual ~edge_map();
		void reset_all();
		void add_to_edge_map(const array_index *permute);
		void remove_allele_from_map(const array_index &allele);
		array_index choose_allele_with_fewest_edges(const array_index &allele);
		array_index get_map_length();
};

class edge_recombination_c : public crossover
{
	DECLARE_DYNAMIC(edge_recombination_c);
	private:
		edge_map map;
		array_index *p1_permutation;
		array_index *p2_permutation;
		array_index *child_permutation;

	public:
		edge_recombination_c();
		virtual ~edge_recombination_c();
		void cross(candidate *p1, candidate *p2, candidate *c);
		virtual crossover* clone();
};

#endif

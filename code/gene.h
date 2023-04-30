// Declarations for shape, coord, edge_node, placement, shape_l, shape_g_l, gene
//									chromosome, LDA_c, LDA_e, environment


#ifndef _gene_h
#define _gene_h
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <strstrea.h>
#include <math.h>

#include "define_vars.h"
#include "uulist.h"
#include "sort.h"
#include "bitstream.h"
#include "Random Number Generator\randlib.h"

#ifndef random_done
#define random_done
#define random() (ignlgi()-1)
#define	MAXRANDOM 2147483561L
#endif

void output_angle(CDumpContext& output_stream, const angle output_ang);
void str_out_angle(char *output, const angle output_ang);

class shape : virtual public CObject
{
	DECLARE_DYNAMIC(shape);
	protected:
		x_size_t x_size;
		y_size_t y_size;
		array_index id;
		bool rotation_ok;

	public:
		// ...default constructor
		shape();
		// ...parameterized constructors
		shape(const x_size_t x_value, const y_size_t y_value);
		// ...destructor
		virtual ~shape();
		// ...copy constructor
		shape(const shape &source);
		// ...overloaded = operator
		shape& operator=(const shape &source);
		// ...Overloaded comparison operators
		friend int operator==(const shape &first_shape, const shape &second_shape);
		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, const shape shape_to_output);
		friend istream& operator>>(istream& input_stream, shape& shape_to_input);

		inline y_size_t height();
		inline x_size_t width();
		inline array_index get_id();
		inline void set_id(array_index &new_id);
		bool is_rotation_ok();
		inline void prevent_rotation();

#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
#endif

};

class shape_group : virtual public CObject
{
	DECLARE_DYNAMIC(shape_group);
	public:
		sequence_size length;
		shape *shape_list;
		xy_size_t total_area;

		shape_group();
		virtual ~shape_group();
		shape_group(const shape_group &source);
		shape_group& operator=(const shape_group &source);

		shape& operator[](const array_index &i);
		friend istream& operator>>(istream& input_stream, shape_group& LDA_e_to_input);
		void set_rotation_validities(xy_size_t width, xy_size_t height);

#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
#endif

};


class coord : virtual public CObject
{
	DECLARE_DYNAMIC(coord);
	public:
		x_pos_t x_pos;
		y_pos_t y_pos;

	public:
		// ...default constructor
		coord();
		// ...parameterized constructors
		coord(const x_pos_t x_value, const y_pos_t y_value);
		// ...destructor
		virtual ~coord();
		// ...copy constructor
		coord(const coord &source);
		// ...overloaded = operator
		coord& operator=(const coord &source);
		friend coord operator+(const coord a, const coord b);	// Overloaded addition
		friend coord operator-(const coord a, const coord b);	// Overloaded subtraction
		// ...Overloaded comparison operators
		friend int operator==(const coord &first_coord, const coord &second_coord);
		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, const coord coord_to_output);
		friend istream& operator>>(istream& input_stream, coord& coord_to_input);

};

class edge_node : virtual public CObject
{
	DECLARE_DYNAMIC(edge_node);
	private:
		coord hotspot;																								// Indexing object
		y_size_t length;																							// Data object
		edge_node *next_edge_node;																		// Used to form list

	public:
		static coord undefined_index;									// Holds definition of an undefined index
		static compare (edge_node::*compare_method)(const coord &hotspot1, const coord &hotspot2);

		edge_node();																						// Default Constructor
		virtual ~edge_node();
		edge_node(const coord &new_hotspot, const y_size_t &new_length); 

		edge_node(const edge_node &source);								// Copy Constructor
		edge_node& operator=(const edge_node &source);					// Overloaded = operator
		friend int operator>(const edge_node &edge1, const edge_node &edge2);

		coord get_index();																			// Return value of index field
		status set_index(const coord new_hotspot);							// Set value of index field 
		void set_x_pos(const x_pos_t &new_x);
		void set_y_pos(const y_pos_t &new_y);
		x_pos_t get_x_pos();
		y_pos_t get_y_pos();

		void set_to_first_index();														// Return first index value
		status set_to_next_index(const coord ref);							// Return next index value
		compare compare_index(const coord &hotspot1, const coord &hotspot2);	// Compare two index objs
		compare compare_index_y(const coord &hotspot1, const coord &hotspot2);	// Compare two index objs
		compare compare_index_x(const coord &hotspot1, const coord &hotspot2);	// Compare two index objs

		y_size_t get_data();																		// Return value of data field
		status set_data(const y_size_t &new_length);							// Set value of data field
		compare compare_data(const y_size_t &length1,						// Return comparison between
												 const y_size_t &length2);						// two data objects
	
		void set_pointer_to(edge_node *p);									// Set pointer field
		edge_node* get_pointer();														// Return value of pointer field
		void print_node();																		// Print Node info
		// Overloaded output operator for name_object
		friend ostream& operator<<(ostream& output_stream, const edge_node &a);

#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
#endif

};

const sequence_size max_coord_list=200; // should be static in coord_group class
class coord_group : virtual public CObject
{
	DECLARE_DYNAMIC(coord_group);
	public:
		// static sequence_size max_coord_list;
		sequence_size length;

		coord coord_list[max_coord_list];
		coord& operator[](const array_index &i);

		coord_group();
		virtual ~coord_group();
		coord_group(const coord_group &source);

#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
#endif
};


class test_set : virtual public CObject
{
	DECLARE_DYNAMIC(test_set);
	public:
		char id[10];
		shape_group shapes;
		char description[1000];
		placement_rule rule;
		x_size_t sheet_width;
		y_size_t sheet_height;

		virtual ~test_set();
		test_set& operator=(const test_set &source);
		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, const test_set shape_l_to_output);
		friend istream& operator>>(istream& input_stream, test_set& shape_l_to_input);
};

class test_set_group : virtual public CObject
{
	DECLARE_DYNAMIC(test_set_group);
	public:
		sequence_size length;
		array_index current;
		test_set *test_list;

		test_set_group();
		virtual ~test_set_group();
		test_set_group(const test_set_group &source);

		test_set& next_current();
		test_set& prev_current();
		test_set& get_current();
		test_set& set_current(const array_index setting);

		test_set& operator[](const array_index &i);
		friend istream& operator>>(istream& input_stream, 
																test_set_group& LDA_e_to_input);
	
#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
#endif

};


class shape_l : public shape, public coord
{
	DECLARE_DYNAMIC(shape_l);
	public:
		shape_l();
		virtual ~shape_l();
		shape_l(const shape_l &source);

		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, const shape_l shape_l_to_output);
		friend istream& operator>>(istream& input_stream, shape_l& shape_l_to_input);
		y_pos_t top();
		y_pos_t bot();
		x_pos_t left();
		x_pos_t right();

#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
#endif

};

class gene : virtual public CObject
{
	DECLARE_DYNAMIC(gene);
public:
		virtual gene* clone() const = 0;
		virtual gene* create() const = 0;
		gene();
		virtual ~gene();
		virtual array_index get_id() = 0;
		virtual void copy(gene *source) = 0;
		virtual void copy_feature_1(gene *source) = 0;
		virtual void copy_feature_2(gene *source) = 0;
		virtual void copy_all_features(gene *source) = 0;
		virtual void randomize_feature_1() = 0;
		virtual void randomize_feature_2() = 0;
		virtual void randomize_all_features() = 0;

		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, const gene gene_to_output);
		friend istream& operator>>(istream& input_stream, gene& gene_to_input);
};

class shape_g_l;
class shape_g : public gene
{
	DECLARE_DYNAMIC(shape_g);
	protected:
		shape *p_piece;
		angle orientation;
		placement_rule heuristic;

	public:
		shape* get_tied_shape() const;
		void set_tied_shape(shape* new_shape);

		virtual array_index get_id();

		angle get_orientation() const;
		void set_orientation(angle new_orientation);

		placement_rule get_heuristic() const;
		void set_heuristic(const placement_rule &h);



		virtual gene* clone() const;
		virtual gene* create() const;
		virtual void copy(gene *source);
		virtual void copy_feature_1(gene *source);
		virtual void copy_feature_2(gene *source);
		virtual void copy_all_features(gene *source);
		virtual void randomize_feature_1();
		virtual void randomize_feature_2();
		virtual void randomize_all_features();


		// ...default constructor
		shape_g();
		// ...destructor
		virtual ~shape_g();
		// ...copy constructor
		shape_g(const shape_g &source);
		// ...overloaded = operator
		shape_g& operator=(const shape_g &source);
		shape_g& operator=(const shape_g_l &source);
		// ...Overloaded comparison operators
		friend int operator==(const shape_g &first_shape_g, const shape_g &second_shape_g);
		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, const shape_g shape_g_to_output);
		friend ostream& operator<<(ostream& output_stream, const shape_g *shape_g_to_output);
		friend istream& operator>>(istream& input_stream, shape_g& shape_g_to_input);

		y_size_t height();
		x_size_t width();
};




class shape_g_l : public shape_g, public coord
{
	DECLARE_DYNAMIC(shape_g_l);
	public:
		shape_g_l();
		shape_g_l(shape_g &source);
		shape_g_l(shape_g &source_shape_g, coord &source_coord);
		// ...destructor
		virtual ~shape_g_l();
		// ...copy constructor
		shape_g_l(const shape_g_l &source);

		// ...overloaded = operator
		shape_g_l& operator=(const shape_g_l &source);
		shape_g_l& operator=(const shape_g &source);
		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, shape_g_l &s);
		friend istream& operator>>(istream& input_stream, shape_g_l& shape_g_l_to_input);

		y_pos_t top();
		y_pos_t bot();
		x_pos_t left();
		x_pos_t right();


#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc );
#endif

};

class environment : virtual public CObject
{
	public:
		virtual ~environment();

};

class chromosome : virtual public CObject
{
	DECLARE_DYNAMIC(chromosome);

protected:
		gene** sequence;
		void generate_place_holders(const sequence_size &length);
		bool fitness_valid;

public:
		chromosome();
		virtual ~chromosome();
		chromosome(const chromosome &source);

		virtual chromosome* clone() const = 0;
		virtual chromosome* create() const = 0;
		virtual chromosome* create_array(sequence_size sz) const = 0;
		virtual chromosome* create_loaded_array(sequence_size sz, chromosome *first_element) = 0;
		virtual void copy(chromosome* source) = 0;

		virtual int size_of() = 0;
		virtual gene*& operator[](const array_index &i);

		virtual fitness_score fitness() = 0;
		virtual void invalidate_fitness() = 0;
		virtual void init_chromosome() = 0;
		virtual void random_chromosome() = 0;
		virtual void ordered_chromosome(array_index* gene_order) = 0;


		virtual void get_permutation(array_index* test) = 0;
		virtual void get_permutation_char(char* test) = 0;
		virtual sequence_size get_length() = 0;
		virtual sequence_size distance(chromosome &c)=0;

		// ...overloaded = operator
//		virtual chromosome& operator=(const chromosome &source);
		// ...Overloaded comparison operators
		friend int operator==(const chromosome &first_chromosome, const chromosome &second_chromosome);
		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, const chromosome chromosome_to_output);
		friend istream& operator>>(istream& input_stream, chromosome& chromosome_to_input);

};

typedef chromosome candidate;


class LDA_e;

class LDA_c : public chromosome
{
	DECLARE_DYNAMIC(LDA_c);
	private:
		fitness_score fitness_value;

	public:
		static sequence_size LDA_length;
		static LDA_e *_environment;

		LDA_c();
		virtual ~LDA_c();
		LDA_c(const LDA_c &source);

		chromosome* clone() const;
		chromosome* create() const;
		chromosome* create_loaded_array(sequence_size sz, chromosome* first_element);

		chromosome* create_array(sequence_size sz) const;
		void copy(chromosome* source);

		virtual int size_of();

		virtual gene*& operator[](const array_index &i);
		virtual fitness_score fitness();
		virtual void invalidate_fitness();
		virtual void init_chromosome();
		virtual void random_chromosome();
		virtual void ordered_chromosome(array_index* gene_order);
		virtual void get_permutation(array_index* test);
		virtual void get_permutation_char(char* test);
		virtual sequence_size get_length();
		virtual sequence_size distance(chromosome &c);


		// ...overloaded = operator
		LDA_c& operator=(const LDA_c &source);
		// ...Overloaded comparison operators
		friend int operator==(const LDA_c &first_LDA_c, const LDA_c &second_LDA_c);
		// Input and output stream operators
		friend ostream& operator<<(ostream& output_stream, const LDA_c &LDA_c_to_output);
		friend istream& operator>>(istream& input_stream, LDA_c& LDA_c_to_input);

#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
#endif
};

class layout_piece : public CObject
{
	public:
		shape_g_l piece;
		sheetflag_t new_sheet_needed;

	layout_piece()
	{	new_sheet_needed=s_NO; }
	friend ostream& operator<<(ostream& output_stream, layout_piece &l);

	#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
	#endif
};

struct area_t {xy_size_t x_span; xy_size_t y_span;};

class fitness_report
{
	public:
		array_index sheet_count;
		array_index next_index;
		area_t sheet_fitness[100];
	
		fitness_report()
		{
			sheet_count=next_index=0;
		}

		void store_fitness(area_t fit)
		{
			sheet_fitness[next_index++]=fit;
			sheet_count++;
		}

		status get_fitness(area_t &fit)
		{
			if (next_index<sheet_count)
			{
				fit=sheet_fitness[next_index++];
				return SUCCESS;
			}
			else
				return FAILURE;
		}


		void reset_index()
		{ next_index=0; }

		void reset_count()
		{ sheet_count=0; next_index=0; }

		//fitness_score overall_fitness();
};


class LDA_e : public environment
{
	DECLARE_DYNAMIC(LDA_e);

	private:
		bool master_LDA;
		array_index max_width_index;

	public:
		static array_index max_layout_items;
		layout_piece *layout;
		array_index next_index;
		char _permutation[10000];
		fitness_score _fitness;
		fitness_report *_ftable;

	protected:
		x_size_t macro_width;
		y_size_t macro_height;

		shape_group *shapes;

		virtual void clear_layout();
		void clear_layout(x_size_t macro_wide, y_size_t macro_high);

		virtual status add_to_layout(shape_g &item);

		virtual area_t sheet_usage();
		virtual fitness_score overall_usage1();
		void fitness_r(LDA_c &LDA_test, const array_index &offset=0);

	public:
		bool mutate_orientation;
		bool mutate_heuristic;
		virtual ~LDA_e();
		LDA_e(x_size_t macro_wide, y_size_t macro_high, layout_piece *lay,
					fitness_report *table);
		LDA_e(x_size_t macro_wide, y_size_t macro_high);
		LDA_e();

		virtual LDA_e* create(x_size_t macro_wide, y_size_t macro_high, 
													layout_piece *lay, fitness_report *table) const;

		void set_size(x_size_t macro_wide, y_size_t macro_high);
		x_size_t get_x_size();
		y_size_t get_y_size();
		fitness_score fitness(LDA_c &LDA_test);
		void init_chromosome(LDA_c &LDA_test);
		void random_chromosome(LDA_c &LDA_test);
		void ordered_chromosome(LDA_c &LDA_test, array_index* gene_order);

		void get_permutation(LDA_c &to_analyse, array_index* test);
		void get_permutation_char(LDA_c &to_analyse, char* test);

		void provide_shapes(shape_group *shape_list);
		friend ostream& operator<<(ostream& output_stream, LDA_e &a);
		virtual void set_rule_regime(const placement_rule &rule);
		virtual placement_rule get_rule_regime();
		virtual placement_rule get_current_rule();
		virtual void process_current_rule(shape_g &item);

};


class LDA_new : public LDA_e
{
	DECLARE_DYNAMIC(LDA_new);

	private:
		coord_group left_places;
		ulist<edge_node> left_profile;

		coord_group top_places;
		ulist<edge_node> top_profile;

		placement_rule current_rule;
		placement_rule rule_regime;

		status build_left_profile_places(shape_g &item);
		coord choose_leftmost_place(const status &left_list_valid,
																const status &top_list_valid);
		coord choose_ileftmost_place(const status &left_list_valid,
												 						const status &top_list_valid);

		void add_shape_at_place_6(shape_g_l &chosen_gene, const profile_t adjust_profile);

		status build_top_profile_places(shape_g &item);
		coord choose_topmost_place(const status &top_list_valid,
															 const status &left_list_valid);
		coord choose_itopmost_place(const status &top_list_valid,
															 const status &left_list_valid);

		virtual status add_to_layout(shape_g &item);
		
		virtual void clear_layout();
		void flip_placement_rule();
		void restore_current_rule();

		virtual area_t sheet_usage();
		virtual fitness_score overall_usage1();

	public:
		virtual ~LDA_new();
		LDA_new(x_size_t macro_wide, y_size_t macro_high);
		LDA_new(x_size_t macro_wide, y_size_t macro_high, layout_piece *lay,
						fitness_report *table);
		LDA_new();

		virtual LDA_e* create(x_size_t macro_wide, y_size_t macro_high, 
													layout_piece *lay, fitness_report *table) const;

		virtual void set_rule_regime(const placement_rule &rule);
		virtual placement_rule get_rule_regime();
		virtual placement_rule get_current_rule();
		virtual void process_current_rule(shape_g &item);
		friend ostream& operator<<(ostream& output_stream, LDA_new &a);
};

class population : virtual public CObject
{
	public:
		int candidate_size;
		sequence_size size;
		candidate *sequence;

		population();
		population(candidate *type, array_index size);
		virtual ~population();
		population(const population &source);
	
		candidate* get_candidate(const array_index &i);
		candidate* new_candidate();
		void replace_candidate(array_index removal, candidate *new_candidate);

		void randomize();
		void standardize();

		friend ostream& operator<<(ostream& output_stream, const population &a);

};



void permutation(sequence_size length, sequence_size permut_length,
									array_index *order);

status check_permutation(sequence_size length, array_index* test);
void seed_random();
void seed_random_new();




#endif

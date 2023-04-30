#include "stdafx.h"
#include "gene.h"
#include "sort.h"

IMPLEMENT_DYNAMIC(shape , CObject);
IMPLEMENT_DYNAMIC(shape_g , CObject);
IMPLEMENT_DYNAMIC(shape_g_l , CObject);
IMPLEMENT_DYNAMIC(shape_l, CObject);
IMPLEMENT_DYNAMIC(shape_group, CObject);
IMPLEMENT_DYNAMIC(test_set, CObject);
IMPLEMENT_DYNAMIC(test_set_group, CObject);


IMPLEMENT_DYNAMIC(coord , CObject);
IMPLEMENT_DYNAMIC(edge_node , CObject);
IMPLEMENT_DYNAMIC(coord_group, CObject);
IMPLEMENT_DYNAMIC(gene , CObject);
IMPLEMENT_DYNAMIC(chromosome , CObject);
IMPLEMENT_DYNAMIC(LDA_c , CObject);
IMPLEMENT_DYNAMIC(LDA_e , CObject);
IMPLEMENT_DYNAMIC(LDA_new , CObject);


ostream& operator<<(ostream& output_stream, layout_piece &l)
{
	char sheet_label;
	if (l.new_sheet_needed)
		sheet_label='S';
	else
		sheet_label='-';

	output_stream << sheet_label << " " << l.piece;

	return output_stream;
}

#ifdef _DEBUG
void layout_piece::Dump( CDumpContext& dc ) const
{
    // call base class function first // CObject::Dump( dc );
	//CObject::Dump( dc );
	char sheet_label;
	if (new_sheet_needed)
		sheet_label='S';
	else
		sheet_label='-';

	dc << sheet_label << " " << piece;
}
#endif


ostream& operator<<(ostream& output_stream, shape_g_l &s)
{

	int rotation;
	if (s.get_orientation()==_0_degrees)
		rotation=0;
	else
		rotation=90;
	output_stream << "ID=" << s.get_id()<< "\tR=" << rotation <<
	"D\t" << s.width() << "x" << s.height() << "\t(" << s.left() << 
	"," << s.top() << ")\n";

	return output_stream;
}

#ifdef _DEBUG
void shape_g_l::Dump( CDumpContext& dc ) 
{
    // call base class function first // CObject::Dump( dc );
//	CObject::Dump( dc );
	int rotation;
	if (get_orientation()==_0_degrees)
		rotation=0;
	else
		rotation=90;
	dc << "ID=" << get_id() << "\tR=" << rotation <<
	"D\t" << width() << "x" << height() << "\t(" << left() << 
	"," << top() << ")\n";
}
#endif

coord_group::coord_group()
{
	length=0;
}

coord_group::~coord_group()
{
}

coord_group::coord_group(const coord_group &source)
{
	length=source.length;
	for (array_index i=0; i<length; i++)
		coord_list[i]=source.coord_list[i];
}

coord& coord_group::operator[](const array_index &i)
{

	try
	{
		if (i>=max_coord_list)
			throw 1;
	}
	catch (int catch_val)
	{
		switch (catch_val)
		{

			case 1:
			#ifdef _DEBUG
				afxDump << "EXCEPTION: coord_group array bounds exceeded\n";
				afxDump << "max coord items in group is " << max_coord_list << "\n";
				afxDump << "called using index of: " << i << "\n";
			#endif
				break;

			default:
				break;
		}

		return coord_list[0];
	}
	
	return coord_list[i];
}


#ifdef _DEBUG
void coord_group::Dump( CDumpContext& dc ) const
{
    // call base class function first
		CObject::Dump( dc );
}
#endif

void output_angle(CDumpContext& output_stream, const angle output_ang)
{
	switch (output_ang)
	{
		case _0_degrees: output_stream << "0d"; break;
		case _90_degrees: output_stream << "90d"; break;
		default: output_stream << "invalid angle"; break;
	}
}

void str_out_angle(char *output, const angle output_ang)
{
	switch (output_ang)
	{
		case _0_degrees: strcpy(output,"0d"); break;
		case _90_degrees: strcpy(output,"90d"); break;
		default: strcpy(output,"bad"); break;
	}
}

istream& operator>>(istream& input_stream, angle &input_angle)
{
	char first_char;
	input_stream >> first_char;
	switch (first_char)
	{
		case 0: input_angle=_0_degrees; return input_stream >> first_char;
		case 9: input_angle=_90_degrees; return input_stream >> first_char >> first_char;
		default: return input_stream;
	}
}

compare (edge_node::*edge_node::compare_method)(const coord &hotspot1, const coord &hotspot2)=&edge_node::compare_index_y;

edge_node::edge_node() : next_edge_node(NULL), hotspot(edge_node::undefined_index), length(0)
{}

edge_node::edge_node(const coord &new_hotspot, const y_size_t &new_length) : 
	next_edge_node(NULL), hotspot(new_hotspot), length(new_length)
{}

edge_node::edge_node(const edge_node &source) : next_edge_node(source.next_edge_node),
	hotspot(source.hotspot), length(source.length)
{}

edge_node::~edge_node()
{
}


edge_node& edge_node::operator=(const edge_node &source)
{	
	next_edge_node=source.next_edge_node;
	hotspot=source.hotspot;
	length=source.length;
	return *this; 
}

coord edge_node::get_index()
{ return hotspot; }	

status edge_node::set_index(const coord new_hotspot)
{ 
	hotspot=new_hotspot;
	return SUCCESS;
}

void edge_node::set_x_pos(const x_pos_t &new_x)
{	hotspot.x_pos=new_x;}

void edge_node::set_y_pos(const y_pos_t &new_y)
{	hotspot.y_pos=new_y;}

x_pos_t edge_node::get_x_pos()
{	return hotspot.x_pos; }

y_pos_t edge_node::get_y_pos()
{ return hotspot.y_pos; }

void edge_node::set_to_first_index()
{	
	hotspot.x_pos=0;
	hotspot.y_pos=0; 
}

status edge_node::set_to_next_index(const coord ref)
{	return SUCCESS;}

compare edge_node::compare_index(const coord &hotspot1, const coord &hotspot2)
{
	return (this->*compare_method)(hotspot1, hotspot2);
}

compare edge_node::compare_index_y(const coord &hotspot1, const coord &hotspot2)
{
	if (hotspot1.y_pos>hotspot2.y_pos)
		return LARGER;
	else
		if (hotspot1.y_pos==hotspot2.y_pos)
			return EQUAL;
		else
			return SMALLER;
}

compare edge_node::compare_index_x(const coord &hotspot1, const coord &hotspot2)
{
	if (hotspot1.x_pos>hotspot2.x_pos)
		return LARGER;
	else
		if (hotspot1.x_pos==hotspot2.x_pos)
			return EQUAL;
		else
			return SMALLER;
}


int operator>(const edge_node &edge1, const edge_node &edge2)
{	
	return (edge1.hotspot.x_pos>edge2.hotspot.x_pos);
}


y_size_t edge_node::get_data()
{ return length; }	

status edge_node::set_data(const y_size_t &new_length)
{	
	length=new_length;
	return SUCCESS; 
}

compare edge_node::compare_data(const y_size_t &length1, const y_size_t &length2)
{
	if (length1>length2)
		return LARGER;
	else
		if (length1==length2)
			return EQUAL;
		else
			return SMALLER;
}

void edge_node::set_pointer_to(edge_node *p)
{
	next_edge_node=p;
}

edge_node* edge_node::get_pointer()	
{ return next_edge_node; }
	
// Define method for outputting name_object contents on standard output
void edge_node::print_node()	
{	cout << hotspot << ' ' << length; }

// Define overloaded output operator for edge_node
ostream& operator<<(ostream& output_stream, const edge_node &a)
{
	output_stream << a.hotspot << ' ' << a.length;
	return output_stream;
}

#ifdef _DEBUG
void edge_node::Dump( CDumpContext& dc ) const
{
    // call base class function first
		CObject::Dump( dc );
		dc << hotspot << " length=" << (int)length << ";";
}
#endif


// Define undefined index as 0,0
coord edge_node::undefined_index(0,0);

shape::shape()
{
	x_size=y_size=id=0;
	rotation_ok=true;
}

shape::shape(const x_size_t x_value, const y_size_t y_value)
{ 
	x_size=x_value;
	y_size=y_value;
	id=0;
	rotation_ok=true;
}

shape::shape(const shape &source)
{	
	x_size=source.x_size; 
	y_size=source.y_size;
	id=source.id;
	rotation_ok=source.rotation_ok;
}

shape::~shape()
{ // do nothing as no memory to do.
}

shape& shape::operator=(const shape &source)
{	
	x_size=source.x_size;	y_size=source.y_size; id=source.id;
	rotation_ok=source.rotation_ok;
	return *this;
}

y_size_t shape::height()
{ return y_size; }
x_size_t shape::width()
{ return x_size; }
array_index shape::get_id() { return id; }
void shape::set_id(array_index &new_id) { id=new_id; }
void shape::prevent_rotation()
{	rotation_ok=false;}
bool shape::is_rotation_ok()
{ return rotation_ok;}


ostream& operator<<(ostream& output_stream, const shape output_shape)
{
	return output_stream << output_shape.x_size << ", " << output_shape.y_size << ";";
}

istream& operator>>(istream& input_stream, shape& input_shape)
{
	return input_stream >> input_shape.x_size >> input_shape.y_size;
}

#ifdef _DEBUG
void shape::Dump( CDumpContext& dc ) const
{
    // call base class function first
		CObject::Dump( dc );
		dc << (int)x_size << ", " << (int)y_size << ";";
}
#endif



int operator==(const shape &shape1, const shape &shape2)
{	return (shape1.x_size==shape2.x_size && shape1.y_size==shape2.y_size
					&& shape1.id==shape2.id); }

shape_l::shape_l()
{
}

shape_l::~shape_l()
{
}

shape_l::shape_l(const shape_l &source)
{
}

y_pos_t shape_l::top()
{ return y_pos; }

y_pos_t shape_l::bot()
{ return y_pos+y_size; }

x_pos_t shape_l::left()
{ return x_pos; }

x_pos_t shape_l::right()
{ return x_pos+x_size; }

#ifdef _DEBUG
void shape_l::Dump( CDumpContext& dc ) const
{
    // call base class function first
		CObject::Dump( dc );
		dc << "(" << (int)x_pos << ", " << (int)y_pos << "): ";
		dc << (int)x_size << ", " << (int)y_size << ";";
}
#endif

ostream& operator<<(ostream& output_stream, const shape_l output_shape_l)
{
	return output_stream << "(" << output_shape_l.x_pos << ", " << output_shape_l.y_pos << "):" <<
													output_shape_l.x_size << ", " << output_shape_l.y_size << ";";
}

istream& operator>>(istream& input_stream, shape_l& input_shape_l)
{
	return input_stream >> "(" >> input_shape_l.x_pos >> ", " >> input_shape_l.y_pos >> "):" >>
													input_shape_l.x_size >> "," >> input_shape_l.y_size >> ";";
}

coord::coord()
{
	x_pos=y_pos=0;
}

coord::coord(const x_pos_t x_value, const y_pos_t y_value)
{ 
	x_pos=x_value;
	y_pos=y_value;
}

coord::coord(const coord &source)
{	
	x_pos=source.x_pos; 
	y_pos=source.y_pos;
}

coord::~coord()
{ // do nothing as no memory to do.
}

coord& coord::operator=(const coord &source)
{	
	x_pos=source.x_pos;	y_pos=source.y_pos;
	return *this;
}

coord operator+(const coord a, const coord b)
{	return coord(a.x_pos+b.x_pos, a.y_pos+b.y_pos);}

coord operator-(const coord a, const coord b)
{	return coord(a.x_pos-b.x_pos, a.y_pos-b.y_pos); }


ostream& operator<<(ostream& output_stream, const coord output_coord)
{
	return output_stream << "(" << output_coord.x_pos << ", " << output_coord.y_pos << "):";
}

istream& operator>>(istream& input_stream, coord& input_coord)
{
	return input_stream >> "(" >> input_coord.x_pos >> ", " >> input_coord.y_pos >> "):";
}

int operator==(const coord &coord1, const coord &coord2)
{	return (coord1.x_pos==coord2.x_pos && coord1.y_pos==coord2.y_pos); }



gene::gene()
{
}

gene::~gene()
{
}

shape_g::shape_g()
{	p_piece=NULL;	orientation=_0_degrees; heuristic=LEFTMOST/*(placement_rule)(random() % 4)*/;
}

 shape_g::shape_g(const shape_g &source)
{	p_piece=source.p_piece; orientation=source.orientation; heuristic=source.heuristic;}

shape_g::~shape_g()
{ // do nothing as no memory to do.
}

shape_g& shape_g::operator=(const shape_g &source)
{	p_piece=source.p_piece;	orientation=source.orientation; heuristic=source.heuristic;
	return *this;
}

shape_g& shape_g::operator=(const shape_g_l &source)
{	p_piece=source.p_piece;	orientation=source.orientation; heuristic=source.heuristic;
	return *this;
}

y_size_t shape_g::height()
{
	if (p_piece==NULL)
		return 0;

	switch (orientation)
	{
		case _0_degrees:
			return p_piece->height();
		case _90_degrees:
			return p_piece->width();
		default:
			return 0;
	}
}

x_size_t shape_g::width()
{
	if (p_piece==NULL)
		return 0;

	switch (orientation)
	{
		case _0_degrees:
			return p_piece->width();
		case _90_degrees:
			return p_piece->height();
		default:
			return 0;
	}	
}

shape* shape_g::get_tied_shape() const
{
	return p_piece;
}

angle shape_g::get_orientation() const
{
	return orientation;
}

void shape_g::set_tied_shape(shape* new_shape)
{
	p_piece=new_shape;
}

void shape_g::set_orientation(angle new_orientation)
{
	orientation=new_orientation;
}

array_index shape_g::get_id()
{ return p_piece->get_id(); }

placement_rule shape_g::get_heuristic() const
{
	return heuristic;
}

void shape_g::set_heuristic(const placement_rule &h)
{
	switch (h)
	{
		case LEFTMOST:
		case ILEFTMOST:
		case TOPMOST:
		case ITOPMOST:
			heuristic=h;
			break;

		case FLIP_LEFT:
		case FLIP_TOP:
		case DYNAMIC:
			// invalid heuristic
			#ifdef _DEBUG
			afxDump << "invalid heuristic\n";
			#endif
			break;
			
		default:
			break;
	}
}


ostream& operator<<(ostream& output_stream, const shape_g output_shape_g)
{
	if (output_shape_g.p_piece==NULL)
		return output_stream << " *Shape_Gene contains no shape* ";
	else
		return output_stream << *output_shape_g.p_piece << output_shape_g.orientation << "  " << output_shape_g.heuristic << "  ";
}


istream& operator>>(istream& input_stream, shape_g& input_shape_g)
{
	input_stream >> *input_shape_g.p_piece >> input_shape_g.orientation;
	// note doesn't read in heuristic from stream
	return input_stream;
}

int operator==(const shape_g &shape_g1, const shape_g &shape_g2)
{	return (shape_g1.p_piece->get_id()==shape_g2.p_piece->get_id()); }


shape_g_l::shape_g_l()
{
	orientation=_0_degrees;
	heuristic=LEFTMOST;
	p_piece=NULL;
}

shape_g_l::shape_g_l(shape_g &source)
{
	p_piece=source.get_tied_shape();
	orientation=source.get_orientation();
	heuristic=source.get_heuristic();
}

shape_g_l::shape_g_l(shape_g &source_shape_g, coord &source_coord)
{
	p_piece=source_shape_g.get_tied_shape();
	orientation=source_shape_g.get_orientation();
	heuristic=source_shape_g.get_heuristic();
	x_pos=source_coord.x_pos;
	y_pos=source_coord.y_pos;
}


shape_g_l::~shape_g_l()
{

}

shape_g_l& shape_g_l::operator=(const shape_g &source)
{
	p_piece=source.get_tied_shape();
	orientation=source.get_orientation();
	heuristic=source.get_heuristic();
	return *this;
}

shape_g_l& shape_g_l::operator=(const shape_g_l &source)
{
	p_piece=source.get_tied_shape();
	orientation=source.get_orientation();
	heuristic=source.get_heuristic();
	x_pos=source.x_pos;
	y_pos=source.y_pos;
	return *this;
}

y_pos_t shape_g_l::top()
{ return y_pos; }

y_pos_t shape_g_l::bot()
{ return y_pos+height(); }

x_pos_t shape_g_l::left()
{ return x_pos; }

x_pos_t shape_g_l::right()
{ return x_pos+width(); }





shape_group::shape_group()
{
	length=total_area=0;
	shape_list=NULL;
}

shape_group::~shape_group()
{
	if (shape_list!=NULL && length!=0)
		delete[] shape_list;
}

shape_group::shape_group(const shape_group &source)
{
	length=source.length;
	total_area=source.total_area;
	shape_list=new shape[length];
	for (array_index i=0; i<length; i++)
		shape_list[i]=source.shape_list[i];
}

shape_group& shape_group::operator=(const shape_group &source)
{
	length=source.length;
	total_area=source.total_area;
	shape_list=new shape[length];
	for (array_index i=0; i<length; i++)
		shape_list[i]=source.shape_list[i];
	return *this;
}
void shape_group::set_rotation_validities(xy_size_t wide, xy_size_t high)
{
	shape* p=shape_list;
	for (array_index i=0; i<length; i++, p++)
	{
		if (p->width()>high || p->height()>wide)
			p->prevent_rotation();
	}
}


shape& shape_group::operator[](const array_index &i)
{
	return shape_list[i];
}

istream& operator>>(istream& input_stream, shape_group& shape_group_to_input)
{
	if (shape_group_to_input.shape_list!=NULL)
		delete[] shape_group_to_input.shape_list;

	shape one_shape;
	array_index i=0;
	streampos shapes_start=input_stream.tellg();
	unsigned char comma;
	while (input_stream >> one_shape && input_stream >> comma)		// Establish number of shapes in file
	{
		i++;
		if (comma!=',') break;
	}


	input_stream.clear();			// Clear error indicating eof reached
	input_stream.seekg(shapes_start);		// Reset stream pointer to start of stream

	shape_group_to_input.length=i;
	shape_group_to_input.shape_list=new shape[i];

	i=0;
	while (input_stream >> shape_group_to_input.shape_list[i] &&
				 input_stream >> comma)	// read in x then y format
	{
		i++;
		if (comma!=',') break;
	}

	shape_group_to_input.total_area=0;
	for (i=0; i<shape_group_to_input.length; i++)
	{
		shape_group_to_input.total_area+=
		shape_group_to_input.shape_list[i].width()*
		shape_group_to_input.shape_list[i].height();
		shape_group_to_input.shape_list[i].set_id(i);
	}

	return input_stream;
}

#ifdef _DEBUG
void shape_group::Dump( CDumpContext& dc ) const
{
    // call base class function first
		CObject::Dump( dc );
		dc << "Number of shapes in shape_group: " << length << "\n";
		for (array_index i=0; i<length; i++)
			dc << shape_list[i];
}
#endif



test_set::~test_set()
{

}


test_set& test_set::operator=(const test_set &source)
{	
	strcpy(id,source.id);
	shapes=source.shapes;
	rule=source.rule;
	sheet_width=source.sheet_width;
	sheet_height=source.sheet_height;
	strcpy(description,source.description);
	return *this;
}

ostream& operator<<(ostream& output_stream, const test_set shape_l_to_output)
{
	return output_stream;
}

istream& operator>>(istream& input_stream, test_set& input)
{
	if (!(input_stream >> input.id))
		return input_stream;
	if (*input.id!='\0') 
		input.id[strlen(input.id)-1]='\0';
	input_stream >> input.shapes;
	input.description[0]='\0';
	char test_word[20];
	while (input_stream >> test_word)
	{
		if (test_word[0]=='!') break;
		strcat(test_word," ");
		strcat(input.description, test_word);
	}

	char rule_digit[20];
	input_stream >> rule_digit;

	if (strcmp(rule_digit,"LEFTMOST")==0)
		input.rule=LEFTMOST;
	else
		if (strcmp(rule_digit,"ILEFTMOST")==0)
			input.rule=ILEFTMOST;
		else
			if (strcmp(rule_digit,"TOPMOST")==0)
				input.rule=TOPMOST;
			else
				if (strcmp(rule_digit,"ITOPMOST")==0)
					input.rule=ITOPMOST;
				else
					if (strcmp(rule_digit,"FLIP_LEFT")==0)
						input.rule=FLIP_LEFT;
					else
						if (strcmp(rule_digit,"FLIP_TOP")==0)
							input.rule=FLIP_TOP;
						else
							if (strcmp(rule_digit,"DYNAMIC")==0)
								input.rule=DYNAMIC;
							else
								input.rule=LEFTMOST;

	input_stream >> input.sheet_width;
	input_stream >> input.sheet_height;
	input.shapes.set_rotation_validities(input.sheet_width, input.sheet_height);
	return input_stream;
}


test_set_group::test_set_group()
{
	length=current=0;
	test_list=NULL;
}

test_set_group::~test_set_group()
{
	if (test_list!=NULL && length!=0)
		delete[] test_list;
}

test_set_group::test_set_group(const test_set_group &source)
{
	length=source.length;
	current=source.current;
	test_list=new test_set[length];
	for (array_index i=0; i<length; i++)
		test_list[i]=source.test_list[i];
}

test_set& test_set_group::next_current()
{
	if (current==length-1)
		return test_list[current];
	else
	{
		current++;
		LDA_c::LDA_length=test_list[current].shapes.length;
		return test_list[current];
	}
}

test_set& test_set_group::get_current()
{
	// this line makes sure current is always < length
	// problem arises if current is at 10, and refreshed
	// file contains only 9 tests. Sets current to last
	// test
	if (current>=length)
		current=length-1;

	LDA_c::LDA_length=test_list[current].shapes.length;
	return test_list[current];

}

test_set& test_set_group::set_current(const array_index setting)
{
	if (setting>0 && setting<=length)
		current=setting-1;

	LDA_c::LDA_length=test_list[current].shapes.length;
	return test_list[current];
}



test_set& test_set_group::prev_current()
{
	if (current==0)
		return test_list[current];
	else
	{
		current--;
		LDA_c::LDA_length=test_list[current].shapes.length;
		return test_list[current];
	}
}

test_set& test_set_group::operator[](const array_index &i)
{
	// first count number of test sets
	// count number of ! on own

	return test_list[i];
}

istream& operator>>(istream& input_stream, test_set_group& input)
{
	if (input.test_list!=NULL)
		delete[] input.test_list;

	test_set one_test_set;
	array_index count=0;
	streampos test_sets_start=input_stream.tellg();

	test_set one_test;
	while (input_stream >> one_test)			// establish number of test sets in file
		count++;

	input_stream.clear();			// Clear error indicating eof reached
	input_stream.seekg(test_sets_start);		// Reset stream pointer to start of stream

	input.length=count;
	input.test_list=new test_set[count];

	count=0;
	while (input_stream >> input.test_list[count])	// read in x then y format
		count++;

	return input_stream;
}

#ifdef _DEBUG
void test_set_group::Dump( CDumpContext& dc ) const
{
    // call base class function first
		CObject::Dump( dc );
		dc << "Number of tests in test_set_group: " << length << "\n";
		for (array_index i=0; i<length; i++)
			dc << test_list[i];
}
#endif


chromosome::chromosome()
{
	sequence=NULL;
	fitness_valid=false;
}

chromosome::~chromosome()
{
	if (sequence!=NULL)
		delete[] sequence;
}

chromosome::chromosome(const chromosome &source)
{
	sequence=NULL;
	fitness_valid=source.fitness_valid;
}

void chromosome::generate_place_holders(const sequence_size &length)
{
	sequence=new gene*[length];
}

gene*& chromosome::operator[](const array_index &i)
{
	return sequence[i];
}


LDA_c::LDA_c()
{
	generate_place_holders(LDA_length);
	for (array_index i=0; i<LDA_length; i++)
		sequence[i]=new shape_g;
	fitness_value=0;
}

LDA_c::~LDA_c()
{
	for (array_index i=0; i<LDA_length; i++)
		delete sequence[i];
}

LDA_c::LDA_c(const LDA_c &source)
{
	// copy constructor
	generate_place_holders(LDA_length);
	for (array_index i=0; i<LDA_length; i++)
		sequence[i]=source.sequence[i]->clone();
	fitness_value=source.fitness_value;
}

LDA_c& LDA_c::operator=(const LDA_c &source)
{	
	// place holders already present
	
	for (array_index i=0; i<LDA_length; i++)
	{
		delete sequence[i];
		sequence[i]=source.sequence[i]->clone();
	}
	fitness_value=source.fitness_value;
	return *this; 
}

chromosome* LDA_c::clone() const { return new LDA_c(*this); }
chromosome* LDA_c::create() const { return new LDA_c; }
chromosome* LDA_c::create_array(sequence_size sz) const 
{ return new LDA_c[sz]; }
chromosome* LDA_c::create_loaded_array(sequence_size sz,
																	chromosome* first_element)
{
	LDA_c *array=new LDA_c[sz];
	LDA_c *first=(LDA_c *)first_element;
	for (array_index i=0; i<sz; i++)
		array[i]=*(first+i);
	return array;
}

void LDA_c::copy(chromosome* source)
{
	for (array_index i=0; i<LDA_length; i++)
	{
		shape_g* target_gene_p=(shape_g *)(sequence[i]);
		shape_g* source_gene_p=(shape_g *)((*source)[i]);
		target_gene_p->copy(source_gene_p);
	}
	fitness_valid=((LDA_c*)source)->fitness_valid;
	fitness_value=((LDA_c*)source)->fitness_value;
}


int LDA_c::size_of() {	return sizeof(*this);}


gene*& LDA_c::operator[](const array_index &i)
{
	return sequence[i];
}

fitness_score LDA_c::fitness()
{	
	if (fitness_valid==false)
	{
		fitness_value=_environment->fitness(*this);
		fitness_valid=true;
	}
	else
	{
		// no need to re-evaluate fitness_value
	}

	return fitness_value;
}

void LDA_c::invalidate_fitness()
{ fitness_valid=false; }

void LDA_c::init_chromosome()
{
	_environment->init_chromosome(*this); 
 invalidate_fitness();
}

void LDA_c::random_chromosome()
{
	_environment->random_chromosome(*this);
 invalidate_fitness();
}

void LDA_c::ordered_chromosome(array_index* gene_order)
{
	_environment->ordered_chromosome(*this, gene_order);
 invalidate_fitness();
}

void LDA_c::get_permutation(array_index* test)
{ _environment->get_permutation(*this, test);}

void LDA_c::get_permutation_char(char* test)
{ _environment->get_permutation_char(*this, test);}

sequence_size LDA_c::get_length()
{ return LDA_c::LDA_length; }

sequence_size LDA_c::distance(chromosome &c)
{
	// compare *this with c1
	sequence_size d=0;
	for (array_index i=0; i<LDA_c::LDA_length; i++)
		if ((*this)[i]->get_id()!=c[i]->get_id())
			d++;
	return d;
}

gene* shape_g::clone() const { return new shape_g(*this); }
gene* shape_g::create() const { return new shape_g; }
void shape_g::copy(gene *source)
{
	shape_g *temp=(shape_g *)source;
	p_piece=temp->p_piece;
	orientation=temp->orientation;
	heuristic=temp->heuristic;
}
void shape_g::copy_feature_1(gene *source)
{	
	if (p_piece==NULL || p_piece->is_rotation_ok())
		orientation=((shape_g *)source)->orientation;
	else
		orientation=_0_degrees;
}
void shape_g::copy_feature_2(gene *source)
{	heuristic=((shape_g *)source)->heuristic; }

void shape_g::copy_all_features(gene *source)
{
	orientation=((shape_g *)source)->orientation;
	heuristic=((shape_g *)source)->heuristic;
}

void shape_g::randomize_feature_1()
{
	if (p_piece->is_rotation_ok())
	{
		if (random()%2==0)
			orientation=_0_degrees;
		else
			orientation=_90_degrees;
	}
	else
		orientation=_0_degrees;
}

void shape_g::randomize_feature_2()
{
	array_index choice=random()%4;
	switch (choice)
	{
		case 0:
			heuristic=LEFTMOST;
			break;

		case 1:
			heuristic=ILEFTMOST;
			break;

		case 2:
			heuristic=TOPMOST;
			break;

		case 3:
			heuristic=ITOPMOST;
			break;

		default:
			break;
	}
}

void shape_g::randomize_all_features()
{
	randomize_feature_1();
	randomize_feature_2();
}



sequence_size LDA_c::LDA_length=3;
LDA_e* LDA_c::_environment=NULL;

ostream& operator<<(ostream& output_stream, const LDA_c &LDA_c_to_output)
{
	for (array_index i=0; i<LDA_c::LDA_length; i++)
		output_stream << LDA_c_to_output.sequence[i];
	return output_stream;
}


#ifdef _DEBUG
void LDA_c::Dump( CDumpContext& dc ) const
{
    // call base class function first // CObject::Dump( dc );
		CObject::Dump( dc );

    // now do the stuff for our specific class
	for (array_index i=0; i<LDA_c::LDA_length; i++)
		dc << *(sequence[i]);
}
#endif

environment::~environment()
{

}

array_index LDA_e::max_layout_items=200;


LDA_e::LDA_e()
{
	layout=new layout_piece[max_layout_items];
	_ftable=new fitness_report;
	master_LDA=true;
	_permutation[0]='\0';
	_fitness=0;
	mutate_orientation=false;
	mutate_heuristic=false;
	macro_width=macro_height=0;
	clear_layout();
}

LDA_e::LDA_e(x_size_t macro_wide, y_size_t macro_high) : 
  macro_width(macro_wide), macro_height(macro_high)
{
	layout=new layout_piece[max_layout_items];
	_ftable=new fitness_report;
	master_LDA=true;
	_permutation[0]='\0';
	_fitness=0;
	clear_layout();
}

LDA_e::LDA_e(x_size_t macro_wide, y_size_t macro_high, layout_piece *lay,
	fitness_report *table) : 
  macro_width(macro_wide), macro_height(macro_high), layout(lay), _ftable(table)
{
	master_LDA=false;
	_permutation[0]='\0';
	_fitness=0;
	clear_layout();
}



LDA_e::~LDA_e()
{
	if (master_LDA)
	{
		delete[] layout;
		delete[] _ftable;
	}
}

LDA_e* LDA_e::create(x_size_t macro_wide, y_size_t macro_high, layout_piece *lay,
										fitness_report *table) const
{ return new LDA_e(macro_wide, macro_high, lay, table); }

void LDA_e::clear_layout()
{
	next_index=0;
}

void LDA_e::clear_layout(x_size_t macro_wide, y_size_t macro_high)
{
	clear_layout();
	macro_width=macro_wide;
	macro_height=macro_high;
}

void LDA_e::provide_shapes(shape_group *shape_list)
{
	shapes=shape_list;
}

status LDA_e::add_to_layout(shape_g &item)
{
	// place shape_g into shape_g_l object
  layout[next_index].piece=item;
	if (next_index==0)
	{
		if (item.height()<=macro_height)
		{			
			// don't update coords in layout[0] as first shape is placed at (0,0)
			max_width_index=0;
		}
		else
		{
			cout << "First piece to high to fit on macrosheet\n";
			return FAILURE;
		}
	}
	else
		// now determine y coord for this item - can it fit?
		if (layout[next_index-1].piece.bot()+item.height()<=macro_height)
		{
			// can fit so add at x in line with previous, and below previous
			layout[next_index].piece.x_pos=layout[next_index-1].piece.left();
			layout[next_index].piece.y_pos=layout[next_index-1].piece.bot();
			if (layout[next_index].piece.right()>layout[max_width_index].piece.right())
				max_width_index=next_index;
		}
		else
		{
			// can't fit so make new column, increase x to max value of previous column
			if (layout[max_width_index].piece.right()+item.width() > macro_width)
				return FAILURE; // shape to wide too fit in a new column in macro_sheet
			else
			{
				layout[next_index].piece.x_pos=layout[max_width_index].piece.right();
				layout[next_index].piece.y_pos=0;												// Start new column at top
				max_width_index=next_index;
			}
		}
	next_index++;
	return SUCCESS;
}

void LDA_e::set_size(x_size_t macro_wide, y_size_t macro_high)
{
	macro_width=macro_wide;
	macro_height=macro_high;
	clear_layout();
}
x_size_t LDA_e::get_x_size()
{ return macro_width; }
y_size_t LDA_e::get_y_size()
{	return macro_height; }


void LDA_e::set_rule_regime(const placement_rule &rule)
{
}

placement_rule LDA_e::get_rule_regime()
{	return LEFTMOST; }

placement_rule LDA_e::get_current_rule()
{	return LEFTMOST; }

void LDA_e::process_current_rule(shape_g &item)
{ }


fitness_score LDA_e::fitness(LDA_c &LDA_test)
{
	fitness_r(LDA_test);
	_fitness=overall_usage1();
	return _fitness;
}

void LDA_e::fitness_r(LDA_c &LDA_test, const array_index &offset)
{
	if (offset==0)
		_ftable->reset_count();

	clear_layout();
	layout[0].new_sheet_needed=s_YES;
	for (array_index i=offset; i<LDA_c::LDA_length; i++)
	{
		if (add_to_layout(*(shape_g *)LDA_test[i])==FAILURE)
		{
			// if hasn't failed on i=0, otherwise quit
			// generate new LDA_new
			if (i>offset)
			{
				_ftable->store_fitness(sheet_usage());
				LDA_e* next=this->create(macro_width, macro_height, layout-offset+i, _ftable);
				switch (get_rule_regime())
				{
					case LEFTMOST:
					case ILEFTMOST:
					case TOPMOST:
					case ITOPMOST:
						next->set_rule_regime(get_rule_regime());
						break;

					case FLIP_LEFT:
						if (get_current_rule()==LEFTMOST)
							next->set_rule_regime(FLIP_LEFT);
						else
							next->set_rule_regime(FLIP_TOP);
						break;

					case FLIP_TOP:
						if (get_current_rule()==TOPMOST)
							next->set_rule_regime(FLIP_LEFT);
						else
							next->set_rule_regime(FLIP_TOP);
						break;

					case DYNAMIC:
						next->set_rule_regime(DYNAMIC);
						break;

					default:
						break;
				}
				next->fitness_r(LDA_test, i);

				delete next;
				return;
			}
			else
			{
			#ifdef _DEBUG
				afxDump << "Warning!!!!! shape too large to fit on a single sheet! Terminated on gene ";
				afxDump << i << ": " << *(shape_g *)LDA_test[i] << "\n";
			#endif
				return;
			}
		}
		else
			if (i>offset)
				layout[i-offset].new_sheet_needed=s_NO;
	}
	_ftable->store_fitness(sheet_usage());
}



area_t LDA_e::sheet_usage()
{	area_t a; return a; }


fitness_score LDA_e::overall_usage1()
{	return 1.0; }

void LDA_e::init_chromosome(LDA_c &LDA_test)
{
	// set up LDA_test to be same order as shapes_list array
	for (array_index i=0; i<LDA_c::LDA_length; i++)
		((shape_g *)(LDA_test[i]))->set_tied_shape(&(*shapes)[i]);
}

void LDA_e::ordered_chromosome(LDA_c &LDA_test, 
					array_index* gene_order)
{
	// set up LDA_test to be same order as shapes_list array
	for (array_index i=0; i<LDA_c::LDA_length; i++)
		((shape_g *)(LDA_test[i]))->set_tied_shape(&(*shapes)[gene_order[i]]);
}

void LDA_e::random_chromosome(LDA_c &LDA_test)
{
	array_index* order=new array_index[LDA_c::LDA_length];

	permutation(LDA_c::LDA_length, LDA_c::LDA_length, order);

	for (array_index i=0; i<LDA_c::LDA_length; i++)
	{
		((shape_g *)(LDA_test[i]))->set_tied_shape(&(*shapes)[order[i]]);
		if (mutate_orientation)
			if (mutate_heuristic)
				((shape_g *)(LDA_test[i]))->randomize_all_features();
			else				
				((shape_g *)(LDA_test[i]))->randomize_feature_1();
		else
			if (mutate_heuristic)
				((shape_g *)(LDA_test[i]))->randomize_feature_2();
	}
	delete[] order;
}


void seed_random()
{
	// Seed random number generator with millisecond time
  struct _timeb timebuffer;
   _ftime( &timebuffer );
	unsigned int milli=(unsigned int)((float)timebuffer.millitm*float(65.536));	// map to unsigned int 4 byte range
  srand(milli);
}

void seed_random_new()
{
	// Seed random number generator with millisecond time
  struct _timeb timebuffer;
   _ftime( &timebuffer );
	unsigned int milli=(unsigned int)((float)timebuffer.millitm*float(65.356));	// map to unsigned int 4 byte range
  srand(milli);
	// generate first seed in range 1 to 2147483562
	long seed_a=(long)((double)rand()*double(32768.49868009))+1;
	// generate first seed in range 1 to 2147483398
	long seed_b=(long)((double)rand()*double(32768.49617762))+1;

	if (seed_a<0 || seed_b<0)
	{
			#ifdef _DEBUG
		afxDump << "invalid negative seed for random number generator\n";
			#endif
	}

  setall(seed_a, seed_b);
}


void permutation(sequence_size length, sequence_size permut_length,
									array_index *order)
{
	array_index* initial=new array_index[length];
	for (array_index i=0; i<length; i++)
		initial[i]=i;

	array_index random_index;

	for (i=0; i<permut_length; i++)
	{
		// Pick random index between 0 and len-i-1
		random_index=random() % (length-i);
		order[i]=initial[random_index];
		initial[random_index]=initial[length-1-i];
	}

	delete[] initial;
}



status check_permutation(sequence_size length, array_index* test)
{
	array_index* check=new array_index[length];
	for (array_index i=0; i<length; i++)
		check[i]=0;

	for (i=0; i<length; i++)		
	{
		if (test[i]<length && check[test[i]]==0)
			check[test[i]]=1;
		else
		{
			delete[] check;
			return FAILURE;
		}
	}
	delete[] check;
	return SUCCESS;
}

void LDA_e::get_permutation(LDA_c &to_analyse, array_index* test)
{
	for (array_index i=0; i<LDA_c::LDA_length; i++)
		test[i]=((shape_g *)(to_analyse[i]))->get_tied_shape()->get_id();
}

/*
void LDA_e::get_permutation(LDA_c &to_analyse, array_index* test)
{
	LDA_c standard_chromosome;
	init_chromosome(standard_chromosome);
	shape* current_shape;

	for (array_index i=0; i<LDA_c::LDA_length; i++)
	{
		current_shape=((shape_g *)(to_analyse[i]))->get_tied_shape();
		// search for current gene in standard_chromosome
		for (array_index j=0; j<LDA_c::LDA_length; j++)
		{
			if (((shape_g *)(standard_chromosome[j]))->get_tied_shape()==current_shape)
			{
				test[i]=j;
				break;
			}
		}
	}
}*/

void LDA_e::get_permutation_char(LDA_c &to_analyse, char* test)
{
	ostrstream permut_stream(test, 9999, ios::out);
	for (array_index i=0; i<LDA_c::LDA_length; i++)
	{
		permut_stream << ((shape_g *)(to_analyse[i]))->get_tied_shape()->get_id();
		if (i<LDA_c::LDA_length-1)
			permut_stream << " ";
		else
			permut_stream << '\0';
	}
}


/*
void LDA_e::get_permutation_char(LDA_c &to_analyse, char* test)
{
	LDA_c standard_chromosome;
	init_chromosome(standard_chromosome);
	shape* current_shape;

	ostrstream permut_stream(test, 9999, ios::out);

	for (array_index i=0; i<LDA_c::LDA_length; i++)
	{
		current_shape=((shape_g *)(to_analyse[i]))->get_tied_shape();
		// search for current gene in standard_chromosome
		for (array_index j=0; j<LDA_c::LDA_length; j++)
		{
			if (((shape_g *)(standard_chromosome[j]))->get_tied_shape()==current_shape)
			{
				permut_stream << j;
				break;
			}
		}
		if (i<LDA_c::LDA_length-1)
			permut_stream << " ";
		else
			permut_stream << '\0';
	}
}
*/


ostream& operator<<(ostream& output_stream, LDA_e &output)
{
	return output_stream;
}

LDA_new::LDA_new()
{
	set_rule_regime(LEFTMOST);
}
	
LDA_new::~LDA_new()
{
}

LDA_new::LDA_new(x_size_t macro_wide, y_size_t macro_high) : 
LDA_e(macro_wide,macro_high)
{
	set_rule_regime(LEFTMOST);
}

LDA_new::LDA_new(x_size_t macro_wide, y_size_t macro_high, layout_piece *lay,
								fitness_report *table) : 
LDA_e(macro_wide,macro_high,lay,table)
{
	set_rule_regime(LEFTMOST);
}

LDA_e* LDA_new::create(x_size_t macro_wide, y_size_t macro_high, layout_piece *lay,
												fitness_report *table) const
{ return new LDA_new(macro_wide, macro_high, lay, table); }

area_t LDA_new::sheet_usage()
{	
	// total shape area / left profile area: max jutting.
	pos_t max_y_jut=0, max_x_jut=0;

	edge_node *current;
	left_profile.reset_transverse();
	do
	{
		current=left_profile.get_transverse_node_pointer();
		if (current->get_index().x_pos>max_x_jut)
			max_x_jut=current->get_index().x_pos;
	}
	while (left_profile.progress_transverse()==SUCCESS);

	top_profile.reset_transverse();
	do
	{
		current=top_profile.get_transverse_node_pointer();
		if (current->get_index().y_pos>max_y_jut)
			max_y_jut=current->get_index().y_pos;
	}
	while (top_profile.progress_transverse()==SUCCESS);

	area_t result;
	result.x_span=max_x_jut;
	result.y_span=max_y_jut;
	return result;
}

fitness_score LDA_new::overall_usage1()
{
	double sheet_area=macro_width*macro_height;

	// add up all sheet areas
	_ftable->reset_index();
	xy_size_t total_area_used=0, sub_area=0;
	area_t single_area;

	sequence_size sheets_used=_ftable->sheet_count;
	while(_ftable->get_fitness(single_area)==SUCCESS)
	{
//		single_area.x_span*=1.01
		sub_area=single_area.x_span*single_area.y_span;
		total_area_used+=sub_area;
	}

	double area_quotient=(double)shapes->total_area / (double)total_area_used;
	double min_sheets=(double)shapes->total_area / (double)sheet_area;
	double actual_sheets=sheets_used-1 + (double)sub_area/(double)sheet_area;
	double penalty=1/(actual_sheets-min_sheets+1);
	
	return area_quotient*penalty;
}

// Version 2...
status LDA_new::add_to_layout(shape_g &item)
{
	process_current_rule(item);

	status left_build_status=build_left_profile_places(item);
	status top_build_status=build_top_profile_places(item);
	if (left_build_status==FAILURE && top_build_status==FAILURE)
		return FAILURE;

	coord chosen_coord;
	switch (current_rule)
	{
		case LEFTMOST:
			chosen_coord=choose_leftmost_place(left_build_status, top_build_status);
			break;
		case ILEFTMOST:
			chosen_coord=choose_ileftmost_place(left_build_status, top_build_status);
			break;
		case TOPMOST:
			chosen_coord=choose_topmost_place(top_build_status, left_build_status);
			break;
		case ITOPMOST:
			chosen_coord=choose_itopmost_place(top_build_status, left_build_status);
			break;
		default:
			break;
	}

	shape_g_l chosen_gene(item, chosen_coord);// Add shape to layout array
	layout[next_index].piece=chosen_gene;
	next_index++;

	add_shape_at_place_6(chosen_gene, MODIFY_LEFT_PROFILE);		// Add shape to left_profile profile
	add_shape_at_place_6(chosen_gene, MODIFY_TOP_PROFILE);		// Add shape to left_profile profile

	flip_placement_rule();

	return SUCCESS;
}

void LDA_new::process_current_rule(shape_g &item)
{
	if (rule_regime==DYNAMIC)
		current_rule=item.get_heuristic();
}

ostream& operator<<(ostream& output_stream, LDA_new &output)
{
	int e=1;
	edge_node current_edge;
	output.left_profile.reset_transverse();
	output_stream << "Left Profile:\n";
	do
	{
		output.left_profile.get_transverse(current_edge);
		output_stream << e++ << ") " << (int)current_edge.get_x_pos() <<
								"," << (int)current_edge.get_y_pos() <<  
								":" << (int)current_edge.get_data() << "\n";
	}
	while (output.left_profile.progress_transverse()==SUCCESS);
	output_stream << "\n\n";

	e=1;
	output.top_profile.reset_transverse();
	output_stream << "Top Profile:\n";
	do
	{
		output.top_profile.get_transverse(current_edge);
		output_stream << e++ << ") " << (int)current_edge.get_x_pos() <<
								"," << (int)current_edge.get_y_pos() <<  
								":" << (int)current_edge.get_data() << "\n";
	}
	while (output.top_profile.progress_transverse()==SUCCESS);


	output_stream << "\nPermutation:\n" << output._permutation;
	output_stream << "\n\nFitness: " << output._fitness;
	return output_stream;
}

status LDA_new::build_left_profile_places(shape_g &item)
{
	// things to remember... item.height(), item.width(), x_pos, y_pos, get_x_pos, get_y_pos,
	// set_x_pos, set_y_pos, max_x_offset_edge, max_x_offset, macro_width, macro_height

	// Clear number of left_places found to 0
	left_places.length=0;
	left_profile.reset_transverse();
	// Start edge is the edge currently being investigated
	edge_node *start_edge;

	// Outer Do Loop: Loop through all edges in the edge profile, set
	// start_edge to point to each edge in turn.
	do
	{
		// Initialise all variables. Set abut variables to first edge.
 		start_edge=left_profile.get_transverse_node_pointer();
		edge_node* abutting_edge=start_edge;
		x_size_t abutting_offset=abutting_edge->get_x_pos();
		y_size_t accumulated_length=0;
		edge_node *masked_edge;
		coord edge_hotspot;
		y_size_t edge_length;

		// Inner while loop: Loop through edges beginning with start edge, until
		// the accumulated edge length equals or exceeds height of item.
		// The new item is to be abutted to the masked_edge encountered which is 
		// rightmost in the profile, so :
		//    abutting_edge: points to edge to abutt new item to
		//		abutting_offset: how much abutting edge juts out of profile compared to start_edge
		do
		{
			// Extract data from masked_edge.
	 		masked_edge=left_profile.get_transverse_node_pointer();
			edge_hotspot=masked_edge->get_index();
			edge_length=masked_edge->get_data();

			// If masked_edge juts further to right than abutting_edge
			// update abutting_edge and abutting_offset
			if (edge_hotspot.x_pos>(x_pos_t)abutting_offset)
			{
				abutting_edge=left_profile.get_transverse_node_pointer();
				abutting_offset=edge_hotspot.x_pos;
			}
			// Add masked_edge length to accumulated edge length
			accumulated_length+=edge_length;
		}
		while (accumulated_length<item.height() && left_profile.progress_transverse()==SUCCESS);

		// now determine if item can be placed at location, given shape size
		// x_location stored in hotspot.x_pos of abutting_edge (abutting_offset)
		// y_location stored in hotspot.y_pos of start_edge (y_offset)
		// and given dimensions of the total sheet
		if (abutting_offset+item.width()<=macro_width && accumulated_length>=item.height())
		{
			// Add item to left_places list
			// Abutting_edge gives the x location, start_edge gives the y location to place item
			// left_places[left_places.length]=placement(abutting_edge, start_edge);
			left_places[left_places.length]=coord(abutting_edge->get_x_pos(),start_edge->get_y_pos());
			left_places.length++;
			if (current_rule==TOPMOST || current_rule==ITOPMOST)			// first position found is always topmost
				break;
		}

		if (start_edge->get_pointer()!=NULL)
			left_profile.set_transverse_node_pointer(start_edge->get_pointer());
		else
			break;
	}
	while (true);
	
	return (left_places.length==0 ? FAILURE : SUCCESS);
}

status LDA_new::build_top_profile_places(shape_g &item)
{
	// things to remember... item.height(), item.width(), x_pos, y_pos, get_x_pos, get_y_pos,
	// set_x_pos, set_y_pos, max_x_offset_edge, max_x_offset, macro_width, macro_height

	// Clear number of left_places found to 0
	top_places.length=0;
	top_profile.reset_transverse();
	// Start edge is the edge currently being investigated
	edge_node *start_edge;

	// Outer Do Loop: Loop through all edges in the edge profile, set
	// start_edge to point to each edge in turn.
	do
	{
		// Initialise all variables. Set abutt variables to first edge.
 		start_edge=top_profile.get_transverse_node_pointer();
		edge_node* abutting_edge=start_edge;
		y_size_t abutting_offset=abutting_edge->get_y_pos();
		x_size_t accumulated_length=0;
		edge_node *masked_edge;
		coord edge_hotspot;
		x_size_t edge_length;

		// Inner while loop: Loop through edges beginning with start edge, until
		// the accumulated edge length equals or exceeds width of item.
		// The new item is to be abutted to the masked_edge encountered which is 
		// bottom-most in the profile, so :
		//    abutting_edge: points to edge to abutt new item to
		//		abutting_offset: how much abutting edge juts out of profile compared to start_edge
		do
		{
			// Extract data from masked_edge.
	 		masked_edge=top_profile.get_transverse_node_pointer();
			edge_hotspot=masked_edge->get_index();
			edge_length=masked_edge->get_data();

			// If masked_edge juts further to bottom than abutting_edge
			// update abutting_edge and abutting_offset
			if (edge_hotspot.y_pos>(y_pos_t)abutting_offset)
			{
				abutting_edge=top_profile.get_transverse_node_pointer();
				abutting_offset=edge_hotspot.y_pos;
			}
			// Add masked_edge length to accumulated edge length
			accumulated_length+=edge_length;
		}
		while (accumulated_length<item.width() && top_profile.progress_transverse()==SUCCESS);

		// now determine if item can be placed at location, given shape size
		// x_location stored in hotspot.x_pos of abutting_edge (abutting_offset)
		// y_location stored in hotspot.y_pos of start_edge (y_offset)
		// and given dimensions of the total sheet
		if (abutting_offset+item.height()<=macro_height && accumulated_length>=item.width())
		{
			// Add item to top_places list
			// Start_edge gives the x location, abutting_edge gives the y location to place item
			//top_places[top_places.length]=placement(start_edge, abutting_edge);
			top_places[top_places.length]=coord(start_edge->get_x_pos(), abutting_edge->get_y_pos());
			top_places.length++;
			if (current_rule==LEFTMOST || current_rule==ILEFTMOST)			// first position found is always leftmost
				break;
		}

		if (start_edge->get_pointer()!=NULL)
			top_profile.set_transverse_node_pointer(start_edge->get_pointer());
		else
			break;
	}
	while (true);
	
	return (top_places.length==0 ? FAILURE : SUCCESS);
}

// Version 3...
coord LDA_new::choose_leftmost_place(const status &left_list_valid,
																			const status &top_list_valid)
{
	if (left_list_valid==SUCCESS)
	{
		// first check all items in left_places array for lefties
		coord chosen=left_places[0];
		for (array_index i=1; i<left_places.length; i++)
		{
			if (left_places[i].x_pos<chosen.x_pos)
				chosen=left_places[i];
		}
		// second check first item in top_places array for toppies
		// prefer the topmost left if on same level (reason for <= not <)
		if (top_list_valid==SUCCESS && top_places[0].x_pos<=chosen.x_pos &&
																	 top_places[0].y_pos<chosen.y_pos)
			chosen=top_places[0];
		return chosen;
	}
	else
		return top_places[0];
}

// Version 3...
coord LDA_new::choose_topmost_place(const status &top_list_valid,
												 						const status &left_list_valid)
{
	if (top_list_valid==SUCCESS)
	{
		// first check all items in left_places array for lefties
		coord chosen=top_places[0];
		for (array_index i=1; i<top_places.length; i++)
		{
			if (top_places[i].y_pos<chosen.y_pos)
				chosen=top_places[i];
		}
		// second check first item in top_places array for toppies
		// prefer the leftmost top if on same level (reason for <= not <)
		if (left_list_valid==SUCCESS && left_places[0].y_pos<=chosen.y_pos &&
																		left_places[0].x_pos<chosen.x_pos)
			chosen=left_places[0];
			
		return chosen;
	}
	else
		return left_places[0];
}

coord LDA_new::choose_itopmost_place(const status &top_list_valid,
												 						const status &left_list_valid)
{
	if (top_list_valid==SUCCESS)
	{
		coord chosen=top_places[0];

		for (array_index i=1; i<top_places.length-1; i++)
		{
			if (top_places[i].y_pos<chosen.y_pos)
				chosen=top_places[i];
		}

		// Consider the last position in top_places only if y_pos non-zero
		if (top_places.length>1 && top_places[top_places.length-1].y_pos>0 &&
				top_places[i].y_pos<chosen.y_pos)
			chosen=top_places[top_places.length-1];
		return chosen;
	}
	else
		if (left_places.length>1)
			return left_places[1];
		else
			return left_places[0];
}


coord LDA_new::choose_ileftmost_place(const status &left_list_valid,
												 						const status &top_list_valid)
{
	if (left_list_valid==SUCCESS)
	{
		coord chosen=left_places[0];

		for (array_index i=1; i<left_places.length-1; i++)
		{
			if (left_places[i].x_pos<chosen.x_pos)
				chosen=left_places[i];
		}

		// Consider the last position in left_places only if x_pos non-zero
		if (left_places.length>1 && left_places[left_places.length-1].x_pos>0 &&
				left_places[i].x_pos<chosen.x_pos)
			chosen=left_places[left_places.length-1];
		return chosen;
	}
	else
		if (top_places.length>1)
			return top_places[1];
		else
			return top_places[0];
}


// Version 6... add!
void LDA_new::add_shape_at_place_6(shape_g_l &chosen_gene, 
											const profile_t adjust_profile)
{
	shape_g item=chosen_gene;


	ulist<edge_node> *list;
	xy_size_t item_p_size;											// item size parallel to edge direction
	pos_t coord::*p_pos;												// position parallel to edge direction
	pos_t coord::*o_pos;												// position orthogonal to edge direction
	pos_t (edge_node::*get_p_pos)();						// get position parallel to edge direction function
	pos_t (edge_node::*get_o_pos)();						// get position orthogonal to edge direction function
	void (edge_node::*set_p_pos)(const pos_t&);	// set position parallel to edge direction function
	// note this function not used by algorithm	// set position orthogonal to edge direction function

	switch (adjust_profile)
	{
		case MODIFY_LEFT_PROFILE:
			list=&left_profile;
			edge_node::compare_method=&edge_node::compare_index_y;

			item_p_size=item.height();
			p_pos=&coord::y_pos;
			o_pos=&coord::x_pos;
			get_p_pos=&edge_node::get_y_pos;
			get_o_pos=&edge_node::get_x_pos;
			set_p_pos=&edge_node::set_y_pos;
			break;

		case MODIFY_TOP_PROFILE:
			list=&top_profile;
			edge_node::compare_method=&edge_node::compare_index_x;

			item_p_size=item.width();
			p_pos=&coord::x_pos;
			o_pos=&coord::y_pos;
			get_p_pos=&edge_node::get_x_pos;
			get_o_pos=&edge_node::get_y_pos;
			set_p_pos=&edge_node::set_x_pos;
			break;

		default:
			break;
	}

	coord edge_location;
	switch (adjust_profile)
	{
		case MODIFY_LEFT_PROFILE:
			edge_location.x_pos=chosen_gene.right();
			edge_location.y_pos=chosen_gene.top();
			break;
		case MODIFY_TOP_PROFILE:
			edge_location.x_pos=chosen_gene.left();
			edge_location.y_pos=chosen_gene.bot();
			break;
		default:
			break;
	}
	edge_node new_edge(edge_location, item_p_size);

	// find out if an edge already present is going to be extended by the new edge
	// both below and above new edge
	// this section is fully validated
	edge_node *previous_edge=NULL, *following_edge=NULL, *start_edge;
	list->reset_transverse();
	do
	{
		start_edge=list->get_transverse_node_pointer();
		if (previous_edge==NULL &&
				(start_edge->*get_o_pos)()==(new_edge.*get_o_pos)() &&
				(start_edge->*get_p_pos)()+(pos_t)start_edge->get_data()==
				(pos_t)(new_edge.*get_p_pos)())
			previous_edge=start_edge;

		if ((start_edge->*get_o_pos)()==(new_edge.*get_o_pos)() &&
				(start_edge->*get_p_pos)()==
				(pos_t)(new_edge.*get_p_pos)()+(pos_t)new_edge.get_data())
		{
			following_edge=start_edge;
			break;
		}
	}
	while (list->progress_transverse()==SUCCESS);

	// move transverse pointer to edge that first gets affected by new edge being added
	// this section is fully validated

	list->reset_transverse();
	do
	{
		start_edge=list->get_transverse_node_pointer();
		// if the bottom of the edge pointed to by transverse is below the
		// y position of the new edge, then break out of loop
	}
	while ((start_edge->*get_p_pos)()+(pos_t)start_edge->get_data()<=(new_edge.*get_p_pos)() &&
					list->progress_transverse()==SUCCESS);

	// now move transverse onto the last edge affected by adding the new edge
	// this section is fully validated
	// first_edge stores a pointer to the edge in line with new_edge.y_pos.
	edge_node *first_edge=start_edge;


	// start_offset stores the distance down the first_edge where top of new item is positioned
	pos_t start_offset=(new_edge.*get_p_pos)() - (first_edge->*get_p_pos)();
	// accumulated_edge stores the length of new edge accounted for starting from top of first edge
	pos_t accumulated_edge=-start_offset;

	do
	{
		accumulated_edge+=list->get_transverse_node_pointer()->get_data();
		// if new edge is behind current edge, then current edge not affected -
		// move start edge on by one if start isn't already pointing to last edge.
		if ((list->get_transverse_node_pointer()->*get_o_pos)()>(new_edge.*get_o_pos)())
			start_edge=start_edge->get_pointer();
	}
	while (accumulated_edge<(pos_t)item_p_size && list->progress_transverse()==SUCCESS);

	edge_node* last_edge_affected=list->get_transverse_node_pointer();

	// first check new parallel edge is behind last edge
	// second check jutting edge not jutting
	if ((new_edge.*get_o_pos)() <= (last_edge_affected->*get_o_pos)() &&
			(new_edge.*get_p_pos)()+item_p_size <= (last_edge_affected->*get_p_pos)()+last_edge_affected->get_data())
		return; // no changes to make to edge profile as new shape is invisible to profile
	
	coord last_edge_position=last_edge_affected->get_index();
	xy_size_t last_edge_length=last_edge_affected->get_data();

	xy_size_t first_edge_length=first_edge->get_data();
	coord first_edge_position=first_edge->get_index();
	coord start_edge_position=start_edge->get_index();


	// now first points to edge in line with new_edge.*p_pos
	// now start points to first edge affected by adding new edge
	// now transverse points to last edge affected by adding new edge
	// this section is fully validated
	list->remove_up_to_transverse(start_edge); // remove any edges bypassed by new edge

	// now adjust the length of the last edge affected - or remove it completely
	// this section is validated
	// remaining stores the amount of the last edge affected that isn't overlapped by new edge
	xy_size_t remaining=accumulated_edge-item_p_size;	



	if (remaining==0)								
		list->remove_transverse();				// last edge affected completely overlapped - remove last edge
	else
	{
		// last edge has got some remaining
		// increase *p_pos by the last edge length - remaining amount
		// reduce length to the amount remaining
		last_edge_position.*p_pos+=last_edge_length-remaining;
		last_edge_affected->set_index(last_edge_position);
		last_edge_affected->set_data(remaining);
	}


	// now add in the new edge.
	// this section is validated

	// if new edge behind first edge then...
	//		 decrease: new_edge.length by (start_edge.*p_pos-new_edge.*p_pos)
	//     set:      new_edge.*p_pos to start_edge.*p_pos
	if (first_edge_position.*o_pos>(new_edge.*get_o_pos)())
	{
		new_edge.set_data(new_edge.get_data()-(start_edge_position.*p_pos-(new_edge.*get_p_pos)()));
		(new_edge.*set_p_pos)(start_edge_position.*p_pos);
	}

	if (previous_edge==NULL)
		if (following_edge==NULL)									// No merging to do
			list->add(new_edge, COUNTER, ASCENDING);
		else																			// Merge new with following
		{
			(following_edge->*set_p_pos)((following_edge->*get_p_pos)()-new_edge.get_data());
			following_edge->set_data(following_edge->get_data()+new_edge.get_data());
		}
	else
		if (following_edge==NULL)						// Merge new with previous
			previous_edge->set_data(previous_edge->get_data()+new_edge.get_data());
		else																// Merge new with prev & follow
		{
			previous_edge->set_data(previous_edge->get_data()+new_edge.get_data()+
															following_edge->get_data());
			list->remove(*following_edge,COUNTER);
		}
}

void LDA_new::clear_layout()
{
	next_index=0;
	left_profile.clearlist();
	top_profile.clearlist();

	// add one edge positioned at top-left corner of macro-sheet, height of macro_height
	left_profile.add_to_end(edge_node(coord(0,0),macro_height));
	left_places.length=0;

	// add one edge positioned at top-left corner of macro-sheet, wdith of macro_width
	top_profile.add_to_end(edge_node(coord(0,0),macro_width));
	top_places.length=0;

	restore_current_rule();
}


void LDA_new::flip_placement_rule()
{
	if (rule_regime==FLIP_LEFT || rule_regime==FLIP_TOP)
		current_rule==LEFTMOST ? current_rule=TOPMOST : current_rule=LEFTMOST;
}

void LDA_new::restore_current_rule()
{
	switch (rule_regime)
	{
		case LEFTMOST:
		case ILEFTMOST:
		case TOPMOST:
		case ITOPMOST:
			current_rule=rule_regime;
			break;
		case FLIP_LEFT:
			current_rule=LEFTMOST;
			break;
		case FLIP_TOP:
			current_rule=TOPMOST;
			break;
		case DYNAMIC:
			current_rule=LEFTMOST;
		default:
			break;
	}
}

void LDA_new::set_rule_regime(const placement_rule &rule)
{
	rule_regime=rule;
	restore_current_rule();
}

placement_rule LDA_new::get_rule_regime()
{
	return rule_regime;
}

placement_rule LDA_new::get_current_rule()
{
	return current_rule;
}

population::population()
{
	sequence=NULL;
	size=0;
	candidate_size=0;
}

population::population(candidate *type, array_index sz)
{
	candidate_size=type->size_of();
	size=sz;
	sequence=type->create_array(sz);
}

population::~population()
{
	delete[] sequence;
}

population::population(const population &source)
{
	size=source.size;
	candidate_size=source.candidate_size;
	sequence=source.sequence->create_loaded_array(size,source.sequence);
}

candidate* population::get_candidate(const array_index &i)
{
	return (chromosome *)((char *)sequence+i*candidate_size);
}

candidate* population::new_candidate()
{
	return sequence->create();
}

void population::randomize()
{
	for (array_index i=0; i<size; i++)
		get_candidate(i)->random_chromosome();
}

void population::standardize()
{
	for (array_index i=0; i<size; i++)
		get_candidate(i)->init_chromosome();
}


ostream& operator<<(ostream& output_stream, const population &a)
{
//	for (array_index i=0; i<a.size; i++)
//		(a.sequence+i*a.candidate_size)->operator<<(afxDump);

	return output_stream;
}

void population::replace_candidate(array_index removal, candidate *new_candidate)
{
	// don't replace if new is worse than candidate to be replaced
	if (new_candidate->fitness()>get_candidate(removal)->fitness())
		get_candidate(removal)->copy(new_candidate);

}

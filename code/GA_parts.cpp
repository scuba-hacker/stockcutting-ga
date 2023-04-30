#include "stdafx.h"
#include "GA_parts.h"

IMPLEMENT_DYNAMIC(crossover, CObject);
IMPLEMENT_DYNAMIC(mutation, CObject);
IMPLEMENT_DYNAMIC(selector, CObject);
IMPLEMENT_DYNAMIC(rank_s, CObject);
IMPLEMENT_DYNAMIC(tournament_s, CObject);
IMPLEMENT_DYNAMIC(heterogeneous_s, CObject);
IMPLEMENT_DYNAMIC(order_c, CObject);
IMPLEMENT_DYNAMIC(seg_order_c, CObject);
IMPLEMENT_DYNAMIC(position_c, CObject);
IMPLEMENT_DYNAMIC(HUX_position_c, CObject);
IMPLEMENT_DYNAMIC(seg_position_c, CObject);
IMPLEMENT_DYNAMIC(n_point_c, CObject);
IMPLEMENT_DYNAMIC(standard_m, CObject);
IMPLEMENT_DYNAMIC(swap_m, CObject);
IMPLEMENT_DYNAMIC(multiple_swap_m, CObject);
IMPLEMENT_DYNAMIC(invert_m, CObject);
IMPLEMENT_DYNAMIC(shunt_m, CObject);
IMPLEMENT_DYNAMIC(cataclysmic_m, CObject);
IMPLEMENT_DYNAMIC(hc_m, CObject);
IMPLEMENT_DYNAMIC(sahc_m, CObject);
IMPLEMENT_DYNAMIC(anneal_m, CObject);
IMPLEMENT_DYNAMIC(random_m, CObject);
IMPLEMENT_DYNAMIC(adaptor, CObject);
IMPLEMENT_DYNAMIC(fixed_rate_a, CObject);
IMPLEMENT_DYNAMIC(adaptive_mutation_a, CObject);
IMPLEMENT_DYNAMIC(COBRA_a, CObject);
IMPLEMENT_DYNAMIC(random_a, CObject);
IMPLEMENT_DYNAMIC(allele_map, CObject);
IMPLEMENT_DYNAMIC(edge_map, CObject);
IMPLEMENT_DYNAMIC(edge_recombination_c, CObject);

extern array_index GLOBAL_MIN_SEGMENT_LENGTH;
extern array_index GLOBAL_MAX_SEGMENT_LENGTH;

selector::selector(population *pop)
{	pool=pop; pop_size=pop->size;}

selector::~selector()
{}

candidate* selector::make_child()
{ return pool->new_candidate(); }
void selector::reset_selector()
{ // do nothing
}

sequence_size selector::get_population_size()
{
	return pool->size;
}

population* selector::get_population()
{
	return pool;
}

worst_rank_s::worst_rank_s(population *pop) : rank_s(pop)
{
}

array_index worst_rank_s::look_up_index(const array_index &r)
{
	return fitness_ranking[pop_size-1-r].id;
}


rank_s::rank_s(population *pop) : selector(pop)
{
	// allocate a rank wheel array which can accommodate
	// 1 + 2 + 3 ... + n elements, where 'n' is population size
	// uses standard arithmetic sum equation
	wheel_size=pop_size*(1+pop_size) / 2;
	rank_wheel=new unsigned long [wheel_size];

	// initialise rank wheel array with candidate identifiers
	// eg for 3 member population: 1 1 1 2 2 3
	array_index current=0;
	unsigned long weight_number;
	for (unsigned long rank=0; rank<pop_size; rank++)
	{
		// weight_number stores the number of instances a candidate number will
		// appear in the rank wheel
		weight_number=pop_size-rank;
		for (unsigned long weight=0; weight<weight_number; weight++)
			rank_wheel[current++]=rank;
	}

	// fitness_ranking used for ordering population in decreasing fitness
	// fitness_pair.key is used to sort on (=fitness)
	// fitness_pair.id identifies the candidate
	fitness_ranking=new fitness_pair [pop_size];
	
	if (pop_size>65535)
		MessageBox(NULL, "Max population 65535 for rank selection", "Max random number is 2147483562...", 
								MB_OK | MB_ICONSTOP | MB_APPLMODAL);
}
 
rank_s::~rank_s()
{
	delete[] rank_wheel;
	delete[] fitness_ranking;
}

array_index rank_s::select_index()
{
	// load fitnesses into fitness_ranking array
	for (array_index i=0; i<pop_size; i++)
	{
		fitness_ranking[i].id=i;
		fitness_ranking[i].key=pool->get_candidate(i)->fitness();
	}

	quicksort<fitness_pair> q;
	q.sort3(fitness_ranking,i,DESCENDING);

	array_index rank_number=rank_wheel[random() % wheel_size];
	if (rank_number==0)
		best_selected=true;
	else
		best_selected=false;

	return look_up_index(rank_number);
}

array_index rank_s::look_up_index(const array_index &r)
{
	return fitness_ranking[r].id;
}

candidate* rank_s::select_candidate()
{
	return pool->get_candidate(fitness_ranking[select_index()].id);
}

selector* rank_s::clone()
{
	return new rank_s(pool);
}

worst_s::worst_s(population *pop) : selector(pop)
{
}

worst_s::~worst_s()
{
}

array_index worst_s::select_index()
{
	fitness_score current_fitness, min_fitness=1;
	array_index worst_index=0;
	for (array_index i=0; i<pop_size; i++)
	{
		current_fitness=pool->get_candidate(i)->fitness();
		if (current_fitness<min_fitness)
		{	
			worst_index=i;
			min_fitness=current_fitness;
		}
	}
	return worst_index;
}

candidate* worst_s::select_candidate()
{
	return pool->get_candidate(select_index());
}

selector* worst_s::clone()
{
	return new worst_s(pool);
}

best_s::best_s(population *pop) : selector(pop)
{
}

best_s::~best_s()
{
}

array_index best_s::select_index()
{
	fitness_score current_fitness, max_fitness=0;
	array_index best_index=0;
	for (array_index i=0; i<pop_size; i++)
	{
		current_fitness=pool->get_candidate(i)->fitness();
		if (current_fitness>max_fitness)
		{	
			best_index=i;
			max_fitness=current_fitness;
		}
	}
	return best_index;
}

candidate* best_s::select_candidate()
{
	return pool->get_candidate(select_index());
}

selector* best_s::clone()
{
	return new best_s(pool);
}


tournament_s::tournament_s(population *pop, sequence_size n) : selector(pop)
{
	if (n<2 || n>pop_size)
		pick_size=2;
	else
		pick_size=n;
}

tournament_s::~tournament_s()
{
}

array_index tournament_s::select_index()
{
	fitness_score max_fit=0, current_fitness;
	array_index best=0;
	array_index random_index;

	for (array_index i=0; i<pick_size; i++)
	{
		random_index=random() % pop_size;
		current_fitness=pool->get_candidate(random_index)->fitness();
		if (current_fitness>max_fit)
		{
			best=random_index;
			max_fit=current_fitness;
		}
	}
	return best;
}

candidate* tournament_s::select_candidate()
{
	return pool->get_candidate(select_index());
}

selector* tournament_s::clone()
{
	return new tournament_s(pool,pick_size);
}

heterogeneous_s::heterogeneous_s(population *pop, sequence_size min_d,
											sequence_size iteration) : selector(pop)
{
	min_distance=min_d;
	stagnate_iteration=iteration;
	parent1=NULL;
	parent1_index=0;
}

heterogeneous_s::~heterogeneous_s()
{
}

array_index heterogeneous_s::select_index()
{
	if (parent1==NULL)
	{
		parent1_index=random() % pop_size;
		parent1=pool->get_candidate(parent1_index);
		return parent1_index;
	}
	else
	{
		candidate* parent2;
		sequence_size iterate=0;
		array_index parent2_index;
		do
		{
			parent2_index=random() % pop_size;
			parent2=pool->get_candidate(parent2_index);
		}
		while (parent1->distance(*parent2)<min_distance &&
					 iterate++<stagnate_iteration);

		parent1=NULL;
		array_index error_index=parent1_index;
		parent1_index=0;

		if (iterate==stagnate_iteration)
			return error_index;
		else
			return parent2_index;
	}
}

candidate* heterogeneous_s::select_candidate()
{
	return pool->get_candidate(select_index());
}

void heterogeneous_s::reset_selector()
{
	parent1=NULL;
	parent1_index=0;
}

selector* heterogeneous_s::clone()
{
	return new heterogeneous_s(pool, min_distance);
}

seg_order_c::seg_order_c()
{
	name="segment_order_c";
}

void seg_order_c::generate_index_mask(const array_index &chromo_length, 
																	const array_index &mask_word_length, 
																	bitstream &index_mask)
{
	for (array_index i=0; i<mask_word_length; i++)
		index_mask.append_word(0);										// zero index mask

	array_index start_point, end_point;
	_get_segment_limits(start_point, end_point, chromo_length);	
	for (i=start_point; i<=end_point; i++)
		index_mask.set_bit_1(i);
}

order_c::order_c()
{
	name="order_c";
}


void order_c::generate_index_mask(const array_index &chromo_length, 
																	const array_index &mask_word_length, 
																	bitstream &index_mask)
{
	for (array_index i=0; i<mask_word_length; i++)
		index_mask.append_word(random());
}

void order_c::cross(candidate *p1, candidate *p2, candidate *c)
{
	sequence_size length=p1->get_length();
	// divide length by 16, add one to mask_word_length if non-integer
	// number of words required
	sequence_size mask_word_length=(length >> 4) + (length % 16 > 0);
	sequence_size mask_char_length=mask_word_length*2;

	// make the index mask for parent2
	unsigned char *index_mask_array=new unsigned char [mask_char_length];

	bitstream index_mask;
	index_mask.attach_char_array(index_mask_array, mask_char_length);

	generate_index_mask(length, mask_word_length, index_mask);

	index_mask.reset_read_write();

	//afxDump << "Index mask\n";
	bool result;
	for (array_index i=0; i<length; i++)
	{
		index_mask.retrieve_bool(result);
		//if (i%16==0) afxDump << " ";
		//afxDump << result;
	}
	//afxDump << "\n";
	index_mask.reset_read_write();

	// make the id mask for parent2
	// for every set bit in index mask, look up that gene in parent2
	// and get the gene id - set this bit in id mask to 1
	unsigned char *id_mask_array=new unsigned char [mask_char_length];

	bitstream id_mask;
	id_mask.attach_char_array(id_mask_array, mask_char_length);
	id_mask.wipe_clean();


	for (i=0; i<length; i++)
	{
		if (index_mask.high_bit(i)==1)
		{
			unsigned long t=(*p2)[i]->get_id();
			id_mask.set_bit_1(t);
		}
	}

	id_mask.reset_read_write();
	//afxDump << "Id mask\n";
	for (i=0; i<length; i++)
	{
		id_mask.retrieve_bool(result);
		//if (i%16==0) afxDump << " ";
		//afxDump << result;
	}
	//afxDump << "\n";
	id_mask.reset_read_write();
	index_mask.reset_read_write();

	// copy genes into child
	// all genes not in gene mask copied from parent1 to child
	// genes in gene mask copied from next gene in parent2 to child
	unsigned long index=-1;
	for (i=0; i<length; i++)
	{
		if (id_mask.high_bit( (*p1)[i]->get_id() ) == 0)
			(*c)[i]->copy((*p1)[i]);		// Copy gene from p1 to child
		else
		{
			// get next gene position from index array
			// gives array index of next masked gene in parent2
			bool result;
			do
			{
				index_mask.retrieve_bool(result);
				index++;
			}
			while (result==false);

			// copy gene in parent2 to child
			(*c)[i]->copy((*p2)[index]);
		}
	}


	delete[] index_mask_array;
	delete[] id_mask_array;

	c->invalidate_fitness();

}

position_c::position_c()
{
	name="position_c";
}


void position_c::cross(candidate *p1, candidate *p2, candidate *c)
{
	sequence_size length=p1->get_length();
	// divide length by 16, add one to mask_word_length if non-integer
	// number of words required
	sequence_size mask_word_length=(length >> 4) + (length % 16 > 0);
	sequence_size mask_char_length=mask_word_length*2;

	// make the index mask for parent2
	unsigned char *index_mask_array=new unsigned char [mask_char_length];

	bitstream index_mask;
	index_mask.attach_char_array(index_mask_array, mask_char_length);
	for (array_index i=0; i<mask_word_length; i++)
		index_mask.append_word(random());

	index_mask.reset_read_write();

	//afxDump << "Index mask\n";
	bool result;
//	for (i=0; i<length; i++)
//	{
//		index_mask.retrieve_bool(result);
//		//if (i%16==0) afxDump << " ";
//		afxDump << result;
//	}
//	afxDump << "\n";
	index_mask.reset_read_write();

	// make the id mask for parent2
	// for every set bit in index mask, look up that gene in parent2
	// and get the gene id - set this bit in id mask to 1
	unsigned char *id_mask_array=new unsigned char [mask_char_length];

	bitstream id_mask;
	id_mask.attach_char_array(id_mask_array, mask_char_length);
	id_mask.wipe_clean();


	for (i=0; i<length; i++)
	{
		if (index_mask.high_bit(i)==1)
		{
			unsigned long t=(*p2)[i]->get_id();
			id_mask.set_bit_1(t);
		}
	}

	id_mask.reset_read_write();
//	afxDump << "Id mask\n";
//	for (i=0; i<length; i++)
//	{
//		id_mask.retrieve_bool(result);
//		//if (i%16==0) afxDump << " ";
//		afxDump << result;
//	}
//	afxDump << "\n";
	id_mask.reset_read_write();
	index_mask.reset_read_write();


	// copy all chosen genes from p2 to c1 - same gene locations
	for (i=0; i<length; i++)
	{
//		if (id_mask.high_bit( (*p2)[i]->get_id() ) == 1)
		if (index_mask.high_bit( i ) == 1)
			(*c)[i]->copy((*p2)[i]);
	}

	// copy genes into child
	// all genes not in gene mask copied from parent1 to child
	// genes in gene mask copied from next gene in parent2 to child
	unsigned long pi=-1, ci=-1;

	do
	{
		// find next gene to take from p1
		do
		{
			pi++;
		}
		while (pi<length && id_mask.high_bit((*p1)[pi]->get_id()) == 1);
		
		if (pi==length)			// all parent genes searched
			break;

		// find next gene to place into child
		do
		{
			ci++;
		}
		while (id_mask.high_bit((*p2)[ci]->get_id()) == 1);

		(*c)[ci]->copy((*p1)[pi]);

	}
	while (ci<length-1);


	delete[] index_mask_array;
	delete[] id_mask_array;

	c->invalidate_fitness();
}



seg_position_c::seg_position_c()
{
	name="segment_position_c";
}


void _get_segment_limits(array_index &start_point, 
												array_index &end_point,
												const array_index &length)
{
	array_index length_max=GLOBAL_MAX_SEGMENT_LENGTH;
	array_index length_min=GLOBAL_MIN_SEGMENT_LENGTH;

	array_index order[2];
	if (length_max==0)
	{
		permutation(length, 2, order);
		if (order[0]>order[1])
			swap(order[0],order[1]);
	}
	else
	{
		order[0]=random() % (length-length_max);
		array_index variation=random() % (length_max-length_min+1);
		order[1]=order[0]+length_min+variation;
	}

	start_point=order[0];
	end_point=order[1];
}

void seg_position_c::get_segment_limits(array_index &start_point, 
																				array_index &end_point,
																				const array_index &length)
{
	_get_segment_limits(start_point,end_point,length);
}


HUX_position_c::HUX_position_c()
{
	name="HUX_position_c";
}

void HUX_position_c::get_segment_limits(array_index &start_point, 
																				array_index &end_point,
																				const array_index &length)
{
	if (random() % 2==0)
	{
		start_point=0;
		end_point=length / 2;
	}
	else
	{
		start_point=length / 2;
		end_point=length;
	}
}

// Copy either first or second half of chromosome from parent2 to child.
// Fill in remaining half of child with unused genes in order found in parent1.
void HUX_position_c::cross(candidate *p1, candidate *p2, candidate *c)
{
	sequence_size length=p1->get_length();
	// divide length by 16, add one to mask_word_length if non-integer
	// number of words required
	sequence_size mask_word_length=(length >> 4) + (length % 16 > 0);
	sequence_size mask_char_length=mask_word_length*2;

	array_index start_point, end_point;
	get_segment_limits(start_point, end_point, length);

	bool result;

	// make the id mask for parent2
	// for every set bit in index mask, look up that gene in parent2
	// and get the gene id - set this bit in id mask to 1
	unsigned char *id_mask_array=new unsigned char [mask_char_length];

	bitstream id_mask;
	id_mask.attach_char_array(id_mask_array, mask_char_length);
	id_mask.wipe_clean();


	for (array_index i=start_point; i<end_point; i++)
	{
		unsigned long t=(*p2)[i]->get_id();
		id_mask.set_bit_1(t);
	}

	id_mask.reset_read_write();
	//afxDump << "Id mask\n";
	for (i=0; i<length; i++)
	{
		id_mask.retrieve_bool(result);
		//if (i%16==0) afxDump << " ";
		//afxDump << result;
	}
	//afxDump << "\n";
	id_mask.reset_read_write();


	// copy all chosen genes from p2 to c1 - same gene locations
	for (i=0; i<length; i++)
	{
		if (id_mask.high_bit( (*p2)[i]->get_id() ) == 1)
			(*c)[i]->copy((*p2)[i]);
	}

	// copy genes into child
	// all genes not in gene mask copied from parent1 to child
	// genes in gene mask copied from next gene in parent2 to child
	unsigned long pi=-1, ci=-1;

	do
	{
		// find next gene to take from p1
		do
		{
			pi++;
		}
		while (pi<length && id_mask.high_bit((*p1)[pi]->get_id()) == 1);
		
		if (pi==length)			// all parent genes searched
			break;

		// find next gene to place into child
		do
		{
			ci++;
		}
		while (id_mask.high_bit((*p2)[ci]->get_id()) == 1);

		(*c)[ci]->copy((*p1)[pi]);

	}
	while (ci<length-1);


	delete[] id_mask_array;

	c->invalidate_fitness();
}


n_point_c::n_point_c()
{
	n_point=1;
	copier=&gene::copy_feature_1;
	name="n_point_c";
}

void n_point_c::cross(candidate *p1, candidate *p2, candidate *c)
{
	array_index points[100];
	sequence_size length=p1->get_length();

	array_index *location= new array_index [length];
	// copy parent1 to child - also building locaiton reference array
	for (array_index i=0; i<length; i++)
	{
		(*c)[i]->copy((*p1)[i]);
		location[(*p1)[i]->get_id()]=i;
	}

	// reorder parent2 so it is the same permutation as parent1- store in temp
	candidate *temp=c->create();
	for (i=0; i<length; i++)
	{
		array_index j=(*p1)[i]->get_id();
		((*temp)[i]->*copier)((*p2)[location[j]]);
	}

	delete[] location;

	// get permutation
	permutation(length, n_point, points);
	// order permutation
	simple_insertsort(points, n_point, ASCENDING);

	candidate *source=p1;
	array_index *current_point=points;
	for (i=0; i<length; i++)
	{
		if (i==*current_point)
		{
			current_point++;
			if (source==p1)
				source=temp;
			else
				source=p1;
		}
		((*c)[i]->*copier)((*source)[i]);
	}
	delete temp;
	c->invalidate_fitness();

}

crossover::~crossover()
{
}

mutation::mutation()
{
	finished=false;
}
mutation::~mutation()
{
}
void mutation::set_in_situ_mutation(const bool &new_val)
{	in_situ_mutation=new_val; }

void mutation::reset_mutator()
{	}

standard_m::standard_m()
{
	gene_count=1;
	randomizer=&gene::randomize_feature_1;
	in_situ_mutation=false;
	name="standard_m";
}

void standard_m::mutate(candidate *p, candidate *c)
{
	array_index indexes[100];
	sequence_size length=p->get_length();
	if (in_situ_mutation)
		c=p;
	else
	{
		// copy parent to child (all genes)
		for (array_index i=0; i<length; i++)
			(*c)[i]->copy((*p)[i]);
	}

	// get permutation
	permutation(length, gene_count, indexes);
	for (array_index i=0; i<gene_count; i++)
		((*c)[indexes[i]]->*randomizer)();
	c->invalidate_fitness();

}


void standard_m::set_gene_count(const sequence_size &new_count)
{	gene_count=new_count; }

swap_m::swap_m()
{
	in_situ_mutation=false;
	name="swap_m";
}


// swap mutation
void swap_m::mutate(candidate *p, candidate *c)
{
	sequence_size length=p->get_length();

	if (in_situ_mutation)
		c=p;
	else
	{
		// copy parent to child (all genes)
		for (array_index i=0; i<length; i++)
			(*c)[i]->copy((*p)[i]);
	}

	array_index picked_indexes[2];
	permutation(length, 2, picked_indexes);

	// swap over the two genes
	gene *temp=(*c)[0]->create();
	temp->copy((*c)[picked_indexes[0]]);
	(*c)[picked_indexes[0]]->copy((*c)[picked_indexes[1]]);
	(*c)[picked_indexes[1]]->copy(temp);

	delete temp;

	c->invalidate_fitness();
}

void swap_m::mutate_choice(candidate *p, candidate *c, pair choice)
{
	sequence_size length=p->get_length();

	if (in_situ_mutation)
		c=p;
	else
	{
		// copy parent to child (all genes)
		for (array_index i=0; i<length; i++)
			(*c)[i]->copy((*p)[i]);
	}

	// swap over the two genes
	gene *temp=(*c)[0]->create();
	temp->copy((*c)[choice.i]);
	(*c)[choice.i]->copy((*c)[choice.j]);
	(*c)[choice.j]->copy(temp);

	delete temp;

	c->invalidate_fitness();
}



multiple_swap_m::multiple_swap_m()
{
	swap_count=1;
	in_situ_mutation=false;
	name="multi_swap_m";
}

// multiple swap mutation
void multiple_swap_m::mutate(candidate *p, candidate *c)
{
	sequence_size length=p->get_length();
	array_index i;
	if (in_situ_mutation)
		c=p;
	else
	{
		// copy parent to child (all genes)
		for (i=0; i<length; i++)
			(*c)[i]->copy((*p)[i]);
	}

	if (swap_count>length/2)
		swap_count=1;

	array_index *picked_indexes=new array_index[swap_count*2];
	permutation(length, swap_count*2, picked_indexes);

	for (i=0; i<swap_count*2; i+=2)
	{
		// swap over the two genes
		gene *temp=(*c)[i]->create();
		temp->copy((*c)[picked_indexes[i]]);
		(*c)[picked_indexes[i]]->copy((*c)[picked_indexes[i+1]]);
		(*c)[picked_indexes[i+1]]->copy(temp);
		delete temp;
	}

	delete[] picked_indexes;
	c->invalidate_fitness();
}

void multiple_swap_m::set_swap_count(const sequence_size &new_count)
{
	swap_count=new_count;
}

// invert mutation

invert_m::invert_m()
{
	name="invert_m";
}

void invert_m::mutate(candidate *p, candidate *c)
{
	sequence_size length=p->get_length();
	array_index picked_indexes[2];
	permutation(length, 2, picked_indexes);

	// if picked_indexes not in increasing order then swap
	if (picked_indexes[0]>picked_indexes[1])
	{
		array_index temp=picked_indexes[0];
		picked_indexes[0]=picked_indexes[1];
		picked_indexes[1]=temp;
	}

	//afxDump << picked_indexes[0] << " " << picked_indexes[1] << "\n";

	// copy parent to child (all genes up to start of inversion)
	for (array_index i=0; i<picked_indexes[0]; i++)
		(*c)[i]->copy((*p)[i]);

	array_index j=picked_indexes[1];
	for (i=picked_indexes[0]; i<=picked_indexes[1]; i++, j--)
		(*c)[i]->copy((*p)[j]);

	for (i=picked_indexes[1]+1; i<length; i++)
		(*c)[i]->copy((*p)[i]);

	c->invalidate_fitness();
}

// shunt mutation
shunt_m::shunt_m()
{
	name="shunt_m";
}

void shunt_m::mutate(candidate *p, candidate *c)
{
	// shunt length minimum: 1
	// shunt length maximum: candidate length - 1
	// position shunt moved to: != position moved from: shunt always occurs

	sequence_size length=p->get_length();
	array_index picked_indexes[2];
	sequence_size shunt_length;
	
	// repick random numbers if shunt length is same as chromo length
	do
	{
		picked_indexes[0]=random() % length;
		picked_indexes[1]=random() % length;

		// if picked_indexes not in increasing order then swap
		if (picked_indexes[0]>picked_indexes[1])
		{
			array_index temp=picked_indexes[0];
			picked_indexes[0]=picked_indexes[1];
			picked_indexes[1]=temp;
		}

		shunt_length=picked_indexes[1]-picked_indexes[0];
	}
	while (shunt_length==length-1 || shunt_length==0);
		

	// choose random target position for shunt bit >=0 and < length-shunt_length
	// repick random target if == to start of shunt length
	array_index position;
	do
	{
		position=random() % (length-shunt_length);
	}
	while (position==picked_indexes[0]);

	//afxDump << picked_indexes[0] << " " << picked_indexes[1] << 
	//				"p=" << position << "\n";

	array_index i=0;									// points to next non-shunt gene to copy from
	array_index j=picked_indexes[0];	// points to next shunt gene to copy from

	// copy up to position or first shunt gene - which ever comes first
	while (i<position && i<picked_indexes[0])
	{
		(*c)[i]->copy((*p)[i]);
		i++;
	}

	array_index ci=i;									// points to next gene to copy to

	// if reached shunt start before insert position found...
	if (i==picked_indexes[0] && i<position)
	{
		// continue copying genes - skip shunt length - until shunt position got to
		i+=shunt_length+1;
		while (ci<position && i<length)
		{
			(*c)[ci]->copy((*p)[i]);
			i++;
			ci++;
		}

		// copy shunt genes into child
		while (j<=picked_indexes[1] && ci<length)
		{
			(*c)[ci]->copy((*p)[j]);
			j++;
			ci++;
		}

		// copy rest of parent genes into child
		while (ci<length)
		{
			(*c)[ci]->copy((*p)[i]);
			i++;
			ci++;
		}
	}
	else
	{
		// copy shunt genes into child
		while (j<=picked_indexes[1] && ci<length)
		{
			(*c)[ci]->copy((*p)[j]);
			j++;
			ci++;
		}

		// copy from position upto start of shunt
		while (i<picked_indexes[0])
		{
			(*c)[ci]->copy((*p)[i]);
			i++;
			ci++;
		}

		i+=shunt_length+1;

		// copy rest of parent genes after shunt into child
		while (ci<length)
		{
			(*c)[ci]->copy((*p)[i]);
			i++;
			ci++;
		}
	}

	c->invalidate_fitness();

}

cataclysmic_m::cataclysmic_m()
{
	swapper.set_in_situ_mutation(true);
	mutate_features=true;
	feature_mut.set_in_situ_mutation(true);
	feature_mut.randomizer=&gene::randomize_all_features;
}

void cataclysmic_m::mutate(candidate *p, candidate *c)
{
}

void cataclysmic_m::global_mutate(population *pool, double percentage_change)
{
	// use swap mutation as the mutator
	sequence_size pop_size=pool->size;
	sequence_size chromo_size=pool->get_candidate(0)->get_length();

	sequence_size swap_count=(unsigned long)ceil(percentage_change*chromo_size);
	swapper.set_swap_count(swap_count/2);
	feature_mut.set_gene_count(swap_count);
	

	// Find most fit candidate
	array_index best_index=0;
	fitness_score best_fitness=0, current_fitness=0;
	for (array_index i=0; i<pop_size; i++)
	{
		current_fitness=pool->get_candidate(i)->fitness();
		if (current_fitness>best_fitness)
		{
			best_index=i;
			best_fitness=current_fitness;
		}
	}

	// mutate all candidates except for the most fit one
	for (i=0; i<best_index; i++)
	{
		swapper.mutate(pool->get_candidate(i), NULL);
		if (mutate_features)
			feature_mut.mutate(pool->get_candidate(i), NULL);
	}
	for (i=best_index+1; i<pop_size; i++)
	{
		swapper.mutate(pool->get_candidate(i), NULL);
		if (mutate_features)
			feature_mut.mutate(pool->get_candidate(i), NULL);
	}
}

mutation* swap_m::clone()
{ 
	swap_m* temp=new swap_m;
	temp->in_situ_mutation=in_situ_mutation;
	return (mutation*)temp;
}

mutation* multiple_swap_m::clone()
{ 
	multiple_swap_m* temp=new multiple_swap_m;
	temp->set_swap_count(swap_count);
	temp->in_situ_mutation=in_situ_mutation;
	return (mutation*)temp;
}

mutation* standard_m::clone()
{
	standard_m* temp=new standard_m;
	temp->set_gene_count(gene_count);
	temp->in_situ_mutation=in_situ_mutation;
	temp->name=name;
	return (mutation*)temp;
}

mutation* hc_m::clone()
{	
	hc_m* temp=new hc_m;
	temp->in_situ_mutation=in_situ_mutation;
	temp->threshold=threshold;
	temp->finished=finished;
	temp->operator_adaptor=operator_adaptor;
	temp->restart_flag=restart_flag;
	return temp;
}
mutation* sahc_m::clone()
{	
	sahc_m* temp=new sahc_m;
	temp->in_situ_mutation=in_situ_mutation;
	temp->threshold=threshold;
	temp->sample_rate=sample_rate;
	temp->finished=finished;
	temp->restart_flag=restart_flag;
	return temp;
}

mutation* anneal_m::clone()
{	
	anneal_m* temp=new anneal_m;
	temp->in_situ_mutation=in_situ_mutation;
	temp->start_temp=start_temp;
	temp->end_temp=end_temp;
	temp->cooling_ratio=cooling_ratio;
	temp->finished=finished;
	temp->operator_adaptor=operator_adaptor;
	return temp;
}

mutation* random_m::clone()
{	
	random_m* temp=new random_m;
	temp->finished=finished;
	return temp;
}

mutation* invert_m::clone()
{ return new invert_m; }
mutation* shunt_m::clone()
{ return new shunt_m; }
mutation* cataclysmic_m::clone()
{ return new cataclysmic_m; }
crossover* order_c::clone()
{ return new order_c; }
crossover* seg_order_c::clone()
{ return new seg_order_c; }
crossover* position_c::clone()
{ return new position_c; }
crossover* HUX_position_c::clone()
{ return new HUX_position_c; }
crossover* seg_position_c::clone()
{ return new seg_position_c; }
crossover* n_point_c::clone()
{ n_point_c* temp=new n_point_c; 
	temp->copier=copier;
	temp->n_point=n_point;
	temp->name=name;
	return (crossover *)temp;}

adaptor::adaptor()
{
	cross_count=mut_count=0;
	select=NULL;
	finished=false;
}

adaptor::adaptor(selector &s)
{
	cross_count=mut_count=0;
	select=s.clone();
	finished=false;
}

void adaptor::set_selector(selector &s)
{
	if (select!=NULL)
		delete select;

	select=s.clone();
}

population* adaptor::get_population()
{
	return select->get_population();
}

adaptor::~adaptor()
{
	for (array_index i=0; i<cross_count; i++)
		delete cross[i];
	for (i=0; i<mut_count; i++)
		delete mut[i];
	delete select;
}

void adaptor::add_mutator(mutation &mu)
{
	mut[mut_count++]=mu.clone();
}

void adaptor::add_crossor(crossover &cr)
{
	cross[cross_count++]=cr.clone();
}

fixed_rate_a::fixed_rate_a(selector &s) : adaptor(s)
{
	rate=0.8;
}


void fixed_rate_a::set_rate(double new_rate)
{
	// rate must be in the range 0 to 1#
	if (rate>=0 && rate<=1)
		rate=new_rate;

	// rate=0: always choose mutation
	// rate=1: always choose crossover
}

double fixed_rate_a::get_rate()
{
	return rate;
}

candidate* fixed_rate_a::apply_operator()
{
	candidate* child=select->make_child();
	candidate* parent1=select->select_candidate();

	// max random number is 'MAXRANDOM'
	double cut_off=MAXRANDOM*rate;
	if (random()>cut_off)
	{
		// randomly choose a mutation operator
		array_index mutate_index=random() % mut_count;
		// Apply mutator to child
		mut[mutate_index]->mutate(parent1,child);
	}
	else
	{
		// randomly choose a crossover operator
		candidate* parent2=select->select_candidate();
		array_index cross_index=random() % cross_count;
		cross[cross_index]->cross(parent1, parent2, child);
	}

	// note: it is the responsibility of the caller to deal with child's memory
	return child;
}

adaptive_mutation_a::adaptive_mutation_a(selector &s) : adaptor(s)
{
}

candidate* adaptive_mutation_a::apply_operator()
{
	candidate* child=select->make_child();
	candidate* parent1=select->select_candidate();
	candidate* parent2=select->select_candidate();
	sequence_size pop_size=select->get_population_size();
	
	double crossover_probability=(double)parent1->distance(*parent2)/(double)parent1->get_length();

	if ((random() % pop_size) <= pop_size * crossover_probability)
		cross[random() % cross_count]->cross(parent1, parent2, child);
	else
		mut[random() % mut_count]->mutate(parent1,child);

	return child;
}

random_a::random_a(selector &s) : adaptor(s)
{


}

candidate* random_a::apply_operator()
{
	candidate* child=select->make_child();
	array_index picked;

	// do random operator pick
	picked=random() % (mut_count+cross_count);

	if (picked<cross_count)
	{
		// crossover operator picked
		// select two parents
		candidate* parent1=select->select_candidate();
		candidate* parent2=select->select_candidate();
		cross[picked]->cross(parent1, parent2, child);
	}
	else
	{
		// mutation operator picked
		// select one parent
		candidate* parent=select->select_candidate();
		mut[picked-cross_count]->mutate(parent, child);
	}
	return child;
}


COBRA_a::COBRA_a(selector &s) : adaptor(s)
{
	operator_wheel=NULL;
	operator_ranking=NULL;
	wheel_size=0;
	number_of_operators=0;
	iteration_point=1000;
	current_iteration=0;
	wheel_in_use=false;
}

COBRA_a::COBRA_a(selector &s, long &iteration) : adaptor(s)
{
	operator_wheel=NULL;
	operator_ranking=NULL;
	wheel_size=0;
	number_of_operators=0;
	iteration_point=(unsigned long)iteration;
	current_iteration=0;
	wheel_in_use=false;
}


COBRA_a::~COBRA_a()
{
	if (wheel_in_use)
	{
		delete[] operator_wheel;
		delete[] operator_ranking;
	}
}

status COBRA_a::update_operator_count()
{
	if (number_of_operators!=cross_count+mut_count)
	{
		if (wheel_in_use)
		{
			delete[] operator_wheel;
			delete[] operator_ranking;
			wheel_in_use=false;
		}

		current_iteration=0;
		wheel_size=0;
		number_of_operators=cross_count+mut_count;

		// fitness_ranking used for ordering operators in decreasing fitness
		// fitness_pair.key is used to sort on (=fitness)
		// fitness_pair.id identifies the candidate
		operator_ranking=new fitness_pair [number_of_operators];
		initialise_operator_ranking();
		generate_weighted_wheel();
		return SUCCESS;
	}
	else
		return FAILURE;
}

void COBRA_a::initialise_operator_ranking()
{
	for (array_index i=0; i<number_of_operators; i++)
	{
		operator_ranking[i].id=i;
		operator_ranking[i].key=0;
	}
}

void COBRA_a::generate_weighted_wheel()
{
	// number_of_operators
	wheel_size=number_of_operators*(1+number_of_operators) / 2;
	operator_wheel=new sequence_size [wheel_size];

	// initialise operator wheel array with index identifiers
	// eg for 3 member population: 1 1 1 2 2 3
	array_index current=0;
	unsigned long weight_number;
	for (unsigned long rank=0; rank<number_of_operators; rank++)
	{
		// weight_number stores the number of instances a candidate number will
		// appear in the rank wheel
		weight_number=number_of_operators-rank;
		for (unsigned long weight=0; weight<weight_number; weight++)
			operator_wheel[current++]=rank;
	}

	wheel_in_use=true;
}

candidate* COBRA_a::apply_operator()
{
	float mutation_points=2;
	float crossover_points=1;

	candidate* child=select->make_child();
	array_index picked;

	// first pick an operator
	update_operator_count();
	if (current_iteration<iteration_point)
	{
		// do random operator pick
		picked=random() % number_of_operators;
	}
	else
	{
		// use the operator_wheel to pick
		// update rank relative fitnesses of operators if iteration_point reached
		if (current_iteration == iteration_point)
		{
			quicksort<fitness_pair> q;
			q.sort3(operator_ranking, number_of_operators, DESCENDING);
			#ifdef _DEBUG
			afxDump << "COBRA operator rankings:\n";
			#endif
			double total_score=0;
			for (array_index j=0; j<number_of_operators; j++)
			{
			#ifdef _DEBUG
				afxDump << operator_ranking[j].key << ": ";
			#endif
				total_score+=operator_ranking[j].key;
			
			#ifdef _DEBUG
				if (operator_ranking[j].id<cross_count)
					afxDump << cross[operator_ranking[j].id]->name << "\n";
				else
					afxDump << mut[operator_ranking[j].id-cross_count]->name << "\n";
			#endif
			}
			
			#ifdef _DEBUG
			afxDump << total_score << " -> TOTAL\n";
			#endif
		}
		// pick an operator to use
		array_index picked_index=random() % wheel_size;
		picked=operator_wheel[picked_index];
		picked=picked;
	}

	if (picked<cross_count)
	{
		// crossover operator picked
		// select two parents
		candidate* parent1=select->select_candidate();
		candidate* parent2=select->select_candidate();
		cross[picked]->cross(parent1, parent2, child);

		fitness_score c_fitness=child->fitness();

		if (c_fitness>parent1->fitness())
			operator_ranking[picked].key+=crossover_points;

		if (c_fitness>parent2->fitness())
			operator_ranking[picked].key+=crossover_points;
	}
	else
	{
		// mutation operator picked
		// select one parent
		candidate* parent=select->select_candidate();
		mut[picked-cross_count]->mutate(parent, child);

		if (child->fitness()>parent->fitness())
			operator_ranking[picked].key+=mutation_points;
	}
	current_iteration++;
	return child;
}

void COBRA_a::set_iteration_point(sequence_size &new_point)
{
	iteration_point=new_point;
}

generation_model::generation_model(adaptor *adapt, selector *remover) : 
	operator_adaptor(adapt), removal_select(remover)
{
	pool=adapt->get_population();
	finished=false;
	best_so_far=NULL;
}
generation_model::~generation_model()
{if (best_so_far!=NULL) delete best_so_far;};

void generation_model::terminate()
{
}

steady_state::steady_state(adaptor *adapt, selector *remover) : 
			generation_model(adapt,remover)
{
}

bool steady_state::evolve_once()
{
	chromosome *child=operator_adaptor->apply_operator();
	array_index remove_index;
	remove_index=removal_select->select_index();

	pool->replace_candidate(remove_index,child);
	delete child;
	return false;
}

stochastic::stochastic(mutation *m, population *p, adaptor *a) : 
			generation_model(a, NULL)
{
	pool=p;
	finished=false;
	mut=m->clone();
	mut->set_in_situ_mutation(true);
	mut->reset_mutator();
	best_so_far=pool->new_candidate();
	best_active=false;
}

stochastic::~stochastic()
{	delete mut; } 

bool stochastic::evolve_once()
{
	candidate *a=pool->get_candidate(0);
	mut->mutate(a,NULL);

	if (mut->finished==true)
		finished=true;

	if (!best_active || a->fitness()>=best_so_far->fitness())
	{
		best_so_far->copy(a);
		best_active=true;
	}
	return mut->restart_flag;
}

void stochastic::terminate()
{
	pool->get_candidate(0)->copy(best_so_far);
}

generational::generational(adaptor *a, selector *r) : 
	generation_model(a,r)
{
}

bool generational::evolve_once()
{
	return false;
}



hc_m::hc_m()
{
	threshold=1000;
	iteration=0;
	restart_flag=false;
}

hc_m::hc_m(adaptor *a)
{
	operator_adaptor=a;
	threshold=1000;
	iteration=0;
}

void hc_m::mutate(candidate *p, candidate *c)
{
	restart_flag=false;
	candidate *child;

	child=operator_adaptor->apply_operator();

	if (in_situ_mutation)
		c=p;

	if (child->fitness() > p->fitness())
	{
		c->copy(child);
		iteration=0;
	}
	else
	{
		iteration++;
		if (iteration>threshold)
		{
			iteration=0;
			restart_flag=true;
			c->random_chromosome();
		}
	}
	delete child;
	c->invalidate_fitness();
}

void sahc_m::generate_pairs()
{
	pairs_length=(LDA_c::LDA_length*(LDA_c::LDA_length+1))/2;
	pair* initial=new pair[pairs_length];
	pairings=new pair[pairs_length];
	pair* current=initial;
	for (array_index j=0; j<LDA_c::LDA_length; j++)
		for (array_index i=j; i<LDA_c::LDA_length; i++)
		{
			current->i=i;
			current->j=j;
			current++;
		}

	array_index random_index;
	for (sequence_size i=0; i<pairs_length; i++)
	{
		// Pick random index between 0 and len-i-1
		random_index=random() % (pairs_length-i);
		pairings[i]=initial[random_index];
		initial[random_index]=initial[pairs_length-1-i];
	}
	delete[] initial;
}

sahc_m::sahc_m()
{
	swapper.set_in_situ_mutation(false);
	threshold=1000;
	sample_rate=10;
	iteration=0;
	restart_flag=false;
	generate_pairs();
}

sahc_m::~sahc_m()
{
	delete[] pairings;
}

void sahc_m::mutate(candidate *p, candidate *c)
{
	restart_flag=false;
	candidate *child = p->clone();
	candidate *best = p->clone();

	// pick random index to start getting pairs from pairings
	sequence_size start=random() % pairs_length;
	// calculate number of pairs to check
	sequence_size pair_count=sample_rate;

	for (array_index k=0; k<pair_count; k++)
	{
		swapper.mutate_choice(p,child, pairings[start++]);
		if (start==pairs_length)
			start=0;
		if (child->fitness() > best->fitness())
			best->copy(child);
	}

	if (in_situ_mutation)
		c=p;

	if (best->fitness() > p->fitness())
	{
		c->copy(best);
		iteration=0;
	}
	else
	{
		iteration++;
		if (iteration>threshold)
		{
			iteration=0;
			restart_flag=true;
			c->random_chromosome();
		}
	}

	delete child; delete best;
	c->invalidate_fitness();
}

anneal_m::anneal_m()
{
	finished=false;
	restart_flag=false;
	start_temp=10000;
	end_temp=0.001;
	cooling_ratio=0.9;
	current_temp=start_temp;
}

anneal_m::anneal_m(adaptor *adap)
{
	finished=false;
	start_temp=10000;
	end_temp=0.001;
	cooling_ratio=0.9;
	current_temp=start_temp;
	operator_adaptor=adap;
}


void anneal_m::reset_mutator()
{	current_temp=start_temp;};


void anneal_m::mutate(candidate *p, candidate *c)
{
	candidate *child;

	child=operator_adaptor->apply_operator();

	if (in_situ_mutation)
		c=p;



	// Acceptance Function
	double difference=fabs(child->fitness() - p->fitness());
	double probability=exp(-difference/current_temp);
	double cut_off=probability*MAXRANDOM;

	if (random() < cut_off)
	{
		c->copy(child);							// Accept the mutant
		c->invalidate_fitness();
	}

	// Amend the Cooling Schedule
	current_temp=cooling_ratio*current_temp;

	if (current_temp<end_temp)
	{
		finished=true;
		reset_mutator();
	}
	else
		finished=false;

	delete child;
}

random_m::random_m()
{
	restart_flag=false;
	finished=false;
}

random_m::random_m(adaptor *a)
{
	restart_flag=false;
	finished=false;
}

void random_m::mutate(candidate *p, candidate *c)
{
	sequence_size length=p->get_length(); 
	if (in_situ_mutation)									
		c=p;																

	c->random_chromosome();
	c->invalidate_fitness();
}

allele_map::allele_map()
{
	edge_count=0;
}

bool allele_map::add_edge(const array_index &i)
{

	if (edge_count<=MAX_EDGES-1)
	{
		// don't allow duplicate ids to be stored
		for (array_index j=0; j<edge_count; j++)
		{
			if (edges[j]==i)
				return false;
		}

		edges[edge_count]=i;
		edge_count++;
		return true;
	}
	else
		return false;
}

bool allele_map::remove_edge(const array_index &i)
{
	// i is the id of the thing to be removed
	// search for id - remove if present
	for (array_index j=0; j<edge_count; j++)
		if (edges[j]==i)
		{
			edges[j]=edges[edge_count-1];
			edge_count--;
			return true;
		}

	// edge not found
	return false;
}

sequence_size allele_map::get_edge_count()
{
	return edge_count;
}

void allele_map::clear()
{
	edge_count=0;
}

edge_map::edge_map()
{
	map_length=LDA_c::LDA_length;
	alleles=new allele_map[map_length];
	chosen_alleles=new array_index[map_length];
}

edge_map::~edge_map()
{
	delete[] alleles;
	delete[] chosen_alleles;
}

void edge_map::reset_all()
{
	for (array_index i=0; i<map_length; i++)
		alleles[i].clear();
}

void edge_map::add_to_edge_map(const array_index *permute)
{
	// receives a permutation
	// process all elements in permutation except 1st and last
	for (array_index i=1; i<map_length-1; i++)
	{
		array_index current_id=permute[i];
		alleles[current_id].add_edge(permute[i-1]);
		alleles[current_id].add_edge(permute[i+1]);
	}

	// process first element in permutation
	alleles[permute[0]].add_edge(permute[map_length-1]);
	alleles[permute[0]].add_edge(permute[1]);

	// process last element in permutation
	alleles[permute[map_length-1]].add_edge(permute[map_length-2]);
	alleles[permute[map_length-1]].add_edge(permute[0]);

}

void edge_map::remove_allele_from_map(const array_index &allele)
{
	for (array_index i=0; i<map_length; i++)
		alleles[i].remove_edge(allele);
}

array_index edge_map::choose_allele_with_fewest_edges(const array_index &allele)
{
	array_index chosen_count=MAX_EDGES+1;
	array_index instances_of_count=0;

	allele_map *a=alleles+allele;

	if (a->get_edge_count()==0)
	{
		// randomly choose a non-zero edge (find alleles with least edges)
		for (array_index i=0; i<map_length; i++)
		{
			array_index current_count=alleles[i].get_edge_count();
			// don't consider alleles with no edges
			if (current_count>0 && current_count<=chosen_count)
				if (current_count==chosen_count)
					chosen_alleles[instances_of_count++]=i;
				else
				{
					instances_of_count=0;
					chosen_count=current_count;
					chosen_alleles[instances_of_count++]=i;
				}
		}
		a=alleles+(chosen_alleles[(random() % instances_of_count)]);
		chosen_count=MAX_EDGES+1;
		instances_of_count=0;
	}

	for (array_index i=0; i<a->get_edge_count(); i++)
	{
		array_index current_count=alleles[a->edges[i]].get_edge_count();
		// don't consider alleles with no edges
		if (current_count<=chosen_count)
			if (current_count==chosen_count)
				chosen_alleles[instances_of_count++]=a->edges[i];
			else
			{
				instances_of_count=0;
				chosen_count=current_count;
				chosen_alleles[instances_of_count++]=a->edges[i];
			}
	}

	return chosen_alleles[random() % instances_of_count];
}


array_index edge_map::get_map_length()
{	return map_length;}

edge_recombination_c::edge_recombination_c()
{
	p1_permutation = new array_index[LDA_c::LDA_length];
	p2_permutation = new array_index[LDA_c::LDA_length];
	child_permutation = new array_index[LDA_c::LDA_length];
	name="edge_recombination_c";
}

edge_recombination_c::~edge_recombination_c()
{
	delete[] p1_permutation;
	delete[] p2_permutation;
	delete[] child_permutation;
}

void edge_recombination_c::cross(candidate *p1, candidate *p2, candidate *c)
{

	map.reset_all();
	// get permutations of p1 and p2 to edge_map
	p1->get_permutation(p1_permutation);
	p2->get_permutation(p2_permutation);

	// add permutations to edge_maps
	map.add_to_edge_map(p1_permutation);
	map.add_to_edge_map(p2_permutation);

	array_index picked_id;
	// set first gene of child permutation to first gene of either p1 or p2

	if (random() % 2==0)
		picked_id=(*p1)[0]->get_id();
	else
		picked_id=(*p2)[0]->get_id();

	array_index map_length=map.get_map_length();

	for (array_index i=0; i<map_length; i++)
	{
		// set ith element of child to picked
		child_permutation[i]=picked_id;
		if (i==map_length-1)
			break;

		// remove picked allele from edge map
		map.remove_allele_from_map(picked_id);

		// find edge map for picked allele - get allele with smallest no of edges
		picked_id=map.choose_allele_with_fewest_edges(picked_id);
	}
	
	c->ordered_chromosome(child_permutation);
	c->invalidate_fitness();
}

crossover* edge_recombination_c::clone()
{
	return new edge_recombination_c;
}




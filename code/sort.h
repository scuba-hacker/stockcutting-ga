#include "define_vars.h"

#ifndef _sort_h
#define _sort_h


class fitness_pair
{
	public:
		array_index id;
		fitness_score key;

		void randomize(array_index new_id);
};

template <class swap_class>
inline void swap(swap_class &a, swap_class &b);

template <class sort_class>
void bubblesort(sort_class *source, unsigned int sourcelength,
									orderproperty direction);

template <class sort_class>
void insertsort(sort_class *source, unsigned int sourcelength,
									orderproperty direction);

template <class sort_class>
void simple_insertsort(sort_class *source, unsigned int sourcelength,
									orderproperty direction);


template <class sort_class>
class quicksort
{
	private:
		sort_class *d;
		int n;
		void quick2_ascend(int left, int right);
		void quick2_descend(int left, int right);
		void quick3_ascend(int left, int right);
		void quick3_descend(int left, int right);
	
	public:
		void sort2(sort_class *data, unsigned int sourcelength,
									orderproperty direction);
		void sort3(sort_class *data, unsigned int sourcelength,
									orderproperty direction);
};

#endif
#include "stdafx.h"
#include "sort.h"
#include "Random Number Generator\randlib.h"

#ifndef random_done
#define random_done
#define random() (ignlgi()-1)
#endif

void fitness_pair::randomize(array_index new_id)
{
	id=new_id;
	key=random();
}


template <class sort_class>
void bubblesort(sort_class *source, int sourcelength,
									orderproperty direction)
{
	bool sorted=false;
	int y=0,x=0;
	switch (direction)
	{
		case DESCENDING:
			for (y=0; y<sourcelength-1; y++)
			{
				sorted=true;
				for (x=0; x<sourcelength-1-y; x++)
					if (source[x].key<source[x+1].key)
					{
						swap(source[x], source[x+1]);
						sorted=false;
					}
				if (sorted) break;
			}
			break;

		case ASCENDING:
			for (y=0; y<sourcelength-1; y++)
			{
				sorted=true;
				for (x=0; x<sourcelength-1-y; x++)
					if (source[x].key>source[x+1].key)
					{
						swap(source[x], source[x+1]);
						sorted=false;
					}
				if (sorted) break;
			}
			break;

		default:
			break;
	}
}


template <class sort_class>
void insertsort(sort_class *source, int sourcelength,
									orderproperty direction)
{
	int j = 0, k = 0;
	sort_class save;

	switch (direction)
	{
		case DESCENDING:
			for (k=sourcelength-1-1; k>=0; k--)
			{
				j=k+1;
				save=source[k];
				while (save.key < source[j].key)
				{
					source[j-1]=source[j];
					j++;
					if (j>sourcelength-1) break;
				}
				source[j-1]=save;
			}
			break;

		case ASCENDING:
			for (k=sourcelength-1-1; k>=0; k--)
			{
				j=k+1;
				save=source[k];
				while (save.key > source[j].key)
				{
					source[j-1]=source[j];
					j++;
					if (j>sourcelength-1) break;
				}
				source[j-1]=save;
			}
			break;

		default:
			break;
	}
}

template <class sort_class>
void simple_insertsort(sort_class *source, int sourcelength,
												orderproperty direction)
{
	int j = 0, k = 0;
	sort_class save;

	switch (direction)
	{
		case DESCENDING:
			for (k=sourcelength-1-1; k>=0; k--)
			{
				j=k+1;
				save=source[k];
				while (save < source[j])
				{
					source[j-1]=source[j];
					j++;
					if (j>sourcelength-1) break;
				}
				source[j-1]=save;
			}
			break;

		case ASCENDING:
			for (k=sourcelength-1-1; k>=0; k--)
			{
				j=k+1;
				save=source[k];
				while (save > source[j])
				{
					source[j-1]=source[j];
					j++;
					if (j>sourcelength-1) break;
				}
				source[j-1]=save;
			}
			break;

		default:
			break;
	}
}

template <class sort_class>
void quicksort<sort_class>::sort2(sort_class *data, 
					int sourcelength, orderproperty direction)
{
	d=data;
	n=sourcelength;
	switch (direction)
	{
		case ASCENDING:
			quick2_ascend(0,n-1);
			break;

		case DESCENDING:
			quick2_descend(0,n-1);
			break;

		default:
			break;
	}
}

template <class sort_class>
void quicksort<sort_class>::sort3(sort_class *data, 
					 int sourcelength, orderproperty direction)
{
	d=data;
	n=sourcelength;
	switch (direction)
	{
		case ASCENDING:
			quick3_ascend(0,n-1);
			break;

		case DESCENDING:
			quick3_descend(0,n-1);
			break;

		default:
			break;
	}
	insertsort(d,n,direction);
}


template <class sort_class>
void quicksort<sort_class>::quick2_ascend(int left, int right)
{
	int j,k;
	if (left < right)
	{
		if (d[left].key>d[right].key)
			swap(d[left],d[right]);
		j=left;
		k=right;
		do
		{
			do
			{
				j++;
			}
			while (d[j].key<d[left].key);

			do
			{
				k--;
			}
			while (d[k].key>d[left].key);
			if (j<k)
				swap(d[j],d[k]);
		}
		while (j<=k);
		swap(d[left],d[k]);
		quick2_ascend(left,k-1);
		quick2_ascend(k+1,right);
	}
}

template <class sort_class>
void quicksort<sort_class>::quick2_descend(int left, int right)
{
	int j,k;
	if (left < right)
	{
		if (d[left].key<d[right].key)
			swap(d[left],d[right]);
		j=left;
		k=right;
		do
		{
			do
			{
				j++;
			}
			while (d[j].key>d[left].key);

			do
			{
				k--;
			}
			while (d[k].key<d[left].key);
			if (j<k)
				swap(d[j],d[k]);
		}
		while (j<=k);
		swap(d[left],d[k]);
		quick2_descend(left,k-1);
		quick2_descend(k+1,right);
	}
}


template <class sort_class>
void quicksort<sort_class>::quick3_ascend(int left, int right)
{
	int j,k;
	if (left<right)
	{
		swap(d[(left+right)/2],d[left+1]);
		if (d[left+1].key>d[right].key) swap(d[left+1],d[right]);
		if (d[left].key>d[right].key) swap(d[left],d[right]);
		if (d[left+1].key>d[left].key) swap(d[left+1],d[left]);
		j=left+1;
		k=right;
		do
		{
			do
			{
				j++;
			}
			while (d[j].key<d[left].key);

			do
			{
				k--;
			}
			while (d[k].key>d[left].key);
			if (j<k)
				swap(d[j],d[k]);

		}
		while (j<=k);
		swap (d[left],d[k]);
		if (k-left>10)
			quick3_ascend(left,k-1);
		if (right-k>10)
			quick3_ascend(k+1,right);
	}
}

template <class sort_class>
void quicksort<sort_class>::quick3_descend(int left, int right)
{
	int j,k;
	if (left<right)
	{
		swap(d[(left+right)/2],d[left+1]);
		if (d[left+1].key<d[right].key) swap(d[left+1],d[right]);
		if (d[left].key<d[right].key) swap(d[left],d[right]);
		if (d[left+1].key<d[left].key) swap(d[left+1],d[left]);
		j=left+1;
		k=right;
		do
		{
			do
			{
				j++;
			}
			while (d[j].key>d[left].key);

			do
			{
				k--;
			}
			while (d[k].key<d[left].key);
			if (j<k)
				swap(d[j],d[k]);

		}
		while (j<=k);
		swap (d[left],d[k]);
		if (k-left>10)
			quick3_descend(left,k-1);
		if (right-k>10)
			quick3_descend(k+1,right);
	}
}


template
void bubblesort(fitness_pair *source, int sourcelength,
									orderproperty direction);
template
void insertsort(fitness_pair *source, int sourcelength,
									orderproperty direction);

template
void simple_insertsort(array_index *source, int sourcelength,
												orderproperty direction);




template <class swap_class>
inline void swap(swap_class &a, swap_class &b)
{
	swap_class temp=a;
	a=b;
	b=temp;
}

template quicksort<fitness_pair>;
template
void swap(array_index &a, array_index &b);


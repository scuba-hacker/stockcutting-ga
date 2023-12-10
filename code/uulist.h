/**************************************************************************************
 * HEADER FILE: ulist.h
 * PURPOSE		: declare templated ulist class
 **************************************************************************************/

#ifndef _ulist_h
#define _ulist_h

#include "define_vars.h"
#include <iostream>

template <class node>
class ulist	
{
	private:
		node *head;															// Points to first node 
		node *tail;															// Points to last node
		node *current;													// Utility pointer
		node *transverse;												// Traverse pointer - controlled
																						// by user using transverse functions
		
		// Search for searchitem using ordering method (COUNTER/DATA)
		node* search(node searchitem, ordering method);
	
		// Search for insertion position for target based upon ordering
		// comparisontype (COUNTER/DATA) and orderproperty direction (ASCENDING/DESCENDING)
		void find_neighbours(node* target, node* &preceding,	node* &proceding,
												ordering comparisontype, orderproperty direction);

	public:
		ulist(void);																			// Default constructor
		ulist(ulist &original);														// Copy constructor
		void clearlist(void);															// Removes all nodes from ulist
		~ulist(void);																			// List destructor function

		// +++++++++++++ AUTOMATIC ORDERING ADD/REMOVE FUNCTIONS +++++++++++++++++++
		// Add copy of newitem to the ulist. Insertion position determined by value
		// of order (COUNTER/DATA) and direction (ASCENDING/DESCENDING) specified
		status add(node newitem, ordering order,	orderproperty direction);
		
		// Remove node containing index or data, contained in item. The search
		// criteria (index/data) is determined by 'method' value, (COUNTER/DATA)
		status remove(node item, ordering method);	

		// Update reference node (which may be found within the ulist) with new_info.
		// Maintain list ordering on order_method/direction.
		status update(node reference, node new_info, ordering update_field,
									ordering order_method, orderproperty direction);
									
		// maintain ulist by adding or updating new_info node
		status maintain(node new_info, ordering order_method, orderproperty direction);
		
		// Append copy of newitem to end of ulist
		status add_to_end(node newitem);
		
		// Search for search_item node using ordering method (COUNTER/DATA)
		status search_node(node &search_item, ordering method);

		// ++++++++++++++++++++++ TRANSVERSE FUNCTIONS +++++++++++++++++++++++++++++	
		status reset_transverse();												// Reset transverse to ulist head
		status get_transverse(node &gotitem);							// Load gotitem with transverse data
		status progress_transverse();											// Move transverse to next node.
		status remove_transverse();												// Remove transverse node
		status transversed_all();													// Are there any nodes left to look at
		status remove_up_to_transverse(node *start);			// Reset transverse to ulist head

		node* get_transverse_node_pointer();							// Get transverse node pointer


		void set_transverse_node_pointer(node* new_transverse);
		
		// ++++++++++++++++++++++ OVERLOADED OPERATORS ++++++++++++++++++++++++++
		friend std::ostream& operator<<(std::ostream& output_stream, const ulist a);																	
		ulist<node>& operator=(ulist<node> &source);
};
#endif
/**************************************************************************************
 * CODE FILE: ulist.c++
 * PURPOSE	: define members of templated ulist class
 **************************************************************************************/
#include "stdafx.h"
#include "uulist.h"
  
// include appropriate header file for each node that we want to make a list out of
#include "gene.h"

// define default constructor
template <class node>
ulist<node>::ulist(void)
{
	head=tail=current=transverse = NULL;												// Initialise ulist empty
}

// define method for clearing ulist of all nodes
template <class node>
void ulist<node>::clearlist(void)
{
	if (reset_transverse()==SUCCESS)														// Reset ulist and remove
		while (remove_transverse()==SUCCESS);											// nodes if ulist not empty
}

// define destructor
template <class node>
ulist<node>::~ulist(void)
{
	clearlist();
}

/*
+++++++++++++++++++++++++++++ SEARCH FUNCTION ++++++++++++++++++++++++++++++++++
If ordering method is COUNTER, search ulist for node with index matching that
contained in searchitem.
If ordering method is DATA, search ulist for node data matching that contained
in searchmitem.
Current is set to the node, if found - else current set to NULL.
The function returns a pointer to the node preceding the searched node.
If searched item not found, previous points to last node in ulist.
If ulist empty, both current and previous are set to NULL.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
node* ulist<node>::search(node searchitem, ordering method)
{
	node *previous;
	current = head;																			// Reset current to start of ulist.
	previous = NULL;																		// Initialise previous pointer.

	if (method == COUNTER)										// Search for node with index=searchitem.index			
		while (current!=NULL && 
					 current->compare_index(current->get_index(),searchitem.get_index()) != EQUAL)																			
  	{	
			previous = current;																			// Maintain previous pointer
  		current = current->get_pointer();												// Progress current pointer
  	}	
  else																				// Search for node with data=searchitem.data	
 		while (current!=NULL && 										
 					current->compare_data(current->get_data(), searchitem.get_data()) != EQUAL)
  	{																					
			previous = current;																			// Maintain previous pointe
  		current = current->get_pointer();												// Progress current pointer
  	}																								

	return previous;
} 


/*
+++++++++++++++++++++++ FIND_NEIGHBOURS FUNCTION +++++++++++++++++++++++++++++++
This function finds the position in the ulist where target should be inserted.
The position is determined on either index or data values, specified by
'comparisontype'.
To perform the search, the form of the ordering must be specified in 'direction'
as being ASCENDING or DESCENDING.
Pointers to preceding and proceding nodes to this position are returned.
If either of these nodes do not exist, the respective pointer is set to NULL.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
void ulist<node>::find_neighbours(node *target, node* &preceding, node* &proceding,
																	 ordering comparisontype, orderproperty direction)
{
	current = head;																			// Reset current to start of ulist.
	preceding = NULL;																		// Initialise previous pointer.

	compare operation;		// Store comparison method for comparing index/data of two nodes.
	
	if (direction == ASCENDING)
		operation=LARGER;													// Nodes get larger from head->tail of list
	else
		operation=SMALLER;												// Nodes get smaller from head->tail of list
	
	if (comparisontype == COUNTER)				// Use compare_index functions to search on index
		while (current!=NULL &&	
					 current->compare_index(current->get_index(), target->get_index())!=operation)
		{																	
			preceding = current;							
			current = current->get_pointer();	
		}
	else																	// Use compare_data functions to search on data
		while (current!=NULL &&								
			 current->compare_data(current->get_data(),
			 											 target->get_data())!=operation)
		{																			
			preceding = current;								
			current = current->get_pointer();
		}

	if (preceding!=NULL)											// Insertion point NOT at head of list... 
		proceding = preceding->get_pointer(); 	// 'proceding' is next node after 'preceding'
	else																			// Insertion point IS at head of list...
		proceding = head;												// Preceding is NULL, so proceding is head

}

// define overloaded output operator
template <class node>
ostream& operator<<(ostream& output_stream, ulist<node> a)
{	
	if (a.head != NULL)														// If ulist not empty
	{	
		a.current = a.head;													// Starting at the head of the list...
		do
		{
			a.current->print_node();									// Print out individual node data
			a.current = a.current->get_pointer();			// Traverse to next node in ulist.
			if (a.current != NULL)										// Separate node outputs with single space
				output_stream << " ";												
		}
		while (a.current != NULL);									// Repeat for all nodes in ulist
		output_stream << '\n';											// Separate ulist output with newline
	}
	else
		output_stream << "This u-list is empty\n";
	return output_stream;
}


/* 
++++++++++++++++++++++++++++ REMOVE FUNCTION +++++++++++++++++++++++++++++++++++
This function will search for removeitem node in the ulist and remove the node
from the ulist. It will match either the index or the data item when applying the
search algorithm. The search method is determined by the 'ordering method' :
method=COUNTER -> search on index	for node to remove
method=DATA		->	search on data for node to remove
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
status ulist<node>::remove(node removeitem, ordering method)
{
	node *previous;													// points to node previous to that being removed
	
	// ************************* TEST BLOCK remove.1 ****************************
	previous=search(removeitem, method);	 				// Set current to the node to be removed.
																								// Set previous to node following current.
	if (current==NULL)	 													// Ulist empty or node not found - FAILURE
		return FAILURE;
		
	// ************************* TEST BLOCK remove.2 ****************************
	if (previous==NULL)																// ### DELETION AT HEAD OF LIST ###
	{																				
		current=current->get_pointer();									// current set to new head of ulist.
		
		if (transverse == head)													// If transverse node being removed...
			transverse = head->get_pointer();							// Update to point to new head of list

		if (tail == head)																// If tail node being removed...
			tail = NULL;																	// tail now points to NULL, empty list
			
		delete head;																		// Delete node at head of ulist
		head = current;																	// Update head to new head of ulist
	}
	
	// ************************* TEST BLOCK remove.3 ****************************
	else																		// ### Deletion in middle or end of ulist. ###
	{																	
		previous->set_pointer_to(current->get_pointer()); 	// delink current node from ulist
		
		if (current == tail)																// If tail node being removed...
			tail = previous;																	// tail now points to new tail

		if (current == transverse)													// If transverse node removed...
			if (current->get_pointer() != NULL)								// & transverse NOT at end of list
				transverse = current->get_pointer(); 						// Move transverse to next node
			else																							// Tranverse IS at end of list
				transverse = previous;													// Move transverse to prev node
					
		delete current;																			// Deallocate removed node
		current = previous;																	// current points to previous node
	}

	return SUCCESS;																				// Removal successful
};


/*
++++++++++++++++++++++++++++ ADD_TO_END FUNCTION +++++++++++++++++++++++++++++++
This function appends a copy of newitem node to the end of the ulist.
If the index of newitem has not been set the index of the new node is
derived by calling set_to_next_index on the index of the last node of the ulist.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
status ulist<node>::add_to_end(node newitem)
{
	node *newnode;
	newnode = new node;																			// Allocate memory for new node
	
	if (newnode == NULL)																		// Out of memory condition
	{
		cout << "ADD_TO_END: reports out of memory!";
		return FAILURE;
	}
	
	*newnode = newitem;																	// Load new node with supplied data

	// *********************** TEST BLOCK add_to_end.1 **************************
	if (head == NULL)																// ######  Append to empty ulist #######
	{
		if (newitem.get_index()==node::undefined_index)						// If index is undefined...
			newnode->set_to_first_index();
		head = transverse = (tail = newnode);											// New node is head and tail
	}
	
	// *********************** TEST BLOCK add_to_end.2 **************************
	else																						// ##### Append to non-empty ulist #####
	{
		if (newitem.get_index()==node::undefined_index)			// If index is undefined...								
			newnode->set_to_next_index(tail->get_index());
		tail->set_pointer_to(newnode);											// Make newnode last node in list
		tail=newnode;																				// Move tail to end of ulist
	}
	
	tail->set_pointer_to(NULL);													// Terminate end of ulist with NULL.
	return SUCCESS;
}

/*
++++++++++++++++++++++++++++ MAINTAIN FUNCTION +++++++++++++++++++++++++++++++++++++++++++
This function checks to see if a node with index==new_info.index or data=new_info.data
(depending upon value of structure_order (COUNTER/DATA)) is present in the ulist. If it
is, then this node has its member that IS NOT SPECIFIED by structure_order, updated
with the appropriate value in new_info node. If the node is not present in the list, 
newinfo node is added to the ulist. Unique list is maintained, ordering is maintained.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>	
status ulist<node>::maintain(node new_info,
														 ordering structure_order, orderproperty direction)
{
	ordering update_field;
	
	node *previous=search(new_info, structure_order);				// Search for the reference node
	if (current==NULL)																			// Node not found...
		return add(new_info, structure_order, direction);			// Attempt an add of the node
	else																										// Node is found...
	{
		switch (structure_order)
		{
			case COUNTER:																				// Search was on COUNTER,
				update_field=DATA;																// so copy across newinfo.data
				break;
			case DATA:																					// Search was on DATA,
				update_field=COUNTER;															// so copy across newinfo.index
				break;
			default:
				cout << "Invalid structure_order ordering enum value\n";
				return FAILURE;
				break;
		}
		// Attempt an update of the update_field of the ulist node searched on above
		return update (*current, new_info, update_field, structure_order, direction);
	}
}

// Define public method of determining presence of node in ulist.
template <class node>
status ulist<node>::search_node(node &search_item, ordering method)
{
	node* previous = search(search_item, method);						// Search match is method field 
	
	if (current==NULL)																			// Node not found
		return FAILURE;
	else																										// Node found
	{
		search_item=*current;																	// Pass back found node
		return SUCCESS;
	}
}

/*
++++++++++++++++++++++++++++ UPDATE FUNCTION +++++++++++++++++++++++++++++++++++++++++++
This function updates a node in ulist with new_info.
The node for updating is found by searching on the COUNTER or DATA field of 'reference'.
The found node is referred to as the 'working node'.
The field for searching on is stored in 'structure_order'.
The field that we want to update is specified in 'update_field'.
This field is copied across from 'reference' to the 'working node'.
If the resulting 'working node' corrupts ulist ordering, specified by 'structure_order'
(COUNTER/DATA) and 'direction' (ASCENDING/DESCENDING) - it is moved to the correct 
position in the ulist.
The list is assumed to be unique on 'structure_order' field. If an update is performed
which breaks the unique property of the list, the update request is refused and FAILURE
returned.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
status ulist<node>::update(node reference, node new_info, ordering update_field,
													 ordering structure_order, orderproperty direction)
{
	compare left_size=SMALLER, right_size=SMALLER;					// Store node comparisons
	node* previous=search(reference, structure_order);			// Search for 'reference' node
	if (current==NULL)																			// list empty or node not found
		return FAILURE;
	
	node *following = current->get_pointer();								// Set pointer to following node 
	
	compare left_comparator, right_comparator;							// Store node comparators
	
	switch (direction)
	{
		case ASCENDING:														// list is ordered in an ASCENDING fashion
			left_comparator=LARGER;
			right_comparator=SMALLER;
			break;
			
		case DESCENDING:													// ulist is ordered in a DESCENDING fashion
			left_comparator=SMALLER;
			right_comparator=LARGER;
			break;
		default:
			cout << "invalid direction enum value\n";
			return FAILURE;
			break;
	}
	
	int move_original_node;								// Is non-zero if updated node needs to be moved.
	
	switch (structure_order)				// Establish if updated node will corrupt ulist ordering
	{
		case COUNTER:																								// Search done on COUNTER
			// move original node if index ordering not correct for:previous, current, following
			move_original_node=
				(previous!=NULL &&  (left_size=previous->compare_index
					(previous->get_index(),  new_info.get_index())) == left_comparator ||
				 following!=NULL && (right_size=following->compare_index
				  (following->get_index(), new_info.get_index())) == right_comparator );
			break;
			
		case DATA:																									// Search done on DATA
			// move original node if data ordering not correct for:previous, current, following
			move_original_node=
				(previous!=NULL && (left_size=previous->compare_data
				 (previous->get_data(),new_info.get_data())) == left_comparator   ||
				following!=NULL && (right_size=following->compare_data
				 (following->get_data(), new_info.get_data())) == right_comparator );
			break;
		default:
			cout << "invalid structure_order enum value\n";
			return FAILURE;
			break;
	}
	
	if (move_original_node)															// Move the node to correct ordering
	{	
		switch (update_field)
		{
			case COUNTER:																					// COUNTER field to be updated
				reference.set_data(current->get_data());						// Keep data field preserved
				break;
			case DATA:																						// DATA field to be updated
				reference.set_index(current->get_index());					// Keep index field preserved
				break;
			default:
				cout << "invalid update_field enum value\n";
				return FAILURE;
				break;
		}
		
		remove(reference, structure_order);								// Remove original node
		add(new_info, structure_order, direction);				// Put node back in correct position
	}
	else																								// Node does not need to be moved
	{
		if (left_size==EQUAL || right_size==EQUAL)			// Check for non-uniqueness both sides
			return FAILURE;																	// FAILURE if non-unique on either side
		else																									// Unique check ok
			switch (update_field)
			{	
				case COUNTER:																			// Update COUNTER of ulist node
					current->set_index(new_info.get_index());				// Copy across index value
					break;
				case DATA:																				// Update DATA of ulist node
					current->set_data(new_info.get_data());					// Copy across data value
					break;
				default:
					cout << "invalid update_field enum value\n";
					return FAILURE;
					break;
			}
	}
	return SUCCESS;																							// Update Successful
}



/*
++++++++++++++++++++++++++++ ADD FUNCTION ++++++++++++++++++++++++++++++++++++++
This function adds a copy of newitem to the ulist. The insertion position is
determined using:
1)	ordering order : order=COUNTER		-		Item is added according to index value
										 order=DATA				-		Item is added according to data value
2)	orderproperty direction : 
										 direction=ASCENDING  - ordered item increases down ulist
					 					 direction=DESCENDING - ordered item decreases down ulist

The addition occurs in such a position as to keep the ordering of the ulist
consistent with the above conditions. Nodes must be unique in the field specified
by 'order'.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
status ulist<node>::add(node newitem, ordering order, orderproperty direction)
{
	node *previous;												//	Required for calling function find_neighbours.
	node *following;											//	Required for calling function find_neighbours.
	node *newnode;												//	Used to point to the new node to be added.
	
	newnode = new node;																		// Allocate memory for new node
	if (newnode==NULL)																		// Allocation failed
	{
		cout << "ADD FUNCTION: Out of memory\n";
		return FAILURE;
	}										
											
	*newnode = newitem;																		// Copy in the newitem data
	newnode->set_pointer_to(NULL);												// Newnode forced to point to NULL
	
	// *************************** TEST BLOCK add.1 *****************************
	if (head == NULL)																			// # insertion into empty ulist #
	{
		head = tail = current = (transverse = newnode);			// Initialise all private pointers
		return SUCCESS;
	}
	else
		current = head;																			// Reset current to head of ulist
	
	
	// Get pointers to nodes which precede and procede insertion position, determined by
	// 'order' (COUNTER/DATA) and 'direction' (ASCENDING/DESCENDING).
	find_neighbours(newnode, previous, following, order, direction);
		
	switch (order)
	{
		case COUNTER:																						// Check COUNTER values unique
			if ((previous!=NULL  &&	 previous->compare_index
						( previous->get_index(), newnode->get_index())==EQUAL) ||
					(following!=NULL && following->compare_index
						(following->get_index(), newnode->get_index())==EQUAL ) )
				return FAILURE;																				// Return FAILURE if non-unique
			break;

		case DATA:																							// Check DATA values unique
			if ((previous!=NULL  &&	 previous->compare_data
						( previous->get_data(), newnode->get_data())==EQUAL) ||
					(following!=NULL && following->compare_data
						(following->get_data(), newnode->get_data())==EQUAL ) )
				return FAILURE;																				// Return FAILURE if non-unique
			break;
	}
	
	// *************************** TEST BLOCK add.2 *****************************
																											// ##### ADD TO END OF LIST #####
	if (following == NULL)															// Node not found by find_neighbours
	{
		previous->set_pointer_to(newnode);								// Set preceding node to newnode
		current=tail = newnode;														// Update current and tail
	}
	
	// *************************** TEST BLOCK add.3 *****************************
	else
	{
		if (previous == NULL)															// ##### ADD BEFORE HEAD IN LIST ###
		{
			newnode->set_pointer_to(head);									// Make newnode head of ulist
			head = current = newnode;												// and set current to head
		}																

	// *************************** TEST BLOCK add.4 *****************************
		else																							// ###ADD NODE IN MIDDLE OF LIST###
		{	
			previous->set_pointer_to(newnode);							// Set preceding node to newnode
			newnode->set_pointer_to(following);							// Set newnode to proceding node
			current = newnode;															// Set current to newnode
		}
	}
	return SUCCESS;																			// Add was successful
};

/*
++++++++++++++++++++++++ RESET_TRANSVERSE FUNCTION +++++++++++++++++++++++++++++
This function sets transverse pointer to the head of the ulist.
Return FAILURE if ulist is empty, otherwise Return SUCCESS
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
status ulist<node>::reset_transverse()
{
// **************************** TEST BLOCK reset.1 ****************************
	if (head == NULL)																													// Empty ulist
		return FAILURE;
// **************************** TEST BLOCK reset.2 ****************************
	else																		// Set transverse to point to the head of ulist
	{
		transverse = head;
		return SUCCESS;
	}
}

/*
++++++++++++++++++++++++ GET_TRANSVERSE FUNCTION +++++++++++++++++++++++++++++++
This function copies the node pointed to by transverse into 'gotitem' which is
returned back to the calling routine by reference.
Return FAILURE if ulist is empty, otherwise return SUCCESS.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
status ulist<node>::get_transverse(node &gotitem)
		// Return the object pointed to by transverse. If ulist is empty,
		// return status FAILURE, else SUCCESS.
{

// **************************** TEST BLOCK get.1 ******************************
	if (transverse != NULL)														// If ulist not empty...
	{
		gotitem = *transverse;													// Copy node pointed to by transverse
		return SUCCESS;																	// to gotitem, and return SUCCESS.
	}
// **************************** TEST BLOCK get.2 ******************************
	else
		return FAILURE;																		// ulist empty
}

/*
+++++++++++++++++++++++++ PROGRESS_TRANSVERSE FUNCTION +++++++++++++++++++++++++
This function will move transverse to point to the next node in the ulist.
If the ulist is empty, or transverse is already at the end of the ulist, FAILURE
is returned. Otherwise, SUCCESS is returned.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
status ulist<node>::progress_transverse()
{
// ************************** TEST BLOCK progress.1 ***************************
	if (transverse != NULL && transverse->get_pointer() != NULL)
	{
		transverse = transverse->get_pointer();			// Progress through ulist by one
		return SUCCESS;															// node and return SUCCESS.	
	}
	else
// ************************** TEST BLOCK progress.2 ***************************
		return FAILURE;
}

/*
++++++++++++++++++++++ REMOVE_TRANSVERSE FUNCTION ++++++++++++++++++++++++++++++
This function deletes the node that transverse points to. FAILURE is returned if
ulist is empty. Transverse is set to point to the next node in the ulist. If there
is no next node, then transverse is set to the previous node to that deleted.
If the ulist becomes empty, transverse is set to NULL.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
status ulist<node>::remove_transverse()
{
	node* preceding=NULL;								// stores the pointer to the node before transverse
	if (transverse != NULL)																						// ulist not empty...
	{
		current = head;
		while (current!=transverse)															// Setup up preceding pointer
		 {																					
			preceding = current;
 		 	current = current->get_pointer();	
	 	 }

	// ************************ TEST BLOCK rem_trans.1 **************************
		if (transverse == head)											// ##### REMOVE FROM HEAD OF LIST #####
		{			
			transverse=transverse->get_pointer();			// Set transverse to next node.
			delete head;															// Deallocate memory held by removed node.
			head=current = transverse;								// Update head and current pointers.
			
			if (head == NULL)													// Empty list - so update tail pointer
				tail = NULL;
		}
		
	// *********************** TEST BLOCK rem_trans.2 ***************************
		else																	// ##### REMOVE FROM ANYWHERE EXCEPT HEAD #####
		{
			preceding->set_pointer_to(transverse->get_pointer());	// remove transverse from list
			if (current == tail)																	// Move tail back one node
				tail = preceding;																		// if last node being removed.
			delete current;																				// Deallocate node.
			
			if (preceding->get_pointer() == NULL)									// Removal from end of list
				transverse = preceding;
			else																									// Removal from mid-list
				transverse = preceding->get_pointer(); 
			current = head;
		}
		return SUCCESS;																					// Successful removal
	}
	
	// *********************** TEST BLOCK rem_trans.2 ***************************
	else
		return FAILURE;																						// List empty.
}

template <class node>
status ulist<node>::remove_up_to_transverse(node *start)			// Reset transverse to ulist head
{
	// note: this function *assumes* that start points to a node previous to transverse
	// in the list. start pointer is assumed to be valid

	// 

	if (start==transverse)
		return SUCCESS;

	node *previous=head;

	if (start!=head)
	{
		// find node previous to start
		while (previous->get_pointer()!=start)
			previous=previous->get_pointer();
	}
	else
		head=transverse;

	// delete intermediate nodes
	node *next_node;
	do
	{
		next_node=start->get_pointer();
		delete start;
		start=next_node;
	}
	while (next_node!=transverse);

	// link previous to transverse
	if (head!=transverse)
		previous->set_pointer_to(transverse);

	return SUCCESS;
}



/*
+++++++++++++++++++++++++ OVERLOAD EQUALS OPERATOR +++++++++++++++++++++++++++++
This function first empties the target (this) of any nodes. Then if source ulist
is not empty, all nodes in source are added in sequence to the target.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
ulist<node>& ulist<node>::operator=(ulist<node> &source)
{
	node working;
	clearlist();																						// Initialise 'this'																						
	if (source.reset_transverse() == SUCCESS)								// If source is not empty...
	{
		do
		{
			source.get_transverse(working);											// Get one node from source.
			add_to_end(working);																// Add the node to 'this'.
		}
		while (source.progress_transverse() == SUCCESS);			// Copy all nodes in source list
	}
	return *this;
}

/*
+++++++++++++++++++++++++++ COPY CONSTRUCTOR +++++++++++++++++++++++++++++++++++
This function uses the overloaded equals operator to make a copy of original
ulist.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
template <class node>
ulist<node>::ulist(ulist<node> &original)
{
	head=tail=current=transverse = NULL;										// Initialise all pointers
	*this=original;																					// Call equals operator
}

// Define method of obtaining transverse pointer
template <class node>
node* ulist<node>::get_transverse_node_pointer()
{ return transverse; }

// Set transverse node pointer
template <class node>
void ulist<node>::set_transverse_node_pointer(node* new_transverse)
{ transverse=new_transverse; }

template <class node>
status ulist<node>::transversed_all()							// Are there any nodes left to look at
{ return ((transverse->get_pointer()==NULL) ? SUCCESS : FAILURE); }


// Make explicit instantiations of all types of ulist required
template class ulist<edge_node>;


// make explicit instantiations of friend functions for each ulist required
ostream& operator<<(ostream& output_stream, ulist<edge_node> a);

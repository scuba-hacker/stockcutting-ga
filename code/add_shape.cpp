void LDA_new::add_shape_at_place_6(shape_g_l &chosen_gene, const edge_list_t adjust_edge_list)
{
	shape_g item=chosen_gene;
	ulist<edge_node> *list;
	xy_size_t item_p_size;											// item size parallel to edge direction
	pos_t coord::*p_pos;												// position parallel to edge direction
	pos_t coord::*o_pos;												// position orthogonal to edge direction
	pos_t (edge_node::*get_p_pos)();						// get position parallel to edge direction function
	pos_t (edge_node::*get_o_pos)();						// get position orthogonal to edge direction function
	void (edge_node::*set_p_pos)(const pos_t&);	// set position parallel to edge direction function
	switch (adjust_edge_list)
	{
		case MODIFY_LEFT_PROFILE:
			list=&edge_list;
			edge_node::compare_method=&edge_node::compare_index_y;
			item_p_size=item.height();
			p_pos=&coord::y_pos;
			o_pos=&coord::x_pos;
			get_p_pos=&edge_node::get_y_pos;
			get_o_pos=&edge_node::get_x_pos;
			set_p_pos=&edge_node::set_y_pos;
			break;
		case MODIFY_TOP_PROFILE:
			list=&edge_list_2;
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
	switch (adjust_edge_list)
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
	edge_node *previous_edge=NULL, *start_edge;
	list->reset_transverse();
	do
	{
		start_edge=list->get_transverse_node_pointer();
		if ((start_edge->*get_o_pos)()==(new_edge.*get_o_pos)() &&
				(start_edge->*get_p_pos)()+(pos_t)start_edge->get_data()==
				(pos_t)(new_edge.*get_p_pos)())
		{
			previous_edge=start_edge;
			break;
		}
	}
	while (list->progress_transverse()==SUCCESS);
	list->reset_transverse();
	do
	{
		start_edge=list->get_transverse_node_pointer();
	}
	while ((start_edge->*get_p_pos)()+(pos_t)start_edge->get_data()<=(new_edge.*get_p_pos)() &&
					list->progress_transverse()==SUCCESS);
	edge_node *first_edge=start_edge;
	pos_t start_offset=(new_edge.*get_p_pos)() - (first_edge->*get_p_pos)();
	pos_t accumulated_edge=-start_offset;
	do
	{
		accumulated_edge+=list->get_transverse_node_pointer()->get_data();
		if ((list->get_transverse_node_pointer()->*get_o_pos)()>(new_edge.*get_o_pos)())
			start_edge=start_edge->get_pointer();
	}
	while (accumulated_edge<(pos_t)item_p_size && list->progress_transverse()==SUCCESS);
	xy_size_t first_edge_length=first_edge->get_data();
	coord first_edge_position=first_edge->get_index();
	coord start_edge_position=start_edge->get_index();
	edge_node* last_edge_affected=list->get_transverse_node_pointer();
	coord last_edge_position=last_edge_affected->get_index();
	xy_size_t last_edge_length=last_edge_affected->get_data();
	if ((new_edge.*get_o_pos)() <= (last_edge_affected->*get_o_pos)() &&
			(new_edge.*get_p_pos)()+item_p_size <= (last_edge_affected->*get_p_pos)()+last_edge_affected->get_data())
		return; // no changes to make to edge profile as new shape is invisible to left profile
	list->remove_up_to_transverse(start_edge); // remove any edges bypassed by new edge
	xy_size_t remaining=accumulated_edge-item_p_size;	
	if (remaining==0)								
		list->remove_transverse();				// last edge affected completely overlapped - remove last edge
	else
	{
		last_edge_position.*p_pos+=last_edge_length-remaining;
		last_edge_affected->set_index(last_edge_position);
		last_edge_affected->set_data(remaining);
	}
	if (first_edge_position.*o_pos>(new_edge.*get_o_pos)())
	{
		new_edge.set_data(new_edge.get_data()-(start_edge_position.*p_pos-(new_edge.*get_p_pos)()));
		(new_edge.*set_p_pos)(start_edge_position.*p_pos);
	}
	if (previous_edge==NULL)
		list->add(new_edge, COUNTER, ASCENDING);
	else
		previous_edge->set_data(previous_edge->get_data()+new_edge.get_data());
}






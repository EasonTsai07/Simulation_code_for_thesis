#ifndef _NODE_MANNAGER_H_

#define _NODE_MANNAGER_H_

#include <iostream>
#include <vector>

#include "Node.h"
#include "Event.h"

extern double System_time;
extern int N_receive;
extern int n_collison;

class Node_manager{

public:

	Node_manager();
	//~Node_manager();

	inline int length(){ return node_list.size(); }
	inline int get_lower_bound(int mode){ return low_bound[mode]; }

	void add_node(Ue_node_p_aloha node);
	void add_event(Sys_event sevent);
	void join_mode(Ue_node_p_aloha node);
	void mode_alloc_channel();
	void new_mode_alloc_channel();
	void calc_lower_bound();
	void node_alloc_channel();
	//void output_nodes();
	void set_event();
	void check_collision();
	void handle_event();
	void new_handle_event();
	void update_event();
	void get_round_info();

	int assign_channel(int mode);
	int count;

protected:


private:

	std::vector<Sys_event> event_list;
	std::vector<Ue_node_p_aloha> node_list;

	int list_lenght;
	int channel_avail[MODE + 1];
	int mode_amount[MODE + 1];
	int low_bound[MODE + 1];

};




#endif 

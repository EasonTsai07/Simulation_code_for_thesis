#include <stdio.h>  

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>

#include "Config.h"
#include "Node.h"
#include "Node_Manager.h"
#include "Event.h"

using namespace std;

unsigned long packet_index = 0;

fstream out_put_src, out_put_nodes, fsrc_axis, fnodes_axis , receive_data;

Node_manager::Node_manager(){

	list_lenght = 0;
	node_list.clear();
	event_list.clear();
	memset(channel_avail, 0, MODE + 1);
	memset(mode_amount, 0, MODE + 1);
	memset(low_bound, 0, MODE + 1);
	count = 1;

}

void Node_manager::mode_alloc_channel(){

	int ness_channel = 0;
	int i = 0;

	for (i = 0; i < MODE + 1; ++i){
		if (mode_amount[i] != 0){

			++channel_avail[i];
			++ness_channel;

		}
	}

	int avail_channel = CHANNEL - ness_channel;

	//cout << "avail_channel = " << avail_channel << endl;

	while (avail_channel >= ness_channel){
		int number = 0, total = 0;
		for (i = 0; i < MODE + 1; ++i){

			//cout << "avail_channel =  " << avail_channel << endl;
			number = floor(avail_channel * ((float)mode_amount[i] / (float)N_UE));
			//printf("mode_amount[%d] = %d \n", i, mode_amount[i]);
			//cout << "number =  " << number << endl;
			channel_avail[i] = channel_avail[i] + number;
			total = total + number;

		}

		avail_channel = avail_channel - total;

	}

	//cout << "avail_channel = " << avail_channel << endl;

	//int temp[MODE + 1];

	int Max = 0, index = 0;

	//memcmp(temp, channel_avail, sizeof(channel_avail));

	if (avail_channel < ness_channel){

		int Max = 0, index = 0;

		for (i = 0; i < MODE + 1; ++i){

			if (mode_amount[i]>Max){

				Max = mode_amount[i];
				index = i;

			}

		}

		channel_avail[index] = channel_avail[index] + avail_channel;
		avail_channel = 0;

	}
	//cout << ness_channel << "Mode has been alloc" << endl;

	for (i = 0; i < MODE + 1; ++i){

	cout << "Mode : " << i << " has allocate " << channel_avail[i] << " channel" << endl;

	}

}

void Node_manager::new_mode_alloc_channel(){

	int ness_channel = 0;
	int i = 0;

	for (i = 0; i < MODE + 1; ++i){
		if (mode_amount[i] != 0){

			++channel_avail[i];
			++ness_channel;

		}
	}

	int avail_channel = CHANNEL - ness_channel;

	cout << "avail_channel = " << avail_channel << endl;

		channel_avail[MODE-2] = channel_avail[MODE-2] + avail_channel;
		avail_channel = 0;

	

	for (i = 0; i < MODE + 1; ++i){

		cout << "Mode : " << i << " has allocate " << channel_avail[i] << " channel" << endl;

	}

}

void Node_manager::join_mode(Ue_node_p_aloha node){

	++mode_amount[node.get_mode()];

}

void Node_manager::add_node(const Ue_node_p_aloha node){

	Node_manager::node_list.push_back(node);

}

void Node_manager::calc_lower_bound(){

	int i = 0;

	for (i = 0; i < MODE + 1; ++i){

		int count = 0, total = 0;

		while (count < i){

			total = total + channel_avail[count];
			++count;

		}

		low_bound[i] = total;
		//cout << "Mode " << i << " lower bound : " << low_bound[i] << endl;

	}

}

void Node_manager::node_alloc_channel(){


	int mode = 0;
	int channel = 0;
	int up_bound = 0;


	for (int i = 0; i < N_UE; ++i){

		mode = Node_manager::node_list[i].get_mode();
		up_bound = low_bound[mode] + channel_avail[mode];
		channel = rand() % (up_bound - low_bound[mode]) + low_bound[mode] + 1;
		//cout << "Mode " << mode << " allocate channel " << channel << endl;
		Node_manager::node_list[i].set_channel(channel);

	}

}

/*void Node_manager::output_nodes(){

	int i = 0;
	
	vector<string> nodes;
	ofstream output_file("./Nodes.txt");
	//ostream_iterator<std::string> output_iterator(output_file, "\n");

	//string myvar;

	//fstream node_file, broadcast_file;
	//node_file.open("Nodes.txt", ios::out | ios::trunc);

	if (!node_file.is_open()){

		cout << stderr << "Node file open failed! " << endl;
		exit(1);
	}

	for (i = 0; i < Node_manager::node_list.size(); ++i){

		nodes.push_back("Node index :");
		myvar = to_string(Node_manager::node_list[i].get_index());
		nodes.push_back(myvar);
		nodes.push_back("Axis X :");
		myvar = to_string(Node_manager::node_list[i].get_axis_x());
		nodes.push_back(myvar);
		nodes.push_back("Axis Y :");
		myvar = to_string(Node_manager::node_list[i].get_axis_y());
		nodes.push_back(myvar);
		nodes.push_back("Velocity : ");
		myvar = to_string(Node_manager::node_list[i].get_v());
		nodes.push_back(myvar);
		nodes.push_back("Theta : ");
		myvar = to_string(Node_manager::node_list[i].get_theta());
		nodes.push_back(myvar);
		nodes.push_back("Status : ");
		myvar = to_string(Node_manager::node_list[i].get_Status());
		nodes.push_back(myvar);
		nodes.push_back("Transmit Prob : ");
		myvar = to_string(Node_manager::node_list[i].get_p());
		nodes.push_back(myvar);
		nodes.push_back("Mode : ");
		myvar = to_string(Node_manager::node_list[i].get_mode());
		nodes.push_back(myvar);
		nodes.push_back("Allocate Channel: ");
		myvar = to_string(Node_manager::node_list[i].get_channel());
		nodes.push_back(myvar);
		nodes.push_back("*******************************************");
		
		//node_file.write(nodes,);

	}

	copy(nodes.begin(), nodes.end(), output_iterator);
	//node_file.close();

}*/

void Node_manager::add_event(Sys_event sevent){

	Node_manager::event_list.push_back(sevent);

}

void Node_manager::set_event(){

	register int i;
	int next_c = 0;
	double delay_n = 0,trans_time=0,next_activate = 0;

	for (i = 0; i < N_UE; ++i){

		if (Node_manager::node_list[i].get_Status() == TRANSMITTER && Node_manager::node_list[i].get_p() <= PROB){

			if (fabs(Node_manager::node_list[i].node_time() - System_time) < MIN_T_UNIT){

				if (Node_manager::node_list[i].announcement() == true){

					Sys_event trans_event;
					trans_event.set_announce_source(Node_manager::node_list[i].get_axis_x(), Node_manager::node_list[i].get_axis_y());
					trans_event.type_declare(TRANSMIT);
					Node_manager::node_list[i].channel_announcement(false);
					trans_time = System_time + DATA_PACKET_SIZE / BANDWIDTH;
					trans_event.alive_time(System_time,trans_time);
					trans_event.assign_next_channel(Node_manager::node_list[i].get_channel());
					++packet_index;
					trans_event.event_index = packet_index;
					Node_manager::add_event(trans_event);
					Node_manager::node_list[i].assign_p_random();
					next_activate = trans_time + (1)*MIN_T_UNIT;
					Node_manager::node_list[i].set_time(next_activate);
					Node_manager::node_list[i].move(MIN_T_UNIT,FREE);
					++Node_manager::node_list[i].k_limit;
					cout << "Node " << i << " has send data packet  on channel " << trans_event.transmit_channel() << " at " << System_time << endl;
					
				}
				else if (Node_manager::node_list[i].announcement() == false){

					Sys_event control_event;
					control_event.set_announce_source(Node_manager::node_list[i].get_axis_x(), Node_manager::node_list[i].get_axis_y());
					control_event.type_declare(CONTORL);
					next_c = Node_manager::assign_channel(Node_manager::node_list[i].get_mode());
					control_event.assign_next_channel(next_c);
					control_event.set_event_mode(Node_manager::node_list[i].get_mode());
					Node_manager::node_list[i].channel_announcement(true);
					Node_manager::node_list[i].set_channel(next_c);
					trans_time = System_time + CONTROL_PACKET_SIZE / BANDWIDTH;
					control_event.alive_time(System_time, trans_time);
					++packet_index;
					control_event.event_index = packet_index;
					Node_manager::add_event(control_event);
					//cout << "Event alive time = " << control_event.event_strat_time() << " ~ " << control_event.event_end_time() << endl;
					//Node_manager::node_list[i].assign_p_random();
					next_activate = trans_time + (rand() % TIME_SHIFT + 5)*MIN_T_UNIT;
					Node_manager::node_list[i].set_time(next_activate);
					Node_manager::node_list[i].move(MIN_T_UNIT, FREE);
					cout << "Node " << i << " has send control packet on mode " << control_event.get_src_mode() << " at " << System_time << endl;
					//cout << "Control event in ( " << Node_manager::node_list[i].get_axis_x() << " , " << Node_manager::node_list[i].get_axis_y() << " ) will transmit at channel " << next_c << endl;
					//cout << "Event alive time " << System_time << " to " << trans_time << endl;

				}

			}

		}
		if (Node_manager::node_list[i].get_Status() == TRANSMITTER && Node_manager::node_list[i].get_p() > PROB){

			if (fabs(Node_manager::node_list[i].node_time() - System_time) < MIN_T_UNIT){

				Node_manager::node_list[i].assign_p_random();
				delay_n = System_time +  (DATA_PACKET_SIZE / BANDWIDTH);
				Node_manager::node_list[i].set_time(delay_n);
				Node_manager::node_list[i].move(MIN_T_UNIT, FREE);
				//cout << "Node " << i << " has send packet failed !" << " Next activate time " << delay_n << endl;
			}
			
		}

	}
	//cout << "Event alive time end = " << event_list[0].event_strat_time() << " ~ " << event_list[0].event_end_time() << endl;
}

/*void Node_manager::handle_event(){

	register int i = 0 , j = 0 , check = 0;
	float c_x = 0, c_y = 0, t_x = 0, t_y = 0;
	double r_duration = 0 , delay_n = 0;

	//cout << "Size of event_list " << Node_manager::event_list.size() << endl;

	for (i = 0; i < Node_manager::event_list.size(); ++i){

		if (Node_manager::event_list[i]._is_activate(System_time) && Node_manager::event_list[i]._is_collision() == false){

			cout << "Event " << i << " is activate !" << endl;
			//cout << "Event alive time = " << event_list[i].event_strat_time() << " ~ " << event_list[i].event_end_time() << endl;

			for (j = 0; j < N_UE; ++j){

				if (Node_manager::event_list[i].get_type() == CONTORL && Node_manager::node_list[j].get_Status() == IDLE){

					//cout << "Event " << i << " compare to node "<< j << endl;

					

				}

				if (Node_manager::event_list[i].get_type() == TRANSMIT && Node_manager::node_list[j].get_Status() == RECEIVER){

					cout << "Node " << j << " match receive situation! " << endl;
					t_x = Node_manager::event_list[i].src_x();
					t_y = Node_manager::event_list[i].src_y();

					if (Node_manager::node_list[j].calc_distance(t_x, t_y) <= R && Node_manager::node_list[j].get_channel() == Node_manager::event_list[i].transmit_channel()){

						Node_manager::node_list[j].receive();

					}

				}

			}

		}

	}

	for (check = 0; check < N_UE; ++check){

		
		if (Node_manager::node_list[check].get_Status() == RECEIVER && Node_manager::node_list[check].get_receive_data() == true){

			cout <<  "Node " << check << " receive !! " << endl;
			Node_manager::node_list[check].change_Status(TRANSMITTER);
			Node_manager::node_list[check].clr_accmu();
			Node_manager::node_list[check].assign_p_random();
			delay_n = System_time + (rand() % TIME_SHIFT +1)*MIN_T_UNIT;
			Node_manager::node_list[check].set_time(delay_n);
			++N_receive;

		}

		if (Node_manager::node_list[check].get_Status() == RECEIVER && Node_manager::node_list[check].get_receive_data() == false && System_time == Node_manager::node_list[check].node_time()){

			//cout << "Node " << check << " receive failed!! " << endl;
			Node_manager::node_list[check].change_Status(IDLE);
			Node_manager::node_list[check].clr_accmu();
			Node_manager::node_list[check].clr_control_channel();
			//delay_n = System_time + (rand() % TIME_SHIFT +1)*MIN_T_UNIT;
			//Node_manager::node_list[check].set_time(delay_n);

		}

		if (Node_manager::node_list[check].get_Status() == IDLE && Node_manager::node_list[check].get_receive_data() == true){

			cout << "Node " << check << " control without collision! " << endl;
			Node_manager::node_list[check].change_Status(RECEIVER);
			//cout << "Status became " << Node_manager::node_list[check].get_Status() << endl;
			Node_manager::node_list[check].clr_accmu();
			Node_manager::node_list[check].set_receive_data(false);
			r_duration = System_time + (TIME_SHIFT + 5)*MIN_T_UNIT + DATA_PACKET_SIZE*2 / BANDWIDTH;
			Node_manager::node_list[check].set_time(r_duration);

		}

		if (Node_manager::node_list[check].get_Status() == IDLE && Node_manager::node_list[check].get_receive_data() == false){

			//cout << "Node " << check << " control  collision! " << endl;
			Node_manager::node_list[check].change_Status(IDLE);
			Node_manager::node_list[check].clr_accmu();
			Node_manager::node_list[check].clr_control_channel();
			//delay_n = System_time + (rand() % TIME_SHIFT + 1)*MIN_T_UNIT;
			//Node_manager::node_list[check].set_time(delay_n);

		}

	}

}*/

void Node_manager::handle_event(){

	register int i = 0 ,j = 0 ;
	float t_x = 0, t_y = 0 , c_x =0 ,c_y = 0;
	double r_duration = 0 , r_head = 0 ,delay_n = 0 ;

	///cout << "Event size = " << Node_manager::event_list.size() << endl;

	for (i = 0; i < Node_manager::node_list.size(); ++i){

		if (Node_manager::node_list[i].get_Status() == RECEIVER && System_time > Node_manager::node_list[i].end_time()){

			///cout << "Node " << i << "  no receive data ! " << endl;
			Node_manager::node_list[i].change_Status(IDLE);
			Node_manager::node_list[i].clr_accmu();
			Node_manager::node_list[i].clr_control_channel();
			Node_manager::node_list[i].set_receive_data(false);

		}

		if (Node_manager::node_list[i].get_Status() == RECEIVER && System_time > Node_manager::node_list[i].start_time()){
			cout << "Node " << i << "  activate ! " << endl;
			for (j = 0; j < Node_manager::event_list.size(); ++j){

				if (Node_manager::node_list[i].start_time() <= Node_manager::event_list[j].event_strat_time() && Node_manager::node_list[i].end_time() >= Node_manager::event_list[j].event_end_time()){

					if (Node_manager::event_list[j].get_type() == TRANSMIT ){

						cout << "Node " << i << " calculate distance " << Node_manager::node_list[i].calc_distance(t_x, t_y) << endl;
						t_x = Node_manager::event_list[j].src_x();
						t_y = Node_manager::event_list[j].src_y();
						//cout << "(t_x,t_y) = " << "( " << t_x << " , " << t_y << " )" << endl;

						if (Node_manager::node_list[i].calc_distance(t_x, t_y) <= R && Node_manager::node_list[i].get_channel() == Node_manager::event_list[j].transmit_channel()){

							//cout << "Node " << i << " in range with distance " << Node_manager::node_list[i].calc_distance(t_x, t_y) << endl;
							Node_manager::node_list[i].receive();

						}

					}

				}

			}

		}


		if (Node_manager::node_list[i].get_Status() == IDLE){

			for (j = 0; j < Node_manager::event_list.size(); ++j){

				if (Node_manager::event_list[j].get_type() == CONTORL ){
					
					c_x = Node_manager::event_list[j].src_x();
					c_y = Node_manager::event_list[j].src_y();
					//cout << "(c_x,c_y) = " << "( " << c_x << " , " << c_y << " )" << endl;
					//cout << "(x,y) = " << "( " << Node_manager::node_list[i].get_axis_x() << " , " << Node_manager::node_list[i].get_axis_y() << " )" << endl;
					cout << "Node " << i << " see control packet!  distance = " << Node_manager::node_list[i].calc_distance(c_x, c_y) <<endl;
					if (Node_manager::node_list[i].calc_distance(c_x, c_y) <= R && Node_manager::node_list[i].get_mode() == Node_manager::event_list[j].get_src_mode()){

						//cout << "Node " << i << " match control situation! " << endl;
						Node_manager::node_list[i].receive();
						Node_manager::node_list[i].set_channel(Node_manager::event_list[j].transmit_channel());

					}


				}

			}

		}

		if (Node_manager::node_list[i].get_receive_data() == true && Node_manager::node_list[i].get_Status() == RECEIVER){

			cout << "Node " << i << " receive !! " << endl;
			Node_manager::node_list[i].change_Status(TRANSMITTER);
			Node_manager::node_list[i].clr_accmu();
			Node_manager::node_list[i].assign_p_random();
			delay_n = System_time + (1)*MIN_T_UNIT;
			Node_manager::node_list[i].set_time(delay_n);
			++N_receive;

		}

		if (Node_manager::node_list[i].get_receive_data() == true && Node_manager::node_list[i].get_Status() == IDLE){

			cout << "Node " << i << " control without collision! " << endl;
			Node_manager::node_list[i].change_Status(RECEIVER);
			//cout << "Status became " << Node_manager::node_list[check].get_Status() << endl;
			Node_manager::node_list[i].clr_accmu();
			Node_manager::node_list[i].set_receive_data(false);
			r_head = System_time + 5*MIN_T_UNIT;
			r_duration = System_time + (TIME_SHIFT + 5)*MIN_T_UNIT + DATA_PACKET_SIZE * 2 / BANDWIDTH;
			Node_manager::node_list[i].set_interval(r_head, r_duration);
			//cout << "Time " << Node_manager::node_list[i].start_time() << " ~ " << Node_manager::node_list[i].end_time() << endl;

		}

		Node_manager::node_list[i].move(MIN_T_UNIT, FREE);
	}

}

void Node_manager::update_event(){

	std::vector<Sys_event>::iterator itor;

	for (itor = Node_manager::event_list.begin(); itor != Node_manager::event_list.end();){

		//cout << "itor time = " << (*itor).event_end_time() << endl;

		if ((*itor).event_end_time() <= System_time){

			itor = Node_manager::event_list.erase(itor);

		}
		/*else if ((*itor)._is_collision() == true){

			itor = Node_manager::event_list.erase(itor);
		}*/
		else{

			itor++;

		}

	}

}

/*void Node_manager::update_event(){

	std::vector<Sys_event>::iterator itor , time;
	int i = 0;
	double next_time = System_time , temp = 0;
	
	cout << "Event list has  " << Node_manager::event_list.size() << " events" << endl;

	for (time = Node_manager::event_list.begin(); time != Node_manager::event_list.end(); ++time){

		//cout << "Event's start time = " << (*time).event_strat_time() << " end time = " << (*time).event_end_time() << endl;

		if ((*time).event_strat_time() > next_time || (*time).event_end_time() > next_time){

			if ((*time).event_strat_time() <= System_time && next_time == System_time){

				next_time = (*time).event_end_time();

			}

			if ((*time).event_strat_time() > System_time && (*time).event_strat_time() < next_time){

				next_time = (*time).event_strat_time();

			}

			if ((*time).event_strat_time() <= System_time && (*time).event_end_time() < next_time){

				next_time = (*time).event_end_time();

			}

		}

	}

	for (i = 0; i < Node_manager::node_list.size(); ++i){

		if (Node_manager::node_list[i].node_time() < next_time && Node_manager::node_list[i].get_Status() == TRANSMITTER){

			next_time = Node_manager::node_list[i].node_time();

		}
		if (Node_manager::event_list.size() == 0 && Node_manager::node_list[i].get_Status() == TRANSMITTER){

			if (next_time == System_time){

				next_time = Node_manager::node_list[i].node_time();

			}
			if (next_time > System_time  && Node_manager::node_list[i].node_time() < next_time){

				next_time = Node_manager::node_list[i].node_time();
			}

		}

	}

	System_time = next_time;
	//cout << "System time move to " << next_time << endl;

	for (itor = Node_manager::event_list.begin(); itor != Node_manager::event_list.end();){

		//cout << "itor time = " << (*itor).event_end_time() << endl;

		if ((*itor).event_end_time() <= System_time){

			itor = Node_manager::event_list.erase(itor);

		}
		else{

			itor++;

		}

	}

}*/

 void Node_manager::new_handle_event(){

	register int i = 0 , j = 0;
	double delay_n = 0, r_head = 0, r_duration = 0;
	float c_x = 0, c_y = 0, t_x = 0, t_y = 0;
	int Idle_data;

	//receive_data.open("Idle_count.txt",ios::out | ios::app);
	Idle_data = 0;
	//receive_data << "**********************************************"<<endl;
	//cout << "Node 1386" << "'s time is " << Node_manager::node_list[1386].e_start << " ~ " << Node_manager::node_list[1386].e_end << endl;
	for (i = 0; i < Node_manager::node_list.size(); ++i){

		if (Node_manager::node_list[i].k_limit > 1000){

			Node_manager::node_list[i].change_Status(STOP);
			cout << "Transmit Stop" << endl;

		}

		if(Node_manager::node_list[i].get_Status() == IDLE){

			++Idle_data;

		}

		if (Node_manager::node_list[i].get_Status() == RECEIVER && fabs(System_time - Node_manager::node_list[i].end_time()) <= MIN_T_UNIT){ 

			if (Node_manager::node_list[i].collison() == false){

				Node_manager::node_list[i].change_Status(TRANSMITTER);
				Node_manager::node_list[i].clr_accmu();
				Node_manager::node_list[i].assign_p_random();
				delay_n = System_time + (1)*MIN_T_UNIT;
				Node_manager::node_list[i].set_time(delay_n);
				++N_receive;

			}

			if (Node_manager::node_list[i].collison() == true){

				Node_manager::node_list[i].change_Status(IDLE);
				Node_manager::node_list[i].clr_accmu();
				Node_manager::node_list[i].set_receive_data(false);
				Node_manager::node_list[i]._is_collison(false);
				Node_manager::node_list[i].e_start = -1;
				Node_manager::node_list[i].e_end = -1;
				Node_manager::node_list[i].p_index = -1;
			}

		}

		if (Node_manager::node_list[i].get_Status() == RECEIVER &&  Node_manager::node_list[i].end_time() < System_time){

			Node_manager::node_list[i].change_Status(IDLE);
			Node_manager::node_list[i].clr_accmu();
			Node_manager::node_list[i].clr_control_channel();
			Node_manager::node_list[i].set_receive_data(false) ;
			Node_manager::node_list[i]._is_collison(false) ;
			Node_manager::node_list[i].e_start = -1;
			Node_manager::node_list[i].e_end = -1;
			Node_manager::node_list[i].p_index = -1;

		}

		if (Node_manager::node_list[i].get_Status() == IDLE && fabs(System_time - Node_manager::node_list[i].e_end) < MIN_T_UNIT/2){
			
			
			if (Node_manager::node_list[i].collison() == false){

				cout << "Node " << i << " became receiver " <<  endl;
				Node_manager::node_list[i].change_Status(RECEIVER);
				//cout << "Status became " << Node_manager::node_list[check].get_Status() << endl;
				Node_manager::node_list[i].clr_accmu();
				Node_manager::node_list[i].set_receive_data(false);
				r_head = System_time + 5 * MIN_T_UNIT;
				r_duration = System_time + (TIME_SHIFT + 5)*MIN_T_UNIT + DATA_PACKET_SIZE * 2 / BANDWIDTH;
				Node_manager::node_list[i].set_interval(r_head, r_duration);
				Node_manager::node_list[i].p_index = -1;

			}

			if (Node_manager::node_list[i].collison() == true){

				Node_manager::node_list[i].clr_accmu();
				Node_manager::node_list[i].set_receive_data(false);
				Node_manager::node_list[i]._is_collison(false);
				Node_manager::node_list[i].e_end = -1;
				Node_manager::node_list[i].e_start = -1;
				Node_manager::node_list[i].p_index = -1;
				//cout << "Reset time" << endl;
			}

		}
		
		Node_manager::node_list[i].move(MIN_T_UNIT, FREE);

	}

	for (i = 0; i < Node_manager::event_list.size(); ++i){

		//cout << Node_manager::event_list.size() << " event in list !" << endl;
		if (fabs(Node_manager::event_list[i].event_strat_time() - System_time) < MIN_T_UNIT || System_time > Node_manager::event_list[i].event_strat_time()){

			for (j = 0; j < Node_manager::node_list.size(); ++j){

				if (Node_manager::node_list[j].get_Status() == IDLE && Node_manager::event_list[i].get_type() == CONTORL){

					c_x = Node_manager::event_list[i].src_x();
					c_y = Node_manager::event_list[i].src_y();

					//cout << "Node " << j << " see control message at distance " << Node_manager::node_list[j].calc_distance(c_x, c_y) << endl;
					if (Node_manager::node_list[j].calc_distance(c_x, c_y) <= R && Node_manager::node_list[j].get_mode() == Node_manager::event_list[i].get_src_mode()){

						
						//cout << "Event's time = " << Node_manager::event_list[i].event_strat_time() << " ~ " << Node_manager::event_list[i].event_end_time() << endl;
						//cout << "Node " << j << "'s time is " << Node_manager::node_list[j].e_start << " ~ " << Node_manager::node_list[j].e_end << endl;
						//cout << "System time = " << System_time << endl;;
						//receive_data << "Node " << j << " receive control signal at " << System_time << endl;
						
						if (fabs(Node_manager::node_list[j].e_start + 1) < MIN_T_UNIT / 10 && fabs(Node_manager::node_list[j].e_end + 1) < MIN_T_UNIT / 10){

							Node_manager::node_list[j].e_start = Node_manager::event_list[i].event_strat_time();
							Node_manager::node_list[j].e_end = Node_manager::event_list[i].event_end_time();
							Node_manager::node_list[j].set_channel(Node_manager::event_list[i].transmit_channel());
							Node_manager::node_list[j].p_index = Node_manager::event_list[i].event_index;
							//cout << "Node " << j << " get control message at distance " << Node_manager::node_list[j].calc_distance(c_x, c_y) << "  from  " << Node_manager::node_list[j].e_start << " ~ " << Node_manager::node_list[j].e_end << endl;

						}
						

						if (Node_manager::node_list[j].in_alive_time(Node_manager::event_list[i].event_strat_time()) || Node_manager::node_list[j].in_alive_time(Node_manager::event_list[i].event_end_time())){

							if (Node_manager::node_list[j].p_index != Node_manager::event_list[i].event_index){

								cout << " Control event collisoin!" << endl;
								Node_manager::node_list[j]._is_collison(true);
								++n_collison;

							}
							

						}

					}

				}

				if (Node_manager::node_list[j].get_Status() == RECEIVER && Node_manager::event_list[i].get_type() == TRANSMIT){

					t_x = Node_manager::event_list[i].src_x();
					t_y = Node_manager::event_list[i].src_y();

					//cout << "Node " << j << " see transmit message at distance " << Node_manager::node_list[j].calc_distance(t_x, t_y) << endl;
					if (Node_manager::node_list[j].calc_distance(t_x, t_y) <= R && Node_manager::node_list[j].get_channel() == Node_manager::event_list[i].transmit_channel()){

						//cout << "Node " << j << " get transmit message at distance " << Node_manager::node_list[j].calc_distance(t_x, t_y) << endl;

						if (fabs(Node_manager::node_list[j].e_start + 1) < MIN_T_UNIT / 10 && fabs(Node_manager::node_list[j].e_end + 1) < MIN_T_UNIT / 10){

							Node_manager::node_list[j].e_start = Node_manager::event_list[i].event_strat_time();
							Node_manager::node_list[j].e_end = Node_manager::event_list[i].event_end_time();
							Node_manager::node_list[j].p_index = Node_manager::event_list[i].event_index;

						}

						if (Node_manager::node_list[j].in_alive_time(Node_manager::event_list[i].event_strat_time()) || Node_manager::node_list[j].in_alive_time(Node_manager::event_list[i].event_end_time())){

							if (Node_manager::node_list[j].p_index != Node_manager::event_list[i].event_index){

								cout << " Transmit event collisoin!" << endl;
								Node_manager::node_list[j]._is_collison(true);
								++n_collison;

							}
	

						}

					}

				}

				//cout << "Node " << j << "'s time is " << Node_manager::node_list[j].e_start << " ~ " << Node_manager::node_list[j].e_end << endl;

			}

		}
		

	}

	//receive_data <<  "Idle = " << Idle_data <<endl;
	//receive_data.close();
	

}

int Node_manager::assign_channel(const int mode){

	int channel = 0;
	int up_bound = 0;
	up_bound = low_bound[mode] + channel_avail[mode];
	channel = rand() % (up_bound - low_bound[mode]) + low_bound[mode] + 1;
	return channel;

}

void Node_manager::check_collision(){

	register int i = 0, j = 0 ;

	for (i = 0; i < Node_manager::event_list.size(); ++i){

		for (j = 0; j < Node_manager::event_list.size(); ++j){

			if (i != j){

				if (Node_manager::event_list[i].get_type() == CONTORL && Node_manager::event_list[j].get_type() == CONTORL ){

					if (Node_manager::event_list[j]._is_activate(Node_manager::event_list[i].event_strat_time()) == true || Node_manager::event_list[j]._is_activate(Node_manager::event_list[i].event_end_time()) == true){

						if (Node_manager::event_list[i].get_src_mode() == Node_manager::event_list[j].get_src_mode()){

							Node_manager::event_list[i].set_collision(true);

						}
						
					}

				}

				if (Node_manager::event_list[i].get_type() == TRANSMIT && Node_manager::event_list[j].get_type() == TRANSMIT ){

					if (Node_manager::event_list[j]._is_activate(Node_manager::event_list[i].event_strat_time()) == true || Node_manager::event_list[j]._is_activate(Node_manager::event_list[i].event_end_time()) == true){

						if (Node_manager::event_list[i].transmit_channel() == Node_manager::event_list[j].transmit_channel()){

							Node_manager::event_list[i].set_collision(true);

						}

					}

				}

			}


		}

	}

}

void Node_manager::get_round_info(){

	char src_file[100], nodes_file[100], src_axis[100], nodes_axis[100];

	//sprintf_s(src_file, "src_%d_%d.txt", N_UE, Node_manager::count);
	//sprintf_s(nodes_file, "nodes_%d_%d.txt", N_UE, Node_manager::count);
	//sprintf_s(src_axis, "src_axis_%d_%d.txt", N_UE, Node_manager::count);
	//sprintf_s(nodes_axis, "nodes_axis_%d_%d.txt", N_UE, Node_manager::count);

	out_put_src.open(src_file, ios::out | ios::trunc);
	out_put_nodes.open(nodes_file, ios::out | ios::trunc);
	fsrc_axis.open(src_axis, ios::out | ios::trunc);
	fnodes_axis.open(nodes_axis, ios::out | ios::trunc);

	std::vector<Ue_node_p_aloha>::iterator itor;
	for (itor = node_list.begin(); itor != node_list.end(); ++itor){

		if (itor->get_Status() == TRANSMITTER){

			out_put_src << itor->get_index() << endl;
			fsrc_axis << itor->get_axis_x() << " " << itor->get_axis_y() << endl;

		}
		else{

			out_put_nodes << itor->get_index() << endl;
			fnodes_axis << itor->get_axis_x() << " " << itor->get_axis_y() << endl;

		}



	}
	++Node_manager::count;
	out_put_src.close();
	out_put_nodes.close();
	fsrc_axis.close();
	fnodes_axis.close();


}

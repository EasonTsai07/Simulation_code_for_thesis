#include <stdio.h>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <vector>


#include "Config.h"
#include "Node_Manager.h"
#include "Node.h"


using namespace std;

static Node_manager  manager;

extern int n_collison = 0;
extern int N_receive = 0;
extern double System_time = 0;
extern Map_Type type =  FREE;



void create_member(){

	fstream x_output , y_output;

	x_output.open("x.txt", ios::out);
	y_output.open("y.txt", ios::out);

	int i = 0;
	double time = 0;

	for (i = 0; i < N_UE; ++i){

		Ue_node_p_aloha node ;

		if (i < SRC*MODE){
			//cout << "Node " << i << " became transmiter !" << endl;
			node.set_index(i);
			node.set_location(SPECIFY, M_WIDTH / 2, M_LENGTH/2);
			node.set_velocity(RANDOM);
			node.set_mode(i+1);
			node.set_time(0);
			node.change_Status(TRANSMITTER);
			node.assign_p_random();
			//node.show_Ue_node_p_aloha_info();
			manager.join_mode(node);
			manager.add_node(node);

		}

		else{

			node.set_index(i);
			node.set_location(RANDOM);
			node.set_velocity(RANDOM);
			node.set_mode();
			time = (rand() % TIME_SHIFT) * MIN_T_UNIT;
			//cout << "Rand() = " << rand() % SLOT_SHIFT << endl;
			//cout << "Node " << i << " default system time = " << time << endl;
			node.set_time(time);
			//node.show_Ue_node_p_aloha_info();
			manager.join_mode(node);
			manager.add_node(node);

		}
		
		x_output << node.get_axis_x()<<endl;
		y_output << node.get_axis_y() << endl;

	}

	x_output.close();
	y_output.close();

}

void channel_alloc(){

	//cout << manager.length() << "Nodes in list" << endl;
	manager.mode_alloc_channel();
	manager.calc_lower_bound();

}

void output_node_info(){

	//manager.output_nodes();

}

int main(int argc, char** argv){

	int debug_count = 0 ,count =0;

	fstream output;

	output.open("total.txt", ios::out );

	srand(SEED);

	

	create_member();
	channel_alloc();
	manager.node_alloc_channel();
	output_node_info();
	

	do{

		manager.set_event();
		//manager.check_collision();
		manager.new_handle_event();
		manager.update_event();
		cout << "Receive node " << N_receive + MODE << " in " << System_time << endl;
		cout << "************************************************" << endl;
		System_time = System_time + MIN_T_UNIT;
		++count;

		if ((count % 500) == 0){

			//cout << "here!" << endl;
			output << N_receive  + MODE << endl;
			//manager.get_round_info();

		}

		if (N_receive + MODE == N_UE){

			break;

		}
		//system("pause");
	} while (System_time < T_TOTAL);
		//++debug_count;
		
	output.close();
	//} while (debug_count < 2);

	//system("pause");
	
}

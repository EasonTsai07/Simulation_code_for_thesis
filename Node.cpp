#include <stdio.h>

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>

#include "Config.h"
#include "Node.h"
#include "Event.h"

using namespace std;


/***********************************************/
/* This part implement functions of basic node */
/***********************************************/

//Constructer of basic node
basic_node::basic_node(){

	basic_node::receive_data = false;
	basic_node::axis_x = 0;
	basic_node::axis_y = 0;
	basic_node::Status = IDLE;

}

//Show information of basic node
void basic_node::show_basic_info(){

	cout << "Axis X : " << axis_x << " Axis Y : " << axis_y << " Receive Data : " << receive_data << " Status : " << Status << endl;

}

//Overload set_location function with spread mode which specify node's location
void basic_node::set_location(const int Spread_Mode, const float x, const float y){

	if (Spread_Mode == SPECIFY){

		basic_node::axis_x = x;
		basic_node::axis_y = y;

	}

}

//Overload set_location function in random spread
void basic_node::set_location(const int Spread_Mode){

	if (Spread_Mode == RANDOM){


		basic_node::axis_x = (double)rand()*M_WIDTH / RAND_MAX;
		basic_node::axis_y = (double)rand()*M_LENGTH / RAND_MAX;

	}

}

//Change node's status
void basic_node::change_Status(int Status){

	basic_node::Status = Status;

}

Ue_node_p_aloha::Ue_node_p_aloha(){

	basic_node();
	index = 0;
	ue_channel = 0;
	velocity = 0;
	distance = 0;
	p_random = 0;
	theta = 0;
	e_start = -1;
	e_end = -1;
	control_channel_available = false;
	activate_time = T_TOTAL + 1;
	congestion_metric =0;
	channel_accumulate = 0;
	k_limit = 0;
	p_index = 0;
	control_collison = false;
	announce_control_channel = true;
	memset(channel, false, CHANNEL);


}

void Ue_node_p_aloha::set_velocity(const int Spread_Mode){

	if (Spread_Mode == RANDOM){


		Ue_node_p_aloha::velocity = (double)rand()*V_MAX / RAND_MAX;
		Ue_node_p_aloha::theta = ((double)rand() * 2 * 3.14159) / RAND_MAX;

	}

}

void Ue_node_p_aloha::set_velocity(const int Spread_Mode, const float velocity, const float theta){

	if (Spread_Mode == SPECIFY){

		Ue_node_p_aloha::velocity = velocity;
		Ue_node_p_aloha::theta = theta;

	}

}

void Ue_node_p_aloha::move(const float time,const int Type){

	float temp = 0;

	if (Type == FREE){

		temp = Ue_node_p_aloha::get_axis_x() + Ue_node_p_aloha::velocity*cos(Ue_node_p_aloha::theta)*time;
		Ue_node_p_aloha::set_axis_x(temp);
		temp = Ue_node_p_aloha::get_axis_y() + Ue_node_p_aloha::velocity*sin(Ue_node_p_aloha::theta)*time;
		Ue_node_p_aloha::set_axis_y(temp);

	}

	if (Type == REFLEX){

		if (Ue_node_p_aloha::axis_x >= M_WIDTH || Ue_node_p_aloha::axis_x <= 0){

			Ue_node_p_aloha::theta = Ue_node_p_aloha::theta - 180;
			temp = Ue_node_p_aloha::get_axis_x() + Ue_node_p_aloha::velocity*cos(Ue_node_p_aloha::theta)*time;
			Ue_node_p_aloha::set_axis_x(temp);
			temp = Ue_node_p_aloha::get_axis_y() + Ue_node_p_aloha::velocity*sin(Ue_node_p_aloha::theta)*time;
			Ue_node_p_aloha::set_axis_y(temp);

		}

		else if (Ue_node_p_aloha::axis_y >= M_LENGTH || Ue_node_p_aloha::axis_y <= 0){

			Ue_node_p_aloha::theta = Ue_node_p_aloha::theta - 180;
			temp = Ue_node_p_aloha::get_axis_x() + Ue_node_p_aloha::velocity*cos(Ue_node_p_aloha::theta)*time;
			Ue_node_p_aloha::set_axis_x(temp);
			temp = Ue_node_p_aloha::get_axis_y() + Ue_node_p_aloha::velocity*sin(Ue_node_p_aloha::theta)*time;
			Ue_node_p_aloha::set_axis_y(temp);

		}

		else if (Ue_node_p_aloha::axis_x <= M_WIDTH && Ue_node_p_aloha::axis_y <= M_LENGTH){

			temp = Ue_node_p_aloha::get_axis_x() + Ue_node_p_aloha::velocity*cos(Ue_node_p_aloha::theta)*time;
			Ue_node_p_aloha::set_axis_x(temp);
			temp = Ue_node_p_aloha::get_axis_y() + Ue_node_p_aloha::velocity*sin(Ue_node_p_aloha::theta)*time;
			Ue_node_p_aloha::set_axis_y(temp);

		}

		else{

			Ue_node_p_aloha::theta = Ue_node_p_aloha::theta - 180;
			temp = Ue_node_p_aloha::get_axis_x() + Ue_node_p_aloha::velocity*cos(Ue_node_p_aloha::theta)*time;
			Ue_node_p_aloha::set_axis_x(temp);
			temp = Ue_node_p_aloha::get_axis_y() + Ue_node_p_aloha::velocity*sin(Ue_node_p_aloha::theta)*time;
			Ue_node_p_aloha::set_axis_y(temp);

		}
		
	}
}

void Ue_node_p_aloha::set_mode(){

	Ue_node_p_aloha::ue_mode = ceil((Ue_node_p_aloha::velocity / V_MAX)*MODE);

}

void Ue_node_p_aloha::set_mode(int mode){

	Ue_node_p_aloha::ue_mode = mode;

}

void Ue_node_p_aloha::show_Ue_node_p_aloha_info(){

	cout << "Index = " << index << endl;
	show_basic_info();
	cout << "Ue_mode = " << ue_mode << " Ue_channel = " << ue_channel << " Control Channel = " << boolalpha << control_channel_available << endl;
	cout << "Velocity = " << velocity << " Theta = " << theta << " p_random = " << p_random << endl;

}

void Ue_node_p_aloha::assign_p_random(){

	Ue_node_p_aloha::p_random = ((double)rand() / RAND_MAX)/**pow(0.9995,k_limit)*/;

}

void Ue_node_p_aloha::set_time(double time){

	Ue_node_p_aloha::activate_time = time;

}

float Ue_node_p_aloha::calc_distance(float x, float y){

	return sqrt((pow(Ue_node_p_aloha::axis_x - x, 2) + pow(Ue_node_p_aloha::axis_y - y, 2)));

}

void Ue_node_p_aloha::receive(){

	++Ue_node_p_aloha::channel_accumulate;
	if (Ue_node_p_aloha::channel_accumulate == 1){

		Ue_node_p_aloha::set_receive_data(true);
		Ue_node_p_aloha::control_collison = false;
		Ue_node_p_aloha::_is_collison(false);

	}
	if (Ue_node_p_aloha::channel_accumulate > 1){

		Ue_node_p_aloha::set_receive_data(false);
		Ue_node_p_aloha::control_collison = true;
		Ue_node_p_aloha::_is_collison(true);
	}

}

void Ue_node_p_aloha::set_interval(double t1 ,double t2){

	Ue_node_p_aloha::start = t1;
	Ue_node_p_aloha::end = t2;

}

bool Ue_node_p_aloha::in_alive_time(double t){

	if (t > Ue_node_p_aloha::e_start + MIN_T_UNIT / 2 && t < Ue_node_p_aloha::e_end - MIN_T_UNIT / 2){

		return true;
	}
	else if (fabs(t - Ue_node_p_aloha::e_start) < MIN_T_UNIT || fabs(t - Ue_node_p_aloha::e_end)< MIN_T_UNIT){

		return true;
	}
	else{

		return false;

	}

}

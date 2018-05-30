#include <iostream>
#include "Event.h"

Sys_event::Sys_event(){

	Sys_event::event_x = 0;
	Sys_event::event_y = 0;
	Sys_event::start_time = 0;
	Sys_event::end_time = 0;
	Sys_event::next_channel = 0;
	Sys_event::event_index = -1;
	Sys_event::type = NODEF;
	Sys_event::collision = false;

}

void Sys_event::set_announce_source(float src_x,float src_y){

	Sys_event::event_x = src_x;
	Sys_event::event_y = src_y;

}

void Sys_event::type_declare(Event_Type type){

	Sys_event::type = type;

}

void Sys_event::alive_time(double start, double end){

	Sys_event::start_time = start ;
	Sys_event::end_time = end ;

}

bool Sys_event::_is_activate(double sys_time){

	if (sys_time >= Sys_event::start_time && sys_time <= Sys_event::end_time){

		return true;

	}
	else{

		return false;

	}

}


Event_Type Sys_event::get_type(){

	return Sys_event::type;

}

/*int Sys_event::assign_transmit_channel(const int mode){



}*/
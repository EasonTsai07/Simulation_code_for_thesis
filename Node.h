#ifndef _NODE_H_

#define _NODE_H_

#include "Config.h"

enum Node{
	UE,
	//BS,
	//ROUTER,
	//SWITCH,
	//END_POINT
};

enum Status{
	TRANSMITTER,
	RECEIVER,
	IDLE,
	STOP
};

enum Spread_Mode{
	RANDOM,
	SPECIFY,
	UNIFORM
};

enum Map_Type{

	FREE,
	REFLEX

};

class basic_node {
private:

	bool receive_data;

	int Status;

protected:

	//bool has_control;

	float axis_x;
	float axis_y;

public:

	basic_node();
	//~basic_node();

	void set_location(int Spread_Mode);
	void set_location(int Spread_Mode, float x, float y);
	void set_receive_data(bool set){ basic_node::receive_data = set; } //whether receive data
	void show_basic_info(); //for debug
	void change_Status(int Status);

	inline bool get_receive_data(){ return receive_data; }

	inline int get_Status(){ return basic_node::Status; }

	inline void set_axis_x(float x){ axis_x = x; }
	inline void set_axis_y(float y){ axis_y = y; }
	

	inline float get_axis_x(){ return axis_x; }
	inline float get_axis_y(){ return axis_y; }

};

class Ue_node_p_aloha : public basic_node{

private:

	bool control_channel_available;
	bool control_collison;
	bool announce_control_channel;

	bool channel[CHANNEL]; //check out which CH can be use, if can then true, otherwise false.

	int index;
	int ue_mode;
	int ue_channel;
	int channel_accumulate;
	int next_channel;


	float velocity;
	float distance;
	float p_random;
	float theta;
	double start;
	double end;
	double activate_time;
	float congestion_metric;
	

public:

	double e_start;
	double e_end;
	int k_limit;

	unsigned long p_index;

	Ue_node_p_aloha();
	//~Ue_node_p_aloha();

	
	void set_velocity(int Spread_Mode);
	void set_velocity(int Spread_Mode, float velocity, float theta);
	void set_mode();
	void set_mode(int mode);
	void set_interval(double time1, double time2);
	
	//void channel_alloc();
	void move(float time,int type);
	void receive();
	void show_Ue_node_p_aloha_info();
	void assign_p_random();
	void set_time(double time);

	inline void set_index(int index){ Ue_node_p_aloha::index = index; }
	inline void _is_collison(bool set){ Ue_node_p_aloha::control_collison = set; }
	inline void assign_next_channel(int next_channel){ Ue_node_p_aloha::next_channel = next_channel; }
	inline void clr_accmu(){ Ue_node_p_aloha::channel_accumulate = 0; }
	inline void clr_control_channel(){ Ue_node_p_aloha::control_channel_available = false; }
	inline void set_channel(int channel){ Ue_node_p_aloha::ue_channel = channel; }
	inline void channel_announcement(bool set){ Ue_node_p_aloha::announce_control_channel = set; }

	inline bool check_contorl_channel(){ return Ue_node_p_aloha::control_channel_available; }
	inline bool collison(){ return Ue_node_p_aloha::control_collison; }
	inline bool announcement(){ return Ue_node_p_aloha::announce_control_channel; }

	//control_signal control();
	//transmit_signal transmit();

	inline int get_index(){ return Ue_node_p_aloha::index; }
	inline int get_mode(){ return Ue_node_p_aloha::ue_mode; }
	inline int get_channel(){ return Ue_node_p_aloha::ue_channel; }
	inline int get_next_channel(){ return Ue_node_p_aloha::next_channel; }

	
	inline float get_p(){ return Ue_node_p_aloha::p_random; }
	inline float get_v(){ return Ue_node_p_aloha::velocity; }
	inline float get_theta(){ return Ue_node_p_aloha::theta; }

	inline double node_time(){ return Ue_node_p_aloha::activate_time; }
	inline double start_time(){ return Ue_node_p_aloha::start; }
	inline double end_time(){ return Ue_node_p_aloha::end; }

	bool in_alive_time(double t);

	float calc_distance(float x, float y);

};


#endif 

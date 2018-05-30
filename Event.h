#ifndef _EVENT_H_

#define _EVENT_H_


enum Event_Type{

	NODEF,
	CONTORL,
	TRANSMIT

};

class Sys_event{

public:

	unsigned long event_index;

	Sys_event();
	void set_announce_source(float x,float y);
	void alive_time(double strat, double end);
	void type_declare(Event_Type type);
	void assign_next_channel(int channel){ Sys_event::next_channel = channel; }
	bool _is_activate(double sys_time);

	//int assign_transmit_channel(int mode);

	Event_Type get_type();

	inline void set_event_mode(const int mode){ Sys_event::src_mode = mode; }
	inline void set_collision(bool set){ Sys_event::collision = set; }

	inline bool _is_collision(){ return Sys_event::collision; }

	inline int transmit_channel(){ return Sys_event::next_channel; }
	inline int get_src_mode(){ return Sys_event::src_mode; }

	inline float src_x(){ return Sys_event::event_x; }
	inline float src_y(){ return Sys_event::event_y; }
	
	inline double event_strat_time(){ return Sys_event::start_time; }
	inline double event_end_time(){ return Sys_event::end_time; }

	//~Sys_event();


protected:

private:

	bool collision;
	 
	int next_channel;
	int src_mode;

	float event_x;
	float event_y;

	double start_time;
	double end_time;


	Event_Type type;

};

#endif 

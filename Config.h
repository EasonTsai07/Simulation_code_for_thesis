#ifndef _CONFIG_H_

#define _CONFIG_H_

#define R 25 //Broadcast radius (m)
#define V_MAX 50 //Maximun Velocity (m/s)
#define MODE 3 //Amount of mode
#define CHANNEL 6 //Amount of channel
#define DATA_PACKET_SIZE 0.0015 //Size of data packet p.s. assume as the biggest Ethernet packet (Mbyte)
#define CONTROL_PACKET_SIZE 0.000015//Size of control packet p.s. 1/10 size of data packet (Mbyte)
#define BANDWIDTH 10 //Bandwidth (MBps)
#define T_TOTAL 20 //Observe Time (s)
#define MIU 0.028 //Density of device (device/m^2)
#define M_WIDTH 500 //Width of map (m)
#define M_LENGTH 500//length of map (m)
#define PROB 0.5 //Probability of transmission
#define SEED 20170406 //seed of random
#define SRC 1 //Amount of node need to transmit data.(src per mode)
#define T_TRANS 0 //Time for Devive to change its status
#define MIN_T_UNIT 0.000001 //Minimum time slot unit
#define N_UE 5000 //Amount of nodes
#define TIME_SHIFT 1 //Scale of time slot drift


#endif 

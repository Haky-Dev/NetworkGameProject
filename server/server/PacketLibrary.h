#pragma once

#define EXTEND_PACKET_SIZE 12
#define GENERAL_PACKET_SIZE 4

class Vector2d;

//temp
class PacketLibrary {

public:
	bool static On(const int& p_iflag, int pt);
	void static pTurnOn(int& p_iflag, const int pt);
	void static pTurnOff(int& p_iflag, const int pt);
		  
	bool static is_extend_packet_client(const int& packet);
	bool static is_extend_packet_server(const int& packet);
		  
	int static make_packet_chat(const int& client, int key);
	int static make_packet_input(const int& client, int key);
	int static make_packet_destroy_bullet(const int& client, int idx);
	int static make_packet_destroy_item(int idx);
	int static make_packet_destroy_player(const int& client);
	int static make_packet_hit_player(const int& client, int damage);
	int static make_packet_game_end(const int& winner);
	int static make_packet_game_start();
	int static get_packet_chat(const int& packet);
	int static get_packet_type(const int& packet);
	int static get_packet_obj_info(const int& packet);
	int static get_packet_obj_type(const int& packet);
	int static get_packet_player_num(const int& packet);
	int static get_packet_input(const int& packet);
	int static get_packet_bullet_idx(const int& packet);
	int static get_packet_bullet_type(const int& packet);
	int static get_packet_event_type(const int& packet);
	int static get_packet_system_type(const int& packet);
		 
	int static get_player_num(const int& num);

};

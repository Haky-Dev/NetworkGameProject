#pragma comment(lib, "ws2_32")
#include <fstream>
#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <mutex>
#include <queue>
#include <list>
#include "Timer.h"
using namespace std;

//Scene
#include "Object.h"
#include "Config.h"
#include <map>

//Packet
#include "PacketLibrary.h"
#include "PacketTypes.h"

#define SERVERPORT 9000
#define MAX_BUFFER_SIZE 200

#define CLIENT_EXIT 0
#define COMMON_BULLET_NUM 128
#define COMMON_BULLET_DAMAGE 1

int g_curUserCnt;
int MAX_PLAYER = 3;
queue<int> idQueue;
mutex g_idlock;
int match_round;

float refreshtime;

//Threads
vector<thread> g_recvThreads;

//Message Queue
mutex g_recvLock;
queue<int> g_recvQueue;
queue<Vector2d> g_recvAddData;
vector<int> SendQueue;

//Scene Value
enum class ServerState {SS_AcceptPlayer, SS_PlayGame};
ServerState state;
bool isEnd = false;

int m_Width = WINDOW_WIDTH;
int m_Height = WINDOW_HEIGHT;
Object* m_wall[4];
Object* m_block[8];
Item* m_item[MAX_ITEM];
map<int, Player> PlayerList;
Vector2d Initialpos[3]{ {-3, -1.5}, {+3, -1.5},{0, 1.5} };

//총알분수
Bullet m_commonBullet[COMMON_BULLET_NUM];
int AddBullet(Vector2d pos, Vector2d vol, Vector2d vel, float r, float g, float b, float a, float mass, float fricCoef)
{
	int idx = -1;
	for (int i = 0; i < COMMON_BULLET_NUM; ++i)
	{
		if (m_commonBullet[i].m_visible == false)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		std::cout << "No more remaining object" << std::endl;
		return idx;
	}

	m_commonBullet[idx].m_visible = true;
	m_commonBullet[idx].SetPos(pos);
	m_commonBullet[idx].SetColor(r, g, b, a);
	m_commonBullet[idx].SetVol(vol);
	m_commonBullet[idx].SetVel(vel);
	m_commonBullet[idx].SetMass(mass);
	m_commonBullet[idx].SetFriction(fricCoef);

	return idx;
}

//총알분수
void ShootBullet(float fTimeElapsed)
{
	static float shootTime = 0.05f;
	static float remainTime = 0.0f;
	static float rot = 3.0f;
	static Vector2d m_pos{ 0, 0 };
	static Vector2d m_dir[4]{ {1, 0},{-1, 0}, {0, 1}, {0, -1} };

	remainTime -= fTimeElapsed;
	if (remainTime > 0) return;


	float fAmountBullet = 8.0f, mass = 1.0f, fricCoef = 0.9f;

	for (auto& dir : m_dir)
	{
		dir.rotate(rot);
		Vector2d hVel = dir * fAmountBullet;
		Vector2d vol(0.05f, 0.05f);
		int idx = AddBullet(m_pos, vol, hVel, 1, 0, 0, 1, mass, fricCoef);
		m_commonBullet[idx].type = 1;
	}

	remainTime = shootTime;
}

//Error Handler
void err_quit(const char* msg);
void err_display(const char* msg);

//SendPacket ID, POS, 
void send_packet_player_id(SOCKET client, const int& id)
{
	int packet = 0;
	PacketLibrary::pTurnOn(packet, id);
	send(client, (const char*)& packet, sizeof(int), 0);
}
void reserve_packet_player_pos(const Player& mover, vector<int>& dat)
{
	int packet = 0;
	PacketLibrary::pTurnOn(packet, p_obj);
	PacketLibrary::pTurnOn(packet, mover.m_id);
	PacketLibrary::pTurnOn(packet, obj_player);
	PacketLibrary::pTurnOn(packet, obj_position);

	int* p_pos = (int*)& mover.m_position.x;
	dat.emplace_back(packet);
	dat.emplace_back(*p_pos++);
	dat.emplace_back(*p_pos++);
}
void reserve_packet_bullet_pos(const Player& shooter, const int& idx, vector<int>& dat)
{
	int packet = 0;
	int bullet_type = shooter.bullets[idx].type << 24;

	PacketLibrary::pTurnOn(packet, p_obj);
	PacketLibrary::pTurnOn(packet, shooter.m_id);
	PacketLibrary::pTurnOn(packet, idx);
	PacketLibrary::pTurnOn(packet, bullet_type);
	PacketLibrary::pTurnOn(packet, obj_bullet);
	PacketLibrary::pTurnOn(packet, obj_position);

	int* p_pos = (int *)&shooter.bullets[idx].m_position.x;
	dat.emplace_back(packet);
	dat.emplace_back(*p_pos++);
	dat.emplace_back(*p_pos++);
}
void reserve_packet_common_bullet_pos(const int& shooter_id, const int& idx, vector<int>& dat)
{
	int packet = 0;

	PacketLibrary::pTurnOn(packet, p_obj);
	PacketLibrary::pTurnOn(packet, shooter_id);
	PacketLibrary::pTurnOn(packet, idx);
	PacketLibrary::pTurnOn(packet, obj_bullet);
	PacketLibrary::pTurnOn(packet, obj_position);

	int* p_pos = (int*)& m_commonBullet[idx].m_position.x;
	dat.emplace_back(packet);
	dat.emplace_back(*p_pos++);
	dat.emplace_back(*p_pos++);
}
void reserve_packet_item_pos(const int& idx, vector<int>& dat)
{
	int packet = 0;
	int item_type = m_item[idx]->type << 24;

	PacketLibrary::pTurnOn(packet, p_obj);
	PacketLibrary::pTurnOn(packet, idx);
	PacketLibrary::pTurnOn(packet, item_type);
	PacketLibrary::pTurnOn(packet, obj_item);
	PacketLibrary::pTurnOn(packet, obj_position);

	int* p_pos = (int*)& m_item[idx]->m_position.x;
	dat.emplace_back(packet);
	dat.emplace_back(*p_pos++);
	dat.emplace_back(*p_pos++);
}

//Message Process
void ProcessInputPacket(const int& packet, queue<Vector2d>& addData) {
	int sender = PacketLibrary::get_packet_player_num(packet);
	int input = PacketLibrary::get_packet_input(packet);
	switch (input)
	{
	case input_Wdown:
		PlayerList[sender].m_keyW = true;
		break;
	case input_Wup:
		PlayerList[sender].m_keyW = false;
		break;

	case input_Sdown:
		PlayerList[sender].m_keyS = true;
		break;
	case input_Sup:
		PlayerList[sender].m_keyS = false;
		break;

	case input_Adown:
		PlayerList[sender].m_keyA = true;
		break;
	case input_Aup:
		PlayerList[sender].m_keyA = false;
		break;

	case input_Ddown:
		PlayerList[sender].m_keyD = true;
		break;
	case input_Dup:
		PlayerList[sender].m_keyD = false;
		break;

	case input_Mleft:
		Vector2d Data = addData.front(); addData.pop();
		PlayerList[sender].ShootBullet(Data);
		break;
	}
}

void PacketReceiver(SOCKET socket, int id)
{
	int recvSize;

	size_t needSize = GENERAL_PACKET_SIZE;
	size_t savedSize = 0;

	int packet = 0;
	Vector2d addData;
	char buffer[MAX_BUFFER_SIZE];
	char savedBuffer[EXTEND_PACKET_SIZE];
	char* bufPos = NULL;

	queue<int> tempPacketQueue;
	queue<Vector2d> tempExtraPacketQueue;

	while (true) {
		recvSize = recv(socket, buffer, MAX_BUFFER_SIZE, 0);
		if (recvSize == 0 || recvSize == SOCKET_ERROR)
		{
			closesocket(socket);
			cout << "PLAYER EXIT : " << socket << endl;
			if (state == ServerState::SS_AcceptPlayer) {
				g_idlock.lock();
				g_curUserCnt--;
				idQueue.emplace(id);
				g_idlock.unlock();
			}
			else {
				PlayerList[id].m_isConnect = false;
			}
			return;
		}

		bufPos = buffer;
		while (recvSize > 0)
		{
			if (recvSize + savedSize >= needSize) {
				int copy_size = (needSize - savedSize);
				memcpy(savedBuffer + savedSize, bufPos, copy_size);
				bufPos += copy_size;
				recvSize -= copy_size;

				switch (needSize) {
				case GENERAL_PACKET_SIZE:
					packet = *(int*)savedBuffer;
					if (PacketLibrary::is_extend_packet_server(packet)) {
						needSize = EXTEND_PACKET_SIZE;
						savedSize = GENERAL_PACKET_SIZE;
						continue;
					}
					needSize = GENERAL_PACKET_SIZE;
					tempPacketQueue.emplace(packet);
					break;

				case EXTEND_PACKET_SIZE:
					packet = *(int*)savedBuffer;
					addData = *(Vector2d*)(savedBuffer + GENERAL_PACKET_SIZE);
					tempPacketQueue.emplace(packet);
					tempExtraPacketQueue.emplace(addData);
					needSize = GENERAL_PACKET_SIZE;
					break;
				}
				savedSize = 0;
			}
			else {
				memcpy(savedBuffer + savedSize, bufPos, recvSize);
				savedSize += recvSize;
				recvSize = 0;
			}
		}
		
		g_recvLock.lock();
		while (tempPacketQueue.empty() != true) {
			g_recvQueue.emplace(tempPacketQueue.front());
			tempPacketQueue.pop();
		}
		while (tempExtraPacketQueue.empty() != true) {
			g_recvAddData.emplace(tempExtraPacketQueue.front());
			tempExtraPacketQueue.pop();
		}
		g_recvLock.unlock();
	}
}
void ProcessPacket() {
	queue<int> cRecvQueue;
	queue<Vector2d> cAddData;

	g_recvLock.lock();
	if (g_recvQueue.empty() == false) {
		cRecvQueue = g_recvQueue;
		while (g_recvQueue.empty() == false)
			g_recvQueue.pop();

		if (g_recvAddData.empty() == false) {
			cAddData = g_recvAddData;
			while (g_recvAddData.empty() == false)
				g_recvAddData.pop();
		}
	}
	g_recvLock.unlock();

	while (cRecvQueue.empty() == false)
	{
		int packet = cRecvQueue.front(); cRecvQueue.pop();
		int packet_type = PacketLibrary::get_packet_type(packet);

		switch (packet_type)
		{
		case p_system:
			break;

		case p_input:
			ProcessInputPacket(packet, cAddData);
			break;

		case p_obj:
			break;

		case p_event:
			SendQueue.emplace_back(packet);
			break;
		}
	}
}

//Game Logic
void Initialize()
{
	int count = 0;
	for (auto& p_pair : PlayerList)
		p_pair.second.m_position = Initialpos[count++];

	//Add Unvisible Wall
	m_wall[0] = new Object();
	m_wall[0]->SetPos((m_Width + m_Height) / 200, 0);
	m_wall[0]->SetVol(m_Height / 100, m_Height / 100);
	m_wall[1] = new Object();
	m_wall[1]->SetPos(-(m_Width + m_Height) / 200, 0);
	m_wall[1]->SetVol(m_Height / 100, m_Height / 100);
	m_wall[2] = new Object();
	m_wall[2]->SetPos(0, (m_Width + m_Height) / 200);
	m_wall[2]->SetVol(m_Width / 100, m_Width / 100);
	m_wall[3] = new Object();
	m_wall[3]->SetPos(0, -(m_Width + m_Height) / 200);
	m_wall[3]->SetVol(m_Width / 100, m_Width / 100);

	//Add Block
	float volumn = 0.5f;
	m_block[0] = new Object();
	m_block[0]->SetPos(m_Width / 400, 0);
	m_block[0]->SetVol(volumn, volumn);
	m_block[1] = new Object();
	m_block[1]->SetPos(-m_Width / 400, 0);
	m_block[1]->SetVol(volumn, volumn);
	m_block[2] = new Object();
	m_block[2]->SetPos(0, m_Height / 400);
	m_block[2]->SetVol(volumn, volumn);
	m_block[3] = new Object();
	m_block[3]->SetPos(0, -m_Height / 400);
	m_block[3]->SetVol(volumn, volumn);

	m_block[4] = new Object();
	m_block[4]->SetPos(m_Width / 400, m_Height / 400 * 2);
	m_block[4]->SetVol(volumn, volumn);
	m_block[5] = new Object();
	m_block[5]->SetPos(-m_Width / 400, m_Height / 400 * 2);
	m_block[5]->SetVol(volumn, volumn);
	m_block[6] = new Object();
	m_block[6]->SetPos(m_Width / 400, -m_Height / 400 * 2);
	m_block[6]->SetVol(volumn, volumn);
	m_block[7] = new Object();
	m_block[7]->SetPos(-m_Width / 400, -m_Height / 400 * 2);
	m_block[7]->SetVol(volumn, volumn);

	//Add Item
	m_item[0] = new Item();
	m_item[0]->SetPos(m_Width / 400, m_Height / 400);
	m_item[0]->SetVol(0.2f, 0.2f);
	m_item[0]->m_visible = true;
	m_item[1] = new Item();
	m_item[1]->SetPos(m_Width / 400, -m_Height / 400);
	m_item[1]->SetVol(0.2f, 0.2f);
	m_item[1]->m_visible = true;
	m_item[2] = new Item();
	m_item[2]->SetPos(-m_Width / 400, -m_Height / 400);
	m_item[2]->SetVol(0.2f, 0.2f);
	m_item[2]->m_visible = true;
	m_item[3] = new Item();
	m_item[3]->SetPos(-m_Width / 400, m_Height / 400);
	m_item[3]->SetVol(0.2f, 0.2f);
	m_item[3]->m_visible = true;

	//아이템 위치 전송
	for (auto& p_pair : PlayerList)
		for (int i = 0; i < MAX_ITEM; i++)
			reserve_packet_item_pos(i, SendQueue);

	for (auto& bullet : m_commonBullet)
		bullet.m_visible = false;
}
void DoGarbageCollection()
{
	//delete bullets
	for (auto& p_pair : PlayerList)
	{
		auto& player = p_pair.second;
		if (player.m_visible == false) continue;

		for (int i = 0; i < MAX_BULLET; ++i)
		{
			if (player.bullets[i].m_visible == false) continue;
			if (player.bullets[i].m_velocity.length() < 0.00001f) {
				player.bullets[i].m_visible = false;
				int packet = PacketLibrary::make_packet_destroy_bullet(player.m_id, i);
				SendQueue.emplace_back(packet);
			}
		}
	}

	for (int i=0;i<100;++i)
	{
		if (m_commonBullet[i].m_visible == false) continue;
		if (m_commonBullet[i].m_velocity.length() < 0.00001f) {
			m_commonBullet[i].m_visible = false;
			int packet = PacketLibrary::make_packet_destroy_bullet(static_cast<int>(player_num::player_num4), i);
			SendQueue.emplace_back(packet);
		}
	}
}
void DeleteObjects() {
	for (int i = 0; i < 4; i++) {
		delete m_wall[i];
		m_wall[i] = NULL;
	}
	for (int i = 0; i < MAX_ITEM; i++) {
		delete m_item[i];
		m_item[i] = NULL;
	}

	for (int i = 0; i < 8; i++) {
		delete m_block[i];
		m_block[i] = NULL;
	}
}
void Update(float deltaTime)
{
	//플레이어 업데이트
	for (auto& p_player : PlayerList)
	{
		auto& player = p_player.second;
		//Move Player
		player.keyMove(deltaTime);
		//총알 발사
		if (player.m_mouseLeft == true && player.CanShootBullet()) {
			player.ShootBullet(player.m_mousepos);
		}
		player.Update(deltaTime);
	}

	//총알분수
	ShootBullet(deltaTime);
	for (auto& b : m_commonBullet)
		b.Update(deltaTime);

	//Collision Detect
	for (auto& p_pair : PlayerList)
	{
		if (p_pair.second.m_visible == false) continue;
		auto& player = p_pair.second;

		//플레이어, 벽 체크
		for (auto& wall : m_wall)
		{
			if (player.isOverlap(*wall)) {
				player.correctpos(*wall);
			}
		}

		//플레이어, 장애물 체크
		for (auto& block : m_block)
		{
			if (player.isOverlap(*block)) {
				player.correctpos(*block);
			}
		}

		//플레이어, 아이템 체크
		for (int i = 0; i < MAX_ITEM; ++i)
		{
			if (m_item[i]->m_visible == false) continue;
			if (player.isOverlap(*m_item[i])) {
				player.weapon = m_item[i]->type;
				m_item[i]->m_visible = false;
				int packet = PacketLibrary::make_packet_destroy_item(i);
				SendQueue.emplace_back(packet);
			}
		}

		//총알 충돌체크
		for (int i = 0; i < MAX_BULLET; ++i)
		{
			if (player.bullets[i].m_visible == false) continue;

			//총알, 벽체크
			for (auto& block : m_block)
			{
				if (block->isOverlap(player.bullets[i])) {
					player.bullets[i].m_visible = false;
					int packet = PacketLibrary::make_packet_destroy_bullet(player.m_id, i);
					SendQueue.emplace_back(packet);
					break;
				}
			}

			//총알, 플레이어 체크
			for (auto& p_other : PlayerList)
			{
				if (p_other.second.m_visible == false) continue;
				if (p_other.first == p_pair.first) continue;
				if (p_other.second.isOverlap(player.bullets[i])) {
					player.bullets[i].m_visible = false;
					int packet = PacketLibrary::make_packet_destroy_bullet(player.m_id, i);
					SendQueue.emplace_back(packet);
					if (p_other.second.getDamage(player.bullets[i])) {
						//사망처리
						p_other.second.die();
						int packet = PacketLibrary::make_packet_destroy_player(p_other.second.m_id);
						SendQueue.emplace_back(packet);
					}
					else {
						//데미지처리
						int packet = PacketLibrary::make_packet_hit_player(p_other.second.m_id, player.m_damage[player.bullets[i].type]);
						SendQueue.emplace_back(packet);
					}
				}
			}
		}

		//중립총알 체크
		for (int i = 0; i < COMMON_BULLET_NUM; i++)
		{
			if (m_commonBullet[i].m_visible == false) continue;
			//총알, 벽체크
			for (auto& block : m_block)
			{
				if (block->isOverlap(m_commonBullet[i])) {
					m_commonBullet[i].m_visible = false;
					int packet = PacketLibrary::make_packet_destroy_bullet(static_cast<int>(player_num::player_num4), i);
					SendQueue.emplace_back(packet);
					break;
				}
			}

			//총알, 플레이어 체크
			for (auto& p_other : PlayerList)
			{
				if (p_other.second.m_visible == false) continue;
				if (p_other.second.isOverlap(m_commonBullet[i])) {
					m_commonBullet[i].m_visible = false;
					int packet = PacketLibrary::make_packet_destroy_bullet(static_cast<int>(player_num::player_num4), i);
					SendQueue.emplace_back(packet);
					if (p_other.second.getDamage(COMMON_BULLET_DAMAGE)) {
						//사망처리
						p_other.second.die();
						int packet = PacketLibrary::make_packet_destroy_player(p_other.second.m_id);
						SendQueue.emplace_back(packet);
					}
					else {
						//데미지처리
						int packet = PacketLibrary::make_packet_hit_player(p_other.second.m_id, COMMON_BULLET_DAMAGE);
						SendQueue.emplace_back(packet);
					}
				}
			}

		}

	}

	//종료 검사
	int live_count = 0;
	int last_liver = 0;
	for (auto& p_player : PlayerList) {
		if (p_player.second.m_visible == true) {
			++live_count;
			last_liver = p_player.second.m_id;
		}
	}

	if (live_count <= 1) {
		int packet = PacketLibrary::make_packet_game_end(last_liver);
		SendQueue.emplace_back(packet);
		isEnd = true;
		return;
	}

	DoGarbageCollection();
}
void SendGameState() {
	for (auto& p_other_player : PlayerList)
	{
		auto& other_player = p_other_player.second;
		if (other_player.m_visible == false) continue;
		reserve_packet_player_pos(other_player, SendQueue);
		for (int i = 0; i < MAX_BULLET; ++i)
			if (other_player.bullets[i].m_visible)
				reserve_packet_bullet_pos(other_player, i, SendQueue);
	}

	for (int i = 0; i < COMMON_BULLET_NUM; ++i) {
		if (m_commonBullet[i].m_visible)
			reserve_packet_common_bullet_pos(static_cast<int>(player_num::player_num4), i, SendQueue);
	}

	for (auto& p_player : PlayerList)
	{
		if (p_player.second.m_isConnect == true)
			send(p_player.second.m_socket, (const char*)SendQueue.data(), SendQueue.size() * sizeof(int), 0);
	}

	SendQueue.clear();
}

int main()
{
	refreshtime = 1.0f / UPDATE_RATE;

	//TCP 소켓 세팅
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_socket == INVALID_SOCKET) err_quit("socket()");

	//네이글 알고리즘 : 작은 패킷을 연속해서 보내 처리하는 비효율을 극복하기 위해 일정량 만큼을 모아서 보내는 알고리즘.
	int opt_val = TRUE;
	setsockopt(listen_socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt_val, sizeof(opt_val));

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(SERVERPORT);

	int retval = ::bind(listen_socket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(SOCKADDR_IN));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	retval = listen(listen_socket, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	SOCKET client_sock;
	SOCKADDR_IN clientAddr;
	int addrlen = sizeof(SOCKADDR_IN);

	while (true) {

#pragma region ResetMatch
		//매치 시작전 초기화
		match_round++;
		PlayerList.clear();
		while (!idQueue.empty()) idQueue.pop();
		idQueue.emplace(player_num::player_num1);
		idQueue.emplace(player_num::player_num2);
		idQueue.emplace(player_num::player_num3);
#pragma endregion


		
		
#pragma region Accept
		//유저접속 대기
		cout << "Start Player Accept\n";
		state = ServerState::SS_AcceptPlayer;
		isEnd = false;
		g_curUserCnt = 0;

		while (g_curUserCnt < MAX_PLAYER) {
			client_sock = accept(listen_socket, reinterpret_cast<SOCKADDR*>(&clientAddr), &addrlen);

			if (client_sock == INVALID_SOCKET) {
				err_display("accept()");
				break;
			}

			cout << "PLAYER ACCPET : " << client_sock << endl;

			g_idlock.lock();
			++g_curUserCnt;
			int id = idQueue.front(); idQueue.pop();
			g_idlock.unlock();

			//플레이어 접속 확인 패킷 전송
			send_packet_player_id(client_sock, id);
			PlayerList[id] = Player(id, static_cast<int>(client_sock));

			if (retval == SOCKET_ERROR)
				err_quit("Accept()_PlayerNum 할당.");

			g_recvThreads.emplace_back(PacketReceiver, client_sock, id);
		}
#pragma endregion

#pragma region Match
		cout << "All User Connected, Start Match #" << match_round << endl;
		state = ServerState::SS_PlayGame;
		SendQueue.emplace_back(PacketLibrary::make_packet_game_start());

		//게임 로직
		refreshtime = 1.0f / 30.0f;
		float remain_time = refreshtime;
		Initialize();
		Timer timer;
		timer.setFPS(60.0f);
		timer.tick();

		while (true) {
			float fTimeElapsed = timer.tick();
			ProcessPacket();
			Update(fTimeElapsed);
			if ((remain_time -= fTimeElapsed) <= 0) {
				SendGameState();
				remain_time += refreshtime;
				if (isEnd == true) break;
			}
		}
#pragma endregion

#pragma region MatchEnd

		//게임 종료처리
		cout << "Match END | Disconnect All Players\n";
		DeleteObjects();

		for (auto& p_player : PlayerList) {
			closesocket(p_player.second.m_socket);
		}

		for (thread& t : g_recvThreads)
			if (t.joinable())
				t.join();
		g_recvThreads.clear();
	
#pragma endregion
	}
		

	for (thread& t : g_recvThreads)
		if (t.joinable())
			t.join();

	closesocket(listen_socket);
	WSACleanup();
}

// 소켓 오류 출력 함수
void err_quit(const char* msg) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)& lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}
void err_display(const char* msg) {
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)& lpMsgBuf, 0, NULL);

	printf("[%s] %s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
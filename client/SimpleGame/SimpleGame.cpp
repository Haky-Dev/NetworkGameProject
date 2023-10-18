#pragma once

/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

#include <thread>
#include <queue>
#include <mutex>

//Network Header
#include "..\..\server\server\PacketLibrary.h"
#include "..\..\server\server\PacketTypes.h"

#include "GameManager.h"
#include "TimeManager.h"

#include "Config.h"
#include "Object.h"
#include "main.h"

GameManager *g_GameManager = NULL;
TimeManager g_timeManager;
SOCKET g_socket;
string SERVERIP;

constexpr int WIDTH_BIAS = WINDOW_WIDTH / 2;
constexpr int HEIGHT_BIAS = WINDOW_HEIGHT / 2;

//Message Queue
HANDLE connect_success;
mutex RecvLock;
queue<int> RecvQueue;
queue<Vector2d> RecvAddData;

//받은 패킷 처리
void PacketReceiver(SOCKET socket)
{
	int recvSize;
	
	size_t needSize = GENERAL_PACKET_SIZE;
	size_t savedSize = 0;

	int packet = 0;
	Vector2d addData;
	char buffer[MAX_BUFFER_SIZE];
	char savedBuffer[EXTEND_PACKET_SIZE];
	char* bufPos = NULL;

	queue<int> tempQueue;
	queue<Vector2d> tempAddQueue;

	while (true) {
		//패킷 수신
		recvSize = recv(socket, buffer, MAX_BUFFER_SIZE, 0);
		if (recvSize == 0 || recvSize == SOCKET_ERROR)
		{
			closesocket(socket);
			return;
		}

		bufPos = buffer; //버퍼 초기 위치 포인터 설정
		while (recvSize > 0)
		{
			if (recvSize + savedSize >= needSize) {

				
				int copy_size = (needSize - savedSize); //이전 미수신된 사이즈 계산
				memcpy(savedBuffer + savedSize, bufPos, copy_size); //버퍼에 저장
				bufPos += copy_size; //수신된 만큼 버퍼 위치 포인터 설정
				recvSize -= copy_size; //처리한 만큼 수신된 사이즈 설정

				switch (needSize) {
				case GENERAL_PACKET_SIZE:
					packet = *(int*)savedBuffer;
					if (PacketLibrary::is_extend_packet_client(packet)) {
						needSize = EXTEND_PACKET_SIZE;
						savedSize = GENERAL_PACKET_SIZE;
						continue;
					}
					needSize = GENERAL_PACKET_SIZE;
					tempQueue.emplace(packet);
					break;

				case EXTEND_PACKET_SIZE:
					packet = *(int*)savedBuffer;
					addData = *(Vector2d*)(savedBuffer + GENERAL_PACKET_SIZE);
					tempQueue.emplace(packet);
					tempAddQueue.emplace(addData);
					needSize = GENERAL_PACKET_SIZE;
					break;
				}
				savedSize = 0;
			}
			else {
				//패킷이 아직 전부 수신되지 않아 임시 저장
				memcpy(savedBuffer + savedSize, bufPos, recvSize);
				savedSize += recvSize;
				recvSize = 0;
			}
		}

		RecvLock.lock();
		while (tempQueue.empty() != true) {
			RecvQueue.emplace(tempQueue.front());
			tempQueue.pop();
		}
		while (tempAddQueue.empty() != true) {
			RecvAddData.emplace(tempAddQueue.front());
			tempAddQueue.pop();
		}
		RecvLock.unlock();
	}
}
void ProcessObjectPacket(const int& packet, queue<Vector2d>& addData) {
	int mover = PacketLibrary::get_packet_player_num(packet);
	int objtype = PacketLibrary::get_packet_obj_type(packet);
	int objinfo = PacketLibrary::get_packet_obj_info(packet);
	
	switch (objinfo)
	{
	case obj_position:
	{
			switch (objtype)
			{
				case obj_player: {
					Vector2d Data = addData.front(); addData.pop();
					if (g_GameManager->m_players[mover].GetAcitve() == false) {
						g_GameManager->m_players[mover].SetDestination(Data);
						g_GameManager->m_players[mover].SetPosition(Data);
					}
					else
						g_GameManager->m_players[mover].SetDestination(Data);
					g_GameManager->m_players[mover].SetActive(true);
				}
					break;

				case obj_bullet: {
					if (mover != static_cast<int>(player_num::player4)) {
						int idx = PacketLibrary::get_packet_bullet_idx(packet);
						int type = PacketLibrary::get_packet_bullet_type(packet);
						Vector2d Data = addData.front(); addData.pop();
						if (g_GameManager->m_players[mover].bullets[idx].GetAcitve() == false)
							g_GameManager->m_players[mover].bullets[idx].SetPosition(g_GameManager->m_players[mover].GetPosition());
						g_GameManager->m_players[mover].bullets[idx].SetActive(true);
						g_GameManager->m_players[mover].bullets[idx].type = type;
						g_GameManager->m_players[mover].bullets[idx].SetDestination(Data);
					}
					else {
						int idx = PacketLibrary::get_packet_bullet_idx(packet);
						Vector2d Data = addData.front(); addData.pop();
						if (g_GameManager->m_bullets[idx]->GetAcitve() == false)
							g_GameManager->m_bullets[idx]->SetPosition(Data);
						g_GameManager->m_bullets[idx]->SetActive(true);
						g_GameManager->m_bullets[idx]->SetDestination(Data);
					}
				}
					break;

				case obj_item: {
					int idx = PacketLibrary::get_packet_bullet_idx(packet);
					int type = PacketLibrary::get_packet_bullet_type(packet);
					Vector2d Data = addData.front(); addData.pop();
					g_GameManager->m_item[idx].SetActive(true);
					g_GameManager->m_item[idx].type = type;
					g_GameManager->m_item[idx].SetPosition(Data);
				}
								 break;
			}	
	}
	break;

	case obj_destroy:
		switch (objtype)
		{
			case obj_player:
				g_GameManager->m_players[mover].SetActive(false);
				g_GameManager->alive_count--;
				break;

			case obj_bullet: {
				int idx = PacketLibrary::get_packet_bullet_idx(packet);
				if (mover != static_cast<int>(player_num::player_num4))
					g_GameManager->m_players[mover].bullets[idx].SetActive(false);
				else
					g_GameManager->m_bullets[idx]->SetActive(false);
				break;
			}

			case obj_item: {
				int idx = PacketLibrary::get_packet_bullet_idx(packet);
				g_GameManager->m_item[idx].SetActive(false);
				break;
			}
		}
		break;
	}

}
void ProcessEventPacket(const int& packet) {
	int client = PacketLibrary::get_packet_player_num(packet);
	int event_type = PacketLibrary::get_packet_event_type(packet);

	switch (event_type)
	{
	case event_hit: {
		int damage = PacketLibrary::get_packet_bullet_idx(packet);
		g_GameManager->m_players[client].m_hp -= damage;
		break;
	}
	case event_chat: {
		int chat = PacketLibrary::get_packet_chat(packet);
		g_GameManager->m_players[client].m_chat = chat;
		g_GameManager->m_players[client].emotion_time = g_GameManager->m_players[client].emotion_duration_time;
		break;
	}
	}
}
void ProcessSystemPacket(const int& packet) {
	int client = PacketLibrary::get_packet_player_num(packet);
	int system_type = PacketLibrary::get_packet_system_type(packet);

	switch (system_type)
	{
	case system_end: {
		closesocket(g_GameManager->soc);
		g_GameManager->winner = client;
		g_GameManager->CurrentSceneIndex = SceneType::scene_end;
		break;
	}
	case system_start:
		g_GameManager->CurrentSceneIndex = SceneType::scene_play;
		g_GameManager->Reset();
		break;
	}
}
void ProcessPacket() {
	queue<int> cRecvQueue;
	queue<Vector2d> cAddData;

	RecvLock.lock();
	if (RecvQueue.empty() == false) {
		cRecvQueue = RecvQueue;
		while (RecvQueue.empty() == false)
			RecvQueue.pop();

		if (RecvAddData.empty() == false) {
			cAddData = RecvAddData;
			while (RecvAddData.empty() == false)
				RecvAddData.pop();
		}
	}
	RecvLock.unlock();

	while (cRecvQueue.empty() == false)
	{
		int packet = cRecvQueue.front(); cRecvQueue.pop();
		int packet_type = PacketLibrary::get_packet_type(packet);

		switch (packet_type)
		{
		case p_system:
			ProcessSystemPacket(packet);
			break;

		case p_obj:
			ProcessObjectPacket(packet, cAddData);
			break;

		case p_event:
			ProcessEventPacket(packet);
			break;
		}
	}
}

// Glut Draw Function
void Display(void)
{
	g_GameManager->RenderScene();
	glutSwapBuffers();
}

// Glut Update Function
void Idle(void)
{
	g_timeManager.TimeUpdate();
	float updateElapsed = g_timeManager.GetUpdateTime();
	if (updateElapsed > UPDATE_FREQUENCY) {
		ProcessPacket();
		g_GameManager->Update(updateElapsed);
		g_timeManager.OnUpdate();
	}
}

void OnMouseInput(int button, int state, int m_x, int m_y)
{
	g_GameManager->OnMouseInput(button, state, m_x-WIDTH_BIAS, -m_y+HEIGHT_BIAS);
}
void OnMouseMove(int m_x, int m_y)
{
	g_GameManager->OnMouseMove(m_x - WIDTH_BIAS, -m_y + HEIGHT_BIAS);
}

void OnKeyDownInput(unsigned char key, int m_x, int m_y)
{
	switch (g_GameManager->CurrentSceneIndex)
	{
	case SceneType::scene_title:
	case SceneType::scene_connect_error:
	{
		TryConnectServer();
		break;
	}
	case SceneType::scene_play:
		g_GameManager->OnKeyDownInput(key, m_x, m_y);
		break;

	case SceneType::scene_end: {
		g_GameManager->CurrentSceneIndex = SceneType::scene_title;
		break;
	}
	}
}
void OnKeyUpInput(unsigned char key, int m_x, int m_y)
{
	g_GameManager->OnKeyUpInput(key, m_x, m_y);
}

void TryConnectServer()
{
	g_GameManager->CurrentSceneIndex = SceneType::scene_connect;
	Display();
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVERPORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVERIP.data());
	g_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int retval = ::connect(g_socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (retval == SOCKET_ERROR) {
		closesocket(g_socket);
		cout << "연결에러" << endl;
		g_GameManager->CurrentSceneIndex = SceneType::scene_connect_error;
	}
	else
	{
		g_GameManager->CurrentSceneIndex = SceneType::scene_wait;
		cout << "성공" << endl;
		int myid;
		recv(g_socket, (char*)&myid, sizeof(int), 0);
		g_GameManager->MYID = myid;
		g_GameManager->soc = g_socket;
		thread recvThread{ PacketReceiver, g_socket };
		recvThread.detach();
	}
}

int main(int argc, char **argv)
{
#pragma region Timer Init
	g_timeManager.Init();
#pragma endregion

#pragma region Network Reset

	//Server IP
	ifstream in("SERVERIP.txt");
	in >> SERVERIP;
	in.close();

	// Socket Initalize
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	
	// Initalize GL
#pragma endregion

#pragma region Initalize GL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	const char* windowTitle = "Network Game Project";
	glutCreateWindow("Network Game Project");
	HWND windowHandle = FindWindow(NULL, windowTitle);
	glewInit();

	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	glutIdleFunc(Idle);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyDownInput);
	glutKeyboardUpFunc(OnKeyUpInput);
	glutMouseFunc(OnMouseInput);
	glutMotionFunc(OnMouseMove);

	glutIgnoreKeyRepeat(1);
	
#pragma endregion

#pragma region Initalize GameManager
	// Initialize RenderManager
	g_GameManager = new GameManager();
#pragma endregion

#pragma region MainLoop
	glutMainLoop();
#pragma endregion

	if(g_GameManager)
		delete g_GameManager;
	g_GameManager = NULL;

	closesocket(g_socket);
	WSACleanup();
    return 0;
}
#pragma once

#include "stdafx.h"
#include "GameManager.h"
#include "Dependencies\freeglut.h"
#include "..\\..\\server\server\PacketLibrary.h"
#include "..\\..\\server\server\PacketTypes.h"
#include <WinSock2.h>
#include "RenderManager.h"
#include "Object.h"

GameManager::GameManager()
{
	//NW
	soc = -1;
	MYID = -1;
	//CurrentSceneIndex = SceneType::scene_play;
	CurrentSceneIndex = SceneType::scene_title;

	m_renderManager = make_unique<RenderManager>(m_Width, m_Height);
	if (!m_renderManager->IsInitialized())
	{
		std::cout << "RenderManager could not be initialized.. \n";
	}

	CreateScene();
}
void GameManager::CreateScene()
{
	int direction[4][2] = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	m_staticObjects.reserve(WALL_NUM + BLOCK_NUM);
	for (int i = 0; i < 4; ++i) {
		shared_ptr<Object> wall = make_shared<Object>();
		wall->SetPosition((m_Width + m_Height) / 200 * direction[i][0], (m_Width + m_Height) / 200 * direction[i][1]);
		wall->SetVolume(m_Width / 100, m_Height / 100);
		wall->SetActive(false);
		m_staticObjects.push_back(wall);
	}
	//Add Unvisible Wall
	//m_wall[0] = new Object();
	//m_wall[0]->SetPosition((m_Width + m_Height) / 200, 0);
	//m_wall[0]->SetVolume(m_Height / 100, m_Height / 100);
	//m_wall[1] = new Object();
	//m_wall[1]->SetPosition(-(m_Width + m_Height) / 200, 0);
	//m_wall[1]->SetVolume(m_Height / 100, m_Height / 100);
	//m_wall[2] = new Object();
	//m_wall[2]->SetPosition(0, (m_Width + m_Height) / 200);
	//m_wall[2]->SetVolume(m_Width / 100, m_Width / 100);
	//m_wall[3] = new Object();
	//m_wall[3]->SetPosition(0, -(m_Width + m_Height) / 200);
	//m_wall[3]->SetVolume(m_Width / 100, m_Width / 100);

	int blockTexId = m_renderManager->GenPngTexture("./Textures/block.png");
	float volume = 50.0f;
	for (int i = 0; i < 4; ++i) {
		shared_ptr<Object> block = make_shared<Object>();
		block->SetPosition(m_Width / 400 * direction[i][0],
			m_Height / 400 * direction[i][1]);
		block->SetVolume(volume, volume);
		block->AddTexture(blockTexId);
		block->SetActive(true);
		m_staticObjects.push_back(block);
	}

	int blockDirection[4][2] = {
		{1, 1}, {-1, 1}, {1, -1}, {-1, -1}
	};

	for (int i = 0; i < 4; ++i) {
		shared_ptr<Object> block = make_shared<Object>();
		block->SetPosition(m_Width / 400 * blockDirection[i][0],
			m_Height / 400 * 2 * blockDirection[i][1]);
		block->SetVolume(volume, volume);
		block->AddTexture(blockTexId);
		block->SetActive(true);
		m_staticObjects.push_back(block);
	}
	/*m_block[4] = new Object();
	m_block[4]->SetPosition(m_Width / 400, m_Height / 400 * 2);
	m_block[4]->SetVolume(volume, volume);
	m_block[5] = new Object();
	m_block[5]->SetPosition(-m_Width / 400, m_Height / 400 * 2);
	m_block[5]->SetVolume(volume, volume);
	m_block[6] = new Object();
	m_block[6]->SetPosition(m_Width / 400, -m_Height / 400 * 2);
	m_block[6]->SetVolume(volume, volume);
	m_block[7] = new Object();
	m_block[7]->SetPosition(-m_Width / 400, -m_Height / 400 * 2);
	m_block[7]->SetVolume(volume, volume);*/

	m_uiObjects.reserve(4);
	Vector2d firstButtonPos(180, -50);
	shared_ptr<Object> btn1 = make_shared<Object>();
	btn1->SetPosition(firstButtonPos);
	btn1->SetVolume(342 / 1.5, 87 / 1.5);
	btn1->AddTexture(m_renderManager->GenPngTexture("./Textures/Start_button.png"));
	btn1->AddTexture(m_renderManager->GenPngTexture("./Textures/On_Start_button.png"));
	btn1->SetActive(false);
	m_uiObjects.push_back(btn1);

	shared_ptr<Object> btn2 = make_shared<Object>();
	btn2->SetPosition(180, firstButtonPos.m_y - 87 / 1.5 - 5);
	btn2->SetVolume(342 / 1.5, 87 / 1.5);
	btn2->AddTexture(m_renderManager->GenPngTexture("./Textures/Exit_button.png"));
	btn2->AddTexture(m_renderManager->GenPngTexture("./Textures/On_Exit_button.png"));
	btn2->SetActive(false);
	m_uiObjects.push_back(btn2);

	shared_ptr<Object> aliveCnt = make_shared<Object>();
	aliveCnt->SetPosition(300, 200);
	aliveCnt->SetVolume(234 / 2, 106 / 2);
	aliveCnt->SetDepth(2);
	aliveCnt->AddTexture(m_renderManager->GenPngTexture("./Textures/alive1.png"));
	aliveCnt->AddTexture(m_renderManager->GenPngTexture("./Textures/alive2.png"));
	aliveCnt->AddTexture(m_renderManager->GenPngTexture("./Textures/alive3.png"));
	aliveCnt->AddTexture(m_renderManager->GenPngTexture("./Textures/alive_many.png"));
	aliveCnt->SetActive(true);

	m_uiObjects.push_back(aliveCnt);

	shared_ptr<Object> bg = make_shared<Object>();
	bg->SetPosition(0, 0);
	bg->SetVolume(WINDOW_WIDTH, WINDOW_HEIGHT);
	bg->AddTexture(m_renderManager->GenPngTexture("./Textures/bg.png"));
	bg->SetActive(true);
	m_uiObjects.push_back(bg);

	m_stateObj = make_shared<Object>();
	m_stateObj->SetPosition(0, 0);
	m_stateObj->SetVolume(WINDOW_WIDTH, -WINDOW_HEIGHT);
	m_stateObj->AddTexture(m_renderManager->GenPngTexture("./Textures/title_J.png"));
	m_stateObj->AddTexture(m_renderManager->GenPngTexture("./Textures/connect_J.png"));
	m_stateObj->AddTexture(m_renderManager->GenPngTexture("./Textures/connect_error_J.png"));
	m_stateObj->AddTexture(m_renderManager->GenPngTexture("./Textures/wait_J.png"));
	m_stateObj->SetActive(true);

	//m_UIbutton[0] = new Object();
	//m_UIbutton[0]->SetPosition(firstButtonPos);
	//m_UIbutton[0]->SetVolume(342 / 1.5, 87 / 1.5);
	//m_UIbutton[1] = new Object();
	//m_UIbutton[1]->SetPosition(180, firstButtonPos.m_y - 87 / 1.5 - 5);
	//m_UIbutton[1]->SetVolume(342 / 1.5, 87 / 1.5);
	//m_UIAliveCount = new Object();
	//m_UIAliveCount->SetPosition(300, 200);
	//m_UIAliveCount->SetVolume(234 / 2, 106 / 2);

	vector<int> bulletTextures;
	bulletTextures.push_back(m_renderManager->GenPngTexture("./Textures/bullet1.png"));
	bulletTextures.push_back(m_renderManager->GenPngTexture("./Textures/bullet2.png"));
	bulletTextures.push_back(m_renderManager->GenPngTexture("./Textures/bullet3.png"));
	for (int i = 0; i < COMMON_BULLET_NUM; ++i)
	{
		shared_ptr<Object> bullet = make_shared<Object>();
		bullet->SetTexture(bulletTextures);
		bullet->SetActive(false);
		bullet->SetTextureIndex(0);
		bullet->SetVolume(5.f, 5.f);
		m_bullets[i] = bullet;
	}

	//for (auto& bullet : m_commonBullet) {
	//	bullet = new Object();
	//	bullet->SetVisibility(false);
	//}
}
void GameManager::InitializeTexture()
{
	textures[0] = m_renderManager->GenPngTexture("./Textures/bg.png");
	playerTexture = m_renderManager->GenPngTexture("./Textures/player.png");
	textures[2] = m_renderManager->GenPngTexture("./Textures/block.png");
	textures[3] = m_renderManager->GenPngTexture("./Textures/mushroom.png");
	bullettextures[0] = m_renderManager->GenPngTexture("./Textures/bullet1.png");
	bullettextures[1] = m_renderManager->GenPngTexture("./Textures/bullet2.png");
	bullettextures[2] = m_renderManager->GenPngTexture("./Textures/bullet3.png");
	winlose[0] = m_renderManager->GenPngTexture("./Textures/win_J.png");
	winlose[1] = m_renderManager->GenPngTexture("./Textures/lose_J.png");
	hpbar = m_renderManager->GenPngTexture("./Textures/hp.png");
	state_texture[0] = m_renderManager->GenPngTexture("./Textures/title_J.png");
	state_texture[1] = m_renderManager->GenPngTexture("./Textures/connect_J.png");
	state_texture[2] = m_renderManager->GenPngTexture("./Textures/connect_error_J.png");
	state_texture[3] = m_renderManager->GenPngTexture("./Textures/wait_J.png");
	item_texture[0] = m_renderManager->GenPngTexture("./Textures/item1.png");
	item_texture[1] = m_renderManager->GenPngTexture("./Textures/item2.png");
	item_texture[2] = m_renderManager->GenPngTexture("./Textures/item3.png");
	message_texture[0] = m_renderManager->GenPngTexture("./Textures/M_HI.png");
	message_texture[1] = m_renderManager->GenPngTexture("./Textures/M_BYE.png");
	message_texture[2] = m_renderManager->GenPngTexture("./Textures/M_NO.png");
	message_texture[3] = m_renderManager->GenPngTexture("./Textures/M_SRY.png");
	message_texture[4] = m_renderManager->GenPngTexture("./Textures/M_STAY.png");
	message_texture[5] = m_renderManager->GenPngTexture("./Textures/M_HELP.png");

	//button
	/*button[0][0] = m_renderManager->GenPngTexture("./Textures/Start_button.png");
	button[0][1] = m_renderManager->GenPngTexture("./Textures/On_Start_button.png");

	button[1][0] = m_renderManager->GenPngTexture("./Textures/Exit_button.png");
	button[1][1] = m_renderManager->GenPngTexture("./Textures/On_Exit_button.png");*/

	//Alive
	/*alive[0] = m_renderManager->GenPngTexture("./Textures/alive1.png");
	alive[1] = m_renderManager->GenPngTexture("./Textures/alive2.png");
	alive[2] = m_renderManager->GenPngTexture("./Textures/alive3.png");
	alive[3] = m_renderManager->GenPngTexture("./Textures/alive_many.png");*/
}
GameManager::~GameManager()
{
}

void GameManager::Update(float deltaTime)
{
	for (auto& b : m_bullets)
		b->Update(deltaTime);

	//플레이어 위치 보간
	for (auto& p_pair : m_players)
		p_pair.second.Update(deltaTime);

	//입력 값, 마우스 위치 서버 전송
	if (m_mouseLeft && m_players[MYID].CanShootBullet()) {
		int packet = PacketLibrary::make_packet_input(MYID, input_Mleft);
		send(soc, (const char*)& packet, sizeof(int), 0);
		send(soc, (const char*)& m_mousepos, sizeof(Vector2d), 0);
	}
}
void GameManager::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	switch (CurrentSceneIndex)
	{
	case SceneType::scene_title:
	case SceneType::scene_connect:
	case SceneType::scene_connect_error:
	case SceneType::scene_wait:
		m_renderManager->DrawTextureObject(m_stateObj.get(), static_cast<int>(CurrentSceneIndex));
		//m_renderManager->DrawTextureRect(0, 0, 0, m_Width, -m_Height, 0, 1, 1, 1, 1, state_texture[CurrentSceneIndex]);
		break;

	case SceneType::scene_play:
	case SceneType::scene_end:
		
		//UI / BG
		for (auto& uiObj : m_uiObjects)
		{
			m_renderManager->DrawTextureObject(uiObj.get());
		}


		//m_renderManager->DrawTextureRect(m_UIAliveCount->m_position.m_x, m_UIAliveCount->m_position.m_y, 2, m_UIAliveCount->m_volume.m_x, -m_UIAliveCount->m_volume.m_y, 0, 1, 1, 1, 1, alive[alive_count]); //On
		//m_renderManager->DrawTextureRect(0, 0, 0, 800, 600, 0, 1, 1, 1, 1, textures[0]);

		//block / Invisible Wall
		for (auto& staticObj : m_staticObjects)
		{
			if(staticObj->GetAcitve())
				m_renderManager->DrawTextureObject(staticObj.get());
		}

		////Draw blocks
		//for (auto& block : m_block)
		//	m_renderManager->DrawTextureRect(block->m_position.m_x * 100, block->m_position.m_y * 100, 0, block->m_volume.m_x * 100, block->m_volume.m_y * 100, 0, 1, 1, 1,1, textures[2]);

		//Draw Items
		for (auto& p_item : m_item)
		{
			auto& item = p_item.second;
			if (item.GetAcitve() == false) continue;
			Vector2d Pos = item.GetPosition();
			m_renderManager->DrawTextureRect(Pos.m_x * 100, Pos.m_y * 100, 0, 20, 20, 0, 1, 1, 1, 1, item_texture[item.type]);
		}

		//중립 총알 그리기
		for (auto& bullet : m_bullets) {
			if (bullet->GetAcitve() == false) continue;
			m_renderManager->DrawTextureObject(bullet.get());
			//m_renderManager->DrawTextureRect(bullet->m_position.m_x * 100, bullet->m_position.m_y * 100, 0, 5, 5, 0, 1, 1, 1, 1, bullettextures[0]);
		}

		for (auto& pair : m_players) {
			auto& player = pair.second;
			if (player.GetAcitve() == false) continue;

			Vector2d playerPos = player.GetPosition();
			Vector2d playerVol= player.GetVolume();
			Color playerColor = player.GetColor();
			//Draw Bullets
			for (auto& bullet : player.bullets)
			{
				if (bullet.GetAcitve() == false) continue;
				Vector2d Pos = bullet.GetPosition();
				/*m_renderManager->DrawTextureObject(&bullet);*/
				m_renderManager->DrawTextureRect(Pos.m_x * 100, Pos.m_y * 100, 0, 5, 5, 0, 1, 1, 1, 1, bullettextures[bullet.type]);
			}

			//Draw Chat
			if (player.m_chat > -1 && player.emotion_time > 0.0f) {
				m_renderManager->DrawTextureRect(playerPos.m_x * 100, (playerPos.m_y + 0.6) * 100, 0,
					60, 60, 0, 0, 0, 0, 1, message_texture[player.m_chat - 1]);
			}
			//Draw HP
			float hp = player.m_hp / 100.0f;
			m_renderManager->DrawTextureRect(playerPos.m_x * 100, (playerPos.m_y + 0.19) * 100, 0, (playerVol.m_x * 100) * hp, 5, 0, playerColor.r, playerColor.g, playerColor.b, playerColor.a, hpbar);

			//Draw Character
			m_renderManager->DrawTextureRect(playerPos.m_x * 100, playerPos.m_y * 100, 0, playerVol.m_x * 100, -playerVol.m_y * 100, 0, playerColor.r, playerColor.g, playerColor.b, playerColor.a, playerTexture);
		}

		//Draw End Title
		if (CurrentSceneIndex == SceneType::scene_end) {
			if (MYID != winner)
				m_renderManager->DrawTextureRect(0, 0, 0, m_Width, -m_Height, 0, 1, 1, 1, 1, winlose[1]);
			else if (MYID == winner)
				m_renderManager->DrawTextureRect(0, 0, 0, m_Width, -m_Height, 0, 1, 1, 1, 1, winlose[0]);
		}
		break;
	}


}

void GameManager::Reset() {
	m_players.clear();
	for (auto& b : m_bullets) {
		b->SetActive(false);
	}
	alive_count = 2;
}

void GameManager::OnKeyDownInput(unsigned char key, int m_x, int m_y)
{
		int packet = -1;
		if (key == 'w' || key == 'W')
		{
			packet = PacketLibrary::make_packet_input(MYID, input_Wdown);
		}
		else if (key == 'a' || key == 'A')
		{
			packet = PacketLibrary::make_packet_input(MYID, input_Adown);
		}
		else if (key == 's' || key == 'S')
		{
			packet = PacketLibrary::make_packet_input(MYID, input_Sdown);
		}
		else if (key == 'd' || key == 'D')
		{
			packet = PacketLibrary::make_packet_input(MYID, input_Ddown);
		}

		else if (key == '1')
		{
			packet = PacketLibrary::make_packet_chat(MYID, 0x01);
		}
		else if (key == '2')
		{
			packet = PacketLibrary::make_packet_chat(MYID, 0x02);
		}
		else if (key == '3')
		{
			packet = PacketLibrary::make_packet_chat(MYID, 0x03);
		}
		else if (key == '4')
		{
			packet = PacketLibrary::make_packet_chat(MYID, 0x04);
		}
		else if (key == '5')
		{
			packet = PacketLibrary::make_packet_chat(MYID, 0x05);
		}
		else if (key == '6')
		{
			packet = PacketLibrary::make_packet_chat(MYID, 0x06);
		}

		if (packet != -1)
			send(soc, (const char*)&packet, sizeof(int), 0);
}
void GameManager::OnKeyUpInput(unsigned char key, int m_x, int m_y)
{
	if (CurrentSceneIndex == SceneType::scene_play) {
		int packet = 0;
		if (key == 'w' || key == 'W')
		{
			packet = PacketLibrary::make_packet_input(MYID, input_Wup);
		}
		else if (key == 'a' || key == 'A')
		{
			packet = PacketLibrary::make_packet_input(MYID, input_Aup);
		}
		else if (key == 's' || key == 'S')
		{
			packet = PacketLibrary::make_packet_input(MYID, input_Sup);
		}
		else if (key == 'd' || key == 'D')
		{
			packet = PacketLibrary::make_packet_input(MYID, input_Dup);
		}
		if (packet != -1)
			send(soc, (const char*)&packet, sizeof(int), 0);
	}
}
void GameManager::OnMouseInput(int button, int state, int m_x, int m_y)
{
	if (CurrentSceneIndex == SceneType::scene_play || CurrentSceneIndex == SceneType::scene_title) {
		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) {
				m_mouseLeft = true;
				m_mousepos.m_x = m_x; m_mousepos.m_y = m_y;
			}
			else if (state == GLUT_UP) m_mouseLeft = false;
		}
	}
}
void GameManager::OnMouseMove(int m_x, int m_y)
{
	if (m_mouseLeft == true) {
		m_mousepos.m_x = m_x;
		m_mousepos.m_y = m_y;
	}
}

void GameManager::DoGarbageCollection()
{
	//delete bullets
	for (auto& p_pair : m_players)
	{
		auto& player = p_pair.second;
		if (player.GetAcitve() == false) continue;

		for (auto& b : player.bullets)
		{
			if (b.GetAcitve() == false) continue;
			if (b.GetVelocity().length() < FLT_EPSILON)
				b.SetActive(false);
		}
	}
}
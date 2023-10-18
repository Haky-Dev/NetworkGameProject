#pragma once
#include "RenderManager.h"
#include "Config.h"
#include "Vector2d.h"
#include <vector>
#include <array>
#include <random>
#include <map>

#define COMMON_BULLET_NUM 128
#define WALL_NUM 4
#define BLOCK_NUM 8
enum class SceneType {
	scene_title = 0,
	scene_connect,
	scene_connect_error,
	scene_wait,
	scene_play,
	scene_end,
	scene_max
};
class Object;
class GameManager
{
public:

	int m_Width = WINDOW_WIDTH;
	int m_Height = WINDOW_HEIGHT;
	
public: //Network Socket
	GameManager();
	void CreateScene();
	void InitializeTexture();
	~GameManager();
	
	void Update(float fTimeElapsed);
	void RenderScene();
	void Reset();

	void DoGarbageCollection();

	// Input
	void OnKeyDownInput(unsigned char key, int m_x, int m_y);
	void OnKeyUpInput(unsigned char key, int m_x, int m_y);
	void OnMouseInput(int button, int state, int m_x, int m_y);
	void OnMouseMove(int m_x, int m_y);

	int soc;
	UserID MYID;
	bool isEnd = false;
	int winner = -1;
	SceneType CurrentSceneIndex;

	unique_ptr<RenderManager> m_renderManager;

	shared_ptr<class Object> m_stateObj;

	vector<shared_ptr<class Object>> m_staticObjects;
	Object* m_wall[4];
	Object* m_block[8];

	//UI
	vector<shared_ptr<class Object>> m_uiObjects;
	Object* m_UIbutton[4];
	Object* m_UIAliveCount;
	int alive_count = 2; //0 - 1 alive / 1 - 2 alive / 2 - 3 alive/ 3 - 생존자 수가 3명 이상일때

	map<int, class Item> m_item;
	map<int, class Player> m_players;

	array<shared_ptr<class Object>, COMMON_BULLET_NUM> m_bullets;

	//Textures
	int textures[4];
	int bullettextures[3];
	int winlose[2];
	int hpbar;
	int playerTexture;
	int state_texture[4];
	int item_texture[3];
	int alive[4];
	int message_texture[6];

	//Button
	int button[4][2];
	//0 - Start Button / 1 - Exit Button
	//1 - On / 0 - Off

	//Key Inputs
	bool m_keyW = false;
	bool m_keyA = false;
	bool m_keyS = false;
	bool m_keyD = false;

	//Mouse Input
	bool m_mouseLeft = false;

	Vector2d m_mousepos;
};
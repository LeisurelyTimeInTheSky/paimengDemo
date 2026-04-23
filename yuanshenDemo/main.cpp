#include <Windows.h>
#include <graphics.h>

#include <iostream>
#include <string>


// 简单尝试
#if 0


int idx_current_anim = 0;// 当前动画帧索引
const int PLAYER_ANIM_NUM = 6; // 动画帧总数
int PLAYER_SPEED = 5;

// 玩家贴图动画
IMAGE img_player_left[PLAYER_ANIM_NUM];
IMAGE img_player_right[PLAYER_ANIM_NUM];

// 玩家位置
POINT player_pos = { 500, 500 };


#pragma comment(lib, "MSIMG32.LIB")
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void LoadAnimation()
{
	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_left[i], path.c_str());
	}
	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"img/player_right_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_right[i], path.c_str());
	}
}

int main()
{
	initgraph(1280, 720);

	bool isRunning = true;

	ExMessage msg;

	IMAGE img_background;
	loadimage(&img_background, _T("img/background.png"));
	LoadAnimation();

	// 玩家移动标志
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;

	// 玩家朝向标志
	bool is_left = true;
	bool is_right = false;

	BeginBatchDraw();
	while (isRunning)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
				isRunning = false;

			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case 'W':
				case VK_UP:
					is_move_up = true;
					break;
				case 'S':
				case VK_DOWN:
					is_move_down = true;
					break;
				case 'A':
				case VK_LEFT:
					is_move_left = true;
					is_left = true;
					is_right = false;
					break;
				case 'D':
				case VK_RIGHT:
					is_move_right = true;
					is_left = false;
					is_right = true;
					break;
				}
			}
			else if (msg.message == WM_KEYUP)
			{
				switch (msg.vkcode)
				{
				case 'W':
				case VK_UP:
					is_move_up = false;
					break;
				case 'S':
				case VK_DOWN:
					is_move_down = false;
					break;
				case 'A':
				case VK_LEFT:
					is_move_left = false;
					break;
				case 'D':
				case VK_RIGHT:
					is_move_right = false;
					break;
				}
			}
		}

		// 原有移动处理逻辑：斜角移动速度快
		if (is_move_up) player_pos.y -= PLAYER_SPEED;
		if (is_move_down) player_pos.y += PLAYER_SPEED;
		if (is_move_left) player_pos.x -= PLAYER_SPEED;
		if(is_move_right) player_pos.x += PLAYER_SPEED;

		static int counter = 0; // 记录当前动画帧一共播放了一个游戏帧
		if (++counter % 5 == 0)
			idx_current_anim++;

		// 动画循环播放
		idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;

		cleardevice();

		// 渲染
		putimage(0, 0, &img_background); // 渲染背景
		// 渲染角色
		if (is_left)
			putimage_alpha(player_pos.x, player_pos.y, &img_player_left[idx_current_anim]);
		if (is_right)
			putimage_alpha(player_pos.x, player_pos.y, &img_player_right[idx_current_anim]);

		FlushBatchDraw();	// 刷新缓冲区

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();

	closegraph();

	return 0;
}


#endif

// 封装动画类
#if 0

#include "Animation.h"

int WINDOW_WIDTH = 1280;	// 屏幕宽度
int WINDOW_HEIGHT = 720;	// 屏幕高度

const int PLAYER_WIDTH = 80;	// 玩家宽度
const int PLAYER_HEIGHT = 80;	// 玩家高度
const int SHADOW_WIDTH = 32;	// 阴影宽度

int pos_x = static_cast<int>(WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2);
int pos_y = static_cast<int>(WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2);

POINT player_pos = { pos_x, pos_y }; // 玩家位置
int PLAYER_SPEED = 5; // 玩家速度

Animation anim_left_player(_T("img/player_left_%d.png"), 6, 45);
Animation anim_right_player(_T("img/player_right_%d.png"), 6, 45);

IMAGE img_background;
IMAGE img_shadow;

void DrawPlayer(int delta, int dir_x)
{
	int pos_shadow_x = player_pos.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = player_pos.y + PLAYER_HEIGHT - 8;
	putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

	static bool facing_left = false;
	if (dir_x < 0)
		facing_left = true;
	else if (dir_x > 0)
		facing_left = false;

	if (facing_left)
		anim_left_player.Play(player_pos.x, player_pos.y, delta);
	else
		anim_right_player.Play(player_pos.x, player_pos.y, delta);
}

int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	bool isRunning = true;

	ExMessage msg;

	// 玩家移动标志
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;

	loadimage(&img_background, _T("img/background.png"));
	loadimage(&img_shadow, _T("img/shadow_player.png"));

	BeginBatchDraw();
	while (isRunning)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
				isRunning = false;

			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case 'W':
				case VK_UP:
					is_move_up = true;
					break;
				case 'S':
				case VK_DOWN:
					is_move_down = true;
					break;
				case 'A':
				case VK_LEFT:
					is_move_left = true;
					break;
				case 'D':
				case VK_RIGHT:
					is_move_right = true;
					break;
				}
			}
			else if (msg.message == WM_KEYUP)
			{
				switch (msg.vkcode)
				{
				case 'W':
				case VK_UP:
					is_move_up = false;
					break;
				case 'S':
				case VK_DOWN:
					is_move_down = false;
					break;
				case 'A':
				case VK_LEFT:
					is_move_left = false;
					break;
				case 'D':
				case VK_RIGHT:
					is_move_right = false;
					break;
				}
			}
		}

		int dir_x = is_move_right - is_move_left;
		int dir_y = is_move_down - is_move_up;
		double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
		if (len_dir != 0)
		{
			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			player_pos.x += static_cast<int>(PLAYER_SPEED * normalized_x);
			player_pos.y += static_cast<int>(PLAYER_SPEED * normalized_y);
		}

		if (player_pos.x < 0) player_pos.x = 0;
		if (player_pos.y < 0) player_pos.y = 0;
		if (player_pos.x + PLAYER_WIDTH > WINDOW_WIDTH) player_pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
		if (player_pos.y + PLAYER_HEIGHT > WINDOW_HEIGHT) player_pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;

		cleardevice();

		// 渲染
		putimage(0, 0, &img_background);	// 渲染背景
		DrawPlayer(1000 / 60, is_move_right - is_move_left);

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();

	closegraph();

	return 0;
}

#endif


#if 1

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Atlas.h"
#include "StartGameButton.h"
#include "QuitGameButton.h"

int WINDOW_WIDTH = 1280;	// 屏幕宽度
int WINDOW_HEIGHT = 720;	// 屏幕高度

Atlas* atlas_player_left = nullptr;
Atlas* atlas_player_right = nullptr;
Atlas* atlas_enemy_left = nullptr;
Atlas* atlas_enemy_right = nullptr;

bool is_game_started = false;
bool isRunning = true;

// 生成新的敌人
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

// 更新子弹位置
void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player)
{
	const double RADIAL_SPEED = 0.0045;							// 径向波动速度
	const double TANGENT_SPEED = 0.0025;						// 切向波动速度
	double radian_interval = 2 * 3.14159 / bullet_list.size();	// 子弹之间的弧度
	POINT player_position = player.GetPosition();
	double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;
		bullet_list[i].position.x = player_position.x + player.PLAYER_WIDTH / 2 + (int)(radius * cos(radian));
		bullet_list[i].position.y = player_position.y + player.PLAYER_HEIGHT / 2 + (int)(radius * sin(radian));
	}
}

// 绘制玩家得分
void DrawPlayerScore(int score)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家得分：%d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}

int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	atlas_player_left = new Atlas(_T("img/player_left_%d.png"), 6);
	atlas_player_right = new Atlas(_T("img/player_right_%d.png"), 6);
	atlas_enemy_left = new Atlas(_T("img/enemy_left_%d.png"), 6);
	atlas_enemy_right = new Atlas(_T("img/enemy_right_%d.png"), 6);

	mciSendString(_T("open mus/bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL);

	ExMessage msg;

	IMAGE img_background;
	IMAGE img_menu;

	Player player;
	std::vector<Enemy*> enemy_list;
	std::vector<Bullet> bullet_list(3);
	int score = 0;	// 玩家得分


	RECT region_btn_start_game, region_btn_quit_game;

	region_btn_start_game.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_start_game.right = region_btn_start_game.left + BUTTON_WIDTH;
	region_btn_start_game.top = 430;
	region_btn_start_game.bottom = region_btn_start_game.top + BUTTON_HEIGHT;

	region_btn_quit_game.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_quit_game.right = region_btn_quit_game.left + BUTTON_WIDTH;
	region_btn_quit_game.top = 550;
	region_btn_quit_game.bottom = region_btn_quit_game.top + BUTTON_HEIGHT;

	StartGameButton btn_start_game = StartGameButton(region_btn_start_game,
		_T("img/ui_start_idle.png"), _T("img/ui_start_hovered.png"), _T("img/ui_start_pushed.png"));
	QuitGameButton btn_quit_game = QuitGameButton(region_btn_quit_game,
		_T("img/ui_quit_idle.png"), _T("img/ui_quit_hovered.png"), _T("img/ui_quit_pushed.png"));

	loadimage(&img_menu, _T("img/menu.png"));
	loadimage(&img_background, _T("img/background.png"));


	BeginBatchDraw();
	while (isRunning)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
				isRunning = false;

			if(is_game_started)
				player.ProcessEvent(msg);
			else {
				btn_start_game.ProcessEvent(msg);
				btn_quit_game.ProcessEvent(msg);
			}
		}

		// 数据处理
		if (is_game_started)
		{
			// 尝试生成新的敌人
			TryGenerateEnemy(enemy_list);

			// 移动玩家
			player.Move();
			// 更新子弹位置
			UpdateBullets(bullet_list, player);
			// 更新敌人位置
			for (Enemy* enemy : enemy_list)
				enemy->Move(player);

			// 检测敌人和玩家的碰撞
			for (Enemy* enemy : enemy_list)
			{
				if (enemy->CheckPlayerCollision(player))
				{
					static TCHAR text[128];
					_stprintf_s(text, _T("最终得分：%d !"), score);
					MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
					isRunning = false;
					break;
				}
			}

			// 检测子弹和敌人的碰撞
			for (Enemy* enemy : enemy_list)
			{
				for (const Bullet& bullet : bullet_list)
				{
					if (enemy->CheckBulletCollision(bullet))
					{
						mciSendString(_T("play hit from 0"), NULL, 0, NULL);
						enemy->Hurt();
					}
				}
			}

			// 移除生命值归零的敌人
			for (size_t i = 0; i < enemy_list.size(); i++)
			{
				Enemy* enemy = enemy_list[i];
				if (!enemy->CheckAlive())
				{
					std::swap(enemy_list[i], enemy_list.back());
					enemy_list.pop_back();
					delete enemy;
					score++;
				}
			}
		}

	
		cleardevice();

		// 渲染
		if (is_game_started)
		{
			putimage(0, 0, &img_background);	// 渲染背景	
			player.Draw(1000 / 60);
			for (Enemy* enemy : enemy_list)
				enemy->Draw(1000 / 60);
			for (const Bullet& bullet : bullet_list)
				bullet.Draw();
			DrawPlayerScore(score);	// 绘制玩家得分
		}
		else
		{
			putimage(0, 0, &img_menu);
			btn_start_game.Draw();
			btn_quit_game.Draw();
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	// 移除玩家/敌人动画资源
	delete atlas_player_left;
	delete atlas_player_right;
	delete atlas_enemy_left;
	delete atlas_enemy_right;

	EndBatchDraw();

	closegraph();
	return 0;
}

#endif


#include "Player.h"
#include "Atlas.h"


Player::Player()
{
	loadimage(&img_shadow, _T("img/shadow_player.png"));
	/*anim_left = new Animation(_T("img/player_left_%d.png"), 6, 45);
	anim_right = new Animation(_T("img/player_right_%d.png"), 6, 45);*/
	anim_left = new Animation(atlas_player_left, 45);
	anim_right = new Animation(atlas_player_right, 45);

	int pos_x = static_cast<int>(WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2);
	int pos_y = static_cast<int>(WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2);

	player_pos = { pos_x, pos_y }; // 玩家位置
}

Player::~Player()
{
	delete anim_left;
	delete anim_right;
}

// 处理玩家操作消息
void Player::ProcessEvent(const ExMessage& msg)
{
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

// 处理玩家移动
void Player::Move()
{
	int dir_x = is_move_right - is_move_left;
	int dir_y = is_move_down - is_move_up;
	double len_dir = sqrt((double)dir_x * dir_x + (double)dir_y * dir_y);
	if (len_dir != 0)
	{
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		player_pos.x += static_cast<int>(SPEED * normalized_x);
		player_pos.y += static_cast<int>(SPEED * normalized_y);
	}

	if (player_pos.x < 0) player_pos.x = 0;
	if (player_pos.y < 0) player_pos.y = 0;
	if (player_pos.x + PLAYER_WIDTH > WINDOW_WIDTH) player_pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
	if (player_pos.y + PLAYER_HEIGHT > WINDOW_HEIGHT) player_pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
}

// 绘制玩家
void Player::Draw(int delta)
{
	int pos_shadow_x = player_pos.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = player_pos.y + PLAYER_HEIGHT - 8;
	putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

	//static bool facing_left = false;
	int dir_x = is_move_right - is_move_left;
	if (dir_x < 0)
		facing_left = true;
	else if (dir_x > 0)
		facing_left = false;

	if (facing_left)
		anim_left->Play(player_pos.x, player_pos.y, delta);
	else
		anim_right->Play(player_pos.x, player_pos.y, delta);
}
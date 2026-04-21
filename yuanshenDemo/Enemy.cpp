#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"

Enemy::Enemy()
{
	loadimage(&img_shadow, _T("img/shadow_enemy.png"));
	anim_left = new Animation(_T("img/enemy_left_%d.png"), 6, 45);
	anim_right = new Animation(_T("img/enemy_right_%d.png"), 6, 45);

	// 敌人生成边界
	enum class SpawnEdge
	{
		Up = 0,
		Down,
		Lfet,
		Right
	};

	srand((unsigned int)time(NULL));

	// 将敌人放置在地图边界处的随机位置
	SpawnEdge edge = (SpawnEdge)(rand() % 4);
	switch (edge)
	{
	case SpawnEdge::Up:
		enemy_pos.x = rand() % WINDOW_WIDTH;
		enemy_pos.y = -ENEMY_HEIGHT;
		break;
	case SpawnEdge::Down:
		enemy_pos.x = rand() % WINDOW_WIDTH;
		enemy_pos.y = WINDOW_HEIGHT;
		break;
	case SpawnEdge::Lfet:
		enemy_pos.x = -ENEMY_WIDTH;
		enemy_pos.y = rand() % WINDOW_HEIGHT;
		break;
	case SpawnEdge::Right:
		enemy_pos.x = WINDOW_WIDTH;
		enemy_pos.y = rand() % WINDOW_HEIGHT;
		break;
	default:
		break;
	}
}

Enemy::~Enemy()
{
	delete anim_left;
	delete anim_right;
}

bool Enemy::CheckBulletCollision(const Bullet& bullet)
{
	// 将子弹等效为点，判断点是否在敌人矩形内
	bool is_overlap_x = bullet.position.x >= enemy_pos.x && bullet.position.x <= enemy_pos.x + ENEMY_WIDTH;
	bool is_overlap_y = bullet.position.y >= enemy_pos.y && bullet.position.y <= enemy_pos.y + ENEMY_HEIGHT;
	return is_overlap_x && is_overlap_y;
}

bool Enemy::CheckPlayerCollision(const Player& player)
{
	// 将敌人中心位置等效为点，判断点是否在玩家矩形内
	POINT check_position = { enemy_pos.x + ENEMY_WIDTH / 2,enemy_pos.y + ENEMY_HEIGHT / 2 };

	POINT player_pos = player.GetPosition();

	bool is_overlap_x = check_position.x >= player_pos.x && check_position.x <= player_pos.x + player.PLAYER_WIDTH;
	bool is_overlap_y = check_position.y >= player_pos.y && check_position.y <= player_pos.y + player.PLAYER_HEIGHT;
	return is_overlap_x && is_overlap_y;
}

void Enemy::Move(const Player& player)
{
	const POINT& player_position = player.GetPosition();
	int dir_x = player_position.x - enemy_pos.x;
	int dir_y = player_position.y - enemy_pos.y;
	double len_dir = sqrt((double)dir_x * dir_x + (double)dir_y * dir_y);
	if (len_dir != 0)
	{
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		enemy_pos.x += (int)(SPEED * normalized_x);
		enemy_pos.y += (int)(SPEED * normalized_y);
	}

	if (dir_x < 0)
		facing_left = true;
	else
		facing_left = false;
}

void Enemy::Draw(int delta)
{
	int pos_shadow_x = enemy_pos.x + (ENEMY_WIDTH / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = enemy_pos.y + ENEMY_HEIGHT - 35;
	putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

	if (facing_left)
		anim_left->Play(enemy_pos.x, enemy_pos.y, delta);
	else
		anim_right->Play(enemy_pos.x, enemy_pos.y, delta);
}
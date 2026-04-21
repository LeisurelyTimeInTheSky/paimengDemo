#ifndef ENEMY_H
#define ENEMY_H

#include "Animation.h"

class Bullet;
class Player;

class Enemy
{
public:
	Enemy();
	~Enemy();

	bool CheckBulletCollision(const Bullet& bullet);
	bool CheckPlayerCollision(const Player& player);
	void Move(const Player& player);
	void Draw(int delta);

	inline const POINT& GetPosition() const
	{
		return enemy_pos;
	}

	void Hurt()
	{
		HP--;
		if (HP <= 0)
		{
			alive = false;
		}
	}

	bool CheckAlive()
	{
		return alive;
	}

private:
	int SPEED = 2; // 敌人速度
	int ENEMY_WIDTH = 80;	// 敌人宽度
	int ENEMY_HEIGHT = 80;	// 敌人高度
	int SHADOW_WIDTH = 48;	// 阴影宽度
	int HP = 4; // 敌人血量

private:
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	POINT enemy_pos = { 0, 0 };
	bool facing_left = false;
	bool alive = true;
};

#endif // !ENEMY_H





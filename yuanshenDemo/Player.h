#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"

class Player
{
public:
	const int PLAYER_WIDTH = 80;	// 玩家宽度
	const int PLAYER_HEIGHT = 80;	// 玩家高度

public:
	Player();
	~Player();

	// 处理玩家操作消息
	void ProcessEvent(const ExMessage& msg);
	// 处理玩家移动
	void Move();
	// 绘制玩家
	void Draw(int delta);

	inline const POINT& GetPosition() const
	{
		return player_pos;
	}

private:
	int SPEED = 5; // 玩家速度
	const int SHADOW_WIDTH = 32;	// 阴影宽度

private:
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	POINT player_pos = { 600, 320 };

	bool facing_left = false; // 玩家向左标志
	// 玩家移动标志
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
};

#endif // !PLAYER_H




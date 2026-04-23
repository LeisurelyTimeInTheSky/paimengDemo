#ifndef ANIMATION_H
#define ANIMATION_H

#include <graphics.h>
#include <string>
#include <vector>

#include "common.h"

class Atlas;
class Animation
{
public:
	Animation() = default;
	Animation(Atlas* atlas, int interval);
	~Animation() = default;

	void Play(int x, int y, int delta);

private:
	int timer = 0;	// 动画计时器
	int idx_frame = 0;	// 动画帧索引
	int interval_ms = 0;// 帧间隔
	/*std::vector<IMAGE*> frame_list;*/

	Atlas* anim_atlas;
};

#endif // !ANIMATION_H





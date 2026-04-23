#pragma once
#include <graphics.h>

class Button
{
public:
	Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
	~Button() = default;

	void ProcessEvent(const ExMessage& msg);
	void Draw();

protected:
	virtual void OnClick() = 0;

private:
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};

private:
	RECT region;	// 描述位置和大小
	IMAGE img_idle;	
	IMAGE img_hovered;
	IMAGE img_pushed;
	Status status = Status::Idle;	// 按钮状态

private:
	bool CheckCursorHit(int x, int y);
};


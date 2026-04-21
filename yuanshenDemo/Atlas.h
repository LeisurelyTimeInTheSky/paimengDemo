#pragma once
#include <graphics.h>
#include <string>
#include <vector>

class Atlas
{
public:
	Atlas(LPCTSTR path, int num);
	~Atlas();

public:
	std::vector<IMAGE*> frame_list;
};


#pragma once

class Checkerboard {
	int displayListId;
	int width;
	int depth;
public:
	Checkerboard(int width, int depth);
	double centerx() { return 0; }
	double centerz() { return 0; }
	void create();
	void draw();
};

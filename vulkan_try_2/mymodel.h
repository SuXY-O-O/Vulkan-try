#pragma once
#include "myvertex.h"
#include <vector>

class MyModel
{
public:
	std::vector<Vertex> vertexs;
	unsigned int face_offset;
	unsigned int face_count;
	unsigned int line_count;
	unsigned int line_offset;
	MyModel();
	unsigned int get_size();
	virtual void update_frame() = 0;
	int width;
	int height;
};

class MyTriangle : public MyModel
{
public:
	MyTriangle(int w, int h);
	void update_frame();
};

class MyStar : public MyModel
{
public:
	MyStar(int w, int h);
	void update_frame();
private:
	Vertex count_cross(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
};
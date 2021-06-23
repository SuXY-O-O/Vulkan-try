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
	float x_off;
	float y_off;
	float z_off;
	MyModel();
	unsigned int get_size();
	virtual void update_frame() = 0;
	void move_xyz(float x, float y, float z);
	void rotate(float x, float y, float z);
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

class MyBox : public MyModel
{
public:
	MyBox(int w, int h, int use_texture);
	void update_frame();
private:
	int side_length = 100;
};

class MyPlain : public MyModel
{
public:
	MyPlain(int w, int h);
	void update_frame();
};

class MyBall : public MyModel
{
public:
	MyBall(int w, int h, int times);
	void update_frame();
private:
	void divide_tri(glm::vec3 a, glm::vec3 b, glm::vec3 c, int depth);
};
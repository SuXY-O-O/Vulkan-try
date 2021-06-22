#include "mymodel.h"
#include "mytool.h"
#include <math.h>
#define PI 3.1415926

MyModel::MyModel()
{
	vertexs.clear();
	face_offset = 0;
	face_count = 0;
	line_count = 0;
	line_offset = 0;
	width = 0;
	height = 0;
}

unsigned int MyModel::get_size()
{
	return vertexs.size();
}

MyTriangle::MyTriangle(int w, int h)
{
	Vertex a;
	a.pos = { 0.0f, -0.5f, 0.0f };
	a.color = { 1.0f, 1.0f, 0.0f };
	vertexs.push_back(a);
	Vertex b;
	b.pos = { 0.5f, 0.5f, 0.0f };
	b.color = { 1.0f, 1.0f, 0.0f };
	vertexs.push_back(b);
	Vertex c;
	c.pos = { -0.5f, 0.5f, 0.0f };
	c.color = { 1.0f, 1.0f, 0.0f };
	vertexs.push_back(c);
	face_count = 3;
	face_offset = 0;

	a.color = { 0.0f, 0.0f, 0.0f };
	b.color = { 0.0f, 0.0f, 0.0f };
	c.color = { 0.0f, 0.0f, 0.0f };
	vertexs.push_back(a);
	vertexs.push_back(b);
	vertexs.push_back(c);
	vertexs.push_back(a);
	line_count = 4;
	line_offset = 3;

	width = w;
	height = h;
}

void MyTriangle::update_frame()
{
	vertexs[1].pos.y += 0.001f;
	vertexs[line_offset + 1].pos.y += 0.001f;
}

MyStar::MyStar(int w, int h)
{
	Vertex tmp[5];
	float radis = 400.0f;
	int begin_offset = -18;
	int i;
	for (i = 0; i < 5; i++)
	{
		tmp[i].pos.x = radis * cos(((72 * (double)i + begin_offset) / 360) * (2 * PI)) / w * 2;
		tmp[i].pos.y = radis * sin(((72 * (double)i + begin_offset) / 360) * (2 * PI)) / h * 2;
		tmp[i].pos.z = 0.5f;
		tmp[i].color = { 0.0f, 0.0f, 0.0f };
	}
	vertexs.push_back(tmp[0]);
	vertexs.push_back(tmp[3]);
	vertexs.push_back(tmp[1]);
	vertexs.push_back(tmp[4]);
	vertexs.push_back(tmp[2]);
	vertexs.push_back(tmp[0]);
	line_count = 6;
	line_offset = 0;

	Vertex tmp_cross[5];
	tmp_cross[0] = count_cross(tmp[0], tmp[2], tmp[1], tmp[3]);
	tmp_cross[1] = count_cross(tmp[1], tmp[3], tmp[2], tmp[4]);
	tmp_cross[2] = count_cross(tmp[2], tmp[4], tmp[3], tmp[0]);
	tmp_cross[3] = count_cross(tmp[3], tmp[0], tmp[4], tmp[1]);
	tmp_cross[4] = count_cross(tmp[4], tmp[1], tmp[0], tmp[2]);
	for (i = 0; i < 5; i++)
	{
		tmp_cross[i].color = { 1.0f, 1.0f, 0.0f };
	}
	vertexs.push_back(tmp_cross[0]);
	vertexs.push_back(tmp_cross[1]);
	vertexs.push_back(tmp_cross[2]);
	vertexs.push_back(tmp_cross[0]);
	vertexs.push_back(tmp_cross[2]);
	vertexs.push_back(tmp_cross[3]);
	vertexs.push_back(tmp_cross[0]);
	vertexs.push_back(tmp_cross[3]);
	vertexs.push_back(tmp_cross[4]);
	vertexs.push_back(tmp_cross[0]);
	vertexs.push_back(tmp_cross[2]);
	vertexs.push_back(tmp_cross[1]);
	vertexs.push_back(tmp_cross[0]);
	vertexs.push_back(tmp_cross[3]);
	vertexs.push_back(tmp_cross[2]);
	vertexs.push_back(tmp_cross[0]);
	vertexs.push_back(tmp_cross[4]);
	vertexs.push_back(tmp_cross[3]);
	face_count = 18;
	face_offset = 6;

	width = w;
	height = h;
}

void MyStar::update_frame()
{
	unsigned int i; 
	for (i = 0; i < vertexs.size(); i++)
	{
		MyTool::rotate(vertexs[i].pos, 0.0f, 1.0f, 0.0f);
	}
}

Vertex MyStar::count_cross(Vertex v0, Vertex v1, Vertex v2, Vertex v3)
{
	Vertex ans;
	ans.pos.x = ((v2.pos.x - v3.pos.x) * (v1.pos.x * v0.pos.y - v0.pos.x * v1.pos.y) -
		(v0.pos.x - v1.pos.x) * (v3.pos.x * v2.pos.y - v2.pos.x * v3.pos.y)) / (
			(v2.pos.x - v3.pos.x) * (v0.pos.y - v1.pos.y) - (v0.pos.x - v1.pos.x) * (v2.pos.y - v3.pos.y));
	ans.pos.y = ((v2.pos.y - v3.pos.y) * (v1.pos.y * v0.pos.x - v0.pos.y * v1.pos.x) -
		(v0.pos.y - v1.pos.y) * (v3.pos.y * v2.pos.x - v2.pos.y * v3.pos.x)) / (
			(v2.pos.y - v3.pos.y) * (v0.pos.x - v1.pos.x) - (v0.pos.y - v1.pos.y) * (v2.pos.x - v3.pos.x));
	ans.pos.z = 0.5f;
	return ans;
}

MyBox::MyBox(int w, int h)
{
	width = w;
	height = h;
	Vertex point[8];
	float nw = (float)side_length / 2.0f / width;
	float nh = (float)side_length / 2.0f / height;
	point[0] = { {-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f} };
	point[1] = { {0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f} };
	point[2] = { {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.0f} };
	point[3] = { {-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.0f} };

	point[4] = { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f} };
	point[5] = { {0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f} };
	point[6] = { {0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f} };
	point[7] = { {-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f} };

	unsigned int i;
	//for (i = 0; i < 8; i++)
	//{
	//	point[i].pos.z = (point[i].pos.z + 1.0f) / 2.0f;
	//}

	line_count = 0;
	line_offset = 0;
	face_offset = 0;
	face_count = 36;

	vertexs.push_back(point[0]);
	vertexs.push_back(point[3]);
	vertexs.push_back(point[2]);
	vertexs.push_back(point[2]);
	vertexs.push_back(point[1]);
	vertexs.push_back(point[0]);

	vertexs.push_back(point[4]);
	vertexs.push_back(point[5]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[7]);
	vertexs.push_back(point[4]);

	vertexs.push_back(point[3]);
	vertexs.push_back(point[0]);
	vertexs.push_back(point[4]);
	vertexs.push_back(point[4]);
	vertexs.push_back(point[7]);
	vertexs.push_back(point[3]);

	vertexs.push_back(point[1]);
	vertexs.push_back(point[2]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[5]);
	vertexs.push_back(point[1]);

	vertexs.push_back(point[2]);
	vertexs.push_back(point[3]);
	vertexs.push_back(point[7]);
	vertexs.push_back(point[7]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[2]);

	vertexs.push_back(point[0]);
	vertexs.push_back(point[1]);
	vertexs.push_back(point[5]);
	vertexs.push_back(point[5]);
	vertexs.push_back(point[4]);
	vertexs.push_back(point[0]);
	
	for (i = 0; i < 6; i++)
	{
		vertexs[i * 6 + 0].texCoord = { 0.0f, 0.0f };
		vertexs[i * 6 + 1].texCoord = { 1.0f, 0.0f };
		vertexs[i * 6 + 2].texCoord = { 1.0f, 1.0f };

		vertexs[i * 6 + 3].texCoord = { 1.0f, 1.0f };
		vertexs[i * 6 + 4].texCoord = { 0.0f, 1.0f };
		vertexs[i * 6 + 5].texCoord = { 0.0f, 0.0f };
	}
}

void MyBox::update_frame()
{
	unsigned int i;
	for (i = 0; i < vertexs.size(); i++)
	{
		MyTool::rotate(vertexs[i].pos, 0.0f, 0.0f, 1.0f);
	}
}

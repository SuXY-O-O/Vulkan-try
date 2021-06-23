#include "mymodel.h"
#include "mytool.h"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
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
	x_off = 0;
	y_off = 0;
	z_off = 0;
}

unsigned int MyModel::get_size()
{
	return vertexs.size();
}

void MyModel::move_xyz(float x, float y, float z)
{
	x_off += x;
	y_off += y;
	z_off += z;
	unsigned int i;
	for (i = 0; i < vertexs.size(); i++)
	{
		MyTool::panning(vertexs[i].pos, x, y, z);
	}
}

void MyModel::rotate(float x, float y, float z)
{
	unsigned int i;
	for (i = 0; i < vertexs.size(); i++)
	{
		MyTool::panning(vertexs[i].pos, -x_off, -y_off, -z_off);
		MyTool::rotate(vertexs[i].pos, x, y, z, false);
		MyTool::rotate(vertexs[i].normal, x, y, z, false);
		MyTool::panning(vertexs[i].pos, x_off, y_off, z_off);
	}
}

MyTriangle::MyTriangle(int w, int h)
{
	Vertex a;
	a.pos = { 0.0f, -0.5f, 0.0f };
	a.color = { 1.0f, 1.0f, 0.0f };
	a.normal = { 0.0f, 0.0f, 1.0f };
	a.needTex = 0;
	vertexs.push_back(a);
	Vertex b;
	b.pos = { 0.5f, 0.5f, 0.0f };
	b.color = { 1.0f, 1.0f, 0.0f };
	b.normal = { 0.0f, 0.0f, 1.0f };
	b.needTex = 0;
	vertexs.push_back(b);
	Vertex c;
	c.pos = { -0.5f, 0.5f, 0.0f };
	c.color = { 1.0f, 1.0f, 0.0f };
	c.normal = { 0.0f, 0.0f, 1.0f };
	c.needTex = 0;
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
	float radis = 0.5f;
	int begin_offset = -18;
	int i;
	for (i = 0; i < 5; i++)
	{
		tmp[i].pos.x = radis * cos(((72 * (double)i + begin_offset) / 360) * (2 * PI));
		tmp[i].pos.y = radis * sin(((72 * (double)i + begin_offset) / 360) * (2 * PI));
		tmp[i].pos.z = 0.0f;
		tmp[i].color = { 0.0f, 0.0f, 0.0f };
		tmp[i].needTex = 0;
		tmp[i].normal = { 0.0f, 0.0f, 1.0f };
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
		tmp_cross[i].needTex = 0;
		tmp_cross[i].normal = { 0.0f, 0.0f, -1.0f };
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
	for (i = 0; i < 5; i++)
	{
		tmp_cross[i].normal = { 0.0f, 0.0f, 1.0f };
	}
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

	this->rotate(0, 90, 0);
}

void MyStar::update_frame()
{
	this->rotate(0.0f, 0.0f, 1.0f);
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
	ans.pos.z = 0.0f;
	return ans;
}

MyBox::MyBox(int w, int h, int use_texture)
{
	width = w;
	height = h;
	Vertex point[8];
	float nw = (float)side_length / 2.0f / width;
	float nh = (float)side_length / 2.0f / height;
	point[0] = { {-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f} };
	point[1] = { {0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f} };
	point[2] = { {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.0f} };
	point[3] = { {-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.0f} };

	point[4] = { {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f} };
	point[5] = { {0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f} };
	point[6] = { {0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 1.0f} };
	point[7] = { {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 1.0f} };

	unsigned int i;

	line_count = 0;
	line_offset = 0;
	face_offset = 0;
	face_count = 36;

	for (i = 0; i < 8; i++)
	{
		point[i].needTex = use_texture;
		point[i].normal = { 0.0f, 0.0f, 1.0f };
	}
	vertexs.push_back(point[0]);
	vertexs.push_back(point[3]);
	vertexs.push_back(point[2]);
	vertexs.push_back(point[2]);
	vertexs.push_back(point[1]);
	vertexs.push_back(point[0]);

	for (i = 0; i < 8; i++)
	{
		point[i].needTex = use_texture;
		point[i].normal = { 0.0f, 0.0f, -1.0f };
	}
	vertexs.push_back(point[4]);
	vertexs.push_back(point[5]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[7]);
	vertexs.push_back(point[4]);

	for (i = 0; i < 8; i++)
	{
		point[i].needTex = use_texture;
		point[i].normal = { -1.0f, 0.0f, 0.0f };
	}
	vertexs.push_back(point[3]);
	vertexs.push_back(point[0]);
	vertexs.push_back(point[4]);
	vertexs.push_back(point[4]);
	vertexs.push_back(point[7]);
	vertexs.push_back(point[3]);

	for (i = 0; i < 8; i++)
	{
		point[i].needTex = use_texture;
		point[i].normal = { 1.0f, 0.0f, 0.0f };
	}
	vertexs.push_back(point[1]);
	vertexs.push_back(point[2]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[5]);
	vertexs.push_back(point[1]);

	for (i = 0; i < 8; i++)
	{
		point[i].needTex = use_texture;
		point[i].normal = { 0.0f, 1.0f, 0.0f };
	}
	vertexs.push_back(point[2]);
	vertexs.push_back(point[3]);
	vertexs.push_back(point[7]);
	vertexs.push_back(point[7]);
	vertexs.push_back(point[6]);
	vertexs.push_back(point[2]);

	for (i = 0; i < 8; i++)
	{
		point[i].needTex = use_texture;
		point[i].normal = { 0.0f, -1.0f, 0.0f };
	}
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
	this->rotate(0.0f, 0.0f, 1.0f);
}

MyPlain::MyPlain(int w, int h)
{
	Vertex point[4];
	float c = 3200;
	float z = -1.0f;
	point[0].pos = { -c / w, -c / h, z };
	point[1].pos = { c / w, -c / h, z };
	point[2].pos = { c / w, c / h, z };
	point[3].pos = { -c / w, c / h, z };
	unsigned int i;
	for (i = 0; i < 4; i++)
	{
		point[i].color = { 1.0f, 1.0f, 1.0f };
		point[i].normal = { 0.0f, 0.0f, 1.0f };
		point[i].needTex = 0;
	}
	vertexs.push_back(point[0]);
	vertexs.push_back(point[2]);
	vertexs.push_back(point[1]);
	vertexs.push_back(point[2]);
	vertexs.push_back(point[0]);
	vertexs.push_back(point[3]);
	face_count = 6;
	face_offset = 0;
	line_count = 0;
	line_offset = 0;
}

void MyPlain::update_frame() {}

MyBall::MyBall(int w, int h, int times)
{
	face_count = 0;
	line_count = 0;
	line_offset = 0;
	face_offset = 0;
	glm::vec3 origin[4];
	if (times > 8)
		times = 8;
	origin[0] = { 0.0f, 0.0f, 1.0f };
	origin[1] = { 0.0f, 0.942809f, -0.333333f };
	origin[2] = { -0.816497f, -0.471405f, -0.333333f };
	origin[3] = { 0.816497f, -0.471405f, -0.333333f };
	divide_tri(origin[0], origin[1], origin[2], times);
	divide_tri(origin[0], origin[3], origin[1], times);
	divide_tri(origin[0], origin[2], origin[3], times);
	divide_tri(origin[1], origin[3], origin[2], times);

	unsigned int i;
	for (i = 0; i < vertexs.size(); i++)
	{
		vertexs[i].needTex = 0;
		vertexs[i].color = { 0.0f,1.0f,1.0f };
	}
}

void MyBall::update_frame() 
{
	// this->rotate(0.0f, 0.0f, 1.0f);
}

void MyBall::divide_tri(glm::vec3 a, glm::vec3 b, glm::vec3 c, int depth)
{
	glm::vec3 ab = glm::normalize(a + b);
	glm::vec3 ac = glm::normalize(a + c);
	glm::vec3 bc = glm::normalize(b + c);
	if (depth == 1)
	{
		Vertex tmp[6];
		tmp[0].pos = a;
		tmp[1].pos = b;
		tmp[2].pos = c;
		tmp[3].pos = ab;
		tmp[4].pos = ac;
		tmp[5].pos = bc;

		tmp[0].normal = -a;
		tmp[1].normal = -b;
		tmp[2].normal = -c;
		tmp[3].normal = -ab;
		tmp[4].normal = -ac;
		tmp[5].normal = -bc;

		vertexs.push_back(tmp[0]);
		vertexs.push_back(tmp[3]);
		vertexs.push_back(tmp[4]);

		vertexs.push_back(tmp[4]);
		vertexs.push_back(tmp[3]);
		vertexs.push_back(tmp[5]);

		vertexs.push_back(tmp[3]);
		vertexs.push_back(tmp[1]);
		vertexs.push_back(tmp[5]);

		vertexs.push_back(tmp[4]);
		vertexs.push_back(tmp[5]);
		vertexs.push_back(tmp[2]);

		face_count += 12;

		return;
	}
	else
	{
		divide_tri(a, ab, ac, depth - 1);
		divide_tri(ab, bc, ac, depth - 1);
		divide_tri(ab, b, bc, depth - 1);
		divide_tri(ac, bc, c, depth - 1);
	}
}

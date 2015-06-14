/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a bowl of fruit out of spheres and a bowl.
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "bowl.h"
#include "sphere.h"

class BowlOfFruit : public Object
{
public:
	BowlOfFruit();
	~BowlOfFruit();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;
	Shader solid_color;
	Bowl * bowl;
	Sphere * fruit1;
	Sphere * fruit2;
	Sphere * fruit3;
	Sphere * fruit4;

private:
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};
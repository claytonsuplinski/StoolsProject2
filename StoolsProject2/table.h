/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a table object out of cylinders and squares.
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "cylinder.h"
#include "square.h"

class Table : public Object
{
public:
	Table();
	~Table();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;
	Shader solid_color;
	Cylinder * leg;
	Cylinder * leg2;
	Cylinder * leg3;
	Cylinder * leg4;
	Square * table;
private:
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};
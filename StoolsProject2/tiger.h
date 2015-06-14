/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a tiger object out of cylinders, discs, and spheres.
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "cylinder.h"
#include "disc.h"
#include "sphere.h"

class Tiger : public Object
{
public:
	Tiger();
	~Tiger();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float rotY);
	void TakeDown();
	void StepShader();
	Shader shader;
	Shader solid_color;
	Cylinder * cO;
	Cylinder * cB;
	Cylinder * leg;
	Cylinder * tail;
	Cylinder * whisker;
	Disc * ear;
	Sphere * body;
	Sphere * eye;
	Sphere * nose;
	Sphere * head;
private:
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};
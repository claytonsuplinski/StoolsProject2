/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a door object with a square and a sphere
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "square.h"
#include "sphere.h"

class Door : public Object
{
public:
	Door();
	~Door();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;
	Shader solid_color;
	Square * door;
	Sphere * knob;
private:
	void BuildNormalVisualizationGeometry();
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};
/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates an ocean object (same as square, except for heights being 
determined by sinusoidal design)
*/

#pragma once
#include "object.h"
#include "shader.h"

class Ocean : public Object
{
public:
	Ocean();
	virtual bool Initialize(int x, float s);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	Shader shader;
	Shader solid_color;

	int shader_index;
	Shader flat_shader;
	Shader gouraud_shader;
	Shader phong_shader;
	std::vector<Shader *> shaders;
	inline void StepShader() {this->shader_index = ++this->shader_index % this->shaders.size();};
private:
	void BuildNormalVisualizationGeometry();
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};
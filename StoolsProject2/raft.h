/*
	Name: Clayton Suplinski
*/

#pragma once
#include "object.h"
#include "shader.h"

class Raft : public Object
{
public:
	Raft();
	virtual bool Initialize(int slices, float R, float r);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	Shader shader;
	Shader solid_color;
private:
	void BuildNormalVisualizationGeometry();
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};
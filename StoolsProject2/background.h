/*
	Name: Clayton Suplinski
*/

/*	Perry Kivolowitz - University of Wisconsin - Madison 
	Computer Sciences Department
*/

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "object.h"
#include "shader.h"

class Background : public Object
{
public:
	Background();
	virtual bool Initialize();
	virtual void Draw(const glm::ivec2 & size);
	virtual void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	BackgroundShader shader;

private:
	glm::vec4 colors[4];
	std::vector<VertexAttributesP> vertices;
	typedef Object super;
};

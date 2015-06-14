/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a stool object out of cylinders, discs, a torus, and stool legs.
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "cylinder.h"
#include "disc.h"
#include "torus.h"
#include "stoolLeg.h"

class Stool : public Object
{
public:
	Stool();
	~Stool();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;
	Shader solid_color;
	float adjustableSeat;
	Cylinder * seat;
	Disc * topSeat;
	Disc * botSeat;

	Cylinder * upSup;
	Disc * topUpSup;
	Disc * botUpSup;

	Cylinder * midSup;
	Disc * topMidSup;
	Disc * botMidSup;

	Cylinder * center;
	Disc * topCenter;
	Disc * botCenter;

	Torus * base;

	StoolLeg * leg;

private:
	

	void BuildNormalVisualizationGeometry();
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};
/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Create a table object out of cylinders and squares.
*/

#include <iostream>
#include "table.h"

using namespace std;
using namespace glm;

//Creates a table object
Table::Table() : Object()
{
}

Table::~Table()
{
	this->TakeDown();
}

//Initializes all the components of the table
bool Table::Initialize()
{
	if (this->GLReturnedError("Table::Initialize - on entry"))
		return false;

	this->leg = new Cylinder();
	this->table = new Square();
	
	this->leg->color = vec3(0.65f, 0.45f, 0.1f);
	this->leg->Initialize(1,3.0f,0.2f,0.2f);	
	this->table->color1 = vec3(0.45f, 0.25f, 0.0f);
	this->table->color2 = vec3(0.45f, 0.25f, 0.0f);
	this->table->Initialize(1, 12);

	if (this->GLReturnedError("Table::Initialize - on exit"))
		return false;

	return true;
}

void Table::StepShader(){
	this->leg->StepShader();
	this->table->StepShader();
}

void Table::TakeDown()
{
	this->leg = NULL;
	this->table = NULL;
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Position the elements of the table
void Table::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Table::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 another;

	another = translate(modelview, vec3(5.5,0,5.5));
	glLoadMatrixf(glm::value_ptr(another));
	this->leg->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(5.5,0,-5.5));
	glLoadMatrixf(glm::value_ptr(another));
	this->leg->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(-5.5,0,5.5));
	glLoadMatrixf(glm::value_ptr(another));
	this->leg->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(-5.5,0,-5.5));
	glLoadMatrixf(glm::value_ptr(another));
	this->leg->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(5,3,6));
	glLoadMatrixf(glm::value_ptr(another));
	this->table->Draw(projection, another, size, 0);

	if (this->GLReturnedError("Table::Draw - on exit"))
		return;
}

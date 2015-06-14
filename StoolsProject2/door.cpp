/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a door object with a square and a sphere
*/

#include <iostream>
#include "door.h"

using namespace std;
using namespace glm;

//Create the door object
Door::Door() : Object()
{
}

Door::~Door(){
	this->TakeDown();
}

//Initialize all the elements of the door object
bool Door::Initialize()
{
	if (this->GLReturnedError("Door::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	this->door = new Square();
	this->knob = new Sphere();

	this->door->color1 = vec3(0.35f, 0.2f, 0.1f);
	this->door->color2 = vec3(0.35f, 0.2f, 0.1f);
	this->door->Initialize(1,10.0f);
	
	this->knob->color = vec3(0.35f, 0.3f, 0.0f);
	this->knob->Initialize(8,0.75f);
	
	if (this->GLReturnedError("Door::Initialize - on exit"))
		return false;

	return true;
}

void Door::StepShader(){
	this->door->StepShader();
	this->knob->StepShader();
}

//Delete the door object
void Door::TakeDown()
{
	this->door = NULL;
	this->knob = NULL;
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw and position the elements of the door
void Door::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Door::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 another, scaler;

	scaler = scale(modelview, vec3(0.5f, 0.0f, 1.0f));
	this->door->Draw(projection, scaler, size, 0);

	another = translate(modelview, vec3(-0.5,0.7,-5));
	glLoadMatrixf(glm::value_ptr(another));
	this->knob->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(-0.5,-0.7,-5));
	glLoadMatrixf(glm::value_ptr(another));
	this->knob->Draw(projection, another, size, 0);

	if (this->GLReturnedError("Door::Draw - on exit"))
		return;
}

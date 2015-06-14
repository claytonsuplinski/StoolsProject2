/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a bowl of fruit out of spheres and a bowl
*/

#include <iostream>
#include "bowlOfFruit.h"

using namespace std;
using namespace glm;

//Make the bowl of fruit object
BowlOfFruit::BowlOfFruit() : Object()
{
}

BowlOfFruit::~BowlOfFruit(){
	this->TakeDown();
}

//Initialize all the elements of the bowl of fruit
bool BowlOfFruit::Initialize()
{
	if (this->GLReturnedError("BowlOfFruit::Initialize - on entry"))
		return false;

	this->bowl = new Bowl();
	this->fruit1 = new Sphere();
	this->fruit2 = new Sphere();
	this->fruit3 = new Sphere();
	this->fruit4 = new Sphere();

	this->bowl->color = vec3(0.55f, 0.55f, 0.55f);
	this->bowl->Initialize(8,1.5f);	
	this->fruit1->color = vec3(0.55f, 0.0f, 0.0f);
	this->fruit1->Initialize(4,0.75f);	
	this->fruit2->color = vec3(0.45f, 0.45f, 0.0f);
	this->fruit2->Initialize(4,0.75f);	
	this->fruit3->color = vec3(0.05f, 0.45f, 0.1f);
	this->fruit3->Initialize(4,0.75f);	
	this->fruit4->color = vec3(0.75f, 0.0f, 0.55f);
	this->fruit4->Initialize(4,0.55f);	

	if (this->GLReturnedError("BowlOfFruit::Initialize - on exit"))
		return false;

	return true;
}

void BowlOfFruit::StepShader(){
	this->bowl->StepShader();
	this->fruit1->StepShader();
	this->fruit2->StepShader();
	this->fruit3->StepShader();
	this->fruit4->StepShader();
}

//Delete all the elements of the bowl of fruit
void BowlOfFruit::TakeDown()
{
	this->bowl = NULL;
	this->fruit1 = NULL;
	this->fruit2 = NULL;
	this->fruit3 = NULL;
	this->fruit4 = NULL;
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw and position the bowl of fruit elements
void BowlOfFruit::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("BowlOfFruit::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 another, scaler;
	
	this->bowl->Draw(projection, modelview, size, 180);	
	
	another = translate(modelview, vec3(0.6,0.4,0.6));
	glLoadMatrixf(glm::value_ptr(another));
	scaler = scale(another, vec3(0.85, 1.1, 0.85));
	this->fruit1->Draw(projection, scaler, size, 0);

	another = translate(another, vec3(-1.2,0.15,0));
	glLoadMatrixf(glm::value_ptr(another));
	scaler = scale(another, vec3(0.55, 1.8, 0.55));
	this->fruit2->Draw(projection, scaler, size, 0);

	another = translate(another, vec3(0,-0.25,-1.2));
	glLoadMatrixf(glm::value_ptr(another));
	scaler = scale(another, vec3(0.8, 1.1, 0.8));
	this->fruit3->Draw(projection, scaler, size, 0);

	another = translate(another, vec3(1.2,0,0));
	glLoadMatrixf(glm::value_ptr(another));
	this->fruit4->Draw(projection, another, size, 0);

	if (this->GLReturnedError("BowlOfFruit::Draw - on exit"))
		return;
}

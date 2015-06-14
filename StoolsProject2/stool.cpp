/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a stool object out of cylinders, discs, a torus, and stool legs.
*/

#include <iostream>
#include "stool.h"

using namespace std;
using namespace glm;

//Create a stool object
Stool::Stool() : Object()
{
	vec4 lighter_color(MakeColor(255, 69, 0, 1.0f));
	vec4 darker_color = vec4(vec3(lighter_color) * 2.0f / 3.0f, 1.0f);
	this->colors[0] = darker_color;
	this->colors[1] = lighter_color;
}

Stool::~Stool()
{
	this->TakeDown();
}

//Initialize all the stool elements.
bool Stool::Initialize()
{
	if (this->GLReturnedError("Stool::Initialize - on entry"))
		return false;

	this->seat = new Cylinder();
	this->topSeat = new Disc();
	this->botSeat = new Disc();

	this->upSup = new Cylinder();
	this->topUpSup = new Disc();
	this->botUpSup = new Disc();

	this->midSup = new Cylinder();
	this->topMidSup = new Disc();
	this->botMidSup = new Disc();

	this->center = new Cylinder();
	this->topCenter = new Disc();
	this->botCenter = new Disc();

	this->base = new Torus();

	this->leg = new StoolLeg();

	this->seat->color = vec3(0.25f, 0.15f, 0.0f);
	this->botSeat->color = vec3(0.25f, 0.15f, 0.0f);
	this->topSeat->color = vec3(0.25f, 0.15f, 0.0f);
	this->seat->Initialize(8,0.083f,0.92f,0.85f);
	this->topSeat->Initialize(6, 0.92f);
	this->botSeat->Initialize(6, 0.85f);

	this->upSup->color = vec3(0.25f, 0.15f, 0.0f);
	this->botUpSup->color = vec3(0.25f, 0.15f, 0.0f);
	this->topUpSup->color = vec3(0.25f, 0.15f, 0.0f);
	this->upSup->Initialize(8,0.133f,0.375f,0.375f);
	this->topUpSup->Initialize(6, 0.375f);
	this->botUpSup->Initialize(6, 0.375f);	

	this->midSup->color = vec3(0.25f, 0.15f, 0.0f);
	this->botMidSup->color = vec3(0.25f, 0.15f, 0.0f);
	this->topMidSup->color = vec3(0.25f, 0.15f, 0.0f);
	this->midSup->Initialize(8,0.15f,0.503f,0.503f);
	this->topMidSup->Initialize(6, 0.503f);
	this->botMidSup->Initialize(6, 0.503f);	

	this->center->color = vec3(0.25f, 0.15f, 0.0f);
	this->botCenter->color = vec3(0.25f, 0.15f, 0.0f);
	this->topCenter->color = vec3(0.25f, 0.15f, 0.0f);
	this->center->Initialize(8,1.5f,0.123f,0.123f);
	this->topCenter->Initialize(8, 0.123f);
	this->botCenter->Initialize(8, 0.123f);

	this->base->color = vec3(0.25f, 0.15f, 0.0f);
	this->base->Initialize(8, 0.927f, 0.123f);	

	this->leg->Initialize();

	if (this->GLReturnedError("Stool::Initialize - on exit"))
		return false;

	return true;
}


void Stool::StepShader(){
	this->seat->StepShader();
	this->topSeat->StepShader();
	this->botSeat->StepShader();
	this->upSup->StepShader();
	this->topUpSup->StepShader();
	this->botUpSup->StepShader();
	this->midSup->StepShader();
	this->topMidSup->StepShader();
	this->botMidSup->StepShader();
	this->center->StepShader();
	this->topCenter->StepShader();
	this->botCenter->StepShader();
	this->base->StepShader();
	this->leg->StepShader();
}

//Delete the stool elements.
void Stool::TakeDown()
{
	this->seat = NULL;
	this->topSeat = NULL;
	this->botSeat = NULL;
	this->upSup = NULL;
	this->topUpSup = NULL;
	this->botUpSup = NULL;
	this->midSup = NULL;
	this->topMidSup = NULL;
	this->botMidSup = NULL;
	this->center = NULL;
	this->topCenter = NULL;
	this->botCenter = NULL;
	this->base = NULL;
	this->leg = NULL;
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();	
}

//Draw and position the stool elements.
void Stool::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Stool::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);
	mat4 another;
	
	another = translate(modelview, vec3(-(3.25*0.25/6),0,-1.525));
	glLoadMatrixf(glm::value_ptr(another));
	this->leg->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(3.25*0.25/6,0,1.525));
	another = rotate(another, (GLfloat) 180, glm::vec3(0,1,0));
	glLoadMatrixf(glm::value_ptr(another));
	this->leg->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(1.525,0,-(3.25*0.25/6)));
	another = rotate(another, (GLfloat) 270, glm::vec3(0,1,0));
	glLoadMatrixf(glm::value_ptr(another));
	this->leg->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(-1.525,0,3.25*0.25/6));
	another = rotate(another, 90.0f, vec3(0,1,0));
	glLoadMatrixf(glm::value_ptr(another));
	this->leg->Draw(projection, another, size, 0);

	another = translate(modelview, glm::vec3(0,0.927,0));
    another = rotate(another, 90.0f, vec3(1,0,0));
    glLoadMatrixf(value_ptr(another));
	this->base->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(0,3.917+adjustableSeat,0));
    another = rotate(another, 180.0f, vec3(1,0,0));
    glLoadMatrixf(value_ptr(another));  
	this->center->Draw(projection, another, size, rotY);
	this->topCenter->Draw(projection, another, size, 0);
    another = translate(another, vec3(0.0f,1.5f,0.0f));  
    this->botCenter->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(0,3.357,0));
    glLoadMatrixf(glm::value_ptr(another));      
	this->midSup->Draw(projection, another, size, rotY);
	this->topMidSup->Draw(projection, another, size, 0);
    another = translate(another, vec3(0.0f,0.15f,0.0f));
	this->botMidSup->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(0,3.777,0));
    glLoadMatrixf(value_ptr(another)); 
	this->upSup->Draw(projection, another, size, rotY);
	this->topUpSup->Draw(projection, another, size, 0);
    another = translate(another, vec3(0.0f,0.133f,0.0f));
	this->botUpSup->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(0,3.982+adjustableSeat,0));
    another = rotate(another, 180.0f, vec3(1,0,0));
    glLoadMatrixf(value_ptr(another));
	this->seat->Draw(projection, another, size, rotY);
	this->topSeat->Draw(projection, another, size, 0);
    another = translate(another, vec3(0.0f,0.083f,0.0f));
	this->botSeat->Draw(projection, another, size, 0);	
	
	if (this->GLReturnedError("Stool::Draw - on exit"))
		return;
}

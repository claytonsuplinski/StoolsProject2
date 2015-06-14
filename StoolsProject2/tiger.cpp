/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a tiger object out of cylinders, discs, and spheres.
*/

#include <iostream>
#include "tiger.h"

using namespace std;
using namespace glm;

//Create a tiger object
Tiger::Tiger() : Object()
{
	vec4 lighter_color(MakeColor(255, 69, 0, 1.0f));
	vec4 darker_color = vec4(vec3(lighter_color) * 2.0f / 3.0f, 1.0f);
	this->colors[0] = darker_color;
	this->colors[1] = lighter_color;
}

Tiger::~Tiger()
{
	this->TakeDown();
}

//Initialize the elements of the tiger object
bool Tiger::Initialize()
{
	if (this->GLReturnedError("Tiger::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	this->cO = new Cylinder();
	this->cB = new Cylinder();
	this->leg = new Cylinder();
	this->tail = new Cylinder();
	this->whisker = new Cylinder();

	this->ear = new Disc();

	this->body = new Sphere();
	this->eye = new Sphere();
	this->nose = new Sphere();
	this->head = new Sphere();

	this->cO->color = vec3(1.0f, 0.35f, 0.0f);
	this->cO->Initialize(8,0.25f,1.0f,1.0f);
	
	this->cB->color = vec3(0.0f, 0.0f, 0.0f);
	this->cB->Initialize(8,0.25f,1.0f,1.0f);

	this->whisker->color = vec3(0.0f, 0.0f, 0.0f);
	this->whisker->Initialize(2,1.0f,0.01f,0.01f);

	this->leg->color = vec3(1.0f, 0.35f, 0.0f);
	this->leg->Initialize(8,3.5f,0.35f,0.65f);	
	this->tail->color = vec3(1.0f, 0.35f, 0.0f);
	this->tail->Initialize(8,2.5f,0.05f,0.05f);	

	this->ear->color = vec3(0.0f, 0.0f, 0.0f);
	this->ear->Initialize(8,0.25f);

	this->body->color = vec3(1.0f, 0.35f, 0.0f);
	this->body->Initialize(8,1.0f);
	
	this->eye->color = vec3(0.0f, 0.0f, 0.0f);
	this->eye->Initialize(8,0.15f);
	this->nose->color = vec3(0.0f, 0.0f, 0.0f);
	this->nose->Initialize(8,0.25f);
	this->head->color = vec3(1.0f, 0.35f, 0.0f);
	this->head->Initialize(8,1.0f);	

	if (this->GLReturnedError("Tiger::Initialize - on exit"))
		return false;

	return true;
}

void Tiger::StepShader(){
	this->cO->StepShader();
	this->cB->StepShader();
	this->leg->StepShader();
	this->tail->StepShader();
	this->whisker->StepShader();
	this->ear->StepShader();
	this->body->StepShader();
	this->eye->StepShader();
	this->nose->StepShader();
	this->head->StepShader();
}

//Delete the elements of the tiger
void Tiger::TakeDown()
{
	this->cO = NULL;
	this->cB = NULL;
	this->leg = NULL;
	this->whisker = NULL;
	this->tail = NULL;
	this->ear = NULL;
	this->body = NULL;
	this->eye = NULL;
	this->nose = NULL;
	this->head = NULL;
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw a tiger object
void Tiger::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Tiger::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 another;
	
	another = rotate(modelview, 40.0f, vec3(0,0,1));
	glLoadMatrixf(glm::value_ptr(another));
	this->tail->Draw(projection, another, size, rotY);
	another = rotate(another, -40.0f, vec3(0,0,1));

	another = rotate(another, 180.0f, vec3(0,0,1));
	another = rotate(another, 180.0f, vec3(0,1,0));
	glLoadMatrixf(glm::value_ptr(another));
	this->body->Draw(projection, another, size, 0);
	this->cB->Draw(projection, another, size, rotY);
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cO->Draw(projection, another, size, rotY);
	another = rotate(another, 90.0f, vec3(1,0,0));
	another = rotate(another, -50.0f, vec3(0,0,1));
	this->leg->Draw(projection, another, size, rotY);
	another = rotate(another, 280.0f, vec3(0,0,1));
	this->leg->Draw(projection, another, size, rotY);
	another = rotate(another, -230.0f, vec3(0,0,1));
	another = rotate(another, -90.0f, vec3(1,0,0));
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cB->Draw(projection, another, size, rotY);
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cO->Draw(projection, another, size, rotY);
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cB->Draw(projection, another, size, rotY);
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cO->Draw(projection, another, size, rotY);
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cB->Draw(projection, another, size, rotY);
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cO->Draw(projection, another, size, rotY);
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cB->Draw(projection, another, size, rotY);
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cO->Draw(projection, another, size, rotY);
	another = rotate(another, 90.0f, vec3(1,0,0));
	another = rotate(another, -50.0f, vec3(0,0,1));
	this->leg->Draw(projection, another, size, rotY);
	another = rotate(another, 280.0f, vec3(0,0,1));
	this->leg->Draw(projection, another, size, rotY);
	another = rotate(another, -230.0f, vec3(0,0,1));
	another = rotate(another, -90.0f, vec3(1,0,0));
	another = translate(another, vec3(0.0f, 0.25f, 0.0f));
	this->cB->Draw(projection, another, size, rotY);
	this->body->Draw(projection, another, size, 0);
	another = rotate(another, -180.0f, vec3(0,1,0));
	another = rotate(another, -180.0f, vec3(0,0,1));

	//trans and ang = 0

	another = rotate(another, 40.0f, vec3(0,0,1));
	another = translate(another, vec3(-1.5f, 0.0f, 0.0f));
	this->head->Draw(projection, another, size, 0);
	another = rotate(another, -40.0f, vec3(0,0,1));

	//trans = back of head; ang = 0;

	another = translate(another, vec3(-1.0f, 0.0f, 0.5f));
	this->ear->Draw(projection, another, size, 0);
	another = translate(another, vec3(0.0f, 0.0f, -1.0f));
	this->ear->Draw(projection, another, size, 0);
	another = translate(another, vec3(1.0f, 0.0f, 0.5f));
	another = translate(another, vec3(0.0f, -1.0f, 0.0f));
	this->nose->Draw(projection, another, size, 0);
	another = rotate(another, 90.0f, vec3(1,0,0));
	this->whisker->Draw(projection, another, size, rotY);
	another = rotate(another, 20.0f, vec3(0,0,1));
	this->whisker->Draw(projection, another, size, rotY);
	another = rotate(another, -40.0f, vec3(0,0,1));
	this->whisker->Draw(projection, another, size, rotY);
	another = rotate(another, 200.0f, vec3(0,0,1));
	this->whisker->Draw(projection, another, size, rotY);
	another = rotate(another, 20.0f, vec3(0,0,1));
	this->whisker->Draw(projection, another, size, rotY);
	another = rotate(another, -40.0f, vec3(0,0,1));
	this->whisker->Draw(projection, another, size, rotY);
	another = rotate(another, -160.0f, vec3(0,0,1));
	another = rotate(another, -90.0f, vec3(1,0,0));
	another = translate(another, vec3(0.0f, 1.0f, 0.0f));

	//trans = back of head; ang = 0;

	another = translate(another, vec3(-0.7f, -0.6f, 0.35f));
	this->eye->Draw(projection, another, size, 0);
	another = translate(another, vec3(0.0f, 0.0f, -0.7f));
	this->eye->Draw(projection, another, size, 0);
	another = translate(another, vec3(0.7f, 0.6f, 0.35f));

	another = rotate(another, 40.0f, vec3(0,0,1));
	another = translate(another, vec3(1.5f, 0.0f, 0.0f));
	another = rotate(another, -40.0f, vec3(0,0,1));

	//trans and ang = 0

	if (this->GLReturnedError("Tiger::Draw - on exit"))
		return;
}

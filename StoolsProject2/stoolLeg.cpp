/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a stool leg object.
*/

#include <iostream>
#include "stoolLeg.h"

using namespace std;
using namespace glm;

//Create a stool leg object
StoolLeg::StoolLeg() : Object()
{
	this->shader_index = 0;
}

//Initialize the stool leg
bool StoolLeg::Initialize()
{
	if (this->GLReturnedError("StoolLeg::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));

	VertexAttributesPCN buR, buL, fuR, fuL , bdL, bdR, fdL, fdR; // (b/f = back/front, u/d = up/down, L/R = left/right)
	VertexAttributesP buRN, buLN, fuRN, fuLN , bdLN, bdRN, fdLN, fdRN;
	float xC = (float)(3.25*0.25/3);
	float yC = 3.86f;
	float zC = 0.88f;
	float offset=(float)(3.25*0.25/3);
	fdL.position = vec3(0,0,0);
	fdL.color = vec3(0.25,0.15,0);
	fdR.position = vec3(xC,0,0);
	fdR.color = vec3(0.25,0.15,0);
	bdL.position = vec3(0,yC,zC);
	bdL.color = vec3(0.25,0.15,0);
	fuL.position = vec3(0,0,offset);
	fuL.color = vec3(0.25,0.15,0);
	buR.position = vec3(xC,yC,zC+offset);
	buR.color = vec3(0.25,0.15,0);
	buL.position = vec3(0,yC,zC+offset);
	buL.color = vec3(0.25,0.15,0);
	fuR.position = vec3(xC,0,offset);
	fuR.color = vec3(0.25,0.15,0);
	bdR.position = vec3(xC,yC,zC);
	bdR.color = vec3(0.25,0.15,0);

	//Bottom Face
	fdL.normal = cross(bdL.position, fdR.position);
	fdR.normal = cross(bdL.position, bdR.position);
	bdR.normal = vec3(0,0,-1);
	bdL.normal = vec3(0,0,-1);
	fdLN.position = fdL.normal;
	fdRN.position = fdR.normal;
	bdRN.position = bdR.normal;
	bdLN.position = bdL.normal;
	this->vertices.push_back(bdL);
	this->vertices.push_back(bdR);
	this->vertices.push_back(fdL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1); 

	this->normal_vertices.push_back(bdLN);
	this->normal_vertices.push_back(bdRN);
	this->normal_vertices.push_back(fdLN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1); 

	this->vertices.push_back(fdL);
	this->vertices.push_back(bdR);
	this->vertices.push_back(fdR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);	

	this->normal_vertices.push_back(fdLN);
	this->normal_vertices.push_back(bdRN);
	this->normal_vertices.push_back(fdRN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1); 

	//Top Face
	fuL.normal = cross(fuR.position, buL.position);
	fuR.normal = cross(buR.position, buL.position);
	buL.normal = vec3(0,0,1);
	buR.normal = vec3(0,0,1);
	fuLN.position = fuL.normal;
	fuRN.position = fuR.normal;
	buRN.position = buR.normal;
	buLN.position = buL.normal;
	this->vertices.push_back(fuL);
	this->vertices.push_back(fuR);
	this->vertices.push_back(buL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(fuLN);
	this->normal_vertices.push_back(fuRN);
	this->normal_vertices.push_back(buLN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);

	
	this->vertices.push_back(buL);
	this->vertices.push_back(fuR);
	this->vertices.push_back(buR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(buLN);
	this->normal_vertices.push_back(fuRN);
	this->normal_vertices.push_back(buRN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);

	//Front Face
	fdL.normal = vec3(0,-1,0);
	fdR.normal = vec3(0,-1,0);
	fuL.normal = vec3(0,-1,0);
	fuR.normal = vec3(0,-1,0);
	fdLN.position = fdL.normal;
	fdRN.position = fdR.normal;
	fuRN.position = fuR.normal;
	fuLN.position = fuL.normal;
	this->vertices.push_back(fdL);
	this->vertices.push_back(fdR);
	this->vertices.push_back(fuL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(fdLN);
	this->normal_vertices.push_back(fdRN);
	this->normal_vertices.push_back(fuLN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);
	
	this->vertices.push_back(fuL);
	this->vertices.push_back(fdR);
	this->vertices.push_back(fuR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(fuLN);
	this->normal_vertices.push_back(fdRN);
	this->normal_vertices.push_back(fuRN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);

	//Right Face
	fdR.normal = vec3(1,0,0);
	bdR.normal = vec3(1,0,0);
	fuR.normal = vec3(1,0,0);
	buR.normal = vec3(1,0,0);
	fuRN.position = fuR.normal;
	fdRN.position = fdR.normal;
	bdRN.position = bdR.normal;
	buRN.position = buR.normal;
	this->vertices.push_back(fdR);
	this->vertices.push_back(bdR);
	this->vertices.push_back(fuR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(fdRN);
	this->normal_vertices.push_back(bdRN);
	this->normal_vertices.push_back(fuRN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);
	
	this->vertices.push_back(fuR);
	this->vertices.push_back(bdR);
	this->vertices.push_back(buR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(fuRN);
	this->normal_vertices.push_back(bdRN);
	this->normal_vertices.push_back(buRN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);

	//Back Face
	bdR.normal = vec3(0,1,0);
	bdL.normal = vec3(0,1,0);
	buR.normal = vec3(0,1,0);
	buL.normal = vec3(0,1,0);
	buLN.position = buL.normal;
	buRN.position = buR.normal;
	bdRN.position = bdR.normal;
	bdLN.position = bdL.normal;
	this->vertices.push_back(bdR);
	this->vertices.push_back(bdL);
	this->vertices.push_back(buR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(bdRN);
	this->normal_vertices.push_back(bdLN);
	this->normal_vertices.push_back(buRN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);
	
	this->vertices.push_back(buR);
	this->vertices.push_back(bdL);
	this->vertices.push_back(buL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(buRN);
	this->normal_vertices.push_back(bdLN);
	this->normal_vertices.push_back(buLN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);

	//Left Face
	bdL.normal = vec3(-1,0,0);
	fdL.normal = vec3(-1,0,0);
	buL.normal = vec3(-1,0,0);
	fuL.normal = vec3(-1,0,0);
	bdLN.position = bdL.normal;
	fdLN.position = fdL.normal;
	buLN.position = buL.normal;
	fuLN.position = fuL.normal;
	this->vertices.push_back(bdL);
	this->vertices.push_back(fdL);
	this->vertices.push_back(buL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(bdLN);
	this->normal_vertices.push_back(fdLN);
	this->normal_vertices.push_back(buLN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);
	
	this->vertices.push_back(buL);
	this->vertices.push_back(fdL);
	this->vertices.push_back(fuL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->normal_vertices.push_back(buLN);
	this->normal_vertices.push_back(fdLN);
	this->normal_vertices.push_back(fuLN);
	this->normal_indices.push_back(this->vertices.size() - 3); 
	this->normal_indices.push_back(this->vertices.size() - 2); 
	this->normal_indices.push_back(this->vertices.size() - 1);

	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertices.size() * sizeof(VertexAttributesPCN), &this->vertices[0]))
		return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(vec3) * 2));	// Note offset - legacy of older code
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(vec3) * 1));	// Same
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (this->normal_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->normal_vertices.size() * sizeof(VertexAttributesP), &this->normal_vertices[0]))
			return false;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesP), (GLvoid *) 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	if (!this->flat_shader.Initialize("flat.vert", "flat.frag"))
		return false;

	this->shaders.push_back(&this->flat_shader);

	if (!this->phong_shader.Initialize("phong.vert", "phong.frag"))
		return false;

	this->shaders.push_back(&this->phong_shader);

	if (!this->gouraud_shader.Initialize("gouraud.vert", "gouraud.frag"))
		return false;

	this->shaders.push_back(&this->gouraud_shader);

	if (!this->solid_color.Initialize("solid_shader.vert", "solid_shader.frag"))
		return false;

	if (this->GLReturnedError("StoolLeg::Initialize - on exit"))
		return false;

	return true;
}

//Delete the stool leg object
void StoolLeg::TakeDown()
{
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw the stool leg object
void StoolLeg::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("StoolLeg::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	modelview = rotate(modelview, time * 30.0f, vec3(1.0f, 0.0f, 0.0f));
	modelview = rotate(modelview, time * 120.0f, vec3(0.0f, 1.0f, 0.0f));
	mat4 mvp = projection * modelview;
	mat3 nm = inverse(transpose(mat3(modelview)));

	this->shaders[this->shader_index]->Use();
	this->shaders[this->shader_index]->CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	glBindVertexArray(this->vertex_array_handle);
	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);

	if (this->GLReturnedError("StoolLeg::Draw - on exit"))
		return;
}

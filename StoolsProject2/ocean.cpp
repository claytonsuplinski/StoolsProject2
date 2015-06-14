/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates an ocean object (same as square, except for heights being 
determined by sinusoidal design)
*/

#include <iostream>
#include "ocean.h"

using namespace std;
using namespace glm;

//Creates an ocean
Ocean::Ocean() : Object()
{
	this->shader_index = 0;
}

//Initializes an ocean (x = # subsections, s = size)
bool Ocean::Initialize(int x, float s)
{
	if (this->GLReturnedError("Ocean::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	if (x < 1)
		x = 2;

	mat4 m;

	const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));
	const vec4 x_axis(1.0f, 0.0f, 0.0f, 1.0f);
	const vec3 y_axis(0.0f, 1.0f, 0.0f);
	const vec3 z_axis(0.0f, 0.0f, 1.0f);
	const vec3 center(0.0f, 0.0f, 0.0f);
	const float increment =  s / float(x); 
	int incrCount = 0;
	float incr = 360 / float(8*s);
	float amp = 0.9f;
	float angle = float(glutGet(GLUT_ELAPSED_TIME));

	for (int i = 0; i < x; ++i)
	{
		angle = 0;
		for (int j = 0; j < x; ++j)
		{
			m = translate(m, vec3(0.0f,amp*sin(angle),0.0f));
			VertexAttributesPCN cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;
			VertexAttributesP cur_vertexN , nxt_vertexN, dwn_vertexN, dwr_vertexN;
			cur_vertex.position = vec3(m * x_axis);
			cur_vertex.color = vec3(0.25,0.25,1);
			cur_vertex.normal = vec3(0,1,0);
			m = translate(m, vec3(0.0f,-amp*sin(angle),0.0f));

			m = translate(m, vec3(0.0f,amp*sin(angle),0.0f));
			m = translate(m, vec3(0.0f,0.0f,-increment));
			dwn_vertex.position = vec3(m * x_axis);
			dwn_vertex.color = vec3(0.25,0.25,1);
			dwn_vertex.normal = vec3(0,1,0);
			m = translate(m, vec3(0.0f,-amp*sin(angle),0.0f));

			angle += incr;

			m = translate(m, vec3(0.0f,amp*sin(angle),0.0f));
			m = translate(m, vec3(-increment, 0.0f,0.0f));
			dwr_vertex.position = vec3(m * x_axis);
			dwr_vertex.color = vec3(0.25,0.25,1);
			dwr_vertex.normal = vec3(0,1,0);

			m = translate(m, vec3(0.0f,-amp*sin(angle),0.0f));

			m = translate(m, vec3(0.0f,amp*sin(angle),0.0f));
			m = translate(m, vec3(0.0f,0.0f,increment));
			nxt_vertex.position = vec3(m * x_axis);
			nxt_vertex.color = vec3(0.25,0.25,1);
			nxt_vertex.normal = vec3(0,1,0);
			m = translate(m, vec3(0.0f,-amp*sin(angle),0.0f));

			cur_vertex.normal = normalize(cross(dwr_vertex.position, nxt_vertex.position));
			nxt_vertex.normal = normalize(cross(dwn_vertex.position, cur_vertex.position));
			dwr_vertex.normal = normalize(cross(dwn_vertex.position, cur_vertex.position));
			dwn_vertex.normal = normalize(cross(dwr_vertex.position, nxt_vertex.position));

			cur_vertexN.position = cur_vertex.normal;
			dwr_vertexN.position = dwr_vertex.normal;
			nxt_vertexN.position = nxt_vertex.normal;
			dwn_vertexN.position = dwn_vertex.normal;
		
			this->vertices.push_back(dwr_vertex);
			this->vertices.push_back(dwn_vertex);
			this->vertices.push_back(nxt_vertex);
			this->vertices.push_back(cur_vertex);

			this->normal_vertices.push_back(dwr_vertexN);
			this->normal_vertices.push_back(dwn_vertexN);
			this->normal_vertices.push_back(nxt_vertexN);
			this->normal_vertices.push_back(cur_vertexN);
	
			this->vertex_indices.push_back(this->vertices.size() - 4);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 3);

			this->vertex_indices.push_back(this->vertices.size() - 3);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 1);

			this->normal_indices.push_back(this->vertices.size() - 4);
			this->normal_indices.push_back(this->vertices.size() - 2);
			this->normal_indices.push_back(this->vertices.size() - 3);

			this->normal_indices.push_back(this->vertices.size() - 3);
			this->normal_indices.push_back(this->vertices.size() - 2);
			this->normal_indices.push_back(this->vertices.size() - 1);

			dwr_vertex.normal = -dwr_vertex.normal;
			dwn_vertex.normal = -dwn_vertex.normal;
			nxt_vertex.normal = -nxt_vertex.normal;
			cur_vertex.normal = -cur_vertex.normal;

			cur_vertexN.position = cur_vertex.normal;
			dwr_vertexN.position = dwr_vertex.normal;
			nxt_vertexN.position = nxt_vertex.normal;
			dwn_vertexN.position = dwn_vertex.normal;

			this->vertices.push_back(dwr_vertex);
			this->vertices.push_back(dwn_vertex);
			this->vertices.push_back(nxt_vertex);
			this->vertices.push_back(cur_vertex);

			this->normal_vertices.push_back(dwr_vertexN);
			this->normal_vertices.push_back(dwn_vertexN);
			this->normal_vertices.push_back(nxt_vertexN);
			this->normal_vertices.push_back(cur_vertexN);

			this->vertex_indices.push_back(this->vertices.size() - 1);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 3);

			this->vertex_indices.push_back(this->vertices.size() - 3);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 4);

			this->normal_indices.push_back(this->vertices.size() - 1);
			this->normal_indices.push_back(this->vertices.size() - 2);
			this->normal_indices.push_back(this->vertices.size() - 3);

			this->normal_indices.push_back(this->vertices.size() - 3);
			this->normal_indices.push_back(this->vertices.size() - 2);
			this->normal_indices.push_back(this->vertices.size() - 4);
		}
		m = translate(m, vec3((x*increment), 0.0f,0.0f));
		m = translate(m, vec3(0.0f,0.0f,-increment));
		incrCount++;
	}

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

	if (this->GLReturnedError("Ocean::Initialize - on exit"))
		return false;

	return true;
}

//Delete the ocean object
void Ocean::TakeDown()
{
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw an ocean 
void Ocean::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Ocean::Draw - on entry"))
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

	if (this->GLReturnedError("Ocean::Draw - on exit"))
		return;
}

/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a torus object.
*/

#include <iostream>
#include "torus.h"

using namespace std;
using namespace glm;

//Create a torus object
Torus::Torus() : Object()
{
	this->shader_index = 0;
}

//Calculate normals for the torus
//Outline of algorithm found here: http://www.cs.ucdavis.edu/~amenta/s12/findnorm.pdf
vec3 getNormal(vec3 pos, float i, float j){
	vec3 norm, t, s;

	//tangent vector with respect to big circle
	t.x = -sin(j);
	t.y = cos(j);
	t.z = 0;
	//tangent vector with respect to little circle
	s.x = cos(j)*(-sin(i));
	s.y = sin(j)*(-sin(i));
	s.z = cos(i);
	//normal is cross-product of tangents
	norm.x = t.y*s.z - t.z*s.y;
	norm.y = t.z*s.x - t.x*s.z;
	norm.z = t.x*s.y - t.y*s.x;
	//normalize normal
	norm = normalize(norm);
	return norm;
}

//Initialize a torus object with the specified parameters
bool Torus::Initialize(int slices, float R, float r)
{
	if (this->GLReturnedError("Torus::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	if (slices < 0)
		slices = 1;

	slices *= 4;

	mat4 m;

	const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));
	const vec4 x_axis(r, 0.0f, 0.0f, 1.0f);
	const vec4 x_axis2(r, 0.0f, 0.0f, 1.0f);
	const vec3 X_axis(R, 0.0f, 0.0f);
	const vec3 x_disp(r, 0.0f, 0.0f);
	const vec3 y_axis(0.0f, 1.0f, 0.0f);
	const vec3 z_axis(0.0f, 0.0f, 1.0f);
	const vec3 theAxis(1.0f, 0.0f, 0.0f);
	const vec3 center(0.0f, 0.0f, 0.0f);
	const float increment =  360.0f / float(slices); 
	float u = 0;
	float v = 0;
	//Create a torus with the mathematical 3D definition
	for (int i = 0; i <= 180; i+=10){
		for (int j = 0; j <= 360; j+=10){
		u = (float) (2* 3.1416 * (float)(i) / 180);
		v = (float) (2* 3.1416 * (float(j) + u) / 360);
		VertexAttributesPCN cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;
		VertexAttributesP cur_vertexN , nxt_vertexN, dwn_vertexN, dwr_vertexN;

		cur_vertex.position = vec3((float)((R + (float)(r)*cos(u))*cos(v)),(float)((R + (float)(r)*cos(u))*sin(v)),(float)((float)(r)*sin(u)));
		cur_vertex.color = color;
		cur_vertex.normal = getNormal(cur_vertex.position, u, v);

		j+=10;

		u = (float) (2* 3.1416 * float(i) / 180);
		v = (float) (2* 3.1416 * (float(j) + u) / 360);
		
		dwn_vertex.position = vec3((float)((R + (float)(r)*cos(u))*cos(v)),(float)((R + (float)(r)*cos(u))*sin(v)),(float)((float)(r)*sin(u)));
		dwn_vertex.color = color;
		dwn_vertex.normal = getNormal(dwn_vertex.position, u, v);

		i+=10;
		u = (float) (2* 3.1416 * float(i) / 180);
		v = (float) (2* 3.1416 * (float(j) + u) / 360);

		dwr_vertex.position = vec3((float)((R + (float)(r)*cos(u))*cos(v)),(float)((R + (float)(r)*cos(u))*sin(v)),(float)((float)(r)*sin(u)));
		dwr_vertex.color = color;
		dwr_vertex.normal = getNormal(dwr_vertex.position, u, v);

		j-=10;
		u = (float) (2* 3.1416 * float(i) / 180);
		v = (float) (2* 3.1416 * (float(j) + u) / 360);

		nxt_vertex.position = vec3((float)((R + (float)(r)*cos(u))*cos(v)),(float)((R + (float)(r)*cos(u))*sin(v)),(float)((float)(r)*sin(u)));
		nxt_vertex.color = color;
		nxt_vertex.normal = getNormal(nxt_vertex.position, u, v);

		i-=10;

		cur_vertexN.position = cur_vertex.normal;
		nxt_vertexN.position = nxt_vertex.normal;
		dwn_vertexN.position = dwn_vertex.normal;
		dwr_vertexN.position = dwr_vertex.normal;
		
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
	
		this->vertex_indices.push_back(this->vertices.size() - 4);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 3);

		this->vertex_indices.push_back(this->vertices.size() - 3);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 1);

		this->normal_indices.push_back(this->vertices.size() - 1);
		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 3);

		this->normal_indices.push_back(this->vertices.size() - 3);
		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 4);
	
		this->normal_indices.push_back(this->vertices.size() - 4);
		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 3);

		this->normal_indices.push_back(this->vertices.size() - 3);
		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 1);
		}
	}

	/* With this attempt, I tried using a reference point and then 
	translating and rotating outwards to form the torus. In several 
	attempts, it either resulted in disconnected cylinders or parts 
	of a sphere. After facing difficulties with this, I decided to 
	use the mathematical equation to define the points as it was 
	easier for me to utilize.

	for (int i = 0; i < slices + 1; ++i)
	{
		m = translate(m, X_axis);
		for (int j = 0; j < slices; ++j)
		{
		m = rotate(m, -90.0f, theAxis);
		VertexAttributesPCN cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;
		cur_vertex.position = vec3(m * x_axis);
		cur_vertex.color = vec3(1,0,0);
		cur_vertex.normal = vec3(0,1,0);

		m = translate(m, z_axis);

		dwn_vertex.position = vec3(m * x_axis2);
		dwn_vertex.color = vec3(1,0,0);
		dwn_vertex.normal = vec3(0,1,0);

		m = translate(m, -z_axis);

		m = rotate(m, increment, y_axis);

		m = translate(m, z_axis);

		dwr_vertex.position = vec3(m * x_axis2);
		dwr_vertex.color = vec3(1,0,0);
		dwr_vertex.normal = vec3(0,1,0);

		m = translate(m, -z_axis);

		m = rotate(m, -increment, y_axis);			

		m = rotate(m, increment, y_axis);
		
		nxt_vertex.position = vec3(m * x_axis);
		nxt_vertex.color = vec3(1,0,0);
		nxt_vertex.normal = vec3(0,1,0);
		m = rotate(m, 90.0f, theAxis);
		
		this->vertices.push_back(dwr_vertex);
		this->vertices.push_back(dwn_vertex);
		this->vertices.push_back(nxt_vertex);
		this->vertices.push_back(cur_vertex);
	
		if(i>0){
		this->vertex_indices.push_back(this->vertices.size() - 1);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 3);

		this->vertex_indices.push_back(this->vertices.size() - 3);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 4);
	
		this->vertex_indices.push_back(this->vertices.size() - 4);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 3);

		this->vertex_indices.push_back(this->vertices.size() - 3);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 1);
		}
		}
		m = translate(m, -X_axis);
		m = rotate(m, increment, z_axis);
	}
    
	//////////////////////Another attempt//////////////////////

	for (int i = 0; i < slices; ++i)
	{
		m = translate(m, X_axis);
		for (int j = 0; j < slices; ++j)
		{
			VertexAttributesPCN cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;
			cur_vertex.position = vec3(m * x_axis);
			cur_vertex.color = vec3(1,0,0);
			cur_vertex.normal = vec3(0,1,0);

			m = rotate(m, -increment, z_axis);

			dwn_vertex.position = vec3(m * x_axis);
			dwn_vertex.color = vec3(1,0,0);
			dwn_vertex.normal = vec3(0,1,0);

			m = rotate(m, increment, z_axis);

			//m = rotate(m, -incrCount*increment, z_axis);

			m = rotate(m, increment, y_axis);

			//m = rotate(m, incrCount*increment, z_axis);

			m = rotate(m, -increment, z_axis);

			dwr_vertex.position = vec3(m * x_axis);
			dwr_vertex.color = vec3(1,0,0);
			dwr_vertex.normal = vec3(0,1,0);

			m = rotate(m, increment, z_axis);

			//m = rotate(m, -incrCount*increment, z_axis);

			m = rotate(m, -increment, y_axis);			

			

			m = rotate(m, increment, y_axis);

			//m = rotate(m, incrCount*increment, z_axis);
		
			nxt_vertex.position = vec3(m * x_axis);
			nxt_vertex.color = vec3(1,0,0);
			nxt_vertex.normal = vec3(0,1,0);
		
			this->vertices.push_back(dwr_vertex);
			this->vertices.push_back(dwn_vertex);
			this->vertices.push_back(nxt_vertex);
			this->vertices.push_back(cur_vertex);
	
			this->vertex_indices.push_back(this->vertices.size() - 1);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 3);

			this->vertex_indices.push_back(this->vertices.size() - 3);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 4);

			this->vertex_indices.push_back(this->vertices.size() - 4);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 3);

			this->vertex_indices.push_back(this->vertices.size() - 3);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 1);
		}
		m = translate(m, -X_axis);
		m = rotate(m, increment, z_axis);
		incrCount++;
	}
	
	//////////////////Another attempt////////////////

	offset += 360.0f / float(8*slices);
	const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));
	const vec4 x_axis(r, 0.0f, 0.0f, 1.0f);
	const vec3 X_axis(R, 0.0f, 0.0f);
	const vec3 X_axis2(R, 0.0f, 0.0f);
	const vec3 y_axis(0.0f, 1.0f, 0.0f);
	const vec3 offset(r/2, 0.0f, 0.0f);
	const vec3 y2_axis(1.0f, 0.0f, 0.0f);
	const vec3 z_axis(0.0f, 2*R*3.1416/slices + 0*R*3.1416/slices, 0.0f);
	const vec3 x_direction(1.0f, 0.0f, 0.0f);
	const float increment =  360.0f / float(slices); 
	int incrCount = 0;

	for (int i = 0; i < slices; ++i)
	{
		m = translate(m, X_axis);
		m = rotate(m, 90.f, y2_axis);
		for (int j = 0; j < slices; ++j)
		{
		VertexAttributesPCN cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;

		cur_vertex.position = vec3(m * x_axis);
		cur_vertex.color = vec3(1,0,0);
		cur_vertex.normal = vec3(0,1,0);

		m = translate(m, z_axis);

		dwn_vertex.position = vec3(m * x_axis);
		dwn_vertex.color = vec3(1,0,0);
		dwn_vertex.normal = vec3(0,1,0);

		m = translate(m, -z_axis);

		m = rotate(m, increment, y_axis);

		m = translate(m, z_axis);

		dwr_vertex.position = vec3(m * x_axis);
		dwr_vertex.color = vec3(1,0,0);
		dwr_vertex.normal = vec3(0,1,0);

		m = translate(m, -z_axis);

		m = rotate(m, -increment, y_axis);			

		m = rotate(m, increment, y_axis);
		
		nxt_vertex.position = vec3(m * x_axis);
		nxt_vertex.color = vec3(1,0,0);
		nxt_vertex.normal = vec3(0,1,0);
		
		this->vertices.push_back(dwr_vertex);
		this->vertices.push_back(dwn_vertex);
		this->vertices.push_back(nxt_vertex);
		this->vertices.push_back(cur_vertex);
	
		this->vertex_indices.push_back(this->vertices.size() - 1);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 3);

		this->vertex_indices.push_back(this->vertices.size() - 3);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 4);
	}
		m = rotate(m, -90.f, y2_axis);
		m = translate(m, -X_axis);
		m = rotate(m, increment, y_axis);
		incrCount++;
	}*/

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

	if (this->GLReturnedError("Torus::Initialize - on exit"))
		return false;

	return true;
}

void Torus::TakeDown()
{
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw a torus object
void Torus::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Torus::Draw - on entry"))
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

	if (this->GLReturnedError("Torus::Draw - on exit"))
		return;
}

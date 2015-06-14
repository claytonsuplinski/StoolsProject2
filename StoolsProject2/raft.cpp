/*
	Name: Clayton Suplinski
*/

#include <iostream>
#include "raft.h"

using namespace std;
using namespace glm;

Raft::Raft() : Object()
{
	vec4 lighter_color(MakeColor(255, 69, 0, 1.0f));
	vec4 darker_color = vec4(vec3(lighter_color) * 2.0f / 3.0f, 1.0f);
	this->colors[0] = darker_color;
	this->colors[1] = lighter_color;
}

inline int ColorIndex(int i, int slices)
{
	return (i / (slices / 4)) % 2;
}

inline int PreviousSlice(int i, int slices)
{
	return (i == 0) ? slices - 1 : i - 1;
}

bool Raft::Initialize(int slices, float R, float r)
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
	for (int i = 0; i <= 180; i+=10)
	{
		for (int j = 0; j <= 360; j+=10)
		{
		u = 2* 3.1416 * float(i) / 180;
		v = 2* 3.1416 * (float(j) + u) / 360;
		VertexAttributesPCN cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;
		cur_vertex.position = vec3((float)((R + (float)(r)*cos(u))*cos(v)),(float)((R + (float)(r)*cos(u))*sin(v)),(float)((float)(r)*sin(u)));
		cur_vertex.color = vec3(1,0.25,0);
		cur_vertex.normal = vec3(0,1,0);

		j+=10;

		u = 2* 3.1416 * float(i) / 180;
		v = 2* 3.1416 * (float(j) + u) / 360;
		
		dwn_vertex.position = vec3((float)((R + (float)(r)*cos(u))*cos(v)),(float)((R + (float)(r)*cos(u))*sin(v)),(float)((float)(r)*sin(u)));
		dwn_vertex.color = vec3(1,0.25,0);
		dwn_vertex.normal = vec3(0,1,0);

		i+=10;
		u = 2* 3.1416 * float(i) / 180;
		v = 2* 3.1416 * (float(j) + u) / 360;

		dwr_vertex.position = vec3((float)((R + (float)(r)*cos(u))*cos(v)),(float)((R + (float)(r)*cos(u))*sin(v)),(float)((float)(r)*sin(u)));
		dwr_vertex.color = vec3(1,0.25,0);
		dwr_vertex.normal = vec3(0,1,0);

		j-=10;
		u = 2* 3.1416 * float(i) / 180;
		v = 2* 3.1416 * (float(j) + u) / 360;

		nxt_vertex.position = vec3(0,0,0);
		nxt_vertex.color = vec3(1,0.25,0);
		nxt_vertex.normal = vec3(0,1,0);

		i-=10;
		
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
	}

	/*	for each slice:
			compute top triangle geometry
			compute vectors to visualize normals for top triangle (BuildNormalVisualizationGeometry())
			compute bottom triangle geometry
			compute vectors to visualize normals for bottom triangle (BuildNormalVisualizationGeometry())
	*/

	/*
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
	*/
	/*	for each slice:
			compute top triangle geometry
			compute vectors to visualize normals for top triangle (BuildNormalVisualizationGeometry())
			compute bottom triangle geometry
			compute vectors to visualize normals for bottom triangle (BuildNormalVisualizationGeometry())
	*/
	//for (int k = 0; k < 8; ++k){
	//	mat4 m;
	//	m = rotate(m, offset, z_axis);
	
	/*
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
	*/
	//offset += 360.0f / float(8*slices);

	//}

	/*const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));
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

	/*	for each slice:
			compute top triangle geometry
			compute vectors to visualize normals for top triangle (BuildNormalVisualizationGeometry())
			compute bottom triangle geometry
			compute vectors to visualize normals for bottom triangle (BuildNormalVisualizationGeometry())
	*/
	/*
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

	/*	The VertexAttributesPCN class stores vertex attributes: position, color and normal in that order.

		Vertex attributes are stored in an interleaved manner aiding speed of vertex processing.
	*/

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

	if (!this->shader.Initialize("top_shader.vert", "top_shader.frag"))
		return false;

	if (!this->solid_color.Initialize("solid_shader.vert", "solid_shader.frag"))
		return false;

	if (this->GLReturnedError("Background::Initialize - on exit"))
		return false;

	return true;
}

void Raft::TakeDown()
{
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

/*	A note about drawing the normals.

	If you scale this object non-uniformly, drawing the normals will
	not be correct. This is because the normals are being stored for
	visualization as geometry. As such, scaling will not be corrected
	by the normal matrix.
*/

/*	A note about the index arrays.

	In this example, the index arrays are unsigned ints. If you know
	for certain that the number of vertices will be small enough, you
	can change the index array type to shorts or bytes. This will have
	the two fold benefit of using less storage and transferring fewer
	bytes.
*/

void Raft::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Torus::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	modelview = rotate(modelview, time * 30.0f, vec3(1.0f, 0.0f, 0.0f));
	modelview = rotate(modelview, time * 120.0f, vec3(0.0f, 1.0f, 0.0f));
	mat4 mvp = projection * modelview;
	mat3 nm = inverse(transpose(mat3(modelview)));

	shader.Use();
	shader.CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	glBindVertexArray(this->vertex_array_handle);
	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);

	if (this->draw_normals)
	{
		this->solid_color.Use();
		this->solid_color.CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
		glBindVertexArray(this->normal_array_handle);
		glDrawElements(GL_LINES , this->normal_indices.size(), GL_UNSIGNED_INT , &this->normal_indices[0]);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	if (this->GLReturnedError("Torus::Draw - on exit"))
		return;
}

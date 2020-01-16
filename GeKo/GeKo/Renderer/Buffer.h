#pragma once
 
/**
* @class Buffer class
* @author Christian Kati
* @brief Basic Buffer Wrapper for Opengl Indeex/Vertexbuffers
*/

#include "glad/glad.h"


#include "../../Math/vec3.h"

namespace gke {

	class VertexBuffer
	{
	public:

		VertexBuffer();

		void create(float* vertices, int size);
		~VertexBuffer();

		void bind();
		void unbind();
	private:
		GLuint id;
	};


	class IndexBuffer
	{
	public:

		IndexBuffer();

		void create(unsigned int* indices, int size);
		~IndexBuffer();

		void bind();
		void unbind();
	private:
		GLuint id;
	};

}
#pragma once
 
#include "glad/glad.h"

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
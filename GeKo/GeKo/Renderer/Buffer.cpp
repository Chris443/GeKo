#include "Buffer.h"

namespace gke {

	VertexBuffer::VertexBuffer() {};

	void VertexBuffer::create(float* vertices, int size) {
		glCreateBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &id);
	}

	void VertexBuffer::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void VertexBuffer::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*********************
	*****IndexBuffer******
	**********************/

	IndexBuffer::IndexBuffer() {};

	void IndexBuffer::create(unsigned int* indices, int size) {
		glCreateBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &id);
	}

	void IndexBuffer::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void IndexBuffer::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
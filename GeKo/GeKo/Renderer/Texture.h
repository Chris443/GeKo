#pragma once
#include <string>
#include <iostream>

#include "glad/glad.h"

namespace gke {

	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		void bind();
		void unbind();

		void generateMipMap();
	private:
		unsigned int id;
		int width, height, channels;
		unsigned char *data;
	};

}

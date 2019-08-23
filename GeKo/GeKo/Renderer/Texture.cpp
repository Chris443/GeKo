#include "Texture.h"

#include "stb_image.h"

namespace gke {
	Texture::Texture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		//could be changed
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (data)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(data);
	}


	Texture::~Texture()
	{
	}

	void Texture::bind() {
		glBindTexture(GL_TEXTURE_2D, id);

	}
	
	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::generateMipMap() {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}
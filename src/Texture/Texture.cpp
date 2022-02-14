#include "Texture.h"
#include "stb_image.h"
#include <GL/glew.h>

Texture::Texture(std::string const& path)
	:m_RedererID(0),m_Filepath(path),m_LocalBuffer(nullptr),m_Height(0),m_Width(0),m_BPP(0)
{
	stbi_set_unpremultiply_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    glewInit();
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &m_RedererID);
	glBindBuffer(GL_TEXTURE, m_RedererID);
	glBindTexture(GL_TEXTURE_2D, m_RedererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D,0);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RedererID);
}

void Texture::Bind(unsigned int slot /*= 0 */) const
{
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_RedererID);

}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


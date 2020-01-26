#include "SkyboxTexture.h"
#include "../vendor/stb_image/stb_image.h"

SkyboxTexture::SkyboxTexture(const std::string & path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	std::string sides[] = { "_rt", "_lf",  "_dn","_up", "_bk", "_ft" };
	std::string fileName;
	for (int i = 0; i < 6; i++) {
		fileName = path + sides[i] + ".tga";
		m_LocalBuffer = stbi_load(fileName.c_str(), &m_Width, &m_Height, &m_BPP, 4);
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		stbi_image_free(m_LocalBuffer);
	}
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

SkyboxTexture::~SkyboxTexture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void SkyboxTexture::Bind(unsigned int slot) const
{

	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void SkyboxTexture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

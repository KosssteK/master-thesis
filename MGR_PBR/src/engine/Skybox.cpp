#include "Skybox.h"
#include "render/VertexBufferLayout.h"

CAT::Skybox::Skybox()
	: shader("res/shaders/skybox.shader"),
	verticiesNumber(0),
	texture("res/objects/skybox/vr"), 
	m_Size(500),
	m_PositionsCount(108), 
	m_Positions{
		-m_Size, m_Size, -m_Size,
		-m_Size, -m_Size, -m_Size,
		m_Size, -m_Size, -m_Size,
		m_Size, -m_Size, -m_Size,
		m_Size, m_Size, -m_Size,
		-m_Size, m_Size, -m_Size,

		-m_Size, -m_Size, m_Size,
		-m_Size, -m_Size, -m_Size,
		-m_Size, m_Size, -m_Size,
		-m_Size, m_Size, -m_Size,
		-m_Size, m_Size, m_Size,
		-m_Size, -m_Size, m_Size,

		m_Size, -m_Size, -m_Size,
		m_Size, -m_Size, m_Size,
		m_Size, m_Size, m_Size,
		m_Size, m_Size, m_Size,
		m_Size, m_Size, -m_Size,
		m_Size, -m_Size, -m_Size,

		-m_Size, -m_Size, m_Size,
		-m_Size, m_Size, m_Size,
		m_Size, m_Size, m_Size,
		m_Size, m_Size, m_Size,
		m_Size, -m_Size, m_Size,
		-m_Size, -m_Size, m_Size,

		-m_Size, m_Size, -m_Size,
		m_Size, m_Size, -m_Size,
		m_Size, m_Size, m_Size,
		m_Size, m_Size, m_Size,
		-m_Size, m_Size, m_Size,
		-m_Size, m_Size, -m_Size,

		-m_Size, -m_Size, -m_Size,
		-m_Size, -m_Size, m_Size,
		m_Size, -m_Size, -m_Size,
		m_Size, -m_Size, -m_Size,
		-m_Size, -m_Size, m_Size,
		m_Size, -m_Size, m_Size }
{

	VertexBufferLayout layout;
	layout.Push<float>(3);

	VertexBuffer vb(GetPositions(), GetPositionsSize());

	vertexArray.AddBuffer(vb, layout);
	vertexArray.Unbind();
}

CAT::Skybox::~Skybox()
{
}

CAT::Container * CAT::Skybox::AddChild(CAT::Container & container)
{
	return nullptr;
}

void CAT::Skybox::UpdateTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	MVP = projection * view * GetMVPMatrix(model);
}

void CAT::Skybox::Draw()
{
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", MVP);
	texture.Bind();
	vertexArray.Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}

float* CAT::Skybox::GetPositions()
{
	return m_Positions;
}

float CAT::Skybox::GetPositionsSize()
{
	return m_PositionsCount * sizeof(float);
}
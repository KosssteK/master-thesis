#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	vec4 pos = u_MVP * vec4(position, 1.0f);
	gl_Position = -pos.xyww;
	v_TexCoord = position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_TexCoord;

uniform samplerCube skybox;

void main()
{
	color = texture(skybox, v_TexCoord);
};
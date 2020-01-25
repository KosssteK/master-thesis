#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 v_Color;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_Color = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec4 v_Color;

void main()
{
	out_color = v_Color;
	//color = vec4(1.0,0.0,0.0, 1.0);
};


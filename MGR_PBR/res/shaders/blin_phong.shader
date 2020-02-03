#shader vertex
#version 330 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_texCoord;
layout(location = 2) in vec3 v_normal;

out vec2 f_TexCoord;
out vec3 f_FragPos;
out vec3 f_Normal;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
//uniform mat4 u_MVP;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(v_position, 1.0);
	//gl_Position = u_MVP * vec4(v_position, 1.0);
	f_FragPos = vec3(u_Model*vec4(v_position, 1.0));
	f_TexCoord = v_texCoord;
	//f_Normal = v_normal;
	f_Normal = mat3(transpose(inverse(u_Model))) * v_normal;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 f_TexCoord;
in vec3 f_FragPos;
in vec3 f_Normal;

uniform sampler2D u_Texture;

uniform vec3 u_CameraPosition;
vec3 lightColor = vec3(1.0, 1.0, 1.0);  // uniform later
vec3 lightPosition = vec3(0.0, 0.0, 0.0);  // uniform later

void main()
{
	//ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	//diffuse
	vec3 normalizedNormal = normalize(f_Normal);
	vec3 lightDirection = normalize(lightPosition - f_FragPos);
	
	float diff = max(dot(normalizedNormal, lightDirection), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 1.0;
	vec3 observerDirection = normalize(u_CameraPosition - f_FragPos);
	vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);

	float spec = pow(max(dot(observerDirection, reflectDirection), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * texture(u_Texture, f_TexCoord).xyz;
	color = vec4(result, 1.0);
};


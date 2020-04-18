#shader vertex
#version 330 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_textureCoords;
layout(location = 2) in vec3 v_normal;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec2 f_textureCoords;
out vec3 f_position;
out vec3 f_normal;


void main()
{
	f_textureCoords = v_textureCoords;
	f_position = vec3(u_Model * vec4(v_position, 1.0));
	f_normal = mat3(u_Model) * v_normal;

	gl_Position = u_Projection * u_View * vec4(f_position, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in vec2 f_textureCoords;
in vec3 f_position;
in vec3 f_normal;

uniform vec3 u_CameraPosition;

uniform sampler2D u_Texture;

vec3 albedo = texture(u_Texture, f_textureCoords).xyz;
////vec3 albedo = vec3(20.0,0.0,0.0)//texture(u_Texture, f_textureCoords).xyz;
//float metallic = 1.0;
//float roughness = 0.1;
float ao = 1.0;

//uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
//uniform float ao;

//uniform vec3 lightPositions[4];
//uniform vec3 lightColors[4];

vec3 lightPositions[4] = { vec3(4.0, 4.0, 0.0), vec3(4.0, -4.0, 0.0), vec3(-4.0, 4.0, 0.0), vec3(-4.0, -4.0, 0.0) };
vec3 lightColors[4] = { vec3(300.0,300.0,300.0), vec3(300.0,300.0,300.0), vec3(300.0,300.0,300.0), vec3(300.0,300.0,300.0) };

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);

void main()
{
	vec3 N = normalize(f_normal);
	vec3 V = normalize(u_CameraPosition);


	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0);
	for (int i = 0; i < 4; i++) {

		vec3 L = normalize(lightPositions[i] - f_position); //light direction vector
		vec3 H = normalize(V + L); // halfway vector
		float distance = length(lightPositions[i] - f_position);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = lightColors[i] * attenuation;


		float NDF = DistributionGGX(N, H, roughness);
		float G = GeometrySmith(N, V, L, roughness);
		vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

		vec3 nominator = NDF * G * F;
		float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
		vec3 specular = nominator / max(denominator, 0.001);

		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;

		kD *= 1.0 - metallic;

		float NdotL = max(dot(N, L), 0.0);
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}
	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 color = ambient + Lo;

	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0 / 2.2));

	o_color = vec4(color, 1.0);
};

//calculates ratio reflected vs refracted
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
	//how much the surface reflects if looking directly at the surface
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH * NdotH;

	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;

	float num = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}
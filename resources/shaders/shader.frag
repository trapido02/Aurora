#version 450 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

// texture sampler
uniform sampler2D texture1;

uniform vec3 ambientLightColor;
uniform float ambientLightStrength;

uniform vec3 directionalLightDirection;
uniform vec3 directionalLightColor;
uniform float directionalLightStrength;

void main()
{
	// Sample the texture
	vec4 texColor = texture(texture1, TexCoord);

	// Ambient light
	vec3 ambient = ambientLightStrength * ambientLightColor; // Strength * color

	// Directional light 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, -directionalLightDirection), 0.0);
    vec3 diffuse = (diff * directionalLightColor) * directionalLightStrength;

	vec3 result = (ambient + diffuse) * texColor.rgb;
	FragColor = vec4(result, 1.0f);
}
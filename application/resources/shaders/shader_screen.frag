#version 450 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

// texture sampler
uniform sampler2D screenTexture;

void main()
{
	// Sample the texture
	vec3 texColor = texture(screenTexture, TexCoord).rgb;
	FragColor = vec4(texColor, 1.0f);
}
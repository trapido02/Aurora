#version 450 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

// Texture sampler
uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0;

void main()
{
	// Sample the texture
	vec3 texColor = texture(screenTexture, TexCoord).rgb;
	FragColor = vec4(texColor, 1.0f);
}
#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 jpg = texture(texture1, TexCoord);
	vec4 png = texture(texture2, TexCoord);
	vec3 color = mix(jpg.rgb, png.rgb, png.a);
	FragColor = vec4(color, 1.0f);
}
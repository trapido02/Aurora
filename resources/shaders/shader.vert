#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
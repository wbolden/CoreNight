#version 420

layout(location = 0) in vec2 vp;
layout(location = 1) in vec2 vt;

out vec2 texCoords;

uniform vec2 pos;
uniform mat4 scale;
//out vec2 st;

void main()
{
	texCoords = vt;

	gl_Position = vec4(vp.x + pos.x, vp.y + pos.y, 0, 1.0) * scale;
}
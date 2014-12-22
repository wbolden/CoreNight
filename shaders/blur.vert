#version 420

layout(location = 0) in vec2 vp;
layout(location = 1) in vec2 vt;

out vec2 texCoords;



void main()
{
	texCoords = vt;


	gl_Position = vec4(vp.x, vp.y, 0, 1.0);
}
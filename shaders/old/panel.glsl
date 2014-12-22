#version 420

layout(location = 0) in vec2 vp;
layout(location = 1) in vec2 vt;

out vec2 texCoords;
//out vec2 st;

void main()
{
	//texCoords = vt;

	//texCoords = (vp + 1.0)*0.5;

	texCoords = vt;
	//texCoords = vp;
	gl_Position = vec4(vp.x *(720.0f/1280.0f) * (1280.0f/1280.0f) /** (560.0f/319.0f)*/, vp.y, 0, 1.0);
	gl_Position.xy *= 1;

	//gl_Position.x += 0.4;
}
#version 400

in vec2 vp;
out vec2 st;

void main()
{
	st = (vp + 1.0)*0.5;
	gl_position = vec4(vp, 0, 1.0);
	gl_Position.xy *= 0.5;
}
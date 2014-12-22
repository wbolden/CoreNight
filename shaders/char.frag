#version 420

in vec2 texCoords;
//layout (binding = 0) uniform sampler2D tex;
uniform sampler2D tex;

out vec4 fragColor;





void main()
{

	vec4 texel = texture(tex, texCoords);
	float ac = texel.w;
	fragColor = texel;
	fragColor.w = ac;
}


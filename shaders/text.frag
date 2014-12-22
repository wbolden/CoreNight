#version 420

in vec2 texCoords;
//layout (binding = 0) uniform sampler2D tex;
uniform sampler2D tex;

out vec4 fragColor;


void main()
{


	fragColor = vec4(texCoords, 1.0f, 1.0);
//fragColor = vec4(1, 0, 1.0f, 1.0);

//if()

vec4 texel = texture(tex, texCoords);
	fragColor = texel ;

	fragColor.rgb += vec3(1,1,1);

	fragColor.rgb *= vec3(1, 1, 1);
	//fragColor = vec4(texCoords, 1, 1);

	//if(texel.x < 0.6)
	{
	//	fragColor = vec4(1, 0, 1.0f, 1.0);
	}
}

//vec3(0.5, 1, 0.3); green
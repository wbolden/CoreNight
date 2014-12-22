#version 420

in vec2 texCoords;
//layout (binding = 0) uniform sampler2D tex;
uniform sampler2D tex;

out vec4 fragColor;

const float sf = (1000.0f/1920.0f);

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}



void main()
{
	vec4 texel = texture(tex, texCoords);


	vec4 total = vec4(0, 0, 0, 0);




	int numit = 1;
	for(int x = 1; x < numit+1+1; x++)
	{
		for(int y = 1; y < numit+1; y++)
		{
			float scale = 0.1 * 5.0f;

			float xloc = texCoords.x + scale *(sf * rand(vec2((texCoords.y+y*texCoords.y)/x, (texCoords.y +y*texCoords.x)/x )) - sf*0.5f);
			float yloc = texCoords.y + scale *(sf * rand(vec2((texCoords.x+x*texCoords.y)/y, (texCoords.x +x*texCoords.x)/y)) - sf*0.5f);

			total += texture(tex, vec2(xloc, yloc)) * (1.0f/(numit*numit+1));
		}
	}
	


	float ac = total.w;
	fragColor = total *0.6f;
	fragColor.w = ac;
}


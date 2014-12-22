#version 420

out vec4 fragColor;

uniform vec4 color;

void main()
{


	//fragColor = vec4(0.5f, 0.5f, 0.5f, 0.5);
//fragColor = vec4(1,1,1, 0.1);


	fragColor = color;

	//fragColor.w = 1;
	
}

//fragColor = vec4(1, 1, 0.5, 0.5); //gold
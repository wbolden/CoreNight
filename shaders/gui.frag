#version 420

out vec4 fragColor;

in float highlight;
//in float idf;


void main()
{
/*
	if(idf < 0)
	{
		fragColor = vec4(1, 0, 0, 0.5);
	}

	if(idf == 0)
	{
		fragColor = vec4(0, 1, 0, 0.5);
	}

	if(idf > 1)
	{
		fragColor = vec4(0, 0, 1, 0.5);
	}
	*/

	fragColor = vec4(0.5f, 0.5f, 0.5f, 0.5);
fragColor = vec4(1,1,1, 0.1);

	if(highlight == 0)	{

		fragColor = vec4(0.8, 0.2, 0.8, 0.5);
	}
}

//fragColor = vec4(1, 1, 0.5, 0.5); //gold
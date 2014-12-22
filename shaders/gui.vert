#version 420

layout(location = 0) in vec2 pos;
layout(location = 1) in float id;

uniform int active;

out float highlight;
//out float idf;


void main()
{

	//highlight = -1;
	//if(active == id)
	//{
	//	highlight = 0;
	//}

	//idf = vec2(0, 0);
	//idf.x = 0;
	//idf.y = 0;
	//id * id;
	//idf = id;
	//idf.y = 0;



	highlight = 1.0f;
	if(id  == active)
	highlight =  0;
	gl_Position = vec4(pos.x *(720.0f/1280.0f), pos.y, 0, 1.0);

}
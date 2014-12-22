#include "Game.h"
#include "Display.h"
#include "Input.h"
#include <iostream>
#include <fstream>

GLFWwindow* window;
GLint resize = GL_FALSE;


bool fullscreen = false;
int width = 1280;
int height = 720;


/*
bool fullscreen = true;
int width = 1920;
int height = 1080;
*/

Display display;
Input input;
bool glfwInitialized = false;


void printfGLInfo()
{
	const GLubyte* renderer = glGetString(GL_RENDER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	
	std::cout << "Renderer: ";
	if(renderer == NULL)
	{
		std::cout << "null" << std::endl;
	}
	else
	{
		std::cout << renderer << std::endl;
	}

	std::cout << "Version: ";
	if(version == NULL)
	{
		std::cout << "null" << std::endl;
	}
	else
	{
		std::cout << version << std::endl;
	}

	std::cout << "Vendor: ";
	if(vendor == NULL)
	{
		std::cout << "null" << std::endl;
	}
	else
	{
		std::cout << vendor << std::endl;
	}

	std::cout << "GLSL Version: ";
	if(glslVersion == NULL)
	{
		std::cout << "null" << std::endl;
	}
	else
	{
		std::cout << glslVersion << std::endl;
	}
}

void initGL()
{



	glfwInitialized = glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, resize);
	

	if(!glfwInitialized)
	{
		std::cout << "GLFW initialization failed" << std::endl;
		return;
	}
	
	std::cout << "GLFW initialized" << std::endl;

	glfwWindowHint(GLFW_SAMPLES, 16);

	if(fullscreen)
	{
		window = glfwCreateWindow(width, height, "Core Night", glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		window = glfwCreateWindow(width, height, "Core Night", NULL, NULL);
	}

	if(!window)
	{
		std::cout << "Window creation failed" << std::endl;
		return;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
}

GLuint guiprog = 0;
GLuint textprog = 0;
GLuint charprog = 0;
GLuint blurprog = 0;
GLuint fadeprog = 0;
GLuint butprog = 0;

Game::Game(void)
{
	std::fstream settings("settings/settings.txt");

	settings >> width;
	settings >> height;
	settings >> fullscreen;

	settings.close();

	initGL();
	printfGLInfo();

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//display
	input = Input(window);
	display = Display(window);

	textprog = display.initShaders("shaders/text.vert", "shaders/text.frag");

	guiprog =  display.initShaders("shaders/gui.vert", "shaders/gui.frag");

	charprog = display.initShaders("shaders/char.vert", "shaders/char.frag");

	blurprog = display.initShaders("shaders/blur.vert", "shaders/blur.frag");

	fadeprog = display.initShaders("shaders/fade.vert", "shaders/fade.frag");
	
	butprog = display.initShaders("shaders/button.vert", "shaders/button.frag");

}

#include "Text.h"
#include "Story.h"
#include "Scene.h"
//	Story s = Story("dialogue/dtest1.txt");
void Game::run()
{
		BoundingBox ctbox = BoundingBox();

	ctbox.setUPos(0, 0, 1.0f, 1.0f);

//	Story s = Story("dialogue/tri2.txt");
//	std::vector<Dialogue> d = s.getDialogue();

//	Text text = Text();

//	text.genText(d, 0.3f, 0.5f, width, height, 0.33f, true, true);


	std::string as = "Artist's Statement";
	//std::string ast = "The purpose of this game is to display through a simple medium etc etc that prejudices are dumb and people should just get along. The actual text will contain a bunch of stuff about culture and whatnot. Imagine this text goes on for a long more time and says a bunch of useless stuff that would be expected of an artists statement. Imagine this text goes on for a long more time and says a bunch of useless stuff that would be expected of an artists statement. Imagine this text goes on for a long more time and says a bunch of useless stuff that would be expected of an artists statement. Imagine this text goes on for a long more time and says a bunch of useless stuff that would be expected of an artists statement. Imagine this text goes on for a long more time and says";
	std::string ast ="We selected this project as we felt it would be an appropriate medium to simplify the often complex cultural clashes that occur in human society. These clashes create untold division and discord in our world, though at their most basic level they have one cause-- disrespect. Through this simple 2D game we hoped to represent exaggerated versions of the choices one would make when interacting with a distant culture and hopefully convey that respect is one value that everyone must hold dear. This idea represents the culmination of our first quarter of studies at Merrill College and the beginning of our lives as informed UCSC students.";
	std::string by = "By: Will Bolden, Derek Kwong, and Ben Hallsted";

	std::string playText = "Play";
	Text play = Text();
	play.genText(playText, 0.66f, 2.2f, -3.1f, width, height, 1.5f, false, true);


	float xBeg = 0.2f;
	float xEnd = 1.7f;
	Text title = Text();
	title.genText(as, 0.1, xBeg, xEnd, width, height, 1, false, true);

	Text statement = Text();
	statement.genText(ast, 0.2, xBeg, xEnd, width, height, 0.4, false, false);

	Text mb = Text();
	mb.genText(by, 0.82, xBeg, xEnd, width, height, 0.4, false, true);

	Text choose = Text();
	std::string chooseShape ="Choose a Shape";
	choose.genText(chooseShape, 0.1, xEnd+0.3f, -2.5f+xBeg, width, height, 1, false, true);


	std::string htp = "How to Play";

	Text howToPlayT = Text();
	howToPlayT.genText(htp, 0.1, xBeg+0.20, xEnd - 0.4, width, height, 1, false, true);

	std::string instructions = "Use the W A S D keys to move your character";
	std::string instructions2 = "Click on a character with your mouse to speak    Click on doors to travel through them";

	Text instructionsBody = Text();
	instructionsBody.genText(instructions, 0.2, xBeg, xEnd, width, height, 0.4, false, false);

	Text instructionsBody2 = Text();
	instructionsBody2.genText(instructions2, 0.5, xBeg, xEnd, width, height, 0.4, false, false);

	std::string continueText = "Continue";

	Text continueT = Text();
	continueT.genText(continueText, 0.66f, 1.971f, -3.1f, width, height, 1.5f, false, true);


	BoundingBox wasdBox = BoundingBox();
	wasdBox.setUPos( - 0.65, +0.05, 300/1280.0f -0.65, 300/720.0f + 0.05);
	GLuint wasdTex = display.loadTexure("images/wasd2.png");
	Scene wasdScene = Scene(wasdTex, ctbox, wasdBox, width, height);



	//title.genText(


	bool startScreen = true;
	int storyChose = 0; //0 = no story, 1 = triangle perspective, 0 = circle perspective

	GLuint textTex = display.loadTexure("font/font.png");

	GLuint cirTex = display.loadTexure("images/circle/circle.png");
	BoundingBox cbox = BoundingBox();

	cbox.setUPos(-1, -1, 800.0f/1920 -1, 800.0f/1080 - 1);


	Scene circleCharacter = Scene(cirTex, ctbox, cbox, width, height);


	GLuint triTex = display.loadTexure("images/triangle/tri.png");
	Scene triangleCharacter = Scene(triTex, ctbox, cbox, width, height);


	triangleCharacter.pos[1] = circleCharacter.pos[1] = 0.85;

	triangleCharacter.pos[0] = circleCharacter.pos[0] = 1.05;
	triangleCharacter.pos[0] += 0.45;

	BoundingBox bbtButton = BoundingBox();
	bbtButton.setUPos(0.48, -0.13, 0.93, 0.57);
	Scene tbutton = Scene(bbtButton, width, height);

	BoundingBox bbcButton = BoundingBox();
	bbcButton.setUPos(0.48- 0.45, -0.13, 0.93 - 0.45, 0.57);
	Scene cbutton = Scene(bbcButton, width, height);



	Scene cbut = Scene(ctbox, width, height);

	BoundingBox startbutton = BoundingBox();
	startbutton.setUPos(0.24, -0.67,0.77 , -0.25);
	Scene startbut = Scene(startbutton, width, height);


	

	//Scene
	glClearColor(0.5, 0.5, 0.4, 0.5);

	float f = 1.0f;
	float fm = 0.01f;

	float acol3[4] = {0.5, 0.5, 0.4, 0.4};
	float acol2[4] = {0.5, 0.5, 0.4, 1};
	//0070ee

//	float acol[4] = {1, 1, 0.4, 1};
	float acol4[4] = {1, 1, 0.4, 1};
	//1e63b0
	float acol[4] = {0x1e/255.0f, 0x63/255.0f, 0xb0/255.0f, 0.8};
	float fullblue[4] = {0x1e/255.0f, 0x63/255.0f, 0xb0/255.0f, 1};

	bool tbutSelected = false;
	bool cbutSelected = false;

	bool doTransition = false;

	bool first = true;



	bool playingTri = false;
	bool playingCirc = false;

	bool howToPlay = false;

	bool doTransitionToGame = false;

	float famt = -0.08f;
	float ftarget = 1.0f;


	//LOCATIONS
		GLuint outsideTex = display.loadTexure("images/backgrounds/out.png");
	BoundingBox obox = BoundingBox();
	obox.setUPos(-1, -1, 1, 1);

	Scene outscene = Scene(outsideTex, ctbox, obox, width, height);

	GLuint chouseTex =  display.loadTexure("images/backgrounds/chouse.png");
	Scene chome = Scene(chouseTex, ctbox, obox, width, height);

	GLuint thouseTex =  display.loadTexure("images/backgrounds/thouse.png");

	Scene thome = Scene(thouseTex, ctbox, obox, width, height);


	GLuint thomeOpenTex = display.loadTexure("images/backgrounds/thouseopen.png");
	Scene thomeopen = Scene(thomeOpenTex, ctbox, obox, width, height);

	GLuint chomeOpenTex = display.loadTexure("images/backgrounds/chouseopen.png");
	Scene chomeopen = Scene(chomeOpenTex, ctbox, obox, width, height);

	GLuint toutopenTex = display.loadTexure("images/backgrounds/outtopen.png");
	GLuint coutopenTex = display.loadTexure("images/backgrounds/outcopen.png");

	Scene toutopen = Scene(toutopenTex, ctbox, obox, width, height);
	Scene coutopen = Scene(coutopenTex, ctbox, obox, width, height);

	//END LOCATIONS



	//CHARACTERS
				//		triangleWife.pos[0] = 1.3;
				//	triangleWife.pos[1] = 0.75;
	BoundingBox twbox = BoundingBox();
	twbox.setUPos(-1 + 1.3, -1 + 0.75, 800.0f/1920 -1 + 1.3, 800.0f/1080 - 1 + 0.75);
	GLuint triWifeTex = display.loadTexure("images/triangle/triwife.png");
	Scene triangleWife = Scene(triWifeTex, ctbox, twbox, width, height);

	BoundingBox cwbox = BoundingBox();
	cwbox.setUPos(-1 + 1.3, -1 + 0.75, 800.0f/1920 -1 + 1.3, 800.0f/1080 - 1 + 0.75);
	GLuint circWifeTex = display.loadTexure("images/circle/circwife.png");
	Scene circleWife = Scene(circWifeTex, ctbox, cwbox, width, height);

	BoundingBox b = BoundingBox();
	b.setUPos(0,  -0.6f, 150.0f/1280.0f, 150.0f/720.0f - 0.6f);

	Scene staticCChar = Scene(cirTex, ctbox, b, width, height);

	BoundingBox cb = BoundingBox();
	cb.setUPos(0 -0.5f,  -0.7f, 150.0f/1280.0f -0.5f, 150.0f/720.0f - 0.7f);

	Scene staticTChar = Scene(triTex, ctbox, cb, width, height);
	//END CHARACTERS



	//CONVERSATION STUFF
	float black[4] = {0, 0, 0, 1};

	bool inConversation = false;

	BoundingBox convBarsTop = BoundingBox();
	convBarsTop.setUPos(-1, 0.75,1, 1);
	Scene cbarTop = Scene(convBarsTop, width, height);

	BoundingBox convBarsBot = BoundingBox();
	convBarsBot.setUPos(-1, -1,1, -0.3);
	Scene cbarBot = Scene(convBarsBot, width, height);



	//END CONVERSATION STUFF

	//LOCATION STUFF
	int location = 0;  //0 = house, 1 = outside;

	BoundingBox triDoorInside = BoundingBox();
	triDoorInside.setUPos(-0.2, 0, 0.2, 0.5);
	Scene tdiScene = Scene(triDoorInside, width, height);

	BoundingBox triDoorOutside = BoundingBox();
	triDoorOutside.setUPos( - 0.7, 0-0.7, 0.3-0.9, 0.3-0.7);
	Scene tdoScene = Scene(triDoorOutside, width, height);


	BoundingBox circDoorInside = BoundingBox();
	circDoorInside.setUPos(-0.2-0.8, 0-0.2, 0.2-0.7, 0.5+0.2);
	Scene cdiScene = Scene(circDoorInside, width, height);

	BoundingBox circDoorOutside = BoundingBox();
	circDoorOutside.setUPos(-0.2+0.47, -0.55, 0.2+0.23, 0.2-0.55);
	Scene cdoScene = Scene(circDoorOutside, width, height);

	//////////////Used when playing circ
	float xStaticTriPos = 0;
	float yStaticTriPos = 0;

	float xStaticCircWifePos = 0;
	float yStaticCircWifePos = 0;
	///////////////

	///////////////Used when playing tri
	float xStaticCircPos = 0;
	float yStaticCircPos = 0;

	float xStaticTriWifePos = 0;
	float yStaticTriWifePos = 0;
	///////////////

	float oldPosX = 0;
	float oldPosY = 0;

	Story circleStory = Story("dialogue/cir.txt");
	Story triStory = Story("dialogue/tri.txt");



	std::vector<Dialogue> currentDialogue;
	Text text = Text();
	//END LOCATION STUFF

	Scene* currentS = &outscene;
	Scene* targetS;

	Scene* talkingTo;

	int dialogueWith = 0; //0 = wife, 1 = neighbor
	bool wdover = false; //wife dialogue over
	bool ndover = false; //neightbor dialogue over
	bool gameOver = false;
	bool dialogueEnded = false;
	
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();


		if(gameOver)
		{
				triangleCharacter.pos[1] = circleCharacter.pos[1] = 0.85;

	triangleCharacter.pos[0] = circleCharacter.pos[0] = 1.05;
	triangleCharacter.pos[0] += 0.45;

			circleStory.state = 0;
			triStory.state = 0;
			f = 1.0f;
			startScreen = true;

			 wdover = false; //wife dialogue over
			 ndover = false; //neightbor dialogue over
			 gameOver = false;
			 dialogueEnded = false;
			currentS = &outscene;
			howToPlay = false;
			cbutSelected = false;
			tbutSelected = false;
			first = true;
				 xStaticTriPos = 0;
	 yStaticTriPos = 0;

	 xStaticCircWifePos = 0;
	 yStaticCircWifePos = 0;
	///////////////

	///////////////Used when playing tri
	 xStaticCircPos = 0;
	 yStaticCircPos = 0;

	 xStaticTriWifePos = 0;
	 yStaticTriWifePos = 0;
	///////////////

	 oldPosX = 0;
	 oldPosY = 0;

	 location = 0;
	  inConversation = false;
		}

		/*
		int selection = text.contains(input.getMouseX(), input.getMouseY());
		if(selection == 0)
		{
			selection = -1;
		}
		
		if(input.clicked() && (selection != -1))
		{
			s.respond(selection);
			d = s.getDialogue();

			

			//text = Text();
			text.genText(d, 0.3f, 0.5f, width, height, 0.33f, true, true);
		}
		input.resetClickedState();
		*/
		/*


		act on events


		*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//if
	//	f -= fm;
		/*
		if(f < 0.9)
		{
			f = 0.95;
			fm *= -1;
		}
		if(f > 1)
		{
			f = 1;
			fm *= -1;
		}

		*/
		if(startScreen)
		{
			if(doTransition)
			{
				display.renderFadeScene(*currentS, *targetS, fadeprog, f, 1);
				f -= 0.08;
				if(f < 0)
				{
					doTransition = false;
					currentS = targetS;
				}
			}
			else
			{
				display.renderScene(*currentS, blurprog);
			}
		}
		else
		{
			if(doTransition)
			{
				display.renderFadeScene(*currentS, *targetS, fadeprog, f, f);
				f += famt;
				if(ftarget < 0.5f)
				{
					if(f < ftarget)
					{
						doTransition = false;
						currentS = targetS;
					}
				}
				else
				{
					if(f > ftarget)
					{
						doTransition = false;
						currentS = targetS;
					}
				}
			}
			else if (ftarget > 0.5f)
			{
				display.renderScene(*currentS, blurprog);
			}
			else
			{
				display.renderScene(*currentS, charprog);
			}
		}
		
		
		//std::cout << f << std::endl;
		//display.renderFadeScene(outscene, outscene, fadeprog, 1, 1);

		

		//triangleCharacter.pos[1] += 0.001f;

		if(startScreen)
		{
		//	display.renderScene(outscene, blurprog);

			if(!howToPlay)
			{
				display.renderText(title, NULL, NULL, -2, guiprog, textprog,textTex);
				display.renderText(statement, NULL, NULL, -2, guiprog, textprog,textTex);
				display.renderText(mb, NULL, NULL, -2, guiprog, textprog,textTex);
				display.renderText(choose, NULL, NULL, -2, guiprog, textprog, textTex);
			}
			else
			{
				display.renderText(howToPlayT, NULL, NULL, -2, guiprog, textprog,textTex);
				display.renderText(instructionsBody, NULL, NULL, -2, guiprog, textprog,textTex);
				display.renderText(instructionsBody2, NULL, NULL, -2, guiprog, textprog,textTex);
				display.renderScene(wasdScene, charprog);
			}
			


			int cbs = cbutton.contains(input.getMouseX(), input.getMouseY());
			int tbs = tbutton.contains(input.getMouseX(), input.getMouseY());
			if(!howToPlay)
			{
				if(cbs == 0 && input.clicked() && !cbutSelected)
				{
					cbutSelected = true;
					tbutSelected = false;

					f = 1.0f;
					targetS = &chome;

					if(!first)
					{
						currentS = &thome;
					}

					if(doTransition && !first)
					{
						//f = 1.0 - f;
					}
					else
					{
						f = 1.0f;
					}

					doTransition = true;
					first = false;
				}

				if(tbs == 0 && input.clicked() && !tbutSelected)
				{
					cbutSelected = false;
					tbutSelected = true;

				
					targetS = &thome;

					if(!first)
					{
						currentS = &chome;
					}

					if(doTransition && !first)
					{
						f = 1.0 - f;
					}
					else
					{
						f = 1.0f;
					}

					doTransition = true;

					first = false;
				}
			}

			if(cbutSelected)
			{
				display.renderButton(cbutton.getVAO(), 12, butprog, acol);
			}
			else if(cbs == 0 && !howToPlay)
			{
				display.renderButton(cbutton.getVAO(), 12, butprog, acol2);
			}
			else
			{
				display.renderButton(cbutton.getVAO(), 12, butprog, acol3);
			}

			if(tbutSelected)
			{
				display.renderButton(tbutton.getVAO(), 12, butprog, acol);
			}
			else if(tbs == 0 && !howToPlay)
			{
				display.renderButton(tbutton.getVAO(), 12, butprog, acol2);
			}
			else
			{
				display.renderButton(tbutton.getVAO(), 12, butprog, acol3);
			}

		//	display.renderButton(tbutton.getVAO(), 12, butprog, acol);

			display.renderScene(circleCharacter, charprog);
			display.renderScene(triangleCharacter, charprog);

			bool smouse = 0 == startbut.contains(input.getMouseX(), input.getMouseY());

			if(tbutSelected || cbutSelected)
			{
				if(smouse)
				{
					display.renderButton(startbut.getVAO(), 12, butprog, fullblue);
				}
				else
				{
				display.renderButton(startbut.getVAO(), 12, butprog, acol);
				}
			}
			else
			{
				display.renderButton(startbut.getVAO(), 12, butprog, acol3);
			}

	

			if(smouse && input.clicked() && (tbutSelected || cbutSelected))
			{
				//startScreen = false;
				if(!howToPlay)
				{
					howToPlay = true;
					playingTri = tbutSelected;
					playingCirc = cbutSelected;
				}
				else
				{
					startScreen = false;
					doTransitionToGame = true;
					doTransition = true;
				}
			}

			if(howToPlay)
			{
				display.renderText(continueT, NULL, NULL, -2, guiprog, textprog, textTex);
			}
			else
			{
				display.renderText(play, NULL, NULL, -2, guiprog, textprog, textTex);
			}

		}
		if(!startScreen)
		{
			if(playingCirc)//////////////////////////////////////////////WORKING ON////////////////////////////
			{
				if(!inConversation)
				{
					circleCharacter.pos[0] -= input.getX();

					circleCharacter.pos[1] -= input.getY();

					if(location == 0)
					{
						if(circleCharacter.pos[0] > 1.6)
						{
							circleCharacter.pos[0] =1.6 ;
						}

						if(circleCharacter.pos[0] < -0.0)
						{
							circleCharacter.pos[0] =-0.0 ;
						}

						if(circleCharacter.pos[1] > 0.2)
						{
							circleCharacter.pos[1] =0.2 ;
						}

						if(circleCharacter.pos[1] < -0.1)
						{
							circleCharacter.pos[1] =-0.1 ;
						}
					}
					else
					{
						if(circleCharacter.pos[0] > 2.8)
						{
							circleCharacter.pos[0] =2.8 ;
						}

						if(circleCharacter.pos[0] < -1.9)
						{
							circleCharacter.pos[0] =-1.9 ;
						}

						if(circleCharacter.pos[1] > -1.4)
						{
							circleCharacter.pos[1] = -1.4 ;
						}

						if(circleCharacter.pos[1] < -1.9)
						{
							circleCharacter.pos[1] =-1.9 ;
						}
					}
				}

				if(doTransitionToGame)
				{
					//inConversation = true;

					doTransitionToGame = false;
					targetS = currentS = &chome;
					f = 1.0f;
					ftarget = 0.0f;
					famt = -0.08f;

					circleCharacter.pos[0] -= 0.4;
					circleCharacter.pos[1] -= 0.9;

				}


				if(inConversation)
				{
					display.renderButton(cbarTop.getVAO(), 12, butprog, black);
					display.renderButton(cbarBot.getVAO(), 12, butprog, black);

					if(!wdover && !ndover)
					{
						currentDialogue = circleStory.getDialogue();
						text.genText(currentDialogue, 0.03f, 0.7f, width, height, 0.33f, true, true);
					}

						int selection = text.contains(input.getMouseX(), input.getMouseY());
						if(selection == 0)
						{
							selection = -1;
						}
		
						if(input.clicked() && (selection != -1))
						{
							if(circleStory.state == 0)
							{
								wdover = true;
								inConversation = false;
								doTransition = true;
								targetS = currentS;
								f = 1.0f;
								ftarget = 0.0f;
								famt = -0.08f;
								dialogueEnded = true;
							}

							circleStory.respond(selection);
							currentDialogue = circleStory.getDialogue();

							if(currentDialogue[1].newState == 0)
							{
								ndover = true;
								wdover = false;

								inConversation = false;
								doTransition = true;
								targetS = currentS;
								f = 1.0f;
								ftarget = 0.0f;
								famt = -0.08f;
								dialogueEnded = true;
							}
			

							//text = Text();
							text.genText(currentDialogue, 0.03f, 0.7f, width, height, 0.33f, true, true);
						
						}

						display.renderText(text, NULL, NULL, selection, guiprog, textprog, textTex);

						display.renderScene(circleCharacter, charprog);
						display.renderScene(*talkingTo, charprog);

						//////////////////////
						if(circleStory.state == 0 && ndover)
						{
							gameOver = true;
							dialogueEnded = true;

							dialogueEnded = false;
							circleWife.scale = 1;
							circleWife.pos[0] = 0; //must find correct pos;
							circleWife.pos[1] = 0;
							circleCharacter.scale = 1;
							circleCharacter.pos[0] = xStaticTriPos;
							circleCharacter.pos[1] = yStaticTriPos;
						}
						////////////////////////

				}
				
				if(!doTransition && !inConversation)
				{
					if(location == 0)
					{
						if(dialogueEnded)
						{
							dialogueEnded = false;
							circleWife.scale = 1;
							circleWife.pos[0] = 0; //must find correct pos;
							circleWife.pos[1] = 0;
							circleCharacter.scale = 1;
							circleCharacter.pos[0] = xStaticTriPos;
							circleCharacter.pos[1] = yStaticTriPos;
						}

						display.renderScene(circleWife, charprog);
						display.renderScene(circleCharacter, charprog);

						//float x = (input.getMouseX() - width/2.0f)/ (width/2.0f);

						if(cdiScene.contains(input.getMouseX(), input.getMouseY() ))  
						{
							currentS = &chome;
						}
						else
						{

							currentS = &chomeopen;
							if(input.clicked())
							{
								if(circleStory.state == 0)
								{
									circleStory.respond(1); //move to the circles part of the story
								}
								circleCharacter.scale = 0.3f;
								location = 1;
								currentS = &outscene;
								circleCharacter.pos[0] = 1.9;
								circleCharacter.pos[1] = -1;
							}
						}



						if(circleWife.contains(input.getMouseX(), input.getMouseY()) == 0 && input.clicked())
						{
							if(!wdover)
							{
								talkingTo = &circleWife;
								inConversation = true;
								xStaticTriPos = circleCharacter.pos[0];
								yStaticTriPos = circleCharacter.pos[1];

								circleWife.pos[0] = -0.899; //must find correct pos;
								circleWife.pos[1] = 0.02;
								circleWife.scale = 1.6;

								circleCharacter.pos[0] = 1.19;
								circleCharacter.pos[1] = 0.78;
								circleCharacter.scale = 1.5;

								doTransition = true;
								targetS = currentS;
								f = 0.0;
								ftarget = 1.0f;
								famt = 0.08f;
							}
						}
					}
					else
					{

						if(dialogueEnded)
						{
							dialogueEnded = false; //CURRENT EDITING SPOT ???????????????????????????????????????????????
							staticTChar.scale = 1.0f;
							staticTChar.pos[0] = 0; //must find correct pos;
							staticTChar.pos[1] = 0;
							circleCharacter.scale = 0.3;
							circleCharacter.pos[0] = xStaticTriPos;
							circleCharacter.pos[1] = yStaticTriPos;
						}

						display.renderScene(staticTChar, charprog);
						display.renderScene(circleCharacter, charprog);

						if(cdoScene.contains(input.getMouseX(), input.getMouseY() ))
						{
							currentS = &outscene;
						}
						else
						{

							currentS = &coutopen;
							if(input.clicked())
							{

								if(!wdover && !ndover)
								{
									circleStory.state = 0;
								}

								circleCharacter.scale = 1.0f;
								location = 0;
								currentS = &chome;
								circleCharacter.pos[0] = -1.5;
								circleCharacter.pos[1] = 2;
							}
						}

						if(staticTChar.contains(input.getMouseX(), input.getMouseY()) == 0 && input.clicked())
						{
						
							if(!ndover)
							{
								talkingTo = &staticTChar;
								inConversation = true;
								xStaticTriPos = circleCharacter.pos[0];
								yStaticTriPos = circleCharacter.pos[1];

								staticTChar.pos[0] = -0.17 + 0.5; //must find correct pos;
								staticTChar.pos[1] = 0.52 + 0.1;
								staticTChar.scale = 5.5;

								circleCharacter.pos[0] = 1.19;
								circleCharacter.pos[1] = 0.78;
								circleCharacter.scale = 1.5;

								doTransition = true;
								targetS = currentS;
								f = 0.0;
								ftarget = 1.0f;
								famt = 0.08f;
							}
						}
					}
				}

			}
			else if(playingTri) /////////////////////////////////////////////////////////////WORKING ON THIS???????//////////////////////////////////
			{
				if(!inConversation)
				{
					triangleCharacter.pos[0] -= input.getX();

					triangleCharacter.pos[1] -= input.getY();

					if(location == 0)
					{
						if(triangleCharacter.pos[0] > 1.6)
						{
							triangleCharacter.pos[0] =1.6 ;
						}

						if(triangleCharacter.pos[0] < 0.5)
						{
							triangleCharacter.pos[0] =0.5 ;
						}

						if(triangleCharacter.pos[1] > 0.5)
						{
							triangleCharacter.pos[1] =0.5 ;
						}

						if(triangleCharacter.pos[1] < -0.3)
						{
							triangleCharacter.pos[1] =-0.3 ;
						}
					}
					else
					{
						if(triangleCharacter.pos[0] > 2.8)
						{
							triangleCharacter.pos[0] =2.8 ;
						}

						if(triangleCharacter.pos[0] < -1.9)
						{
							triangleCharacter.pos[0] =-1.9 ;
						}

						if(triangleCharacter.pos[1] > -1.4)
						{
							triangleCharacter.pos[1] = -1.4 ;
						}

						if(triangleCharacter.pos[1] < -1.9)
						{
							triangleCharacter.pos[1] =-1.9 ;
						}
					}
				}

				if(doTransitionToGame)
				{
					//inConversation = true;

					doTransitionToGame = false;
					targetS = currentS = &thome;
					f = 1.0f;
					ftarget = 0.0f;
					famt = -0.08f;

					triangleCharacter.pos[0] -= 0.4;
					triangleCharacter.pos[1] -= 0.9;

				}


				if(inConversation)
				{
					display.renderButton(cbarTop.getVAO(), 12, butprog, black);
					display.renderButton(cbarBot.getVAO(), 12, butprog, black);

					if(!wdover && !ndover)
					{
						currentDialogue = triStory.getDialogue();
						text.genText(currentDialogue, 0.03f, 0.7f, width, height, 0.33f, true, true);
					}

						int selection = text.contains(input.getMouseX(), input.getMouseY());
						if(selection == 0)
						{
							selection = -1;
						}
		
						if(input.clicked() && (selection != -1))
						{
							if(triStory.state == 0)
							{
								wdover = true;
								inConversation = false;
								doTransition = true;
								targetS = currentS;
								f = 1.0f;
								ftarget = 0.0f;
								famt = -0.08f;
								dialogueEnded = true;
							}

							triStory.respond(selection);
							currentDialogue = triStory.getDialogue();

							if(currentDialogue[1].newState == 0)
							{
								ndover = true;
								wdover = false;

								inConversation = false;
								doTransition = true;
								targetS = currentS;
								f = 1.0f;
								ftarget = 0.0f;
								famt = -0.08f;
								dialogueEnded = true;
							}
			

							//text = Text();
							text.genText(currentDialogue, 0.03f, 0.7f, width, height, 0.33f, true, true);
						
						}
						display.renderText(text, NULL, NULL, selection, guiprog, textprog, textTex);

						display.renderScene(triangleCharacter, charprog);
						display.renderScene(*talkingTo, charprog);

						//////////////////////
						if(triStory.state == 0 && ndover)
						{
							gameOver = true;
							dialogueEnded = true;

							dialogueEnded = false;
							triangleWife.scale = 1;
							triangleWife.pos[0] = 0; //must find correct pos;
							triangleWife.pos[1] = 0;
							triangleCharacter.scale = 1;
							triangleCharacter.pos[0] = xStaticTriPos;
							triangleCharacter.pos[1] = yStaticTriPos;
						}
						////////////////////////

				}
				
				if(!doTransition && !inConversation)
				{
					if(location == 0)
					{
						if(dialogueEnded)
						{
							dialogueEnded = false;
							triangleWife.scale = 1;
							triangleWife.pos[0] = 0; //must find correct pos;
							triangleWife.pos[1] = 0;
							triangleCharacter.scale = 1;
							triangleCharacter.pos[0] = xStaticTriPos;
							triangleCharacter.pos[1] = yStaticTriPos;
						}

						display.renderScene(triangleWife, charprog);
						display.renderScene(triangleCharacter, charprog);

						//float x = (input.getMouseX() - width/2.0f)/ (width/2.0f);

						if(tdiScene.contains(input.getMouseX(), input.getMouseY() ))
						{
							currentS = &thome;
						}
						else
						{

							currentS = &thomeopen;
							if(input.clicked())
							{
								if(triStory.state == 0)
								{
									triStory.respond(1); //move to the circles part of the story
								}
								triangleCharacter.scale = 0.3f;
								location = 1;
								currentS = &outscene;
								triangleCharacter.pos[0] = -1.5;
								triangleCharacter.pos[1] = -1;
							}
						}



						if(triangleWife.contains(input.getMouseX(), input.getMouseY()) == 0 && input.clicked())
						{
							if(!wdover)
							{
								talkingTo = &triangleWife;
								inConversation = true;
								xStaticTriPos = triangleCharacter.pos[0];
								yStaticTriPos = triangleCharacter.pos[1];

								triangleWife.pos[0] = -0.8; //must find correct pos;
								triangleWife.pos[1] = 0;
								triangleWife.scale = 2;

								triangleCharacter.pos[0] = 1.05;
								triangleCharacter.pos[1] = 0.65;
								triangleCharacter.scale = 2;

								doTransition = true;
								targetS = currentS;
								f = 0.0;
								ftarget = 1.0f;
								famt = 0.08f;
							}
						}
					}
					else
					{

						if(dialogueEnded)
						{
							dialogueEnded = false;
							staticCChar.scale = 1.0f;
							staticCChar.pos[0] = 0; //must find correct pos;
							staticCChar.pos[1] = 0;
							triangleCharacter.scale = 0.3;
							triangleCharacter.pos[0] = xStaticTriPos;
							triangleCharacter.pos[1] = yStaticTriPos;
						}

						display.renderScene(staticCChar, charprog);
						display.renderScene(triangleCharacter, charprog);

						if(tdoScene.contains(input.getMouseX(), input.getMouseY() ))
						{
							currentS = &outscene;
						}
						else
						{

							currentS = &toutopen;
							if(input.clicked())
							{

								if(!wdover && !ndover)
								{
									triStory.state = 0;
								}

								triangleCharacter.scale = 1.0f;
								location = 0;
								currentS = &thome;
								triangleCharacter.pos[0] = -1.5;
								triangleCharacter.pos[1] = 2;
							}
						}

						if(staticCChar.contains(input.getMouseX(), input.getMouseY()) == 0 && input.clicked())
						{
						
							if(!ndover)
							{
								talkingTo = &staticCChar;
								inConversation = true;
								xStaticTriPos = triangleCharacter.pos[0];
								yStaticTriPos = triangleCharacter.pos[1];

								staticCChar.pos[0] = -0.16; //must find correct pos;
								staticCChar.pos[1] = 0.54;
								staticCChar.scale = 5.5;

								triangleCharacter.pos[0] = 1.05;
								triangleCharacter.pos[1] = 0.65;
								triangleCharacter.scale = 2;

								doTransition = true;
								targetS = currentS;
								f = 0.0;
								ftarget = 1.0f;
								famt = 0.08f;
							}
						}
					}
				}

				/*
				if(doConvTransition)
				{

				}
				*/



			}
		}


		




		//display.render(text, NULL, NULL, selection, guiprog, textprog);
		/*
		if(cbut.contains(input.getMouseX(), input.getMouseY()))
		{
			display.renderButton(cbut.getVAO(), 12,butprog, acol);
		}
		else
		{
			
			display.renderButton(cbut.getVAO(), 12, butprog, acol2);
		}
		*/
		input.resetClickedState();
		glfwSwapBuffers(window);
	}
}

//just an idea
void render(Text& text, float* sColor, float* rColor, int active, GLuint guiShader, GLuint textShader)
{
	int guiuloc = glGetUniformLocation(guiShader, "active");
	glUseProgram(guiShader);
	glUniform1i(guiuloc, active);
	glBindVertexArray(text.getBoxVAO());
	glDrawArrays(GL_TRIANGLES, 0, text.getNumBoxVerts());

	glUseProgram(textShader);
	glBindVertexArray(text.getTextVAO());
	glDrawArrays(GL_TRIANGLES, 0, text.getNumTextVerts());
}


Game::~Game(void)
{
	glfwTerminate();
}

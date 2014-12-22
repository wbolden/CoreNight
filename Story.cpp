#include "Story.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

Story::Story(void)
{
	state = 0;
}

Story::Story(const char* file)
{
	state = 0;
	loadDialogue(file);
}

bool Story::loadDialogue(const char* file)
{
	std::ifstream dialogueFile;
	dialogueFile.open(file);

	if(!dialogueFile.is_open())
	{
		return false;
	}

	int stateIndex = -1; 
	//int dialogueIndex = 0;

	while(!dialogueFile.eof())
	{
		int i;
		std::string dialogueString = "";

		dialogueFile >> i;

		if(i > -1)
		{
			stateIndex++;

			std::vector<Dialogue> dialogues;
			std::getline(dialogueFile, dialogueString);

			dialogues.push_back(Dialogue(dialogueString, i));

			dialogueTree.push_back(dialogues);
		}
		else
		{
			int newState;

			//while(! dialogueFile >> newState)
			bool intFound = false;

			std::string word;

			while(!intFound)
			{
				dialogueFile >> word;

				if(std::isdigit(word[0]))
				{
					newState = std::atoi(word.data());
					intFound = true;
				}
				else
				{
					dialogueString += word;
					dialogueString += " ";
				}
			}



			dialogueTree[stateIndex].push_back(Dialogue(dialogueString, newState));
		}


	}
	dialogueFile.close();

	return true;
}

std::vector<Dialogue>& Story::getDialogue()
{
	return dialogueTree[state];
}

bool Story::respond(int response)
{
	if(response < dialogueTree[state].size())
	{
		state = dialogueTree[state][response].newState;
		return true;
	}
	else
	{
		return false;
	}
}


Story::~Story(void)
{
}

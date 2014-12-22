#pragma once

#include <vector>

struct Dialogue
{
	Dialogue(std::string& dialogue, int state)
	{
		this->dialogue = dialogue;
		newState = state;
	}

	Dialogue(const char* dialogue, int state)
	{
		this->dialogue = dialogue;
		newState = state;
	}

	std::string dialogue;
	int newState;
};

class Story
{
public:
	Story(void);
	Story(const char* file);

	bool loadDialogue(const char* file);

	/*
		Returns the dialogue for the current state
		The first Dialogue is the prompt
		The proceeding Dialogues are the possible responses
	*/
	std::vector<Dialogue>& getDialogue(); 

	/*
		Changes the state to change to the newState of the dialogue pointed to by the response
		A response of 0 will not change the state
	*/
	bool respond(int response);

	~Story(void);
	int state;

private:
	std::vector<std::vector<Dialogue>> dialogueTree;
	
};


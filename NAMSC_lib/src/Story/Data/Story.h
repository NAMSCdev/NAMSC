#pragma once
#include "Global.h"

#include "Story/Data/Save/StoryState.h"

class Scene;
class Chapter;
class Voice;
class Scerey;
class SceneryObject;	
class Character;

class MainMenuTheme;

//TODO: add the rest of the load fuctions
//Represents entire story that will be played
class Story
{
public:
	Story() = default;

	//TODO: move to .cpp
	std::vector<Scene*>					removeScene			(int id);
	/*
	{
		std::vector<Scene*>	affectedScenes;
		if (id < 0u || id > scenes.size())
			throw CriticalErr("Story doesn't contain a scene with id " + std::to_string(id), __func__, __FILE__, __LINE__); 
		//Mark every jump done to the removed Scene as invalid
		for (Chapter &chapter : chapters)
			for (Scene &scene : chapter.scenes)
				for (Action &events : scene.events)
					if (action.type == ActionType::Jump)
					{
						ActionJump &jump = dynamic_cast<ActionJump>(action);
						if (jump.destination == id)
							jump.destination = ActionJump::JUMP_INVALID;
						affectedScenes.push_back(&scene);
					}
					//TODO: Choices too
					//else if
		return affectedScenes;
	}*/

	//Adds Chapter
	//Should be used only in the editor
	static void							addChapter			(Chapter &&chapter)		{ chapters.push_back(move(chapter)); }

	static void							removeChapter		(Chapter &&chapter)		{ chapters.push_back(move(chapter)); }

	//Creates new Story State and loads it into the saveslot
	static void							newState			(unsigned slot);

	//Loads player's StoryState from a savefile in given saveslot
	static void							loadState			(unsigned slot);
	
	//Saves player's StoryState to a savefile in given saveslot
	static void							saveState			(unsigned slot);

	//Loads entire Story from multiple files
	static void							loadStory			()						{ StorySettings::load(); loadAssets(); loadVoices(); loadSceneryObjects(); loadCharacters(); loadChapters(); }

private:
	//Loads Assets definitions (not its resources) from a single file
	static inline void					loadAssets			();

	//Loads Voices from a single file
	static inline void					loadVoices			();

	//Loads SceneryObject definitions (not its resources) from a single file
	static inline void					loadSceneryObjects	();

	//Loads Character definitions (not its resources) from a single file
	static inline void					loadCharacters		();


	//Loads Chapters definitions (not its resources) from a single file
	static inline void					loadChapters		();

	//Loads Chapter resources
	static inline void					loadChapterResources(QString chapterName);

	//TODO: move to StoryState?
	//Loads Stats from a single file
	static inline void					loadStats			();

	//TODO: fix places where Voice links are named URIS, not names
	//Contains all Voices, which contain all the Scenes in the Story
	static std::vector<Voice>			voices;

	//TODO: fix places where Voice links are named URIS, not names
	//Contains all Chapter, which contain all the Scenes in the Story
	static std::vector<SceneryObject>	sceneryObjects;

	//TODO: fix places where Character links are named URIS, not names
	//Contains all Chapter, which contain all the Scenes in the Story
	static std::vector<Character>		character;

	//TODO: fix places where Chapter links are named URIS, not names
	//Contains all Chapter, which contain all the Scenes in the Story
	static std::vector<Chapter>			chapters;

	//Current StoryState containing all the player progression
	static StoryState					save;
};
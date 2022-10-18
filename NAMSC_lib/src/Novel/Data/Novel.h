#pragma once
#include "Global.h"

#include "Novel/Data/Save/NovelState.h"

class Chapter;
class Voice;
class SceneryObject;	
class Character;

///The entire Visual Novel
///**Singleton**
class Novel
{
public:
	static Novel& getInstance()
	{
		static Novel instance;
		return instance;
	}

	Novel() { logFile.open(QIODevice::WriteOnly | QIODevice::Truncate); };
	Novel(Novel const&)				= delete;
	void operator=(Novel const&)	= delete;

	///TODO: move to Chapter .cpp
	QVector<Scene*>	removeScene(int id);
	/*
	{
		QVector<Scene*>	affectedScenes;
		if (id < 0u || id > scenes.size())
			throw CriticalErr("Novel doesn't contain a scene with id " + std::to_string(id), __func__, __FILE__, __LINE__); 
		///Mark every jump done to the removed Scene as invalid
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
			///TODO: Choices too
			///else if
		return affectedScenes;
	}*/

	///Adds Chapter
	///Should be used only in the Editor
	void addChapter(Chapter &&chapter)			{ chapters.push_back(move(chapter)); }

	void removeChapter(Chapter &&chapter)		{ chapters.push_back(move(chapter)); }

	void nextScene();

	///Creates new Novel State and loads it into the saveslot
	void newState(uint slot)
	{
		save.;
	}

	///Loads player's NovelState from a savefile in given saveslot
	bool loadState(uint slot);
	
	///Saves player's NovelState to a savefile in given saveslot
	void saveState(uint slot);

	///Loads entire Novel from multiple files
	void loadNovel(uint slot, bool createNew)
	{ 
		NovelSettings::load(); 
		if (createNew || !save.load(slot))
			save.createNew(slot);
		loadAssetsDefs(); 
		loadVoices(); loadSceneryObjectsDefs(); loadCharacters(); 
		loadChapterDefs(); 
	}
	
	///Allows to access a Voice from the Voices array
	Voice*			findVoice(const QString &voiceName); 

	///Allows to access a SceneryObject from the SceneryObjects array
	SceneryObject*	findSceneryObject(const QString &sceneryObjectName); 

	///Allows to access a Character from the Characters array
	Character*		findCharacter(const QString &characterName); { return findInArray(characterName, characters); }

	///Allows to access characterName
	///@todo: ensure everywhere a reference to Voice is name voiceName, not voiceName
	Chapter*		findChapter(const QString &chapterName); 

	///Allows to access Voices
	///@todo: ensure everywhere a reference to Voice is name voiceName, not voiceName
	NovelState*		getNovelState();

private:
	///Loads Assets definitions (not its resources) from a single file
	inline void	loadAssetsDefs();

	///Loads Voices from a single file
	inline void	loadVoices();

	///Loads SceneryObject definitions (not its resources) from a single file
	inline void	loadSceneryObjectsDefs();

	///Loads Character definitions (not its resources) from a single file
	inline void	loadCharacters();

	///Loads Chapters definitions (not its resources) from a single file
	inline void	loadChapterDefs();

	///Loads Chapter resources
	inline void	loadChapterResources(QString chapterName);

	///TODO: move to NovelState?
	///Loads Stats from a single file
	inline void	loadStats();

	///Contains all available Voices
	QVector<Voice> voices;

	///Contains all available sceneryObjects
	QVector<SceneryObject> sceneryObjects;

	///Contains all available Characters
	QVector<Character> characters;

	///Contains all available Chapters, which contain all the Scenes in the Novel
	QVector<Chapter> chapters;

	///Current NovelState containing the player's progression
	NovelState save;

	///Currently displayed media of the Scene
	Scenery scenery;
};
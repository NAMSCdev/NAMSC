#include "pvnLib/Novel/Action/Visual/ActionCharacter.h"

#include "pvnLib/Novel/Data/Save/NovelState.h"
#include "pvnLib/Novel/Data/Scene.h"

ActionCharacter::~ActionCharacter() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionCharacter& first, ActionCharacter& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<Action&>(first), static_cast<Action&>(second));
	swap(first.characterName_, second.characterName_);
	swap(first.character_,     second.character_);
}

ActionCharacter::ActionCharacter(Event* const parentEvent, const QString& characterName, Character* character)
	: Action(parentEvent),
	characterName_(characterName), 
	character_(character)
{
}

bool ActionCharacter::operator==(const ActionCharacter& obj) const noexcept
{
	if (this == &obj) return true;

	return characterName_ == obj.characterName_;// &&
		   //character_     == obj.character_;
}

void ActionCharacter::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> characterName_;
}

void ActionCharacter::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << characterName_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

QString ActionCharacter::getCharacterName() const noexcept
{
	return characterName_;
}

const Character* ActionCharacter::getCharacter() const noexcept
{
	return character_;
}

Character* ActionCharacter::getCharacter() noexcept
{
	return character_;
}

void ActionCharacter::setCharacter(const QString& characterName, Character* character) noexcept
{
	if (character)
	{
		if (character->name != characterName)
		{
			qCritical() << NovelLib::ErrorType::CharacterInvalid << "Character's name missmatch (characterName=\"" + characterName + "\", character->name=\"" + character->name + "\")";
			return;
		}
	}
	
	if (parentEvent->parentScene->scenery.getDisplayedCharacter(characterName_) == nullptr)
		qCritical() << NovelLib::ErrorType::CharacterMissing << "Character \"" + characterName + "\" does not exist";
	characterName_ = characterName_;
	errorCheck(true);
}
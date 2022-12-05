#include "Novel/Action/Visual/ActionCharacter.h"

#include "Novel/Data/Save/NovelState.h"
#include "Novel/Data/Scene.h"

ActionCharacter::ActionCharacter(Event* const parentEvent, Scene* const parentScene) noexcept
	: Action(parentEvent, parentScene)
{
}

ActionCharacter::ActionCharacter(Event* const parentEvent, Scene* const parentScene, const QString& characterName)
	: Action(parentEvent, parentScene), characterName_(characterName)
{
	///checkForErrors(true);
}

ActionCharacter& ActionCharacter::operator=(const ActionCharacter& obj) noexcept
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	characterName_ = obj.characterName_;
	character_     = obj.character_;

	return *this;
}

bool ActionCharacter::operator==(const ActionCharacter& obj) const noexcept
{
	if (this == &obj) return true;

	return	Action::operator==(obj)              &&
			characterName_ == obj.characterName_;// &&
			//character_     == obj.character_;
}

bool ActionCharacter::checkForErrors(bool bComprehensive) const
{
	bool bError = Action::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (parentScene_->scenery.getDisplayedCharacter(characterName_) == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::CharacterInvalid << "No valid Character assigned. Was it deleted and not replaced?";
			if (characterName_ != "")
				qCritical() << this << NovelLib::ErrorType::CharacterMissing << "Character \"" << characterName_ << "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionCharacter::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionCharacter::setCharacter(const QString& characterName) noexcept
{
	if (parentScene_->scenery.getDisplayedCharacter(characterName_) == nullptr)
		qCritical() << this << NovelLib::ErrorType::CharacterMissing << "Character \"" << characterName << "\" does not exist";
	else
	{
		characterName_ = characterName;
		checkForErrors(true);
	}
}

Character* ActionCharacter::getCharacter() noexcept 
{
	return character_; 
}

const Character* ActionCharacter::getCharacter() const noexcept
{ 
	return character_; 
}

QString ActionCharacter::getCharacterName() const noexcept
{ 
	return characterName_; 
}

void ActionCharacter::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> characterName_;
	///checkForErrors();
}

void ActionCharacter::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << characterName_;
}
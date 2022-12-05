#include "Novel/Event/Event.h"

#include "Novel/Action/ActionsAll.h"
#include "Novel/Data/Scene.h"

Event::Event(Scene* const parentScene) noexcept
	: parentScene_(parentScene)
{
}

Event::Event(Scene* const parentScene, const QString label)
	: parentScene_(parentScene), label(label)
{
	//checkForErrors(true);
}

Event::Event(Scene* const parentScene, const QString label, std::vector<std::unique_ptr<Action>>&& actions) 
	: parentScene_(parentScene), label(label), actions_(std::move(actions))
{
	//checkForErrors(true);
}

Event& Event::operator=(const Event& obj) noexcept
{
	if (this == &obj) return *this;

	label    = obj.label;
	//actions_.clear();
	//
	//for (uint i = 0; i != obj.actions_.size(); ++i)
	//	actions_,emplace_back(new Event(dnymaic_cast<Event*>(obj.actions_[i].get()))) ) //GET EVENT TYPE
	return *this;
}

bool Event::operator==(const Event& obj) const noexcept
{
	if (this == &obj) return true;

	if (label != obj.label)
		return false;

	if (actions_.size() != obj.actions_.size())
		return false;

	for (uint i = 0; i != actions_.size(); ++i)
		if (*(actions_[i]) != *(obj.actions_[i]))
			return false;

	return	true;
}

bool Event::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	for (const std::unique_ptr<Action>& action : actions_)
		bError |= action->checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (bComprehensive)
			for (auto it = parentScene_->events_.cbegin(); it != parentScene_->events_.cend(); ++it)
				if (((*it)->label == label) && ((*it).get() != this))
				{
					bError = true;
					qCritical() << this << NovelLib::ErrorType::NameDuplicate << "Duplicate labels \"" << label << "\" for Scene " << getIndex() << " and Scene " << (*it)->getIndex();
					break;
				}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	//if (bError)
	//	qDebug() << "An Error occurred in Event::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << getIndex();

	return bError;
}

uint Event::getIndex() const
{
	const std::vector<std::unique_ptr<Event>>* events = parentScene_->getEvents();
	return std::find_if(events->cbegin(), events->cend(), [&](const std::unique_ptr<Event>& obj) { return this == obj.get(); }) - events->cbegin();
}

void Event::run()
{
	ensureResourcesAreLoaded();
	for (std::unique_ptr<Action>& action : actions_)
		action->run();
}

void Event::end()
{
	for (std::unique_ptr<Action>& action : actions_)
		action->end();
}

void Event::update()
{
	for (std::unique_ptr<Action>& action : actions_)
		action->update();
}

void Event::syncWithSave() noexcept
{
	for (std::unique_ptr<Action>& action : actions_)
		action->syncWithSave();
}

void Event::ensureResourcesAreLoaded()
{
	for (std::unique_ptr<Action>& action : actions_)
		action->ensureResourcesAreLoaded();
}

void Event::serializableLoad(QDataStream& dataStream)
{
	dataStream >> label;

	uint actionsSize;
	dataStream >> actionsSize;
	for (uint i = 0u; i != actionsSize; ++i)
	{
		NovelLib::SerializationID type;
		dataStream >> type;

		Action* action;
		switch (type)
		{
		case NovelLib::SerializationID::ActionAudioSetMusic:
			action = new ActionAudioSetMusic(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionAudioSetSounds:
			action = new ActionAudioSetSounds(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionStatSetValue:
			action = new ActionStatSetValue(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimColor:
			action = new ActionSceneryObjectAnimColor(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimMove:
			action = new ActionSceneryObjectAnimMove(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimRotate:
			action = new ActionSceneryObjectAnimRotate(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimScale:
			action = new ActionSceneryObjectAnimScale(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimFade:
			action = new ActionSceneryObjectAnimFade(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionCharacterSetVoice:
			action = new ActionCharacterSetVoice(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectSetImage:
			action = new ActionSceneryObjectSetImage(this, this->parentScene_);
			break;
		case NovelLib::SerializationID::ActionSetBackground:
			action = new ActionSetBackground(this, this->parentScene_);
			break;
		default:
			qCritical() << this << NovelLib::ErrorType::General << "Invalid Action's Type " << static_cast<int>(type);
			break;
		}
		dataStream >> *action;
		actions_.emplace_back(action);
	}
}

void Event::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType() << label;
	for (const std::unique_ptr<Action>& action : actions_)
		dataStream << *action;
}
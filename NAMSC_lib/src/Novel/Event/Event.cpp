#include "Novel/Event/Event.h"

#include "Novel/Action/ActionAll.h"
#include "Novel/Data/Scene.h"
#include "Helpers.h"

Event::~Event() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Event& first, Event& second) noexcept
{
	using std::swap;
	swap(first.label,    second.label);
	swap(first.scenery,  second.scenery);
	swap(first.actions_, second.actions_);
}

Event::Event(Scene* const parentScene, const QString& label, const std::vector<std::shared_ptr<Action>>& actions)
	: parentScene(parentScene),
	label(label),
	scenery(parentScene)
{
	for (const std::shared_ptr<Action>& action : actions)
	{
		//TODO: create abstract factory for this
		Action* clone = nullptr;
		switch (action->getType())
		{
		case NovelLib::SerializationID::ActionAudioSetMusic:
			clone = new ActionAudioSetMusic(this);
			*static_cast<ActionAudioSetMusic*>(clone) = *(static_cast<ActionAudioSetMusic*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionAudioSetSounds:
			clone = new ActionAudioSetSounds(this);
			*static_cast<ActionAudioSetSounds*>(clone) = *(static_cast<ActionAudioSetSounds*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionStatSetValue:
			clone = new ActionStatSetValue(this);
			*static_cast<ActionStatSetValue*>(clone) = *(static_cast<ActionStatSetValue*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimColor:
			clone = new ActionSceneryObjectAnimColor(this);
			*static_cast<ActionSceneryObjectAnimColor*>(clone) = *(static_cast<ActionSceneryObjectAnimColor*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimMove:
			clone = new ActionSceneryObjectAnimMove(this);
			*static_cast<ActionSceneryObjectAnimMove*>(clone) = *(static_cast<ActionSceneryObjectAnimMove*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimRotate:
			clone = new ActionSceneryObjectAnimRotate(this);
			*static_cast<ActionSceneryObjectAnimRotate*>(clone) = *(static_cast<ActionSceneryObjectAnimRotate*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimScale:
			clone = new ActionSceneryObjectAnimScale(this);
			*static_cast<ActionSceneryObjectAnimScale*>(clone) = *(static_cast<ActionSceneryObjectAnimScale*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimFade:
			clone = new ActionSceneryObjectAnimFade(this);
			*static_cast<ActionSceneryObjectAnimFade*>(clone) = *(static_cast<ActionSceneryObjectAnimFade*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionCharacterSetVoice:
			clone = new ActionCharacterSetVoice(this);
			*static_cast<ActionCharacterSetVoice*>(clone) = *(static_cast<ActionCharacterSetVoice*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionSceneryObjectSetImage:
			clone = new ActionSceneryObjectSetImage(this);
			*static_cast<ActionSceneryObjectSetImage*>(clone) = *(static_cast<ActionSceneryObjectSetImage*>(action.get()));
			break;
		case NovelLib::SerializationID::ActionSetBackground:
			clone = new ActionSetBackground(this);
			*static_cast<ActionSetBackground*>(clone) = *(static_cast<ActionSetBackground*>(action.get()));
			break;
		default:
			qCritical() << NovelLib::ErrorType::General << "Invalid Action's type" << static_cast<int>(action->getType());
			continue;
			break;
		}
		actions_.emplace_back(clone);
	}
}

void Event::serializableLoad(QDataStream& dataStream)
{
	dataStream >> label >> scenery;

	size_t actionsSize;
	dataStream >> actionsSize;
	for (size_t i = 0u; i != actionsSize; ++i)
	{
		NovelLib::SerializationID type;
		dataStream >> type;

		//TODO: create abstract factory for this
		Action* action = nullptr;
		switch (type)
		{
		case NovelLib::SerializationID::ActionAudioSetMusic:
			action = new ActionAudioSetMusic(this);
			break;
		case NovelLib::SerializationID::ActionAudioSetSounds:
			action = new ActionAudioSetSounds(this);
			break;
		case NovelLib::SerializationID::ActionStatSetValue:
			action = new ActionStatSetValue(this);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimColor:
			action = new ActionSceneryObjectAnimColor(this);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimMove:
			action = new ActionSceneryObjectAnimMove(this);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimRotate:
			action = new ActionSceneryObjectAnimRotate(this);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimScale:
			action = new ActionSceneryObjectAnimScale(this);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectAnimFade:
			action = new ActionSceneryObjectAnimFade(this);
			break;
		case NovelLib::SerializationID::ActionCharacterSetVoice:
			action = new ActionCharacterSetVoice(this);
			break;
		case NovelLib::SerializationID::ActionSceneryObjectSetImage:
			action = new ActionSceneryObjectSetImage(this);
			break;
		case NovelLib::SerializationID::ActionSetBackground:
			action = new ActionSetBackground(this);
			break;
		default:
			qCritical() << NovelLib::ErrorType::General << "Invalid Action's type" << static_cast<int>(type);
			continue;
			break;
		}
		dataStream >> *action;
		actions_.emplace_back(action);
	}
}

void Event::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType() << label << scenery;
	for (const std::shared_ptr<Action>& action : actions_)
		dataStream << *action;
}

//  MEMBER_FIELD_SECTION_CHANGE END

Event::Event(Event&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

uint Event::getIndex() const
{
	const std::vector<std::shared_ptr<Event>>* events = parentScene->getEvents();
	return std::find_if(events->cbegin(), events->cend(), [this](const std::shared_ptr<Event>& obj) { return (obj && (this == obj.get())); }) - events->cbegin();
}

const std::vector<std::shared_ptr<Action>>* Event::getActions() const noexcept
{
	return &actions_;
}

const std::shared_ptr<Action> Event::getAction(uint index) const
{
	return *NovelLib::Helpers::listGet(actions_, index, "Action", NovelLib::ErrorType::ActionMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

std::shared_ptr<Action> Event::getAction(uint index)
{
	return *NovelLib::Helpers::listGet(actions_, index, "Action", NovelLib::ErrorType::ActionMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

const std::vector<std::shared_ptr<Action>>* Event::setActions(const std::vector<std::shared_ptr<Action>>& actions) noexcept
{
	return &(actions_ = std::move(actions));
}

const std::vector<std::shared_ptr<Action>>* Event::setActions(std::vector<std::shared_ptr<Action>>&& actions) noexcept
{
	return &(actions_ = std::move(actions));
}

std::shared_ptr<Action> Event::addAction(Action* action)
{
	return *NovelLib::Helpers::listAdd(actions_, std::move(std::shared_ptr<Action>(action)), "Action", NovelLib::ErrorType::ActionInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

std::shared_ptr<Action> Event::addAction(std::shared_ptr<Action>&& action)
{
	return *NovelLib::Helpers::listAdd(actions_, std::move(action), "Action", NovelLib::ErrorType::ActionInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

std::shared_ptr<Action> Event::insertAction(uint index, Action* action)
{
	return *NovelLib::Helpers::listInsert(actions_, index, std::move(std::shared_ptr<Action>(action)), "Action", NovelLib::ErrorType::ActionInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

std::shared_ptr<Action> Event::insertAction(uint index, std::shared_ptr<Action>&& action)
{
	return *NovelLib::Helpers::listInsert(actions_, index, std::move(action), "Action", NovelLib::ErrorType::ActionInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

std::shared_ptr<Action> Event::reinsertAction(uint index, uint newIndex)
{
	return *NovelLib::Helpers::listReinsert(actions_, index, newIndex, "Action", NovelLib::ErrorType::ActionMissing, NovelLib::ErrorType::ActionInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

bool Event::removeAction(uint index)
{
	return NovelLib::Helpers::listRemove(actions_, index, "Action", NovelLib::ErrorType::ActionMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

void Event::clearActions() noexcept
{
	actions_.clear();
}
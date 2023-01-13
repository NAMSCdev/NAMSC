#include "Novel/Event/Event.h"

#include "Novel/Action/ActionAll.h"
#include "Novel/Data/Scene.h"

Event::~Event() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Event& first, Event& second) noexcept
{
	using std::swap;
	swap(first.label, second.label);
	swap(first.scenery, second.scenery);
	swap(first.actions_, second.actions_);
}

Event::Event(Scene* const parentScene, const QString& label, std::vector<std::unique_ptr<Action>>&& actions)
	: parentScene(parentScene), 
	label(label), 
	actions_(std::move(actions))
{
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
			qCritical() << NovelLib::ErrorType::General << "Invalid Action's Type" << static_cast<int>(type);
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

//  MEMBER_FIELD_SECTION_CHANGE END

Event::Event(Event&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

uint Event::getIndex() const
{
	const std::vector<std::unique_ptr<Event>>* events = parentScene->getEvents();
	return std::find_if(events->cbegin(), events->cend(), [&](const std::unique_ptr<Event>& obj) { return this == obj.get(); }) - events->cbegin();
}

const std::vector<std::unique_ptr<Action>>* Event::getActions() const noexcept
{
	return &actions_;
}

const Action* Event::getAction(uint actionIndex) const
{
#define getActionBody                   \
    if (actionIndex >= actions_.size()) \
    {                                   \
        qCritical() << NovelLib::ErrorType::General << "Tried to get an Action past the `actions_` container's size (" + QString::number(actionIndex) + " >= " + QString::number(actions_.size()) + ") in an Event \"" + label + "\", Scene \"" + parentScene->name + '\"'; \
        return nullptr;                 \
    }                                   \
                                        \
    return actions_[actionIndex].get();
	getActionBody
}

Action* Event::getAction(uint actionIndex)
{
	getActionBody
#undef getActionBody
}

void Event::addAction(Action* action)
{
	actions_.emplace_back(action);
}

bool Event::insertAction(uint actionIndex, Action* action)
{
	if (actionIndex > actions_.size())
	{
		qCritical() << NovelLib::ErrorType::General << "Tried to insert a new Action past the `actions_` container's size (" + QString::number(actionIndex) + " > " + QString::number(actions_.size()) + ") in an Event \"" + label + "\", Scene \"" + parentScene->name + '\"';
		return false;
	}

	actions_.emplace(actions_.begin() + actionIndex, action);

	return true;
}

bool Event::removeAction(uint actionIndex)
{
	if (actionIndex >= actions_.size())
	{
		qCritical() << NovelLib::ErrorType::General << "Tried to remove an Action past the `actions_` container's size (" + QString::number(actionIndex) + " >= " + QString::number(actions_.size()) + ") in an Event \"" + label + "\", Scene \"" + parentScene->name + '\"';
		return false;
	}

	actions_.erase(actions_.begin() + actionIndex);

	return true;
}

void Event::clearActions() noexcept
{
	actions_.clear();
}
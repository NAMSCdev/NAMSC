#include "Novel/Data/Scene.h"

#include "Novel/Data/Novel.h"
#include "Novel/Event/EventsAll.h"

Scene::Scene(const QString& name, const QString& chapterName, const Scenery& scenery)
    : name(name), chapterName_(chapterName), scenery(scenery)
{
    chapter_ = Novel::getInstance().getChapter(chapterName_);
    checkForErrors(true);
}

Scene::Scene(const QString& label, const QString& chapterName, const Scenery& scenery, std::vector<std::unique_ptr<Event>>&& events)
	: name(name), chapterName_(chapterName), scenery(scenery), events_(std::move(events))
{
    chapter_ = Novel::getInstance().getChapter(chapterName_);
    checkForErrors(true);
}

Scene::Scene(const Scene& obj) noexcept
    : name(obj.name), 
      chapterName_(obj.chapterName_),
      chapter_(obj.chapter_),
      //events_(std::move(obj.events_)), 
      scenery(obj.scenery)
{
}

Scene& Scene::operator=(Scene obj) noexcept
{ 
    if (this == &obj) return *this;

    std::swap(this->name, obj.name);
    std::swap(this->chapterName_, obj.chapterName_);
    std::swap(this->chapter_, obj.chapter_);
    std::swap(this->scenery, obj.scenery);

    return *this; 
}

void Scene::run()
{
    const NovelState* currentState = NovelState::getCurrentlyLoadedState();
    uint eventID = currentState->eventID;

    if (eventID >= events_.size())
    {
        qCritical() << this << NovelLib::ErrorType::SaveCritical << " Tried to run an Event past the `events_` container's size (" << eventID << " >= " << events_.size() << ") in a Scene \"" << name << "\"";
        return;
    }

    events_[eventID]->run();
}

void Scene::update()
{
    const NovelState* currentState = NovelState::getCurrentlyLoadedState();
    uint eventID             = currentState->eventID;

    if (eventID >= events_.size())
    {
        qCritical() << this << NovelLib::ErrorType::SaveCritical << " Tried to update an Event past the `events_` container's size (" << eventID << " >= " << events_.size() << ") in a Scene \"" << name << "\"";
        return;
    }

    events_[eventID]->update();
}

void Scene::end()
{
    const NovelState* currentState = NovelState::getCurrentlyLoadedState();
    uint eventID             = currentState->eventID;

    if (eventID >= events_.size())
    {
        qCritical() << this << NovelLib::ErrorType::SaveCritical << " Tried to end an Event past the `events_` container's size (" << eventID << " >= " << events_.size() << ") in a Scene \"" << name << "\"";
        return;
    }

    events_[eventID]->end();
}

bool Scene::checkForErrors(bool bComprehensive) const
{
    bool bError = false;
    //static auto errorChecker = [&](bool bComprehensive)
    //{
    //};

	for (const std::unique_ptr<Event>& event : events_)
        bError |= event->checkForErrors(bComprehensive);

    //bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
    //if (bError)
    //    qDebug() << "An Error occurred in Scene::checkForErrors (object's name: \"" << name << "\")";

    return bError;
}

void Scene::ensureResourcesAreLoaded()
{
    const NovelState* currentState = NovelState::getCurrentlyLoadedState();
    uint eventID             = currentState->eventID;

    if (eventID >= events_.size())
    {
        qCritical() << this << NovelLib::ErrorType::SaveCritical << " Tried to end an Event past the `events_` container's size (" << eventID << " >= " << events_.size() << ") in a Scene \"" << name << "\"";
        return;
    }

    events_[eventID]->ensureResourcesAreLoaded();
}

QString Scene::nextFreeEventName()
{
    for (uint i = 0; i != events_.size(); ++i)
    {
        QString checked = "Event " + QString::number(i + 1);
        if (std::find_if(events_.cbegin(), events_.cend(), [&checked] (const std::unique_ptr<Event> &obj) { return obj->label == checked; }) != events_.cend())
            return checked;
    }
    return "Event " + QString::number(events_.size() + 1);
}

void Scene::syncWithSave() noexcept
{
    const NovelState* currentState = NovelState::getCurrentlyLoadedState();
    uint eventID             = currentState->eventID;

    if (eventID >= events_.size())
    {
        qCritical() << this << NovelLib::ErrorType::SaveCritical << " Tried to synchronize an Event past the `events_` container's size (" << eventID << " >= " << events_.size() << ") with the Save in the slot " << currentState->saveSlot << " in a Scene \"" << name << "\"";
        return;
    }

    events_[eventID]->syncWithSave();
}

const std::vector<std::unique_ptr<Event>>* Scene::getEvents() const noexcept
{
    return &events_;
}

const Event* Scene::getEvent(uint eventIndex) const
{
#define getEventBody                   \
    if (eventIndex >= events_.size())  \
    {                                  \
        qCritical() << this << NovelLib::ErrorType::General << "Tried to get an Event past the `events_` container's size (" << eventIndex << " >= " << events_.size() << ") in a Scene \"" << name << "\""; \
        return nullptr;                \
    }                                  \
                                       \
    return events_[eventIndex].get();
    getEventBody
}

Event* Scene::getEvent(uint eventIndex)
{
    getEventBody
#undef getEventBody
}

bool Scene::insertEvent(uint eventIndex, std::unique_ptr<Event>&& event)
{
    if (eventIndex > events_.size())
    {
        qCritical() << this << NovelLib::ErrorType::General << "Tried to insert a new Event past the `events_` container's size (" << eventIndex << " > " << events_.size() << ") in a Scene \"" << name << "\"";
        return false;
    }

    events_.insert(events_.begin() + eventIndex, std::move(event));
    
    return true;
}

bool Scene::removeEvent(uint eventIndex)
{
    if (eventIndex >= events_.size())
    {
        qCritical() << this << NovelLib::ErrorType::General << "Tried to remove an Event past the `events_` container's size (" << eventIndex << " >= " << events_.size() << ") in a Scene \"" << name << "\"";
        return false;
    }

    events_.erase(events_.begin() + eventIndex);
    
    return true;
}

void Scene::serializableLoad(QDataStream& dataStream)
{
    dataStream >> name >> chapterName_ >> scenery;
    uint size;
    dataStream >> size;
    for (uint i = 0; i != size; ++i)
    {
        Event* ev;
        NovelLib::SerializationID type;
        dataStream >> type;
        switch (type)
        {
        case NovelLib::SerializationID::EventChoice:
            ev = new EventChoice(this);
            break;
        case NovelLib::SerializationID::EventEndIf:
            ev = new EventEndIf(this);
            break;
        case NovelLib::SerializationID::EventIf:
            ev = new EventIf(this);
            break;
        case NovelLib::SerializationID::EventInput:
            ev = new EventInput(this);
            break;
        case NovelLib::SerializationID::EventJump:
            ev = new EventJump(this);
            break;
        case NovelLib::SerializationID::EventDialogue:
            ev = new EventDialogue(this);
            break;
        case NovelLib::SerializationID::EventWait:
            ev = new EventWait(this);
            break;
        default:
            qCritical() << this << NovelLib::ErrorType::Critical << "Could not find a Stat's type: " << static_cast<int>(type) << '!';
            break;
        }
        dataStream >> *ev;
        events_.emplace_back(ev);
    }
    chapter_ = Novel::getInstance().getChapter(chapterName_);
}

void Scene::serializableSave(QDataStream& dataStream) const
{
    dataStream << name << chapterName_ << scenery << events_.size();
    for (const std::unique_ptr<Event>& ev : events_)
        dataStream << *ev;
}
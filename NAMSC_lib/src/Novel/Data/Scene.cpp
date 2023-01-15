#include "Novel/Data/Scene.h"

#include "Novel/Data/Novel.h"
#include "Novel/Event/EventAll.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Scene& first, Scene& second) noexcept
{
    using std::swap;
    swap(first.name,         second.name);
    swap(first.chapterName_, second.chapterName_);
    swap(first.chapter_,     second.chapter_);
    swap(first.scenery,      second.scenery);
    swap(first.events_,      second.events_);
}

Scene::Scene(const QString& name, const QString& chapterName, /*const Scenery& scenery,*/ std::vector<std::unique_ptr<Event>>&& events)
    : name(name),
    chapterName_(chapterName),
    //scenery(scenery), 
    events_(std::move(events))
{
    if (this->name.isEmpty())
        this->name = Novel::getInstance().nextFreeSceneName();

    if (!chapterName_.isEmpty())
        chapter_ = Novel::getInstance().getChapter(chapterName_);
    errorCheck(true);
}

void Scene::serializableLoad(QDataStream& dataStream)
{
    dataStream >> name >> chapterName_ >> scenery;
    size_t size;
    dataStream >> size;
    for (size_t i = 0u; i != size; ++i)
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
            qCritical() << NovelLib::ErrorType::Critical << "Could not find a Stat's type:" << static_cast<int>(type) << '!';
            break;
        }
        dataStream >> *ev;
        events_.emplace_back(ev);
    }
    if (!chapterName_.isEmpty())
        chapter_ = Novel::getInstance().getChapter(chapterName_);
}

void Scene::serializableSave(QDataStream& dataStream) const
{
    dataStream << name << chapterName_ << scenery << events_.size();
    for (const std::unique_ptr<Event>& ev : events_)
        dataStream << *ev;
}

//  MEMBER_FIELD_SECTION_CHANGE END

Scene::Scene(Scene&& obj) noexcept
    : Scene()
{
    swap(*this, obj);
}

QString Scene::nextFreeEventName()
{
    for (uint i = 0; i != events_.size(); ++i)
    {
        QString checked = "Event " + QString::number(i + 1);
        if (std::find_if(events_.cbegin(), events_.cend(), [&checked] (const std::unique_ptr<Event>& obj) { return obj->label == checked; }) != events_.cend())
            return checked;
    }
    return "Event " + QString::number(events_.size() + 1);
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
        qCritical() << NovelLib::ErrorType::General << "Tried to get an Event past the `events_` container's size (" + QString::number(eventIndex) + " >= " + QString::number(events_.size()) + ") in a Scene \"" + name + '\"'; \
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

void Scene::addEvent(Event* event)
{
    events_.emplace_back(event);
}

bool Scene::insertEvent(uint eventIndex, Event* event)
{
    if (eventIndex > events_.size())
    {
        qCritical() << NovelLib::ErrorType::General << "Tried to insert a new Event past the `events_` container's size (" << eventIndex << ">" << events_.size() << ") in a Scene \"" + name + '\"';
        return false;
    }

    events_.emplace(events_.begin() + eventIndex, event);
    
    return true;
}

bool Scene::removeEvent(uint eventIndex)
{
    if (eventIndex >= events_.size())
    {
        qCritical() << NovelLib::ErrorType::General << "Tried to remove an Event past the `events_` container's size (" + QString::number(eventIndex) + " >= " + QString::number(events_.size()) + ") in a Scene \"" + name + '\"';
        return false;
    }

    events_.erase(events_.begin() + eventIndex);
    
    return true;
}

void Scene::clearEvents() noexcept
{
    events_.clear();
}
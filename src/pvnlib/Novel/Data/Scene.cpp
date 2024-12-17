#include "pvnLib/Novel/Data/Scene.h"

#include "pvnLib/Novel/Data/Novel.h"
#include "pvnLib/Novel/Event/EventAll.h"

#include "pvnLib/Helpers.h"

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

Scene::Scene(const QString& name, const QString& chapterName/*, const Scenery& scenery,*/)
	: name(name), 
    chapterName_(chapterName),
    scenery(this)
{
    if (this->name.isEmpty())
        this->name = Novel::getInstance().nextFreeSceneName();

    if (!chapterName_.isEmpty())
        chapter_ = Novel::getInstance().getChapter(chapterName_);
    errorCheck(true);
}

Scene::Scene(const Scene& obj) noexcept
    : name(obj.name), 
    chapterName_(obj.chapterName_), 
    chapter_(obj.chapter_)
{
    scenery = obj.scenery;

    for (const std::shared_ptr<Event>& event : obj.events_)
    {
        //TODO: Create an abstract factory for this
        Event* clone = nullptr;
        switch (event->getType())
        {
        case NovelLib::SerializationID::EventChoice:
            clone = new EventChoice(this);
            *static_cast<EventChoice*>(clone) = *static_cast<EventChoice*>(event.get());
            break;
        case NovelLib::SerializationID::EventDialogue:
            clone = new EventDialogue(this);
            *static_cast<EventDialogue*>(clone) = *static_cast<EventDialogue*>(event.get());
            break;
        case NovelLib::SerializationID::EventEndIf:
            clone = new EventEndIf(this);
            *static_cast<EventEndIf*>(clone) = *static_cast<EventEndIf*>(event.get());
            break;
        case NovelLib::SerializationID::EventIf:
            clone = new EventIf(this);
            *static_cast<EventIf*>(clone) = *static_cast<EventIf*>(event.get());
            break;
        case NovelLib::SerializationID::EventInput:
            clone = new EventInput(this);
            *static_cast<EventInput*>(clone) = *static_cast<EventInput*>(event.get());
            break;
        case NovelLib::SerializationID::EventJump:
            clone = new EventJump(this);
            *static_cast<EventJump*>(clone) = *static_cast<EventJump*>(event.get());
            break;
        case NovelLib::SerializationID::EventWait:
            clone = new EventWait(this);
            *static_cast<EventWait*>(clone) = *static_cast<EventWait*>(event.get());
            break;
        default:
            qCritical() << NovelLib::ErrorType::Critical << "Could not find the Event type:" << static_cast<int>(event->getType()) << '!';
            continue;
            break;
        }
        events_.emplace_back(clone);
    }
}

Scene& Scene::operator=(const Scene& obj) noexcept
{
    if (this == &obj)
        return *this;

    name         = obj.name;
    chapterName_ = obj.chapterName_;
    chapter_     = obj.chapter_;
    scenery      = obj.scenery;

    for (const std::shared_ptr<Event>& event : obj.events_)
    {
        Event* clone = nullptr;
        switch (event->getType())
        {
        case NovelLib::SerializationID::EventChoice:
            clone = new EventChoice(this);
            *static_cast<EventChoice*>(clone) = *static_cast<EventChoice*>(event.get());
            break;
        case NovelLib::SerializationID::EventDialogue:
            clone = new EventDialogue(this);
            *static_cast<EventDialogue*>(clone) = *static_cast<EventDialogue*>(event.get());
            break;
        case NovelLib::SerializationID::EventEndIf:
            clone = new EventEndIf(this);
            *static_cast<EventEndIf*>(clone) = *static_cast<EventEndIf*>(event.get());
            break;
        case NovelLib::SerializationID::EventIf:
            clone = new EventIf(this);
            *static_cast<EventIf*>(clone) = *static_cast<EventIf*>(event.get());
            break;
        case NovelLib::SerializationID::EventInput:
            clone = new EventInput(this);
            *static_cast<EventInput*>(clone) = *static_cast<EventInput*>(event.get());
            break;
        case NovelLib::SerializationID::EventJump:
            clone = new EventJump(this);
            *static_cast<EventJump*>(clone) = *static_cast<EventJump*>(event.get());
            break;
        case NovelLib::SerializationID::EventWait:
            clone = new EventWait(this);
            *static_cast<EventWait*>(clone) = *static_cast<EventWait*>(event.get());
            break;
        default:
            qCritical() << NovelLib::ErrorType::Critical << "Could not find the Event type:" << static_cast<int>(event->getType()) << '!';
            continue;
            break;
        }
        events_.emplace_back(clone);
    }

    return *this;
}

bool Scene::operator==(const Scene& obj) const noexcept
{
    if (this == &obj)
        return true;
    
    return scenery == obj.scenery &&
           events_ == obj.events_;
}

void Scene::serializableLoad(QDataStream& dataStream)
{
    dataStream >> name >> chapterName_ >> scenery;
    uint size;
    dataStream >> size;
    for (uint i = 0u; i != size; ++i)
    {
        //TODO: Create an abstract factory for this
        Event* event = nullptr;
        NovelLib::SerializationID type;
        dataStream >> type;
        switch (type)
        {
        case NovelLib::SerializationID::EventChoice:
            event = new EventChoice(this);
            break;
        case NovelLib::SerializationID::EventEndIf:
            event = new EventEndIf(this);
            break;
        case NovelLib::SerializationID::EventIf:
            event = new EventIf(this);
            break;
        case NovelLib::SerializationID::EventInput:
            event = new EventInput(this);
            break;
        case NovelLib::SerializationID::EventJump:
            event = new EventJump(this);
            break;
        case NovelLib::SerializationID::EventDialogue:
            event = new EventDialogue(this);
            break;
        case NovelLib::SerializationID::EventWait:
            event = new EventWait(this);
            break;
        default:
            qCritical() << NovelLib::ErrorType::Critical << "Could not find the Event type:" << static_cast<int>(type) << '!';
            continue;
            break;
        }
        dataStream >> *event;
        events_.emplace_back(event);
    }
    if (!chapterName_.isEmpty())
        chapter_ = Novel::getInstance().getChapter(chapterName_);
}

void Scene::serializableSave(QDataStream& dataStream) const
{
    dataStream << name << chapterName_ << scenery << static_cast<uint>(events_.size());
    for (const std::shared_ptr<Event>& ev : events_)
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
        if (std::find_if(events_.cbegin(), events_.cend(), [&checked] (const std::shared_ptr<Event>& obj) { return obj->label == checked; }) != events_.cend())
            return checked;
    }
    return "Event " + QString::number(events_.size() + 1);
}

const std::vector<std::shared_ptr<Event>>* Scene::getEvents() const noexcept
{
    return &events_;
}

const std::shared_ptr<Event> Scene::getEvent(uint index) const
{
    return *NovelLib::Helpers::listGet(events_, index, "Event", NovelLib::ErrorType::EventMissing, "Scene", name);
}

std::shared_ptr<Event> Scene::getEvent(uint index)
{
    return *NovelLib::Helpers::listGet(events_, index, "Event", NovelLib::ErrorType::EventMissing, "Scene", name);
}

const std::shared_ptr<Event> Scene::getEvent(const QString& name) const
{
    return *NovelLib::Helpers::listGet(events_, name, "Event", NovelLib::ErrorType::EventMissing, "Scene", this->name);
}

std::shared_ptr<Event> Scene::getEvent(const QString& name)
{
    return *NovelLib::Helpers::listGet(events_, name, "Event", NovelLib::ErrorType::EventMissing, "Scene", this->name);
}

const std::vector<std::shared_ptr<Event>>* Scene::setEvents(std::vector<std::shared_ptr<Event>>&& events) noexcept
{
    return &(events_ = std::move(events));
}

std::shared_ptr<Event> Scene::addEvent(Event* event) noexcept
{
    return *NovelLib::Helpers::listAdd(events_, std::move(std::shared_ptr<Event>(event)), "Event", NovelLib::ErrorType::EventInvalid, "Scene", name);
}

std::shared_ptr<Event> Scene::addEvent(std::shared_ptr<Event>&& event) noexcept
{
    return *NovelLib::Helpers::listAdd(events_, std::move(event), "Event", NovelLib::ErrorType::EventInvalid, "Scene", name);
}

std::shared_ptr<Event> Scene::insertEvent(uint index, Event* event)
{
    return *NovelLib::Helpers::listInsert(events_, index, std::move(std::shared_ptr<Event>(event)), "Event", NovelLib::ErrorType::EventInvalid, "Scene", name);
}

std::shared_ptr<Event> Scene::insertEvent(uint index, std::shared_ptr<Event>&& event)
{
    return *NovelLib::Helpers::listInsert(events_, index, std::move(event), "Event", NovelLib::ErrorType::EventInvalid, "Scene", name);
}

std::shared_ptr<Event> Scene::reinsertEvent(uint index, uint newIndex)
{
    return *NovelLib::Helpers::listReinsert(events_, index, newIndex, "Event", NovelLib::ErrorType::EventMissing, NovelLib::ErrorType::EventInvalid, "Scene", name);
}

bool Scene::removeEvent(uint index)
{
    return NovelLib::Helpers::listRemove(events_, index, "Event", NovelLib::ErrorType::EventMissing, "Scene", name);
}

bool Scene::removeEvent(const QString& name)
{
    return NovelLib::Helpers::listRemove(events_, name, "Event", NovelLib::ErrorType::EventMissing, "Scene", this->name);
}

void Scene::clearEvents() noexcept
{
    events_.clear();
}
#pragma once

#include <QString>

/// The additonal label of a Scene, which allows us to put Scenes into easier managable bins
class Chapter
{
    /// Swap trick
    friend void swap(Chapter& first, Chapter& second) noexcept;
public:
    Chapter(const QString& name = "", const QString& parentName = "");
    Chapter(const Chapter& obj)                noexcept = default;
    Chapter(Chapter&& obj)                     noexcept = default;
    Chapter& operator=(const Chapter &obj)     noexcept = default;
    //Chapter& operator=(Chapter obj)            noexcept = default;
    bool operator==(const QString& name) const noexcept;
    bool operator==(const Chapter& obj)  const noexcept = default;
    bool operator!=(const QString& name) const noexcept;
    bool operator!=(const Chapter& obj)  const noexcept = default;

    QString getParentName()    const noexcept;
    const Chapter* getParent() const noexcept;
    Chapter*       getParent()       noexcept;
    void setParent(const QString& parentName, Chapter* parent = nullptr) noexcept;

    QString name         = "";

private:
    QString  parentName_ = "";
    Chapter* parent_     = nullptr;
    
public:
    //---SERIALIZATION---
    /// Loading an object from a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to read from
    void serializableLoad(QDataStream& dataStream);
    /// Saving an object to a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to save to
    void serializableSave(QDataStream& dataStream) const;
};
#pragma once

#include <QString>

/// [optional] The additonal label of a Scene, which allows us to put Scenes into easier managable bins
struct Chapter
{
    Chapter() = default;
    Chapter(const QString& name, const QString& parentName);
    Chapter(const Chapter& obj) = default;
    Chapter& operator=(Chapter obj) noexcept;
    bool operator==(const QString& name) const noexcept;
    bool operator==(const Chapter& obj) const = default;
    bool operator!=(const QString& name) const noexcept;
    bool operator!=(const Chapter& obj) const = default;

    void setParent(const QString& parentName, Chapter* parent = nullptr) noexcept;
    const Chapter* getParent() const noexcept;
    Chapter* getParent() noexcept;
    QString getParentName() const noexcept;

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
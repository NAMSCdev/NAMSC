#pragma once

#include <QString>

namespace NovelLib
{
	template<typename T>
	const T* getFromNamedMap(const QHash<QString, T>& map, const QString& name, const QString& type) noexcept
	{
		if (!map.contains(name))
		{
			qDebug() << "Tried to get an non-existent " << type << " \"" << name << "\"";
			return nullptr;
		}

		return &(*map.constFind(name));
	}

	template<typename T>
	T* getFromNamedMap(QHash<QString, T>& map, const QString& name, const QString& type) noexcept
	{
		if (!map.contains(name))
		{
			qDebug() << "Tried to get an non-existent " << type << " \"" << name << "\"";
			return nullptr;
		}

		return &(*map.find(name));
	}

	template<typename T>
	bool removeFromNamedMap(QHash<QString, T>& map, const QString& name, const QString& type) noexcept
	{
		if (!map.contains(name))
		{
			qDebug() << "Tried to remove a non-existent " << type << " \"" << name << "\"";
			return false;
		}

		map.remove(name);

		return true;
	}
}
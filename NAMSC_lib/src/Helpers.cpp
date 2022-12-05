#include "Helpers.h"

namespace NovelLib
{
	template<typename T>
	const T* getFromNamedMap(const std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept
	{
		if (!map.contains(name))
		{
			qDebug() << "Tried to get an non-existent " << type << " \"" << name << "\"";
			return nullptr;
		}

		return &(map.at(name));
	}

	template<typename T>
	T* getFromNamedMap(std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept
	{
		if (!map.contains(name))
		{
			qDebug() << "Tried to get an non-existent " << type << " \"" << name << "\"";
			return nullptr;
		}

		return &(map.at(name));
	}

	template<typename T>
	bool removeFromNamedMap(std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept
	{
		if (!map.contains(name))
		{
			qDebug() << "Tried to remove a non-existent " << type << " \"" << name << "\"";
			return false;
		}

		map.erase(name);

		return true;
	}
}
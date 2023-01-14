#pragma once

#include <QString>

namespace NovelLib
{
	template<typename T>
	const T* getFromNamedMap(const std::unordered_map<QString, T>& map, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, bool bThrowErrors = true) noexcept
	{
		if (!map.contains(name))
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get an non-existent " + type + "\"" + name + '\"';
			return nullptr;
		}

		return &(map.at(name));
	}

	template<typename T>
	T* getFromNamedMap(std::unordered_map<QString, T>& map, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, bool bThrowErrors = true) noexcept
	{
		if (!map.contains(name))
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get an non-existent " + type + "\"" + name + '\"';
			return nullptr;
		}

		return &(map.at(name));
	}

	template<typename T>
	T* setInNamedMap(std::unordered_map<QString, T>& map, const QString& name, const T& object, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, bool bThrowErrors = true) noexcept
	{

		if (object.name != name)
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + "'s name missmatch (name=\"" + name + "\", object.name=\"" + object.name + "\")";
			return nullptr;
		}

		return &(map[name] = object);
	}

	//todo: merge these two templates, or branch name setting only
	template<typename T>
	T* renameInNamedMap(std::unordered_map<QString, T>& map, const QString& oldName, const QString& newName, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, bool bThrowErrors = true, typename std::enable_if<std::is_pointer<T>::value>::type* = 0) noexcept
	{
		if (!map.contains(oldName))
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "There is no " + type + " with name \"" + oldName + "\"!";
			return nullptr;
		}
		if (map.contains(newName))
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + " with name \"" + newName + "\" already exists!";
			return nullptr;
		}

		auto&& object = std::move(map.at(oldName));
		object->name  = newName;
		map.emplace(newName, std::move(object));
		map.erase(oldName);
	}

	template<typename T>
	T* renameInNamedMap(std::unordered_map<QString, T>& map, const QString& oldName, const QString& newName, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, bool bThrowErrors = true, typename std::enable_if<!std::is_pointer<T>::value>::type* = 0) noexcept
	{
		if (!map.contains(oldName))
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "There is no " + type + " with name \"" + oldName + "\"!";
			return nullptr;
		}
		if (map.contains(newName))
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + " with name \"" + newName + "\" already exists!";
			return nullptr;
		}

		auto&& object = std::move(map.at(oldName));
		object.name   = newName;
		map.emplace(newName, std::move(object));
		map.erase(oldName);
		return &(map.at(newName));
	}

	template<typename T, typename R>
	R renameSharedInNamedMap(std::unordered_map<QString, T>& map, const QString& oldName, const QString& newName, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, bool bThrowErrors = true, typename std::enable_if<!std::is_pointer<T>::value>::type* = 0) noexcept
	{
		if (!map.contains(oldName))
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "There is no " + type + " with name \"" + oldName + "\"!";
			return nullptr;
		}
		if (map.contains(newName))
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + " with name \"" + newName + "\" already exists!";
			return nullptr;
		}

		auto&& object = std::move(map.at(oldName));
		object->name  = newName;
		map.emplace(newName, std::move(object));
		map.erase(oldName);
		return map.at(newName).get();
	}

	template<typename T>
	T* addToNamedMap(std::unordered_map<QString, T>& map, const QString& name, T&& object, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, bool bThrowErrors = true) noexcept
	{
		if (map.contains(name))
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << "A " + type + " with name \"" + name + "\" already exists!";
			return nullptr;
		}

		map.emplace(name, std::move(object));
		return &(map.at(name));
	}

	template<typename T>
	bool removeFromNamedMap(std::unordered_map<QString, T>& map, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, bool bThrowErrors = true) noexcept
	{
		if (!map.contains(name))
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to remove a non-existent " + type + "\"" + name + '\"';
			return false;
		}

		map.erase(name);

		return true;
	}
}
#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "Exceptions.h"

namespace NovelLib
{
	//Helper's helpers

	template<typename T>
	concept NotQObject = !std::derived_from<T, QObject>;

	template<typename T>
	concept NamedObject = NotQObject<T> && requires(T& t)
	{
		t.name = QString();
	};

	template<typename T>
	concept NamedPointer = NotQObject<T> && requires(T& t)
	{
		t->name = QString();
	};

	template<typename T>
	concept NamedEntity = NamedObject<T> || NamedPointer<T>;

	template<NamedObject T>
	QString getName(const T& object)
	{
		return object.name;
	}

	template<NamedPointer T>
	QString getName(const T& pointer)
	{
		return pointer->name;
	}

	template<NamedObject T>
	void setName(T& object, const QString& name)
	{
		object.name = name;
	}

	template<NamedPointer T>
	void setName(T& pointer, const QString& name)
	{
		pointer->name = name;
	}

	QString parentMsg(const QString& parentType, const QString& parentName, const QString& parentParentType, const QString& parentParentName);

	template<typename T>
	bool checkMapExistence(const std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!map.contains(key))
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get a non-existent " + type + "\"" + key + '\"' + parentMsg(parentType, parentName, parentParentType, parentParentName);
			return false;
		}
		return true;
	}

	template<typename T>
	bool checkMapDuplicate(const std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (map.contains(key))
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + " \"" + key + "\" already exists" + parentMsg(parentType, parentName, parentParentType, parentParentName);
			return false;
		}
		return true;
	}

	//template<NamedEntity T>
	//bool checkName(const QString& name, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	//{
	//	if (getName(entity) != name)
	//	{
	//		if (bThrowErrors)
	//			qCritical() << errorTypeInvalid << type + "'s name missmatch (name=\"" + name + "\", instace name=\"" + getName(entity) + "\")" + parentMsg(parentType, parentName, parentParentType, parentParentName);
	//		return false;
	//	}
	//	return true;
	//}

	template<typename T>
	bool checkListIndex(const std::vector<T>& list, uint index, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (index >= list.size())
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Index " + QString::number(index) + " exceeds container's size " + QString::number(list.size()) + parentMsg(parentType, parentName, parentParentType, parentParentName);
			return false;
		}
		return true;
	}

	template<NamedEntity T>
	std::vector<T>::iterator checkListExistence(std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = std::find_if(list.begin(), list.end(), [&name](T& listEntity) { return getName(listEntity) == name; });
		if (ret == list.end())
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get a non-existent " + type + "\"" + name + '\"' + parentMsg(parentType, parentName, parentParentType, parentParentName);
		}
		return ret;
	}

	template<NamedEntity T>
	std::vector<T>::iterator checkListDuplicate(std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = std::find_if(list.begin(), list.end(), [&name](T& listEntity) { return getName(listEntity) == name; });
		if (ret != list.end())
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + " \"" + name + "\" already exists" + parentMsg(parentType, parentName, parentParentType, parentParentName);
		}
		return ret;
	}

	////Maps

	template<typename T>
	const T* mapGet(const std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		if (!checkMapExistence(map, key, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		return &(map.at(key));	
	}

	template<typename T>
	T* mapGet(std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		if (!checkMapExistence(map, key, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		return &(map.at(key));
	}

	template<NamedEntity T>
	T* mapSet(std::unordered_map<QString, T>& map, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		return &(map[getName(entity)] = entity);
	}

	template<NamedEntity T>
	T* mapSet(std::unordered_map<QString, T>& map, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		const QString name = getName(entity);
		if (map.contains(name))
			map.erase(name);

		map.emplace(name, std::move(entity));
		
		return &map.at(name);
		return nullptr;
	}

	template<NamedEntity T>
	T* mapRename(std::unordered_map<QString, T>& map, const QString& oldName, const QString& newName, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		if (!checkMapExistence(map, oldName, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		if (!checkMapDuplicate(map, newName, type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		T&& object = std::move(map.at(oldName));
		setName(object, newName);

		auto iteratorBoolPair = map.emplace(newName, std::move(object));
		map.erase(oldName);
		
		return &(iteratorBoolPair.first->second);
	}

	template<typename T>
	bool mapRemove(std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		if (!checkMapExistence(map, key, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return false;

		map.erase(key);

		return true;
	}

	//Lists

	template<typename T>
	const T* listGet(std::vector<T>& list, uint index, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		return &(list.at(index));
	}

	template<typename T>
	T* listGet(std::vector<T>& list, uint index, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		return &(list.at(index));
	}

	template<NamedEntity T>
	const T* listGet(const std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::const_iterator ret = std::find_if(list.cbegin(), list.cend(), [&name](const T& listEntity) { return getName(listEntity) == name; });
		if (ret == list.cend())
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get a non-existent " + type + "\"" + name + '\"' + parentMsg(parentType, parentName, parentParentType, parentParentName);
			return nullptr;
		}
		return &(*ret);
	}

	template<NamedEntity T>
	T* listGet(std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = std::find_if(list.begin(), list.end(), [&name](T& listEntity) { return getName(listEntity) == name; });
		if (ret == list.end())
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get a non-existent " + type + "\"" + name + '\"' + parentMsg(parentType, parentName, parentParentType, parentParentName);
			return nullptr;
		}
		return &(*ret);
	}

	template<NamedEntity T>
	T* listInsert(std::vector<T>& list, uint index, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, NovelLib::ErrorType::General, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		typename std::vector<T>::iterator ret = checkListDuplicate(list, getName(entity), type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret != list.end())
			return nullptr;
		return &(*(list.insert(list.begin() + index, entity)));
	}

	template<NamedEntity T>
	T* listInsert(std::vector<T>& list, uint index, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, NovelLib::ErrorType::General, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		typename std::vector<T>::iterator ret = checkListDuplicate(list, getName(entity), type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret != list.end())
			return nullptr;
		return &(*(list.insert(list.begin() + index, std::move(entity))));
	}

	template<typename T>
	T* listInsert(std::vector<T>& list, uint index, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, NovelLib::ErrorType::General, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		return &(*(list.insert(list.begin() + index, entity)));
	}

	template<typename T>
	T* listInsert(std::vector<T>& list, uint index, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, NovelLib::ErrorType::General, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		return &(*(list.insert(list.begin() + index, std::move(entity))));
	}

	template<NamedEntity T>
	T* listAdd(std::vector<T>& list, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = checkListDuplicate(list, getName(entity), type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret != list.end())
			return nullptr;

		list.push_back(entity);

		return &(list.back());
	}

	template<typename T>
	T* listAdd(std::vector<T>& list, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		list.push_back(entity);

		return &(list.back());
	}

	template<NamedEntity T>
	T* listAdd(std::vector<T>& list, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = checkListDuplicate(list, getName(entity), type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret != list.end())
			return nullptr;

		list.push_back(std::move(entity));

		return &(list.back());
	}

	template<typename T>
	T* listAdd(std::vector<T>& list, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		list.push_back(std::move(entity));

		return &(list.back());
	}

	template<typename T>
		bool listRemove(std::vector<T>& list, uint index, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return false;

		list.remove(list.begin() + index);

		return true;
	}

	template<NamedEntity T>
	bool listRemove(std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = checkListExistence(list, name, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret == list.end())
			return false;

		list.erase(ret);

		return true;
	}
}
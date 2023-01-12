#include "ChoiceItemModel.h"

#include "Novel/Data/Novel.h"

ChoiceItemModel::ChoiceItemModel(std::vector<Choice>* choices, QObject *parent)
	: QAbstractTableModel(parent)
{
	
}

ChoiceItemModel::~ChoiceItemModel()
{}

Qt::ItemFlags ChoiceItemModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

int ChoiceItemModel::rowCount(const QModelIndex& parent) const
{
	return choices_->size();
}

int ChoiceItemModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant ChoiceItemModel::data(const QModelIndex& index, int role) const
{
	QVariant retVal;

	switch(index.column())
	{
	case Name:
		retVal = choices_->at(index.row()).name;
		break;
	case Text:
		retVal = choices_->at(index.row()).text.text();
		break;
	case JumpToScene:
		retVal = choices_->at(index.row()).jumpToSceneName;
		break;
	case Condition:
		retVal = choices_->at(index.row()).condition;
		break;
	}

	return retVal;
}

bool ChoiceItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	Choice& affectedRow = choices_->at(index.row());

	switch(index.column())
	{
	case Name:
		affectedRow.name = value.toString();
		break;
	case Text:
		affectedRow.text.setTranslation(NovelSettings::getInstance().language, value.toString());
		break;
	case JumpToScene:
		affectedRow.jumpToSceneName = value.toString();
		break;
	case Condition:
		affectedRow.condition = value.toString();
		break;
	default:
		return false;
	}

	emit dataChanged(index, index);
	return true;
}


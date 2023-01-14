#include "ChoiceItemModel.h"

#include "Novel/Data/Novel.h"
#include "Novel/Event/EventChoice.h"

ChoiceItemModel::ChoiceItemModel(EventChoice* parentEvent, QObject *parent)
	: QAbstractTableModel(parent), parentEvent(parentEvent), choices(&parentEvent->choices)
{
	setHeaderData(Name, Qt::Horizontal, tr("Name"));
}

ChoiceItemModel::~ChoiceItemModel()
{}

Qt::ItemFlags ChoiceItemModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

int ChoiceItemModel::rowCount(const QModelIndex& parent) const
{
	return choices->size();
}

int ChoiceItemModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant ChoiceItemModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	if (index.row() >= choices->size() || index.row() < 0) return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		switch (index.column())
		{
		case Name:
			return choices->at(index.row()).name;
		case Text:
			return choices->at(index.row()).text.text();
		case JumpToScene:
			return choices->at(index.row()).jumpToSceneName;
		case Condition:
			return choices->at(index.row()).condition;
		}
	}

	return QVariant();
}

bool ChoiceItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		Choice& affectedRow = choices->at(index.row());

		switch (index.column())
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

		emit dataChanged(index, index, { Qt::DisplayRole | Qt::EditRole });
		return true;
	}

	return false;
}

QVariant ChoiceItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case Name:
			return tr("Name");
		case Text:
			return tr("Text");
		case JumpToScene:
			return tr("Jump to scene");
		case Condition:
			return tr("Condition");
		}
	}

	return QVariant();
}

bool ChoiceItemModel::insertRows(int row, int count, const QModelIndex& parent)
{
	Q_UNUSED(parent);

	beginInsertRows(QModelIndex(), row, row + count - 1);

	for (int rowNum = 0; rowNum < count; ++rowNum)
	{
		choices->emplace(choices->cbegin() + row + rowNum, parentEvent);
	}

	endInsertRows();
	return true;
}


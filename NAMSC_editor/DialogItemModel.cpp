#include "DialogItemModel.h"

#include "Novel/Event/EventDialogue.h"

DialogItemModel::DialogItemModel(EventDialogue* event, QObject* parent)
	: QAbstractListModel(parent), parentEvent(event), sentences(&event->sentences)
{}

DialogItemModel::~DialogItemModel()
{}

int DialogItemModel::rowCount(const QModelIndex& parent) const
{
	if (sentences == nullptr) {
		return 0;
	}
	else
	{
		return sentences->size();
	}
}

QVariant DialogItemModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || sentences == nullptr) return QVariant();
	if (index.row() >= sentences->size() || index.row() < 0) return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		return sentences->at(index.row()).displayedName;
	}

	return QVariant();
}

Qt::ItemFlags DialogItemModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool DialogItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		sentences->at(index.row()).displayedName = value.toString();

		emit dataChanged(index, index, { Qt::DisplayRole | Qt::EditRole });
		return true;
	}

	return false;
}

QVariant DialogItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		return tr("Name");
	}

	return QVariant();
}

bool DialogItemModel::insertRows(int row, int count, const QModelIndex& parent)
{
	Q_UNUSED(parent);

	beginInsertRows(QModelIndex(), row, row + count - 1);

	for (int rowNum = 0; rowNum < count; ++rowNum)
	{
		sentences->emplace(sentences->cbegin() + row + rowNum, Sentence(parentEvent));
	}

	endInsertRows();
	return true;
}

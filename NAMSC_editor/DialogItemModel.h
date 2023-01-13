#pragma once

#include <QAbstractListModel>

#include "Novel/Data/Text/Sentence.h"

class DialogItemModel : public QAbstractListModel
{
	Q_OBJECT

public:
	DialogItemModel(EventDialogue* event, QObject *parent = nullptr);
	~DialogItemModel();

	int rowCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

private:
	EventDialogue* parentEvent;
	std::vector<Sentence>* sentences;
};

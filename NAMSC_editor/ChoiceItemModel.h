#pragma once

#include <QAbstractItemModel>

#include "Novel/Data/Text/Choice.h"
#include "GraphView.h"

class ChoiceItemModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	ChoiceItemModel(EventChoice* parentEvent, GraphView* graph, QObject* parent = nullptr);
	~ChoiceItemModel() override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent) const override;
	int columnCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
	enum ColumnElementEnum
	{
		Name,
		Text,
		JumpToScene,
		Condition
	};

	GraphView* graph;
	EventChoice* parentEvent;
	std::vector<Choice>* choices;
};

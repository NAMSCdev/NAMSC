#pragma once

#include <QAbstractItemModel>

#include "Novel/Data/Text/Choice.h"

class ChoiceItemModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	ChoiceItemModel(std::vector<Choice>* choices, QObject *parent = nullptr);
	~ChoiceItemModel() override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent) const override;
	int columnCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;

private:
	enum ColumnElementEnum
	{
		Name,
		Text,
		JumpToScene,
		Condition
	};

	std::vector<Choice>* choices_;
};

#include "LineEditDelegate.h"

#include <QLineEdit>

LineEditDelegate::LineEditDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{}

LineEditDelegate::~LineEditDelegate()
{}

QWidget* LineEditDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	QLineEdit* editor = new QLineEdit(parent);
	editor->setFrame(false);

	return editor;
}

void LineEditDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	// todo check if EditRole is correct
	QString text = index.model()->data(index, Qt::EditRole).toString();

	QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
	lineEdit->setText(text);
}

void LineEditDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
	// low possibility that there should be a signal emitted
	QString text = lineEdit->text();

	model->setData(index, text, Qt::EditRole); // Maybe | Qt::DisplayRole
}

void LineEditDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	editor->setGeometry(option.rect);
}

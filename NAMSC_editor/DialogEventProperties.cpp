#include "DialogEventProperties.h"

#include <QContextMenuEvent>
#include <QMenu>

#include "DialogItemModel.h"

DialogEventProperties::DialogEventProperties(EventDialogue* dialogue, QWidget *parent)
	: QFrame(parent), dialogue(dialogue)
{
	ui.setupUi(this);

	ui.dialogEventCollapseButton->setContent(ui.dialogEventPropertiesContent);
	ui.dialogEventCollapseButton->setText(tr("Dialog event properties"));
	if (expanded) ui.dialogEventCollapseButton->toggle();

	prepareDataInUi();
	prepareConnections();

	createContextMenu();
}

DialogEventProperties::~DialogEventProperties()
{}

void DialogEventProperties::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu menu(this);
	menu.addAction(addSentenceAction);
	menu.exec(event->globalPos());
}

void DialogEventProperties::mousePressEvent(QMouseEvent* event)
{
	ui.dialogListView->clearSelection();
	QFrame::mousePressEvent(event);
}

void DialogEventProperties::prepareConnections()
{
	connect(ui.dialogEventCollapseButton, &CollapseButton::clicked, this, [] { expanded = !expanded; });

	connect(ui.dialogListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&](const QItemSelection& selected, const QItemSelection& deselected)
	{
			if (selected.isEmpty()) {
				ui.dialogTextEdit->blockSignals(true); // Prevent firing textchanged signal by setting text

				ui.dialogTextEdit->setEnabled(false);
				ui.dialogTextEdit->setText("");

				ui.dialogTextEdit->blockSignals(false);
			}
			else
			{
				ui.dialogTextEdit->blockSignals(true); // Prevent firing textchanged signal by setting text

				changeTextEdit(selected.indexes().constFirst());

				ui.dialogTextEdit->blockSignals(false);
			}
	});
	//connect(ui.dialogListView, &QListView::clicked, this, &changeTextEdit);
	connect(ui.dialogTextEdit, &QTextEdit::textChanged, this, &DialogEventProperties::changeModelItem);
}

void DialogEventProperties::prepareDataInUi()
{
	ui.dialogListView->setModel(new DialogItemModel(dialogue, ui.dialogListView));
	ui.dialogListView->setItemDelegate(&lineEditDelegate);
}

void DialogEventProperties::createContextMenu()
{
	addSentenceAction = new QAction(tr("Add new sentence"));

	connect(addSentenceAction, &QAction::triggered, this, [&]
		{
			static_cast<DialogItemModel*>(ui.dialogListView->model())->insertRows(ui.dialogListView->model()->rowCount(), 1);
		});
}

void DialogEventProperties::changeTextEdit(const QModelIndex& index)
{
	ui.dialogTextEdit->setEnabled(true);
	ui.dialogTextEdit->setText(dialogue->sentences.at(index.row()).text.text(NovelSettings::getInstance().language));
	lastClickedModelIndex = index;
}

void DialogEventProperties::changeModelItem()
{
	if (dialogue->sentences.size() > lastClickedModelIndex.row()) {
		dialogue->sentences.at(lastClickedModelIndex.row()).text.setTranslation(NovelSettings::getInstance().language, ui.dialogTextEdit->toPlainText());
	}
	else
	{
		qDebug() << "Clicked sentence index in EventDialogue properties is out of bounds";
	}
}

#include "ChoiceEventProperties.h"

#include <QAction>
#include <QContextMenuEvent>
#include <qinputdialog.h>
#include <QMenu>
#include <qmessagebox.h>

#include "ChoiceItemModel.h"

ChoiceEventProperties::ChoiceEventProperties(EventChoice* choices, GraphView* graph, QWidget *parent)
	: QFrame(parent), choices(choices), graph(graph)
{
	ui.setupUi(this);
	ui.choiceEventTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.choiceEventTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui.choiceEventCollapseButton->setContent(ui.choiceEventContent);
	ui.choiceEventCollapseButton->setText(tr("Choice event properties"));
	if (expanded) ui.choiceEventCollapseButton->toggle();

	prepareDataInUi();
	prepareConnections();

	createContextMenu();
}

ChoiceEventProperties::~ChoiceEventProperties()
{}

void ChoiceEventProperties::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu menu(this);
	menu.addAction(addChoiceAction);
	menu.addAction(removeChoiceAction);
	if (ui.choiceEventTableView->selectionModel()->hasSelection()) removeChoiceAction->setEnabled(true);
	else removeChoiceAction->setDisabled(true);
	menu.exec(event->globalPos());
}

void ChoiceEventProperties::prepareConnections()
{
	connect(ui.choiceEventCollapseButton, &CollapseButton::clicked, this, [] { expanded = !expanded; });
}

void ChoiceEventProperties::prepareDataInUi()
{
	ui.choiceEventTableView->setModel(new ChoiceItemModel(choices, graph, ui.choiceEventTableView));
	ui.choiceEventTableView->setColumnHidden(0, true); // Name

	//ui.choiceEventTableView->setItemDelegateForColumn(ChoiceItemModel::ColumnElementEnum::Name, &lineEditDelegate);
	//ui.choiceEventTableView->setItemDelegateForColumn(ChoiceItemModel::ColumnElementEnum::Condition, &lineEditDelegate);
	//ui.choiceEventTableView->setItemDelegateForColumn(ChoiceItemModel::ColumnElementEnum::JumpToScene, &lineEditDelegate);
	//ui.choiceEventTableView->setItemDelegateForColumn(ChoiceItemModel::ColumnElementEnum::Text, &lineEditDelegate);
	ui.choiceEventTableView->setItemDelegate(&lineEditDelegate);

	ui.choicePlainTextEdit->setPlainText(choices->getMenuText()->text());
	connect(ui.choicePlainTextEdit, &QPlainTextEdit::textChanged, this, &ChoiceEventProperties::updateChoiceLabel);
}

void ChoiceEventProperties::createContextMenu()
{
	addChoiceAction = new QAction(tr("Add new choice"), this);

	connect(addChoiceAction, &QAction::triggered, this, [&]
		{
			static_cast<ChoiceItemModel*>(ui.choiceEventTableView->model())->insertRows(ui.choiceEventTableView->model()->rowCount(), 1);
		});

	removeChoiceAction = new QAction(tr("Remove choice"), this);

	connect(removeChoiceAction, &QAction::triggered, this, [&]
	{
			for (auto elem : ui.choiceEventTableView->selectionModel()->selectedIndexes())
			{
				ui.choiceEventTableView->model()->removeRows(elem.row(), 1);
			}
	});
}

void ChoiceEventProperties::updateName(Choice* c, QString name)
{
	// todo eventually remove
}

void ChoiceEventProperties::updateJumpToSceneName(Choice* c, QString name)
{
	// todo eventually remove
}

void ChoiceEventProperties::updateCondition(Choice* c, QString cond)
{
	// todo eventually remove
}

void ChoiceEventProperties::updateText(Choice* c, QString text)
{
	// todo eventually remove
}

void ChoiceEventProperties::updateChoiceLabel()
{
	Translation translation = *choices->getMenuText();
	translation.setTranslation(NovelSettings::getInstance().language, ui.choicePlainTextEdit->toPlainText());
	choices->setMenuText(translation);

	choices->run();
}
#include "ChoiceEventProperties.h"

#include <QAction>
#include <QContextMenuEvent>
#include <qinputdialog.h>
#include <QMenu>
#include <qmessagebox.h>

#include "ChoiceItemModel.h"

ChoiceEventProperties::ChoiceEventProperties(EventChoice* choices, QWidget *parent)
	: QFrame(parent), choices(choices)
{
	ui.setupUi(this);

	ui.choiceEventCollapseButton->setContent(ui.choiceEventContent);
	ui.choiceEventCollapseButton->setText(tr("Choice event properties"));

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
	menu.exec(event->globalPos());
}

void ChoiceEventProperties::prepareConnections()
{
	// todo eventually remove
}

void ChoiceEventProperties::prepareDataInUi()
{
	ui.choiceEventTableView->setModel(new ChoiceItemModel(&choices->choices));
}

void ChoiceEventProperties::createContextMenu()
{
	addChoiceAction = new QAction(tr("Add new choice"), this);

	connect(addChoiceAction, &QAction::triggered, this, [&]
		{
			QString name;
			bool pressedOk = false;
			bool isNameOk = false;
			do {
				name = QInputDialog::getText(this, tr("Add new choice"), tr("Provide unique choice name:"), QLineEdit::Normal, "", &pressedOk);

				if (!pressedOk) break;
				else if (name.isNull() || name.isEmpty())
				{
					continue;
				}
				else if (std::find_if(choices->choices.begin(), choices->choices.end(), [&](Choice elem)
					{
						return elem.name == name;
					}) != choices->choices.end())
				{
					QMessageBox(QMessageBox::Critical, tr("Invalid choice name"), tr("Choice with this name already exists, please provide another name."), QMessageBox::Ok).exec();
					continue;
				}
				else isNameOk = true; 
			} while (!isNameOk);

		if (pressedOk)
		{
			// push_back, potentially want to insert
			choices->choices.push_back(Choice(name, Translation(), "", "", Choice::ChoiceDisplayOptions()));
		}
		
		ui.choiceEventTableView->update(); // todo check if this works
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

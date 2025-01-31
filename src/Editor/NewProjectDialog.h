#pragma once

#include <QDialog>
#include <QDir>

#include "ui_NewProjectDialog.h"

class NewProjectDialog : public QDialog
{
	Q_OBJECT

public:
	NewProjectDialog(QWidget *parent = nullptr);
	~NewProjectDialog();

	QDir getProjectCatalog();
	QString getProjectName();

private:
	void projectCatalogSelection();

	QDir projectCatalog_ = QDir::currentPath();
	QString projectName_ = "New Project";


	Ui::NewProjectDialogClass ui_;
};

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
	QDir projectCatalog = QDir::currentPath();
	QString projectName = "New_project";

	void projectCatalogSelection();

	Ui::NewProjectDialogClass ui;
};

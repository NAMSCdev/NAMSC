#include "NewProjectDialog.h"

#include <QFileDialog>

NewProjectDialog::NewProjectDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.projectNameLineEdit->setText(projectName);
	ui.projectPathLineEdit->setText(projectCatalog.path() + '/' + projectName);

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &NewProjectDialog::accept);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &NewProjectDialog::reject);
	connect(ui.selectDirectoryToolButton, &QToolButton::clicked, this, &NewProjectDialog::projectCatalogSelection);
	connect(ui.projectNameLineEdit, &QLineEdit::textChanged, this, [&](const QString& name)
		{
			projectName = name;
			ui.projectPathLineEdit->setText(projectCatalog.path() + '/' + projectName);
		});
}

NewProjectDialog::~NewProjectDialog()
{}

QDir NewProjectDialog::getProjectCatalog()
{
	return projectCatalog;
}

QString NewProjectDialog::getProjectName()
{
	return projectName;
}

void NewProjectDialog::projectCatalogSelection()
{
	QFileDialog fileDialog = QFileDialog(nullptr, tr("Choose project location"), projectCatalog.path());
	fileDialog.setFileMode(QFileDialog::Directory);
	fileDialog.setViewMode(QFileDialog::Detail);

	// todo check if filename, project path is correct
	if (fileDialog.exec())
	{
		projectCatalog = fileDialog.directory();
		ui.projectPathLineEdit->setText(projectCatalog.path() + '/' + projectName);

	}
	else 
	{
		// TODO error	
	}
}

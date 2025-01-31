#include "NewProjectDialog.h"

#include <QFileDialog>

NewProjectDialog::NewProjectDialog(QWidget *parent)
	: QDialog(parent)
{
	//todo: load from QSettings
	ui_.setupUi(this);

	ui_.projectNameLineEdit->setText(projectName_);
	ui_.projectPathLineEdit->setText(projectCatalog_.path() + '/' + projectName_);

	connect(ui_.buttonBox, &QDialogButtonBox::accepted, this, &NewProjectDialog::accept);
	connect(ui_.buttonBox, &QDialogButtonBox::rejected, this, &NewProjectDialog::reject);
	//todo: change ui names
	//todo: connections as variables, to connect and disconnect, to avoid infinite loop
	connect(ui_.selectDirectoryToolButton, &QToolButton::clicked, this, &NewProjectDialog::projectCatalogSelection);
	connect(ui_.projectNameLineEdit, &QLineEdit::textChanged, this, [&](const QString& name)
	{
		projectName_ = name;
		//ui_.projectPathLineEdit->disconnect
		ui_.projectPathLineEdit->setText(projectCatalog_.path() + '/' + projectName_);
		//ui_.projectPathLineEdit->connect
	});
	/*connect(ui_.projectPathLineEdit, &QLineEdit::textChanged, this, [&](const QString& path)
	{
		projectCatalog_ = QDir(path);
		//todo: check if right is the wrong, unoptimal function. Replace all \ to match Linux subsystem path names
		ui_.projectNameLineEdit->setText(path.right(path.size() - std::max(path.lastIndexOf('/'), path.lastIndexOf('\\'))));
		// todo: add invalid path error!
	});*/
}

NewProjectDialog::~NewProjectDialog()
{}

QDir NewProjectDialog::getProjectCatalog()
{
	return projectCatalog_;
}

QString NewProjectDialog::getProjectName()
{
	return projectName_;
}

void NewProjectDialog::projectCatalogSelection()
{
	QFileDialog fileDialog = QFileDialog(nullptr, tr("Choose project location"), projectCatalog_.path());
	fileDialog.setFileMode(QFileDialog::Directory);
	fileDialog.setViewMode(QFileDialog::Detail);

	// todo check if filename, project path is correct
	if (fileDialog.exec())
	{
		projectCatalog_ = fileDialog.directory();
		ui_.projectPathLineEdit->setText(projectCatalog_.path() + '/' + projectName_);

	}
	else 
	{
		// TODO error	
	}
}

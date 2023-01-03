#include "ProjectConfiguration.h"

#include <QFileDialog>

#include "NewProjectDialog.h"

void ProjectConfiguration::createNewProject()
{
	std::unique_ptr<NewProjectDialog> newProjectDialog = std::make_unique<NewProjectDialog>();
	int retVal = newProjectDialog.get()->exec();
	
	if (retVal == NewProjectDialog::Accepted)
	{
		projectName = newProjectDialog.get()->getProjectName();
		projectPath = newProjectDialog.get()->getProjectCatalog();

		if (projectPath.mkdir(projectName))
		{
			// todo create other files etc
		}
		else
		{
			// todo error, catalog was not made, probably not enough privileges 
		}
	}
	else if (retVal == NewProjectDialog::Rejected)
	{
		// TODO ?
	}
	

}

ProjectConfiguration::ProjectConfiguration(QObject* parent)
	: QObject(parent)
{}

ProjectConfiguration* ProjectConfiguration::getInstance()
{
	static ProjectConfiguration* instance;
	if (instance == nullptr) instance = new ProjectConfiguration();

	return instance;
}

void ProjectConfiguration::setProjectPath(const QString& path)
{
	projectPath = QDir(path);
}

void ProjectConfiguration::setProjectPath(const QDir& path)
{
	projectPath = path;
}

QDir ProjectConfiguration::getProjectPath()
{
	return projectPath;
}

ProjectConfiguration::~ProjectConfiguration()
{}

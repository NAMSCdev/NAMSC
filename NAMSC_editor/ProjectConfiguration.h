#pragma once

#include <QDir>
#include <QObject>

class ProjectConfiguration : public QObject
{
	Q_OBJECT

public:
	~ProjectConfiguration();

	static ProjectConfiguration* getInstance();

	void setProjectPath(const QString& path);
	void setProjectPath(const QDir& path);

	QDir getProjectPath();
	const QString& getLoadingLockFilename();

private:
	ProjectConfiguration(QObject* parent = nullptr);
	Q_DISABLE_COPY(ProjectConfiguration);
	QDir projectPath = QDir::currentPath();
	QString projectName = "project";
	const QString loadingLockFilename = "projectLoading.lock";

public slots:
	void createNewProject();

	signals:

};

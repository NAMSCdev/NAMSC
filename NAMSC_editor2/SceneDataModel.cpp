#include "SceneDataModel.h"

QString SceneDataModel::caption() const
{
	return _caption;
}

void SceneDataModel::setCaption(QString caption)
{
	_caption = std::move(caption);
}

QString SceneDataModel::portCaption(PortType portType, PortIndex portIndex) const
{
	return QString(); // TODO
}

QJsonObject SceneDataModel::save() const
{
	QJsonObject modelJson;

	modelJson["name"] = name();

	return modelJson; // TODO?
}

unsigned int SceneDataModel::nPorts(PortType portType) const
{
	return 0; // TODO
}

NodeDataType SceneDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	return NodeDataType(); // TODO
}

std::shared_ptr<NodeData> SceneDataModel::outData(PortIndex port)
{
	return std::shared_ptr<NodeData>(); // TODO
}

void SceneDataModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
{
	// TODO
}

NodeValidationState SceneDataModel::validationState() const
{
	return _currentValidationState;
}

QString SceneDataModel::validationMessage() const
{
	return _currentValidationMessage;
}

void SceneDataModel::restore(const QJsonObject& obj)
{
	// TODO
}

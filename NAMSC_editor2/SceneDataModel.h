#pragma once
#include <QObject>
#include <nodes/NodeDataModel>

using namespace QtNodes;

class SceneDataModel :
    public NodeDataModel
{

public:
    SceneDataModel() = default;
    //SceneDataModel(QString caption, ) // TODO
    ~SceneDataModel() = default;

    /// <summary>
    /// Caption of a specific data model instance
    /// </summary>
    /// <returns>Caption of a data model instance</returns>
    QString caption() const override;

    /// <summary>
    /// Sets caption for a data model instance
    /// </summary>
    /// <param name="portType">New caption</param>
    void setCaption(QString caption);

    /// <summary>
    /// Is a caption visible?
    /// </summary>
    /// <returns>true</returns>
    bool captionVisible() const override { return true; }

    /// <summary>
    /// Returns a port caption for a specified port index of a port type
    /// </summary>
    /// <param name="portType">QtNodes::PortType::In or Out</param>
    /// <param name="portIndex">Index of a port - int</param>
    /// <returns></returns>
    QString portCaption(PortType portType, PortIndex portIndex) const override;

    /// <summary>
    ///  It's basically an ID of the data model
    /// </summary>
    /// <returns>Data model ID</returns>
    QString name() const override { return "scene"; }

    /// <summary>
    /// Serializes data model to QJsonObject data type
    /// </summary>
    /// <returns>Serialized data model</returns>
    QJsonObject save() const override;

    /// <summary>
    /// Returns a number of ports for a port type
    /// </summary>
    /// <param name="portType">QtNodes::PortType::In or Out</param>
    /// <returns>Number of ports for a port type</returns>
    unsigned int nPorts(PortType portType) const override; 
    // TODO notes - not sure if changing the number of ports is possible
    // Possibly a recreation of an object may be needed
    // It's possible that a data model of a different class will be needed -> template<size_t In, size_t Out> ?? -> automatic generation of data models

    /// <summary>
    /// TODO most likely returns a data type of a specified port
    /// </summary>
    /// <param name="portType">QtNodes::PortType::In or Out</param>
    /// <param name="portIndex"></param>
    /// <returns></returns>
    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    /// <summary>
    /// Returns a shared pointer to output data from a specified port
    /// </summary>
    /// <param name="port">Index of a port - int</param>
    /// <returns>Shared pointer to output data</returns>
    std::shared_ptr<NodeData> outData(PortIndex port) override;

    /// <summary>
    /// Sets input data of a specified port
    /// </summary>
    /// <param name="nodeData">Shared pointer to data</param>
    /// <param name="port">Index of a port - int</param>
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) override;

    /// <summary>
    /// Returns a pointer to an embedded QWidget
    /// </summary>
    /// <returns>nullptr</returns>
    QWidget* embeddedWidget() override { return nullptr; }

    /// <summary>
    /// TODO Probably for displaying warnings etc
    /// </summary>
    /// <returns></returns>
    NodeValidationState validationState() const override;

    /// <summary>
    /// Returns a message for a current validation state
    /// </summary>
    /// <returns>Message for a current validation state</returns>
    QString validationMessage() const override;

    ConnectionPolicy portInConnectionPolicy(PortIndex) const override { return ConnectionPolicy::One; }

private:
    void restore(const QJsonObject& obj) override;

    QString _caption;
    NodeValidationState _currentValidationState; // TODO What should be the default? NodeValidationState::Warning
    QString _currentValidationMessage; // TODO same as above
};

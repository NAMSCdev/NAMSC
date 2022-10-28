#pragma once
#include <nodes/FlowView>

using namespace QtNodes;

class GraphView: public FlowView
{
public:
	GraphView(FlowScene* scene);
	~GraphView();

	void addNode(const QString& modelName, const QPoint& pos);
	void mousePressEvent(QMouseEvent* event) override;

private:
	QtNodes::FlowScene* _scene;
};


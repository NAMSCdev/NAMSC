#include "ScreenModeSettingsWidget.h"

ScreenModeSettingsWidget::ScreenModeSettingsWidget(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
}

ScreenModeSettingsWidget::~ScreenModeSettingsWidget()
{}

void ScreenModeSettingsWidget::setListener(QObject* receiver, std::function<void(int)> onClicked)
{
	connect(ui.screenModeFullscreenCheckBox, &QCheckBox::stateChanged, receiver, onClicked);
}

#pragma once
#include <QDialog>

#include "ui_ChoiceEventDialog.h"

class ChoiceEventDialog : public QDialog
{
	Q_OBJECT

public:
	ChoiceEventDialog(QWidget *parent = nullptr);
	~ChoiceEventDialog();

private:
	Ui::ChoiceEventDialogClass ui;
};

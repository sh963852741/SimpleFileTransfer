#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include <qthread.h>

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	~QtGuiApplication1();
	void CloseWindows();
private:
	Ui::QtGuiApplication1Class ui;
	QThread receiveFiles;
	QThread sendFiles;
public slots:
	void StopReceiving();
	void ShowMsg();
};

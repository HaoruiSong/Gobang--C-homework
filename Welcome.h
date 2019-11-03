#pragma once
#ifndef WELCOME_H
#define WELCOME_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qdialog.h>
#include <qtsql>
#include <QSqlDatabase>
#include "ui_Welcome.h"
#include "GobangProject.h"
#include "SignUpWidget.h"

class Welcome : public QDialog
{
	Q_OBJECT

public:
	Welcome(QWidget* parent = 0);
	~Welcome();
	QSqlDatabase database;
private:
	Ui::WelcomeDialog ui;
	GobangProject q;
	SignUpWidget* sup;

public slots:
	void sign_in_clicked();
	void sign_up_clicked();
	void receiveData(QString data);   //接收传递过来的数据的槽
};
#endif // !WELCOME_H



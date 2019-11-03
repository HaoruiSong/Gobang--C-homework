#pragma once
#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QtWidgets/qdialog.h>
#include <ui_SignUpWidget.h>
#include <GobangProject.h>
#include <qtsql>
#include <qsqldatabase.h>
#include <qdialog.h>
#include <qmessagebox.h>

class SignUpWidget :
	public QDialog
{

	Q_OBJECT

public:
	SignUpWidget(QWidget* parent = 0);
	~SignUpWidget();
private:
	Ui::SignUpDialog ui;
public slots:
	void sign_up_confirm_clicked();
signals:
	void sendData(QString);   //用来传刚注册的用户名
};

#endif // !SIGNUPWIDGET
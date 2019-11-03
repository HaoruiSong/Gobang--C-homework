#pragma once
#ifndef NEWGAMESTART_H
#define NEWGAMESTART_H

#include <ui_NewGameStart.h>
#include <qdialog.h>
#include <QCloseEvent>
#include <qmessagebox.h>


class NewGameStart :
	public QDialog
{

	Q_OBJECT;
public:
	NewGameStart(QWidget* parent);
	~NewGameStart();
	void setCurrentUser(QString);
	QString getCurrentUser();
	void setCurrentUserLable();
	void closeEvent(QCloseEvent*);
	
private: 
	Ui::NewGame ui;
	QString cuser;


public slots:
	void on_Start_clicked();
};

#endif
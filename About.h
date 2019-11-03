#pragma once
#ifndef ABOUT_H
#define ABOUT_H

#include <ui_About.h>
#include <qdialog.h>
#include <QCloseEvent>

class About :
	public QDialog
{

	Q_OBJECT;
public:
	About(QWidget* parent);
	~About();

private:
	Ui::About ui;
};
#endif // !ABOUT_H

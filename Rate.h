#pragma once
#ifndef _RATE_H
#define _RATE_H

#include <QDialog>
#include <string>
#include <fstream>
#include <iostream>
#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlquerymodel.h>
#include <qmessagebox.h>
#include <qstandarditemmodel.h>
#include "ui_Rate.h"
#include "RANK.h"
#include "Timer.h"
#include "Config.h"


class Rate : public QDialog
{
	Q_OBJECT

public:
	friend class GobangProject;
	Rate(QWidget *parent = Q_NULLPTR);
	~Rate();
	void print_rank_list(std::string);
	QSqlDatabase database;
	QStandardItemModel *model = new QStandardItemModel();

private slots:
	void on_refresh_clicked();


private:
	Ui::Rate ui;
};


#endif

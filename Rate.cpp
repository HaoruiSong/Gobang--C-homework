#include "Rate.h"
#include <iostream>
#include <fstream>
using namespace std;
Rate::Rate(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	setFixedSize(907, 566);                     // 禁止拖动窗口大小
	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	setWindowTitle("Rate");
	this->setWindowModality(Qt::WindowModal);
	connect(ui.refresh, SIGNAL(clicked()), this, SLOT(on_refresh_clicked()));

	
	
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("gobangAccount.db");//创建xxx.db文件
	database.setUserName("root");
	database.setPassword("123456");
	if (!database.open())
	{
		QMessageBox::warning(NULL, "Error", "Error: Failed to connect database");
	}

	
	/*model->setHeaderData(0, Qt::Horizontal, QObject::tr("Username"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Total Move"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Time"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Status"));
	ui.tableView->setModel(model);
	this->update();*/
}

Rate::~Rate()
{
	//database.close();
}

void Rate::print_rank_list(string fileName)//print the rank list, take file name as a parameter to choose which file to open
{
	//ui.tableView->setModel(NULL);
	
	model->setHeaderData(0, Qt::Horizontal, QObject::tr("Username"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Total Move"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Time"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Status"));
	ui.tableView->setModel(model);
	this->update();
	ifstream inlist(fileName, ios::in | ios::binary);
	if (!inlist)
	{
		//QMessageBox::warning(this, "ERROR", "File could not be open.");
		//exit(0);
	}

	int counter = 0;

	ranklist rankdata;

	inlist.read(reinterpret_cast<char *>(&rankdata), sizeof(rankdata));

	while (inlist && !inlist.eof())
	{
		if (rankdata.getname() != "")
		{
			++counter;
			QString u = QString::fromStdString(rankdata.getname());
			model->setItem(counter-1, 0, new QStandardItem(u));
			QString moveString = QString::number(rankdata.getmove());
			model->setItem(counter-1, 1, new QStandardItem(moveString));
			QString timeString = QString::number(rankdata.gettime()) + " s";
			model->setItem(counter-1, 2, new QStandardItem(timeString));
			QString winToString = (rankdata.getwin()) ? "Win" : "Lose";
			model->setItem(counter - 1, 3, new QStandardItem(winToString));
			update();
		}
		inlist.read(reinterpret_cast<char *>(&rankdata),
			sizeof(rankdata));
	}
	update();
	
}

void Rate::on_refresh_clicked()
{
	model->clear();
	ui.tableView->setModel(model);
	this->update();
	ui.tableView->update();
	QString difficulty = ui.comboBox->currentText();
	
	if (difficulty == "Easy")
	{
		QString temp = "RankList_easy.dat";
		std::string a = temp.toStdString();
		print_rank_list(a);
	}
	else if (difficulty == "Normal")
	{
		QString temp = "RankList_normal.dat";
		std::string a = temp.toStdString();
		print_rank_list(a);
	}
	else if (difficulty == "Hard")
	{
		QString temp = "RankList_hard.dat";
		std::string a = temp.toStdString();
		print_rank_list(a);
	}
	else if (difficulty == "Expert")
	{
		QString temp = "RankList_expert.dat";
		std::string a = temp.toStdString();
		print_rank_list(a);
	}
	else if (difficulty == "Master")
	{
		QString temp = "RankList_master.dat";
		std::string a = temp.toStdString();
		print_rank_list(a);
	}
	this->update();
	//std::string a = Config::fileName0.toStdString();
	//print_rank_list(a);
}

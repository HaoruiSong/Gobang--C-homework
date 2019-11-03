#include "NewGameStart.h"
#include "GobangProject.h"
#include <QString>
using namespace std;

NewGameStart::NewGameStart(QWidget* parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	setFixedSize(644, 394);                     // 禁止拖动窗口大小
	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	setWindowTitle("Start a new game");
	this->setWindowModality(Qt::WindowModal);
	
}


NewGameStart::~NewGameStart()
{
}

void NewGameStart::setCurrentUser(QString c)
{
	cuser = c;
}

QString NewGameStart::getCurrentUser()
{
	return cuser;
}

void NewGameStart::on_Start_clicked()
{
	QRadioButton* pbtn = qobject_cast<QRadioButton*>(ui.BG->checkedButton());
	QString name = pbtn->objectName();
	QString difficulty = ui.comboBox->currentText();
	if (difficulty == "Easy")
	{
		Config::searchDeep = 2;
		Config::star = true;
		Config::fileName0 = "RankList_easy.dat";
	}
	else if (difficulty == "Normal")
	{
		Config::searchDeep = 4; 
		Config::star = true;
		Config::fileName0 = "RankList_normal.dat";
		//GobangProject::setFileName("RankList_normal.dat");

	}
	else if (difficulty == "Hard")
	{
		Config::searchDeep = 6; 
		Config::star = true;
		Config::fileName0 = "RankList_hard.dat";
		//GobangProject::setFileName("RankList_hard.dat");

	}
	else if (difficulty == "Expert")
	{
		Config::searchDeep = 8;
		Config::star = true;
		Config::fileName0 = "RankList_expert.dat";
		//GobangProject::setFileName("RankList_expert.dat");

	}
	else if (difficulty == "Master")
	{
		Config::searchDeep = 8;
		Config::star = false;
		Config::fileName0 = "RankList_master.dat";
		//GobangProject::setFileName("RankList_master.dat");

	}


	if (!QString::compare(name, "PVP"))
	{
		QMessageBox::information(this, "Tips", "PVP", QMessageBox::Ok);
		GobangProject::gameMode = GobangProject::PVP;
	}
	else if (!QString::compare(name, "UserFirst"))
	{
		QMessageBox::information(this, "Tips", "UserFirst\nDifficulty: " + difficulty, QMessageBox::Ok);
		GobangProject::gameMode = GobangProject::USERFIRST;
	}
	else
	{
		QMessageBox::information(this, "Tips", "AIFirst\nDifficulty: " + difficulty, QMessageBox::Ok);
		GobangProject::gameMode = GobangProject::AIFIRST;
	}
	
	

	this->accept();
}

void NewGameStart::setCurrentUserLable()
{
	ui.Currentuser->setText("Current user : " + cuser);
}

void NewGameStart::closeEvent(QCloseEvent* event)
{
	int choose;
	choose = QMessageBox::question(this, tr("Exit"),
		QString(tr("Are you sure to exit?")),
		QMessageBox::Yes | QMessageBox::No);

	if (choose == QMessageBox::No)
	{
		event->ignore();
	}
	else if (choose == QMessageBox::Yes)
	{
		exit(0);
	}
}

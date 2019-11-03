
#include "GobangProject.h"
#include "AI.h"
#include <cmath>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QTextOption>
#include <QFileDialog>
#include <qtextstream.h>
//#include "ui_GobangProject.h"
#include <fstream>
#include <iostream>
#include <QString>
#include "Rate.h"
#include "FileProcessing.h"
using namespace std;


int GobangProject::gameMode = NULLMODE;
GobangProject::GobangProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
	setFixedSize(this->width(), this->height());                     // 禁止拖动窗口大小
	setWindowTitle("Alpha Bang v4.0");
	initializeBoard();

	QMainWindow* mainForm = this;
	rate = new Rate(mainForm); //传入父窗口
	//初始化排行榜窗口
	//isStart = false;
	//stepTimer = new QTimer;
	//gameTimer = new QTimer;
	//TimeRecord = new QTime(0, 0, 0);

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(menuGame_actionExit()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(menuAbout_actionAbout()));
	connect(ui.actionNew_Game, SIGNAL(triggered()), this, SLOT(menuGame_actionNew_Game()));
	connect(ui.actionRank_List, SIGNAL(triggered()), this, SLOT(menuGame_actionRank_List()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	//connect(stepTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
	//connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateTime()));


	fstream datafileeasy;
	fstream datafilenormal;
	fstream datafilehard;
	fstream datafileexpert;
	fstream datafilemaster;
	datafileeasy.open("RankList_easy.dat", ios::out | ios::in | ios::binary);
	datafilenormal.open("RankList_normal.dat", ios::out | ios::in | ios::binary);
	datafilehard.open("RankList_hard.dat", ios::out | ios::in | ios::binary);
	datafileexpert.open("RankList_expert.dat", ios::out | ios::in | ios::binary);
	datafilemaster.open("RankList_master.dat", ios::out | ios::in | ios::binary);
	if (datafileeasy&&datafilenormal&&datafilehard&&datafileexpert&&datafilemaster)
	{
		datafileeasy.close();
		datafilenormal.close();
		datafilehard.close();
		datafileexpert.close();
		datafilemaster.close();
	}
	else
	{
		if (!datafileeasy)
		{
			initialize_list("RankList_easy.dat");
		}
		if (!datafilenormal)
		{
			initialize_list("RankList_normal.dat");
		}
		if (!datafilehard)
		{
			initialize_list("RankList_hard.dat");
		}
		if (!datafileexpert)
		{
			initialize_list("RankList_expert.dat");
		}
		if (!datafilemaster)
		{
			initialize_list("RankList_master.dat");
		}
	}
}

void GobangProject::on_pushButton_clicked() 
{
	//QMainWindow* mainForm = this;
	//rate = new Rate(mainForm); //传入父窗口
	rate->show();
}

//void GobangProject::updateTime()
//{
//	//*TimeRecord = TimeRecord->addSecs(1);
//	
//}

void GobangProject::paintEvent(QPaintEvent*event)
{
	paint = new QPainter;
	paint->begin(this);
	paint->setPen(QPen(Qt::black, 3, Qt::SolidLine));//钢笔工具：颜色，线号，实线
	QFont drawFont("Arial", fontSize, QFont::Light, false);
	
	QPainter paintString(this);
	paintString.setFont(drawFont);
	paintString.setPen(Qt::black);

	

	for (int i = 0; i < sizeOfBorad; i++)
	{
		QPoint point1(spaceOfEachCell * i + 50, 50 + menuHeight);
		QPoint point2(spaceOfEachCell * i + 50,
			50 + spaceOfEachCell * (sizeOfBorad - 1) + menuHeight);
		paint->drawLine(point1,point2);
		if (i >= 9)
		{
			QPoint pointString(point1.x() - 2 * horizontalBias, point1.y() - fontSize / 2);
			paintString.drawText(pointString, QString::number(i + 1, 10));
		}
		else
		{
			QPoint pointString(point1.x() - horizontalBias, point1.y() - fontSize / 2);
			paintString.drawText(pointString, QString::number(i + 1, 10));
		}
	}

	for (int i = 0; i < sizeOfBorad; i++)
	{
		QPoint point3(50 , spaceOfEachCell * i + 50 + menuHeight);
		QPoint point4(50 + spaceOfEachCell * (sizeOfBorad - 1), 
			spaceOfEachCell * i + 50 + menuHeight);
		paint->drawLine(point3,point4);
		if (i + 1 < 10)
		{
			QPoint pointString(point3.x() - 9 * horizontalBias, point3.y() + 3 * horizontalBias);
			paintString.drawText(pointString, " " + QString::number(i + 1, 10));

		}
		else
		{
			QPoint pointString(point3.x() - 9 * horizontalBias, point3.y() + 3 * horizontalBias);
			paintString.drawText(pointString, QString::number(i + 1, 10));
		}
	}
	
	//绘制棋子
	QPainter g0(this);
	//g0.drawImage(100, 100, blackChess);
	
	QPoint thisPoint(x, y);
	QPoint tempThisPoint = standardizing(thisPoint, sizeOfChessPicture);
	for (int i = 0; i < sizeOfBorad; i++)
		for (int j = 0; j < sizeOfBorad; j++)
		{
			QPoint temp(i, j);
			QPoint tempP = standardizing(temp, sizeOfChessPicture);
			if (tempx == i && tempy == j)
			{
				g0.drawImage(tempP.x(),tempP.y(), (checkerBoard[i][j] == BLACK) ? presentBlackChess : presentWhiteChess);
				continue;
			}
			if (checkerBoard[i][j] == BLACK)
			{
				g0.drawImage(tempP.x(),tempP.y(), blackChess);			
			}
			else if (checkerBoard[i][j] == WHITE)
			{
				g0.drawImage(tempP.x(), tempP.y(), whiteChess);
			}
		}


	if (gameMode == AIFIRST && cnt == 0)
	{
		point p = game0.begin();
		QPoint p0(p.x, p.y);
		ChessMove(p0, BLACK);
		cnt++;

		this->update();
	}
	
}


void GobangProject::mousePressEvent(QMouseEvent* m)
{
	/*this->update();
	if (!boardEnable)
	{
		return;
	}*/

	QString coursePosition;
	QString coursePosition0;
	
	QPoint coursePoint = m->globalPos() - frameGeometry().topLeft();//获取当前光标的位置
	QPoint pointOnBoard = optimizePoints(coursePoint);

	if (pointOnBoard.x() > 14 || pointOnBoard.x() < 0 ||
		pointOnBoard.y() > 14 || pointOnBoard.y() < 0 ||
		checkerBoard[pointOnBoard.x()][pointOnBoard.y()]!=0)
	{
		return;
	}
	if (m->button() == Qt::LeftButton)
	{

		/*temp_x.setNum(coursePoint.x());
		temp_y.setNum(coursePoint.y());
		coursePosition.append(" X- ");
		coursePosition.append(temp_x);
		coursePosition.append(" Y- ");
		coursePosition.append(temp_y);
		ui.label->setText(coursePosition);*/

		temp_x.setNum(pointOnBoard.x());
		temp_y.setNum(pointOnBoard.y());
		coursePosition0.append(" X- ");
		coursePosition0.append(temp_x);
		coursePosition0.append(" Y- ");
		coursePosition0.append(temp_y);
		ui.textEdit->setText(coursePosition0);
		
		clickPosRow = pointOnBoard.y();
		clickPosCol = pointOnBoard.x();
	}
	update();

	clickPosCol = pointOnBoard.x();
	clickPosRow = pointOnBoard.y();
	
	if (gameMode == PVP)
	{
		//QMessageBox::information(this, "", "我还没做好", QMessageBox::Ok);
		ChessMove(pointOnBoard, current);
		//userx = pointOnBoard.x();
		//usery = pointOnBoard.y();
		game0.set(pointOnBoard.x(), pointOnBoard.y(), current);
		boardEnable = false;
		cnt++;
		if (cnt == sizeOfBorad * sizeOfBorad)
		{
			drawDialog();
			return;
		}
		if (game0.check()!= 0)
		{
			cheakDialogPVP();
			return;
		}
		current = 3 - current;
		
	}

	else if (gameMode == AIFIRST)
	{
		ChessMove(pointOnBoard, WHITE);
		game0.set(clickPosCol, clickPosRow, Role::hum);
		///
		if (cnt == 0)
		{
			game0.resetTime();
		}
		boardEnable = false;
		cnt++;
		if (cnt == sizeOfBorad * sizeOfBorad)
		{
			drawDialog();
			return;
		}
		if (game0.check()!=0)
		{
			end = true;
			cheakDialog();
			return;
		}
		
		//point result = game0.turn(pointOnBoard.x(), pointOnBoard.y());
		//QPoint qresult(result.x, result.y);
		//ChessMove(qresult, BLACK);
		//if (game0.check() != 0)
		//{
		//	cheakDialog();
		//	return;
		//}
		//cnt++;
		//boardEnable = true;
		////cnt++;
	}
	
	else if (gameMode == USERFIRST)
	{
		ChessMove(pointOnBoard, BLACK);
		game0.set(clickPosCol, clickPosRow, Role::hum);
		///
		if (cnt == 0)
		{
			game0.resetTime();
		}
		boardEnable = false;
		cnt++;
		if (cnt == sizeOfBorad * sizeOfBorad)
		{
			drawDialog();
			return;
		}
		if (game0.check() != 0)
		{
			end = true;
			cheakDialog();
			return;
		}
		
		/*point result = game0.turn(pointOnBoard.x(), pointOnBoard.y());
		QPoint qresult(result.x, result.y);
		ChessMove(qresult, WHITE);
		if (game0.check() != 0)
		{
			cheakDialog();
			return;
		}
		boardEnable = true;
		cnt++;*/
	}
	
	//else
	//{
	//	QString coursePosition;
	//	QString coursePosition0;
	//	QString temp_x;
	//	QString temp_y;
	//	QPoint coursePoint = m->globalPos() - frameGeometry().topLeft();//获取当前光标的位置
	//	QPoint pointOnBoard = optimizePoints(coursePoint);
	//	if (m->button() == Qt::LeftButton)
	//	{

	//		temp_x.setNum(coursePoint.x());
	//		temp_y.setNum(coursePoint.y());
	//		coursePosition.append(" X- ");
	//		coursePosition.append(temp_x);
	//		coursePosition.append(" Y- ");
	//		coursePosition.append(temp_y);
	//		ui.label->setText(coursePosition);

	//		temp_x.setNum(pointOnBoard.x());
	//		temp_y.setNum(pointOnBoard.y());
	//		coursePosition0.append(" X- ");
	//		coursePosition0.append(temp_x);
	//		coursePosition0.append(" Y- ");
	//		coursePosition0.append(temp_y);
	//		ui.textEdit->setText(coursePosition0);

	//		//if (cheak % 2 == WHITE_OFF)
	//		//{
	//		//	if (ChessMove(pointOnBoard, WHITE))
	//		//	{
	//		//		//setTextBox(WhitePresent, optP0);
	//		//		cnt++;
	//		//		cheak++;
	//		//		x = pointOnBoard.x();
	//		//		y = pointOnBoard.y();
	//		//	}
	//		//}
	//		//else
	//		//{
	//		//	if (ChessMove(pointOnBoard, BLACK))
	//		//	{
	//		//		//setTextBox(BlackPresent, optP0);
	//		//		cnt++;
	//		//		cheak++;
	//		//		x = pointOnBoard.x();
	//		//		y = pointOnBoard.y();
	//		//	}
	//		//}
	//		
	//	}
	//	point result = game0.turn(pointOnBoard.x(), pointOnBoard.y());
	//	if (true)
	//	{
	//		ChessMove(pointOnBoard, BLACK);
	//		
	//		QPoint tempAI(result.x, result.y);
	//		ChessMove(tempAI, WHITE);
	//		temp_x.setNum(tempAI.x());
	//		temp_y.setNum(tempAI.y());
	//		coursePosition0.append(" X- ");
	//		coursePosition0.append(temp_x);
	//		coursePosition0.append(" Y- ");
	//		coursePosition0.append(temp_y);
	//		ui.textEdit->setText(coursePosition0);
	//		
	//	}
	//	else
	//	{
	//	}
	//}
	QString cntt;
	cntt.setNum(cnt);
	ui.label->setText(cntt);
	this->update();
}

void GobangProject::mouseReleaseEvent(QMouseEvent* m)
{
	QPoint coursePointR = m->globalPos() - frameGeometry().topLeft();//获取当前光标的位置
	QPoint pointOnBoardR = optimizePoints(coursePointR);

	QString coursePosition0;
	update();
	if (!boardEnable)
	{
		//return;
	}
	if (end)
	{
		return;
	}

	if (pointOnBoardR.x() > 14 || pointOnBoardR.x() < 0 ||
		pointOnBoardR.y() > 14 || pointOnBoardR.y() < 0 ||
		pointOnBoardR.x() != clickPosCol || 
		pointOnBoardR.y() != clickPosRow)
	{
		QMessageBox::warning(this, "Warning", "You can not place your cheaker here.", QMessageBox::Ok);
		return;
	}
	
	if (gameMode == PVP)
	{
		//QMessageBox::information(this, "", "我还没做好", QMessageBox::Ok);
		return;
	}

	else if (gameMode == AIFIRST)
	{
		/*ChessMove(pointOnBoard, WHITE);
		boardEnable = false;
		cnt++;
		if (game0.check() != 0)
		{
			cheakDialog();
			return;
		}*/

		point result = game0.begin();
		QPoint qresult(result.x, result.y);
		clickPosCol = -1;
		clickPosRow = -1;
		temp_x.setNum(qresult.x());
		temp_y.setNum(qresult.y());
		coursePosition0.append(" X- ");
		coursePosition0.append(temp_x);
		coursePosition0.append(" Y- ");
		coursePosition0.append(temp_y);
		ui.textEdit->setText(coursePosition0);
		
		update();
		ChessMove(qresult, BLACK);
		//userx = qresult.x();
		//usery = qresult.y();
		if (game0.check() != 0)
		{
			cheakDialog();
			return;
		}
		cnt++;
		if (cnt == sizeOfBorad * sizeOfBorad)
		{
			drawDialog();
			return;
		}
		boardEnable = true;
		//cnt++;
	}

	else if (gameMode == USERFIRST)
	{
		/*ChessMove(pointOnBoard, BLACK);
		boardEnable = false;
		cnt++;
		if (game0.check() != 0)
		{
			cheakDialog();
			return;
		}*/

		point result = game0.begin();
		QPoint qresult(result.x, result.y);
		clickPosCol = -1;
		clickPosRow = -1;
		temp_x.setNum(qresult.x());
		temp_y.setNum(qresult.y());
		coursePosition0.append(" X- ");
		coursePosition0.append(temp_x);
		coursePosition0.append(" Y- ");
		coursePosition0.append(temp_y);
		ui.textEdit->setText(coursePosition0);
		
		update();
		ChessMove(qresult, WHITE);
		//userx = qresult.x();
		//usery = qresult.y();
		if (game0.check() != 0)
		{
			cheakDialog();
			return;
		}
		cnt++;
		if (cnt == sizeOfBorad * sizeOfBorad)
		{
			drawDialog();
			return;
		}
		boardEnable = true;
	}
	QString cntt;
	cntt.setNum(cnt);
	ui.label->setText(cntt);
	this->update();
	update();
}

QPoint GobangProject::optimizePoints(QPoint p)
{
	double h = round(((double)p.x() - 50) / spaceOfEachCell);
	double v = round(((double)p.y() - 118) / spaceOfEachCell);		//118直接暴力修正（手动滑稽
	QPoint ans((int)(h), (int)(v));
	return ans;
}

void GobangProject::cheakDialog()
{
	bool u = false;
	if (game0.check() == 1)
	{
		QMessageBox::information(this, "Game Over", "You lose.", QMessageBox::Ok);
		u = false;
	}
	else if (game0.check() == 2)
	{
		QMessageBox::information(this, "Congratulations!", "You win!" , QMessageBox::Ok);
		u = true;
	}

	long time = game0.getTime();
	//time /= 1000;
	
	QString timeString = QString::number(time);
	QString cntString = QString::number(cnt);
	write(cnt, time, u);
	if (game0.check() == 1)
	{
		QMessageBox::information(this, "Notice", "Total time: " + timeString + "s\nTotal steps: " + cntString, QMessageBox::Ok);
	}
	else if (game0.check() == 2)
	{
		QMessageBox::information(this, "Notice", "Total time: " + timeString + "s\nTotal steps: " + cntString, QMessageBox::Ok);
	}
	initializeBoard();
	//game0.start();
	this->update();
	ng->show();
}



void GobangProject::cheakDialogPVP()
{
	if (game0.check() == 1)
		QMessageBox::information(this, "Congratulations!", "Black wins!", QMessageBox::Ok);
	else if (game0.check() == 2)
		QMessageBox::information(this, "Congratulations!", "White wins!", QMessageBox::Ok);
	initializeBoard();
	//game0.start();
	this->update();
	ng->show();
}

void GobangProject::drawDialog()
{
	QMessageBox::information(this, "Notice", "Game is draw.", QMessageBox::Ok);
	initializeBoard();
	//game0.start();
	this->update();
	ng->show();
}

bool GobangProject::ChessMove(QPoint p, int a)
{
	/*QPixmap pixmap;
	pixmap.convertFromImage(blackChess);
	QLabel label;
	label.setGeometry(p.x(), p.y(), 30, 30);
	label.setPixmap(pixmap);*/

	if (p.y() >= 0 && p.y() <= sizeOfBorad - 1 && p.x() >= 0 && p.x() <= sizeOfBorad - 1)
	{
		if (checkerBoard[p.x()][p.y()] == 0)
		{
			//落子
			checkerBoard[p.x()][p.y()] = a;
			tempx = p.x();
			tempy = p.y();
			return true;
		}
	}
	return false;
}

void GobangProject::initializeBoard()
{
	for (int i = 0; i < sizeOfBorad; i++)
	{
		for (int j = 0; j < sizeOfBorad; j++)
		{
			checkerBoard[i][j] = 0;
		}
	}
	game0.resetTime();
	ui.label->setText("");
	this->update();
	game0.start();
	cnt = 0;
	boardEnable = true;
	tempx = -1;
	tempy = -1;
	end = false;
	gameMode = NULLMODE;

}

QPoint GobangProject::standardizing(QPoint p, int Correctedvalue)
{
	//这个函数把取到的棋盘上的（不是原始的）点向左上方平移，使得画的棋子的中心与网格交点重合
	//其中Correctvalue表示平移的距离大小
	QPoint returnPoint0 
	(p.x() * spaceOfEachCell + 50 - Correctedvalue,
		p.y() * spaceOfEachCell + 68 /*- Correctedvalue*/);	//118暴力修正
	return returnPoint0;
}

void GobangProject::setCurrentUser(QString u)
{
	currentUser = u;
}


void GobangProject::startNewGame()
{
	QMainWindow* mainForm = this;
	ng = new NewGameStart(mainForm); //传入父窗口
	ng->setCurrentUser(currentUser);
	ng->setCurrentUserLable();
	ng->show();
	
}

void GobangProject::write(int move, long time, bool win)
{
	std::string fileName = Config::fileName0.toStdString();
	cout << "enter write" << endl;
	if (!decide_write(move, time, fileName))
	{
		//QMessageBox::information(this, "Notice", "Sorry, you are not able to crack in top 10.");
		return;
	}
	//QMessageBox::information(this, "Notice", "Congratulations! You have made into top 10.");

	ranklist rankdata;

	//set the data
	rankdata.setmove(move);
	string a = currentUser.toStdString();
	rankdata.setname(a);
	rankdata.settime(time);
	rankdata.setwin(win);

	fstream outlist(fileName, ios::out | ios::in | ios::binary);

	if (!outlist)
	{
		//QMessageBox::warning(this, "ERROR", "File could not be open.");
		//exit(EXIT_FAILURE);
	}



	int rank = 1;
	while (rank < 11)
	{
		if (read_one(rank, fileName).getmove() == 0)
		{
			outlist.seekp((rank - 1) * sizeof(ranklist));
			outlist.write(reinterpret_cast<char *>(&rankdata), sizeof(ranklist));
			break;
		}
		if (rankdata.getmove() > read_one(rank, fileName).getmove())
		{
			++rank;
			continue;
		}
		else if (rankdata.getmove() == read_one(rank, fileName).getmove())
		{

			if (rankdata.gettime() <= read_one(rank, fileName).gettime())
			{

				for (int i = 9; i >= rank; i--)
				{
					ranklist temp(read_one(i, fileName).getname(),
						read_one(i, fileName).getmove(), read_one(i, fileName).gettime());

					outlist.seekp((i) * sizeof(ranklist));
					outlist.write(reinterpret_cast<char *>(&temp), (sizeof(ranklist)));
				}
				outlist.seekp((rank - 1) * sizeof(ranklist));
				outlist.write(reinterpret_cast<char *>(&rankdata), sizeof(ranklist));
				break;
			}
			else
			{
				++rank;
				continue;
			}
		}
		else
		{
			for (int i = 9; i >= rank; i--)
			{
				ranklist temp(read_one(i, fileName).getname(), read_one(i, fileName).getmove(), read_one(i, fileName).gettime());

				outlist.seekp((i) * sizeof(ranklist));
				outlist.write(reinterpret_cast<char *>(&temp), (sizeof(ranklist)));
			}
			outlist.seekp((rank - 1) * sizeof(ranklist));
			outlist.write(reinterpret_cast<char *>(&rankdata), sizeof(ranklist));
			break;
		}
	}


}

//void GobangProject::stepTimerStart()
//{
//	stepTimer->start(1000);
//}

//void GobangProject::setFileName(std::string a)
//{
//	fileName = a;
//}

void GobangProject::menuGame_actionExit()
{
	int choose;
	choose = QMessageBox::question(this, tr("Exit"),
		QString(tr("Are you sure to exit?")),
		QMessageBox::Yes | QMessageBox::No);

	if (choose == QMessageBox::Yes)
	{
		exit(0);
	}
}

void GobangProject::menuAbout_actionAbout()
{
	QMainWindow* mainForm = this;
	ab = new About(mainForm); //传入父窗口
	ab->show();
}

void GobangProject::menuGame_actionNew_Game()
{
	QMainWindow* mainForm = this;
	ng = new NewGameStart(mainForm); //传入父窗口
	ng->setCurrentUser(currentUser);
	ng->setCurrentUserLable();
	ng->show();
}

void GobangProject::menuGame_actionRank_List()
{
	QMainWindow* mainForm = this;
	rate = new Rate(mainForm); //传入父窗口
	rate->show();
}

void GobangProject::on_pushButtonNewGame_clicked()
{
	initializeBoard();
	ng->show();
	//game0.newGame();
}



#pragma once
#ifndef GOBANGPROJECT_H
#define GOBANGPROJECT_H

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include <QImage>
#include <qtimer.h>
#include <QTime>
#include <qtextedit.h>
#include "ui_GobangProject.h"
#include "Game.h"
#include "NewGameStart.h"
#include "About.h"
#include "Rate.h"
#include <string>


class GobangProject : public QMainWindow
{
	Q_OBJECT

public:
	friend class Rate;

	GobangProject(QWidget* parent = Q_NULLPTR);
	const int SIZE = 15;
	const int WIDTH = 40;
	
	Game game0;
	NewGameStart* ng;
	About *ab;
	Rate *rate;
	void paintEvent(QPaintEvent*);								//绘图函数声明
	int win();
	void GobangProject::mousePressEvent(QMouseEvent* m);		//定义鼠标点击的事件
	void GobangProject::mouseReleaseEvent(QMouseEvent* m);		//定义鼠标释放的事件
	QPoint optimizePoints(QPoint p);							//将原始坐标计算为棋盘上的坐标
	void cheakDialog();
	void cheakDialogPVP();
	void drawDialog();
	bool ChessMove(QPoint p, int a);							//落子函数声明
	void initializeBoard();										//初始化棋盘
	QPoint standardizing(QPoint, int);							//平移棋子
	void setCurrentUser(QString);
	//std::string getCurrentUser();
	//QString getCurrentUserQString();
	void startNewGame();
	void write(int, long,bool);
	//void stepTimerStart();										//步长计时器开始计时
	//void stepTimerStop();										//步长计时器停止计时
	//void stepTimerPause();										//步长计时器暂停计时
	//void gameTimerStart();										//整个游戏计时器开始计时
	//void gameTimerStop();										//整个游戏计时器停止计时
	//void gameTimerPause();										//整个游戏计时器暂停计时

	//游戏状态数据
	static const int WHITE_OFF = 0;        //白棋先手：对应2
	static const int BLACK_OFF = 1;        //黑棋先手：对应1
	static const int BLACK = 1;            //放在棋盘里表示黑棋
	static const int WHITE = 2;            //放在棋盘里表示白棋
	int current = 1;
	QString temp_x;
	QString temp_y;
	int tempx = -1;
	int tempy = -1;
	static int gameMode;
	//static QString fileName0;
	//static void setFileName(std::string);

	enum GameMode
	{
		NULLMODE=-1,			//空游戏状态
		AIFIRST,				//电脑先行
		USERFIRST,				//用户先行
		PVP						//对战模式
	};


private slots:
	void on_pushButtonNewGame_clicked();
	void menuGame_actionExit();
	void menuAbout_actionAbout();
	void menuGame_actionNew_Game();
	void menuGame_actionRank_List();
	void on_pushButton_clicked();
	//void updateTime();						//更新时间

private:
	Ui::GobangProjectClass ui;
	//void mousePressEvent(QMouseEvent *);
	QPainter* paint;
	
	//图形绘制数据
	static const int sizeOfBorad = 15;
	static const int spaceOfEachCell = 45;
	static const int radiusOfChess = 12;
	static const int sizeOfChessPicture = 12;
	static const int fontSize = 12;					//边界数字的字号
	static const int menuHeight = 29;
	static const int horizontalBias = 3;			//边界数字位置修正值

	//整个棋盘
	int checkerBoard[sizeOfBorad][sizeOfBorad];

	//游戏数据
	int offensive;
	int defensive;
	int cnt = 0;				//步数记录器
	int cheak = 1;				//落子顺序判定器
	int lastX = 0;				//上一次落子坐标，用于覆盖
	int lastY = 0;				//同上
	bool boardEnable = true;	//控制棋盘是否可用
	int x = -1;					//当前落子位置，下同
	int y = -1;
	int clickPosRow = -1;		//用户临时点击点
	int clickPosCol = -1;
	QString currentUser;
	bool end = false;
	//QTimer * stepTimer;			//单步定时器 每秒更新时间
	//QTimer * gameTimer;			//总棋局计时器 每秒更新时间	
	//QTime * stepTimeRecord;		//记录单步长时间
	//bool isStart;				//记录是否已经开始计时

	//四种棋子图片
	QImage blackChess = QImage(":/GobangProject/Resources/24pixel_BlackChess0.png");
	QImage whiteChess = QImage(":/GobangProject/Resources/24pixel_WhiteChess0.png");
	QImage presentBlackChess = QImage(":/GobangProject/Resources/24pixel_BlackChess0_new.png");
	QImage presentWhiteChess = QImage(":/GobangProject/Resources/24pixel_WhiteChess0_new.png");



};

#endif


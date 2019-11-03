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
	void paintEvent(QPaintEvent*);								//��ͼ��������
	int win();
	void GobangProject::mousePressEvent(QMouseEvent* m);		//������������¼�
	void GobangProject::mouseReleaseEvent(QMouseEvent* m);		//��������ͷŵ��¼�
	QPoint optimizePoints(QPoint p);							//��ԭʼ�������Ϊ�����ϵ�����
	void cheakDialog();
	void cheakDialogPVP();
	void drawDialog();
	bool ChessMove(QPoint p, int a);							//���Ӻ�������
	void initializeBoard();										//��ʼ������
	QPoint standardizing(QPoint, int);							//ƽ������
	void setCurrentUser(QString);
	//std::string getCurrentUser();
	//QString getCurrentUserQString();
	void startNewGame();
	void write(int, long,bool);
	//void stepTimerStart();										//������ʱ����ʼ��ʱ
	//void stepTimerStop();										//������ʱ��ֹͣ��ʱ
	//void stepTimerPause();										//������ʱ����ͣ��ʱ
	//void gameTimerStart();										//������Ϸ��ʱ����ʼ��ʱ
	//void gameTimerStop();										//������Ϸ��ʱ��ֹͣ��ʱ
	//void gameTimerPause();										//������Ϸ��ʱ����ͣ��ʱ

	//��Ϸ״̬����
	static const int WHITE_OFF = 0;        //�������֣���Ӧ2
	static const int BLACK_OFF = 1;        //�������֣���Ӧ1
	static const int BLACK = 1;            //�����������ʾ����
	static const int WHITE = 2;            //�����������ʾ����
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
		NULLMODE=-1,			//����Ϸ״̬
		AIFIRST,				//��������
		USERFIRST,				//�û�����
		PVP						//��սģʽ
	};


private slots:
	void on_pushButtonNewGame_clicked();
	void menuGame_actionExit();
	void menuAbout_actionAbout();
	void menuGame_actionNew_Game();
	void menuGame_actionRank_List();
	void on_pushButton_clicked();
	//void updateTime();						//����ʱ��

private:
	Ui::GobangProjectClass ui;
	//void mousePressEvent(QMouseEvent *);
	QPainter* paint;
	
	//ͼ�λ�������
	static const int sizeOfBorad = 15;
	static const int spaceOfEachCell = 45;
	static const int radiusOfChess = 12;
	static const int sizeOfChessPicture = 12;
	static const int fontSize = 12;					//�߽����ֵ��ֺ�
	static const int menuHeight = 29;
	static const int horizontalBias = 3;			//�߽�����λ������ֵ

	//��������
	int checkerBoard[sizeOfBorad][sizeOfBorad];

	//��Ϸ����
	int offensive;
	int defensive;
	int cnt = 0;				//������¼��
	int cheak = 1;				//����˳���ж���
	int lastX = 0;				//��һ���������꣬���ڸ���
	int lastY = 0;				//ͬ��
	bool boardEnable = true;	//���������Ƿ����
	int x = -1;					//��ǰ����λ�ã���ͬ
	int y = -1;
	int clickPosRow = -1;		//�û���ʱ�����
	int clickPosCol = -1;
	QString currentUser;
	bool end = false;
	//QTimer * stepTimer;			//������ʱ�� ÿ�����ʱ��
	//QTimer * gameTimer;			//����ּ�ʱ�� ÿ�����ʱ��	
	//QTime * stepTimeRecord;		//��¼������ʱ��
	//bool isStart;				//��¼�Ƿ��Ѿ���ʼ��ʱ

	//��������ͼƬ
	QImage blackChess = QImage(":/GobangProject/Resources/24pixel_BlackChess0.png");
	QImage whiteChess = QImage(":/GobangProject/Resources/24pixel_WhiteChess0.png");
	QImage presentBlackChess = QImage(":/GobangProject/Resources/24pixel_BlackChess0_new.png");
	QImage presentWhiteChess = QImage(":/GobangProject/Resources/24pixel_WhiteChess0_new.png");



};

#endif


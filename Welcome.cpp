#include "Welcome.h"
#include <qwidget.h>
#include <QtWidgets/qapplication.h>
#include <qmessagebox.h>



Welcome::Welcome(QWidget* parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	setFixedSize(this->width(), this->height());                     // 禁止拖动窗口大小
	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
	ui.passwordTextBox->setEchoMode(QLineEdit::Password);
	setWindowTitle("Alpha Bang v4.0 - Welcome");
	connect(ui.sign_in, SIGNAL(clicked()), this, SLOT(sign_in_clicked()));
	connect(ui.sign_up, SIGNAL(clicked()), this, SLOT(sign_up_clicked()));
	
	QDialog* dlg = new QDialog;
	connect(dlg, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
	//dlg->show();

	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		database = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		database = QSqlDatabase::addDatabase("QSQLITE");
		database.setDatabaseName("gobangAccount.db");//创建xxx.db文件
		database.setUserName("root");
		database.setPassword("123456");
	}
	if (!database.open())
	{
		QMessageBox::warning(NULL, "Error", "Error: Failed to connect database");
	}

	QSqlQuery sql_query;//这个是数据库操作对象
	QString create_sql = "CREATE TABLE IF NOT EXISTS user_info(username VARCHAR(32) primary key,password VARCHAR(260));";
	
	sql_query.prepare(create_sql);
	if (!sql_query.exec())
	{
		qDebug("Error: Fail to create test table.%s", sql_query.lastError().text());
	}
	else
	{
		qDebug("Table test created!");
	}

	create_sql = "insert into user_info values (?, ?);";
	sql_query.prepare(create_sql);
	sql_query.addBindValue("admin");
	sql_query.addBindValue("12345");

	if (!sql_query.exec())
	{
		qDebug("Error: Fail to insert to info table.%s", sql_query.lastError().text());
	}
	


	QSqlQuery sql_query_data;
	QString create_sql_userdata = "CREATE TABLE IF NOT EXISTS user_data(username VARCHAR(32) primary key,total INT(8),totalwin INT(8),rate DECIMAL(8,2),easy INT(8),easywin INT(8),normal INT(8),normalwin INT(8),hard INT(8),hardwin INT(8),expert INT(8),expertwin INT(8),master INT(8),masterwin INT(8));";

	sql_query_data.prepare(create_sql_userdata);
	if (!sql_query_data.exec())
	{
		qDebug("Error: Fail to create data table.%s", sql_query_data.lastError().text());
	}
	else
	{
		qDebug("Data table created!");
	}

	create_sql_userdata = "insert into user_data values (?,?,?,?,?,?,?,?,?,?,?,?,?,?);";
	sql_query_data.prepare(create_sql_userdata);
	sql_query_data.addBindValue("admin");
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0.0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);
	sql_query_data.addBindValue(0);

	if (!sql_query_data.exec())
	{
		qDebug("Error: Fail to insert to test table.%s", sql_query_data.lastError().text());
	}
	
	database.close();
}


Welcome::~Welcome()
{
}

void Welcome::sign_in_clicked()
{
	if (ui.usernameTextBox->text() == "")
		QMessageBox::warning(this, "Warning", "Username cannot be empty!");
	else if (ui.passwordTextBox->text() == "")
		QMessageBox::warning(this, "Warning", "Password cannot be empty!");
	else
	{
		//
		//if (QSqlDatabase::contains("qt_sql_default_connection"))
		//{
		//	database = QSqlDatabase::database("qt_sql_default_connection");
		//}
		//else
		//{
		//	database = QSqlDatabase::addDatabase("QSQLITE");
		//	database.setDatabaseName("gobangAccount.db");//创建xxx.db文件
		//	database.setUserName("root");
		//	database.setPassword("123456");
		//}
		//if (!database.open())
		//{
		//	QMessageBox::warning(NULL, "Error", "Error: Failed to connect database");
		//}

		//QSqlQuery sql_query;//这个是数据库操作对象
		//QString create_sql = "CREATE TABLE IF NOT EXISTS user_info(username VARCHAR(32) primary key,password VARCHAR(260));";
		//sql_query.prepare(create_sql);
		//if (!sql_query.exec())
		//{
		//	qDebug("Error: Fail to create test table.%s", sql_query.lastError().text());
		//}
		//else
		//{
		//	qDebug("Table test created!");
		//}

		//create_sql = "insert into user_info values (?, ?);";
		//sql_query.prepare(create_sql);
		//sql_query.addBindValue("admin");
		//sql_query.addBindValue("12345");

		//if (!sql_query.exec())
		//{
		//	qDebug("Error: Fail to insert to test table.%s", sql_query.lastError().text());
		//}

		QSqlDatabase database;
		database = QSqlDatabase::addDatabase("QSQLITE");
		database.setDatabaseName("gobangAccount.db");//创建xxx.db文件
		database.setUserName("root");
		database.setPassword("123456");
		QString s = QString("select username,password from user_info where username='%1' and password='%2'")
			.arg(ui.usernameTextBox->text()).arg(ui.passwordTextBox->text());
		if (!database.open())
		{
			QMessageBox::warning(NULL, "Error", "Error: Failed to connect database");
		}
		QSqlQuery query = QSqlQuery(database);

		if (query.exec(s) && query.next())
		{
			database.close();
			this->hide();
			q.setCurrentUser(ui.usernameTextBox->text());
			q.show();
			q.startNewGame();
		}
		else
			QMessageBox::warning(NULL, "Error", "Incorrect username or password!");
		database.close();
	}

	
}

void Welcome::sign_up_clicked()
{
	QDialog* mainForm = this;
	sup = new SignUpWidget(mainForm);//传入父窗口
	sup->show();
	
}

void Welcome::receiveData(QString data)
{
	ui.usernameTextBox->setText(data);
}

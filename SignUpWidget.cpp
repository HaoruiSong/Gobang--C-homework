#include "SignUpWidget.h"



SignUpWidget::SignUpWidget(QWidget* parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint); 
	// 禁止最大化按钮

	ui.conpassword->setEchoMode(QLineEdit::Password);
	ui.password->setEchoMode(QLineEdit::Password);

	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	setWindowTitle("Sign up");
	setFixedSize(453, 333);                     // 禁止拖动窗口大小
	this->setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(sign_up_confirm_clicked()));

}


SignUpWidget::~SignUpWidget()
{

}

void SignUpWidget::sign_up_confirm_clicked()
{
	
	QSqlDatabase database;

	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("gobangAccount.db");//创建xxx.db文件
	database.setUserName("root");
	database.setPassword("123456");

	if (!database.open())
	{
		QMessageBox::warning(NULL, "Error", "Error: Failed to connect database");
	}

	QSqlQuery query(database), sql_query(database);
	QString un=ui.username->text();
	QString pwd=ui.password->text();

	QString select_sql = "select username from user_info";
	//查询是否重名
	bool r = false;
	if (!sql_query.exec(select_sql))
	{
		QMessageBox::warning(NULL, "Error", "Error: Failed to connect database");
	}
	else
	{
		while (sql_query.next())
		{
			QString name = sql_query.value(0).toString();
			if (name == un)
			{
				r = true;
				break;
			}
		}
	}

	if (r)
	{
		QMessageBox::warning(this,"Error","Username is already taken!");
		ui.username->setText("");
		ui.password->setText("");
		ui.conpassword->setText("");
	}
	else if (ui.password->text() != ui.conpassword->text())
	{
		QMessageBox::warning(this, "Error", "The passwords are not equal!");
		ui.password->setText("");
		ui.conpassword->setText("");
	}
	else if (un==""||pwd=="")
	{
		QMessageBox::warning(this, "Error", "Username and password cannot be empty!");
		ui.password->setText("");
		ui.conpassword->setText("");
	}
	else
	{
		QString create_sql = "insert into user_info values (?, ?);";
		sql_query.prepare(create_sql);
		sql_query.addBindValue(un);
		sql_query.addBindValue(pwd);


		QString create_sql_userdata;
		QSqlQuery sql_query_data;
		create_sql_userdata = "insert into user_data values (?,?,?,?,?,?,?,?,?,?,?,?,?,?);";
		sql_query_data.prepare(create_sql_userdata);
		sql_query_data.addBindValue(un);
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		sql_query_data.addBindValue("0");
		if (!sql_query.exec()||!sql_query_data.exec())
		{
			QMessageBox::warning(this, "Error", "Error: Fail to sign up.");
		}
		else
		{
			QMessageBox::information(this, "Notice", "Sign up successfully!");
			emit sendData(un);
			this->accept();

		}
	}
	database.close();
}

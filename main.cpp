#include "GobangProject.h"
#include "Welcome.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	//GobangProject w;
	//w.show();
	Welcome w;
	w.show();
	return a.exec();

}

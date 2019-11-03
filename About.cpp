#include "About.h"
//#include "GobangProject.h"



About::About(QWidget* parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	setFixedSize(673, 480);                     // 禁止拖动窗口大小
	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	setWindowTitle("About");
	this->setWindowModality(Qt::WindowModal);

}


About::~About()
{
}

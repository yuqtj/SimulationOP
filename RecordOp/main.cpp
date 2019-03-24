#include "RecordOp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/RecordOp/Resources/icon.ico"));
	RecordOp w;
	
	return a.exec();
}

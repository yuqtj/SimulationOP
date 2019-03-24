#pragma once
#include <qapplication.h>
class GlobalApplication :
	public QApplication
{
public:
	GlobalApplication(int&argc, char **argv);
	~GlobalApplication();

	virtual bool notify(QObject *, QEvent *) override;

};


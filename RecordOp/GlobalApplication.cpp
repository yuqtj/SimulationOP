#include "GlobalApplication.h"
#include <QKeyEvent>
#include <QMouseEvent>

#ifdef _DEBUG
	#include <QDebug>
#endif


GlobalApplication::GlobalApplication(int&argc, char **argv) : QApplication(argc, argv)
{
}


GlobalApplication::~GlobalApplication()
{
}

bool GlobalApplication::notify(QObject *obj, QEvent *e)
{
	const QMetaObject* objMeta = obj->metaObject();
	QString clName = objMeta->className();

	qDebug() << clName;

	if (e->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(e);
		if (keyEvent->key() == Qt::Key_F1)
		{
		}
	}
	else if (e->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(e);
		if (mouseEvent->buttons() == Qt::LeftButton)
		{
			//qDebug() << "LeftButton";
		}

		if (mouseEvent->buttons() == Qt::RightButton)
		{
			//qDebug() << "RightButton";
		}

		if (mouseEvent->buttons() == Qt::MidButton)
		{
			//qDebug() << "MidButton";
		}
	}

	return QApplication::notify(obj, e);
}

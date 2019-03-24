#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include <QList>
#include <QTime>
#include <QSystemTrayIcon>
#include <QMenu>

#include "ui_RecordOp.h"
#include "windows.h"
#include "XGlobalHook.h"


enum AppState
{
	IDLE,
	RECORDING,
	OPERATING,
	// �ж�
	BREAK,
};

struct OPBase
{
	enum OPType
	{
		MOUSE,
		KEYBOARD
	};

	OPType type;
	int opCode;
	// ����ʱ��������ɲ�����ȴ�internelSecondsʱ�䣬Ĭ��1000����
	int internelSeconds = 1000;
};

struct OPMouse : public OPBase
{
	int x;
	int y;
};

struct OPKeyboard : public OPBase
{
	int isPressed;
};

class RecordOp : public QMainWindow
{
	Q_OBJECT

public:
	RecordOp(QWidget *parent = Q_NULLPTR);
	~RecordOp();

public slots:
	void onStartRecord();
	void onDoOperation();
	void onClearOp();

	void mouseEvent(TRANSFER_PARAM);
	void keyEvent(TRANSFER_PARAM);
	void onActivatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
	void onExitApp();

private:
	// ��ʼ�����̳���
	void initTrayIcon();

private:
	void onStopRecord();
	//
	void addMouseOperate(int x, int y, int opCode);
	void addKeyOperate(int isPressed, int opCode);
	void addOperate(OPBase* op, int opCode);

	void doMouseOperate(OPMouse* op);
	void doKeyOperate(OPKeyboard* op);

private:
	Ui::RecordOpClass ui;
	QList<OPBase*> operations;

	// ���̳���
	QSystemTrayIcon* sysTrayIcon;
	QMenu* trayIconMenu;

	AppState appState;
	// ������������֮��ļ��
	QTime* opTimer;
};

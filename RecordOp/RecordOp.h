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
	// 中断
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
	// 操作时间间隔，完成操作后等待internelSeconds时间，默认1000毫秒
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
	// 初始化托盘程序
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

	// 托盘程序
	QSystemTrayIcon* sysTrayIcon;
	QMenu* trayIconMenu;

	AppState appState;
	// 计算两个操作之间的间隔
	QTime* opTimer;
};

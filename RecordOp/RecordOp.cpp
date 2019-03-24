#include "RecordOp.h"
#include <QIntValidator>
#include <QMessageBox>

#include <QDebug>

RecordOp::RecordOp(QWidget *parent)
	: QMainWindow(parent), appState(IDLE)
{
	ui.setupUi(this);
	QIntValidator* validator = new QIntValidator(0, 100, this);
	ui.operationTimesText->setValidator(validator);
	this->setWindowFlags(Qt::Tool);
	this->show();

	opTimer = new QTime();

	initTrayIcon();

	connect(ui.recordButton, SIGNAL(clicked()), this, SLOT(onStartRecord()));
	connect(ui.operateButton, SIGNAL(clicked()), this, SLOT(onDoOperation()));
	connect(ui.clearButton, SIGNAL(clicked()), this, SLOT(onClearOp()));
	connect(xHook, SIGNAL(mouseEvent(int, WPARAM, LPARAM)), this, SLOT(mouseEvent(int, WPARAM, LPARAM)));
	connect(xHook, SIGNAL(keyEvent(int, WPARAM, LPARAM)), this, SLOT(keyEvent(int, WPARAM, LPARAM)));
}

void RecordOp::initTrayIcon()
{
	sysTrayIcon = new QSystemTrayIcon(this);
	QIcon icon = QIcon(":/RecordOp/Resources/icon.ico");
	sysTrayIcon->setIcon(icon);
	sysTrayIcon->setToolTip("Made in China");

	// Menu
	QAction* exitAct = new QAction("退出", this);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(onExitApp()));

	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(exitAct);
	sysTrayIcon->setContextMenu(trayIconMenu);

	sysTrayIcon->show();

	//给QSystemTrayIcon添加槽函数
	connect(sysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onActivatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
}

RecordOp::~RecordOp()
{
	onClearOp();
}

void RecordOp::onStartRecord()
{
	if (operations.size() > 0)
	{
		if (QMessageBox::question(this, "提示", "你之前的记录还在，确定覆盖?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
		{
			return;
		}
	}

	qDebug() << "Start Record";
	appState = RECORDING;

	onClearOp();

	this->hide();

	xHook->installMouseHook();
	xHook->installKeyHook();

	// 开始计时
	opTimer->restart();
}

void RecordOp::onStopRecord()
{
	xHook->uninstallMouseHook();
	xHook->uninstallKeyHook();

	this->show();

	appState = IDLE;
	qDebug() << "End Record";
}

void RecordOp::onDoOperation()
{
	this->hide();
	appState = OPERATING;

	QString operateTimesStr = ui.operationTimesText->text();
	// 循环执行次数，默认为1次
	int operateTimes = 1;
	if (!operateTimesStr.isEmpty())
	{
		operateTimes = operateTimesStr.toInt();
	}
	for (int i = 0; i < operateTimes; i++)
	{
		for each (OPBase* op in operations)
		{
			if (op->type == OPBase::MOUSE)
			{
				OPMouse* mouseOp = static_cast<OPMouse*>(op);
				doMouseOperate(mouseOp);
			}
			else if (op->type == OPBase::KEYBOARD)
			{
				OPKeyboard* keyOp = static_cast<OPKeyboard*>(op);
				doKeyOperate(keyOp);
			}

			if (appState == BREAK)
			{
				qDebug() << "Op Break!";
				break;
			}

			Sleep(op->internelSeconds);
		}
	}

	appState = IDLE;
	this->show();

	qDebug() << "Op Completed!";
}

void RecordOp::onClearOp()
{
	for each (OPBase* op in operations)
	{
		delete op;
	}

	operations.clear();
	qDebug() << "had Clear!";
}

void RecordOp::addMouseOperate(int x, int y, int opCode)
{
	static int lastX = -1;
	static int lastY = -1;
	static int lastOpCode = 0;
	// 看上一个信息的鼠标事件是否在同一位置，防止频繁构建
	if (lastOpCode == opCode && lastX == x && lastY == y)
	{
		return;
	}
	
	lastX = x;
	lastY = y;
	lastOpCode = opCode;

	OPMouse* op = new OPMouse();
	op->type = OPBase::MOUSE;
	op->x = x;
	op->y = y;

	addOperate(op, opCode);
}

void RecordOp::addKeyOperate(int isPressed, int opCode)
{
	OPKeyboard* op = new OPKeyboard();
	op->type = OPBase::KEYBOARD;
	op->isPressed = isPressed;

	addOperate(op, opCode);
}

void RecordOp::addOperate(OPBase* op, int opCode)
{
	op->opCode = opCode;
	op->internelSeconds = opTimer->restart();

	operations.append(op);

	qDebug() << "addOperate";
	qDebug() << op->internelSeconds;
}

void RecordOp::doMouseOperate(OPMouse* op)
{
	SetCursorPos(op->x, op->y);
	mouse_event(op->opCode, 0, 0, 0, 0);
}

void RecordOp::doKeyOperate(OPKeyboard* op)
{
	keybd_event(op->opCode, 0, op->isPressed, 0);
}

void RecordOp::mouseEvent(TRANSFER_PARAM)
{
	PMOUSEHOOKSTRUCT pMouseHookStruct = (PMOUSEHOOKSTRUCT)lParam;
	int x = pMouseHookStruct->pt.x;
	int y = pMouseHookStruct->pt.y;
	//qDebug() << "Mouse X:" << pMouseHookStruct->pt.x;
	//qDebug() << "Mouse Y:" << pMouseHookStruct->pt.y;

	switch (wParam)
	{
	case WM_LBUTTONDOWN:
		qDebug() << "Mouse Left Button Down:";
		addMouseOperate(x, y, MOUSEEVENTF_LEFTDOWN);
		break;

	case WM_RBUTTONDOWN:
		//qDebug() << "Mouse Right Button Down:";
		addMouseOperate(x, y, MOUSEEVENTF_RIGHTDOWN);
		break;

	case WM_LBUTTONUP:
		qDebug() << "Mouse Left Button Up:";
		addMouseOperate(x, y, MOUSEEVENTF_LEFTUP);
		break;

	case WM_RBUTTONUP:
		//qDebug() << "Mouse Right Button Up:";
		addMouseOperate(x, y, MOUSEEVENTF_RIGHTUP);
		break;

	case WM_MOUSEMOVE:
		addMouseOperate(x, y, MOUSEEVENTF_MOVE);
		break;

	// 按下鼠标中键后停止录制
	case WM_MBUTTONDOWN:
		if (appState == OPERATING)
		{
			appState = BREAK;
		}
		else if (appState == RECORDING)
		{
			onStopRecord();
		}
		break;

	default:
		break;
	}
	
}

void RecordOp::keyEvent(TRANSFER_PARAM)
{
	PKBDLLHOOKSTRUCT pKeyHookStruct = (PKBDLLHOOKSTRUCT)lParam;

	switch (wParam)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		addKeyOperate(0, pKeyHookStruct->vkCode);
		qDebug() << "WM_KEYDOWN" << pKeyHookStruct->vkCode;

		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		addKeyOperate(KEYEVENTF_KEYUP, pKeyHookStruct->vkCode);
		qDebug() << "WM_KEYUP" << pKeyHookStruct->vkCode;

		break;
	}
}

void RecordOp::onActivatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::DoubleClick:
	case QSystemTrayIcon::Trigger:
		this->show();
		break;

	default:
		break;
	}
}

void RecordOp::onExitApp()
{
	exit(0);
}

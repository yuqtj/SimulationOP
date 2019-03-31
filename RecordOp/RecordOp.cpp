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

	updateTable();
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
	QAction* exitAct = new QAction("�˳�", this);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(onExitApp()));

	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(exitAct);
	sysTrayIcon->setContextMenu(trayIconMenu);

	sysTrayIcon->show();

	//��QSystemTrayIcon��Ӳۺ���
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
		if (QMessageBox::question(this, "��ʾ", "��֮ǰ�ļ�¼���ڣ�ȷ������?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
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

	// ��ʼ��ʱ
	opTimer->restart();
}

void RecordOp::onStopRecord()
{
	xHook->uninstallMouseHook();
	xHook->uninstallKeyHook();

	// ��ʾ����UI
	showOP();

	this->show();

	appState = IDLE;
	qDebug() << "End Record";
}

void RecordOp::onDoOperation()
{
	// ��Table����������operations
	generateOPFromTable();

	this->hide();
	appState = OPERATING;

	QString operateTimesStr = ui.operationTimesText->text();
	// ѭ��ִ�д�����Ĭ��Ϊ1��
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
	// ���Table
	ui.opTable->clear();
	updateTable();

	clearOP();
}

void RecordOp::addMouseOperate(int x, int y, int opCode, const QString& opCodeText)
{
	static int lastX = -1;
	static int lastY = -1;
	static int lastOpCode = 0;
	// ����һ����Ϣ������¼��Ƿ���ͬһλ�ã���ֹƵ������
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

	addOperate(op, opCode, opCodeText);
}

void RecordOp::addKeyOperate(int isPressed, int opCode, const QString& opCodeText)
{
	OPKeyboard* op = new OPKeyboard();
	op->type = OPBase::KEYBOARD;
	op->isPressed = isPressed;

	addOperate(op, opCode, opCodeText);
}

void RecordOp::addOperate(OPBase* op, int opCode, const QString& opCodeText)
{
	op->opCode = opCode;
	op->internelSeconds = opTimer->restart();
	op->opCodeText = opCodeText;

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

void RecordOp::showOP()
{
	int length = operations.size();
	ui.opTable->setRowCount(length);
	for (int i = 0; i < length; i++)
	{
		OPBase* opBase = operations[i];

		if (opBase->type == OPBase::MOUSE)
		{
			ui.opTable->setItem(i, 0, new QTableWidgetItem("���"));
			
			OPMouse* opMouse = static_cast<OPMouse*>(opBase);
			ui.opTable->setItem(i, 3, new QTableWidgetItem(QString::number(opMouse->x)));
			ui.opTable->setItem(i, 4, new QTableWidgetItem(QString::number(opMouse->y)));
		}
		else if (opBase->type == OPBase::KEYBOARD)
		{
			ui.opTable->setItem(i, 0, new QTableWidgetItem("����"));
			OPKeyboard* opKeyboard = static_cast<OPKeyboard*>(opBase);
			ui.opTable->setItem(i, 5, new QTableWidgetItem(QString::number(opKeyboard->isPressed)));
		}

		if (opBase->opCodeText == "")
		{
			ui.opTable->setItem(i, 1, new QTableWidgetItem(QString::number(opBase->opCode)));
		}
		else
		{
			ui.opTable->setItem(i, 1, new QTableWidgetItem(opBase->opCodeText));
		}
		ui.opTable->setItem(i, 2, new QTableWidgetItem(QString::number(opBase->internelSeconds)));
		ui.opTable->setItem(i, 6, new QTableWidgetItem(QString::number(opBase->opCode)));
	}

	updateTable();
}

void RecordOp::generateOPFromTable()
{
	// ���ڼ�һ����ʶ���������ı�ʱ����������
	if (false)
	{
		return;
	}

	clearOP();
	
	int length = ui.opTable->rowCount();
	operations.reserve(length);
	
	for (int i = 0; i < length; i++)
	{
		OPBase* opBase = nullptr;
		QString opType = ui.opTable->item(i, 0)->text();
		if (opType == "���")
		{
			OPMouse* opMouse = new OPMouse();
			QString mouseXText = ui.opTable->item(i, 3)->text();
			QString mouseYText = ui.opTable->item(i, 4)->text();
			
			opMouse->x = mouseXText.toInt();
			opMouse->y = mouseYText.toInt();

			opBase = opMouse;
		}
		else if (opType == "����")
		{
			OPKeyboard* opKeyboard = new OPKeyboard();
			QString isPressedText = ui.opTable->item(i, 5)->text();
			opKeyboard->isPressed = isPressedText.toInt();
			
			opBase = opKeyboard;
		}

		if (opBase)
		{
			QString internelSecondsText = ui.opTable->item(i, 2)->text();
			opBase->internelSeconds = internelSecondsText.toInt();

			QString opCode = ui.opTable->item(i, 6)->text();
			opBase->opCode = opCode.toInt();

			operations.push_back(opBase);
		}
	}
}

void RecordOp::updateTable()
{
	ui.opTable->setColumnCount(7);
	ui.opTable->setHorizontalHeaderLabels(QStringList() << "�����¼�" << "��������" << "ʱ����" << "���X" << "���Y" << "����״̬" << "OpCode");
}

void RecordOp::clearOP()
{
	for each (OPBase* op in operations)
	{
		delete op;
	}

	operations.clear();
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
		addMouseOperate(x, y, MOUSEEVENTF_LEFTDOWN, "WM_LBUTTONDOWN");
		break;

	case WM_RBUTTONDOWN:
		//qDebug() << "Mouse Right Button Down:";
		addMouseOperate(x, y, MOUSEEVENTF_RIGHTDOWN, "WM_RBUTTONDOWN");
		break;

	case WM_LBUTTONUP:
		qDebug() << "Mouse Left Button Up:";
		addMouseOperate(x, y, MOUSEEVENTF_LEFTUP, "WM_LBUTTONUP");
		break;

	case WM_RBUTTONUP:
		//qDebug() << "Mouse Right Button Up:";
		addMouseOperate(x, y, MOUSEEVENTF_RIGHTUP, "WM_RBUTTONUP");
		break;

	case WM_MOUSEMOVE:
		addMouseOperate(x, y, MOUSEEVENTF_MOVE, "WM_MOUSEMOVE");
		break;

	// ��������м���ֹͣ¼��
	case WM_MBUTTONDOWN:
		if (appState == OPERATING)
		{
			// BUG��Ŀǰ�м��޷��жϲ���
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
		addKeyOperate(0, pKeyHookStruct->vkCode, "WM_KEYDOWN");
		qDebug() << "WM_KEYDOWN" << pKeyHookStruct->vkCode;

		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		addKeyOperate(KEYEVENTF_KEYUP, pKeyHookStruct->vkCode, "WM_KEYUP");
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

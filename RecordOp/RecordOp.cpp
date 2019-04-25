#include "RecordOp.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QFileDialog>

#include <QDebug>

#define IF_PROJECT_NULLPTR if (currentOpProject == nullptr) return;

AppState appState = IDLE;

RecordOp::RecordOp(QWidget *parent)
	: QMainWindow(parent), currentOpProject(nullptr)
{
	ui.setupUi(this);
	QIntValidator* validator = new QIntValidator(0, 100, this);
	ui.operationTimesText->setValidator(validator);
	//this->setWindowFlags(Qt::Tool);
	this->show();

	opTimer = new QTime();
	opExcutor = new OpExcutor();
	//initTrayIcon();

	treeWidgetMenu = new QMenu();
	treeWidgetMenu->addAction("复制", this, SLOT(copyTreeItemAction()));
	treeWidgetMenu->addAction("删除", this, SLOT(deleteTreeItemAction()));

	ui.opTreeList->setMenu(treeWidgetMenu);
	
	connect(ui.recordButton, SIGNAL(clicked()), this, SLOT(onStartRecord()));
	connect(ui.operateButton, SIGNAL(clicked()), this, SLOT(onDoOperation()));
	connect(xHook, SIGNAL(mouseEvent(int, WPARAM, LPARAM)), this, SLOT(mouseEvent(int, WPARAM, LPARAM)));
	connect(xHook, SIGNAL(keyEvent(int, WPARAM, LPARAM)), this, SLOT(keyEvent(int, WPARAM, LPARAM)));
	connect(opExcutor, SIGNAL(finished()), this, SLOT(onExcuteOpCompeleted()));


	// Action
	connect(ui.newButton, SIGNAL(triggered()), this, SLOT(onNewFile()));
	connect(ui.openButton, SIGNAL(triggered()), this, SLOT(onOpenFile()));
	connect(ui.saveButton, SIGNAL(triggered()), this, SLOT(onSaveFile()));
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
	delete opExcutor;
	delete opTimer;

}

void RecordOp::onStartRecord()
{
	currentOpProject = new OpProject();

	qDebug() << "Start Record";
	appState = RECORDING;

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

	addOpProject(currentOpProject);
	// 显示操作UI
	//showOP();

	this->show();

	appState = IDLE;
	qDebug() << "End Record";
}

void RecordOp::onDoOperation()
{
	// 从Table中重新生成operations
	//generateOPFromTable();

	this->hide();
	appState = OPERATING;

	xHook->installMouseHook();
	xHook->installKeyHook();

	int length = ui.opTreeList->topLevelItemCount();
	for (int i = 0; i < length ; i++)
	{
		getActiveOpProjects(ui.opTreeList->topLevelItem(i));
	}

	// 如果没有方案
	if (opExcutor->opProjectSize() == 0)
	{
		QMessageBox::information(NULL, "提示", "当前没有测试方案", QMessageBox::Ok);
		return;
	}

	opExcutor->start();

	//QString operateTimesStr = ui.operationTimesText->text();
	//// 循环执行次数，默认为1次
	//int operateTimes = 1;
	//if (!operateTimesStr.isEmpty())
	//{
	//	operateTimes = operateTimesStr.toInt();
	//}
	//for (int i = 0; i < operateTimes; i++)
	//{
	//	
	//}
}

void RecordOp::onExcuteOpCompeleted()
{
	xHook->uninstallMouseHook();
	xHook->uninstallKeyHook();

	appState = IDLE;
	this->show();

	qDebug() << "Op Completed!";
}

void RecordOp::onNewFile()
{
	if (treeItemToProject.size() > 0)
	{
		if (QMessageBox::No == QMessageBox::information(NULL, "提示", "新建会清空你当前记录，确认吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
		{
			return;
		}
	}
	
	clearOP();
}

void RecordOp::onOpenFile()
{
	QFileDialog fileDialog;
	QString fileName = fileDialog.getOpenFileName(this, "Open File", "", "Text File(*.xml)");
	if (fileName == "")
	{
		return;
	}

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
		return;

	QDomDocument doc;
	if (!doc.setContent(&file))
	{
		file.close();
		return;
	}
	file.close();

	// 清除之前的记录
	clearOP();

	// 返回根节点
	QDomElement root = doc.documentElement(); 
	
	// Node
	QDomElement nodeElement = root.firstChildElement();
	while (!nodeElement.isNull())
	{
		// 创建节点树
		QTreeWidgetItem* item = loadTreeItem(nodeElement);
		loadXmlRecursion(item, nodeElement);
		ui.opTreeList->addTopLevelItem(item);

		nodeElement = nodeElement.nextSiblingElement();
	}
}

void RecordOp::loadXmlRecursion(QTreeWidgetItem* parentItem, QDomElement& parentElement)
{
	QDomElement nodeElement = parentElement.firstChildElement();
	while (!nodeElement.isNull())
	{
		if (nodeElement.nodeName() == "Node")
		{		
			// 创建节点树
		 	QTreeWidgetItem* item = loadTreeItem(nodeElement);
			parentItem->addChild(item);

			loadXmlRecursion(item, nodeElement);
		}
		else if (nodeElement.nodeName() == "OPs")
		{
			loadXmlOp(parentItem, nodeElement);
		}

		nodeElement = nodeElement.nextSiblingElement();
	}
}

QTreeWidgetItem* RecordOp::loadTreeItem(QDomElement& nodeElement)
{
	if (nodeElement.nodeName() != "Node")
	{
		return nullptr;
	}

	QTreeWidgetItem* item = new OPTreeWidgetItem();
	QString name = nodeElement.attribute("name");
	int checkState = nodeElement.attribute("checkState").toInt();
	item->setCheckState(0, Qt::CheckState(checkState));
	item->setText(0, name);

	return item;
}

void RecordOp::loadXmlOp(QTreeWidgetItem* parentItem, QDomElement& opsElement)
{
	OpProject* opProject = new OpProject();
	opProject->loadXml(opsElement);

	treeItemToProject.insert(parentItem, opProject);
}

void RecordOp::onSaveFile()
{
	QFileDialog fileDialog;
	QString fileName = fileDialog.getSaveFileName(this, "Save File", "", "Text File(*.xml)");
	if (fileName == "")
	{
		return;
	}

	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
		return;

	QDomDocument doc;
	//写入xml头部
	QDomProcessingInstruction instruction; //添加处理命令
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(instruction);
	//添加根节点
	QDomElement root = doc.createElement("RecordOp");
	doc.appendChild(root);

	saveXml(doc, root);

	//输出到文件
	QTextStream out_stream(&file);
	doc.save(out_stream, 4); //缩进4格
	file.close();
}

void RecordOp::addMouseOperate(int x, int y, int opCode, const QString& opCodeText)
{
	if (appState != RECORDING)
	{
		return;
	}

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

	addOperate(op, opCode, opCodeText);
}

void RecordOp::addKeyOperate(int isPressed, int opCode, const QString& opCodeText)
{
	if (appState != RECORDING)
	{
		return;
	}

	OPKeyboard* op = new OPKeyboard();
	op->type = OPBase::KEYBOARD;
	op->isPressed = isPressed;

	addOperate(op, opCode, opCodeText);
}

void RecordOp::addOperate(OPBase* op, int opCode, const QString& opCodeText)
{
	IF_PROJECT_NULLPTR

	op->opCode = opCode;
	op->internelSeconds = opTimer->restart();
	op->opCodeText = opCodeText;

	currentOpProject->addOperate(op);

	qDebug() << "addOperate";
	qDebug() << op->internelSeconds;
}

void RecordOp::addOpProject(OpProject* opProject)
{
	QTreeWidgetItem* item = new OPTreeWidgetItem();
	item->setText(0, QString("Project%1").arg(treeItemToProject.size()));
	ui.opTreeList->addTopLevelItem(item);
	ui.opTreeList->setCurrentItem(item);
	item->setCheckState(0, Qt::Checked);

	treeItemToProject.insert(item, opProject);
}

void RecordOp::getActiveOpProjects(QTreeWidgetItem* item)
{
	if (item->checkState(0) == Qt::Unchecked)
	{
		return;
	}

	auto iter = treeItemToProject.find(item);
	if (iter != treeItemToProject.end())
	{
		opExcutor->addOpProject(iter.value());
	}
	
	for (int i = 0; i < item->childCount(); i++)
	{
		getActiveOpProjects(item->child(i));
	}
}

void RecordOp::showOP()
{
	IF_PROJECT_NULLPTR
	currentOpProject->showOPToTableWidget(ui.opTable);
}

void RecordOp::generateOPFromTable()
{
	// 后期加一个标识，当发生改变时才重新生成
	if (false)
	{
		return;
	}

	IF_PROJECT_NULLPTR
	currentOpProject->generateOPFromTable(ui.opTable);
}

void RecordOp::deleteOpProject(QTreeWidgetItem* item)
{
	auto iter = treeItemToProject.find(item);
	if (iter != treeItemToProject.end())
	{
		delete iter.value();
		treeItemToProject.remove(item);
	}
}

void RecordOp::clearOP()
{
	// 清空所有OpProject
	auto iter = treeItemToProject.begin();
	while (iter != treeItemToProject.end())
	{
		delete iter.value();
		++iter;
	}

	treeItemToProject.clear();
	ui.opTreeList->clear();
	ui.opTable->clear();
}

void RecordOp::saveXml(QDomDocument& doc, QDomElement& parent)
{
	int length = ui.opTreeList->topLevelItemCount();
	for (int i = 0; i < length; i++)
	{
		saveXmlRecursion(doc, parent, ui.opTreeList->topLevelItem(i));
	}
}

void RecordOp::saveXmlRecursion(QDomDocument& doc, QDomElement& parent, QTreeWidgetItem* item)
{
	QDomElement nodeXml = doc.createElement("Node");
	nodeXml.setAttribute("name", item->text(0));
	nodeXml.setAttribute("checkState", item->checkState(0));
	parent.appendChild(nodeXml);

	auto iter = treeItemToProject.find(item);
	if (iter != treeItemToProject.end())
	{
		OpProject* opProject = iter.value();
		opProject->saveXml(doc, nodeXml);
	}

	for (int i = 0; i < item->childCount(); i++)
	{
		saveXmlRecursion(doc, nodeXml, item->child(i));
	}
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

	// 按下鼠标中键后停止录制
	case WM_MBUTTONDOWN:
		if (appState == OPERATING)
		{
			OpProject::breakOp();
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

void RecordOp::copyTreeItemAction()
{
	QTreeWidgetItem* curItem = ui.opTreeList->currentItem();
	if (curItem == nullptr)
	{
		return;
	}

	// 复制逻辑
	auto iter = treeItemToProject.find(curItem);
	if (iter == treeItemToProject.end())
	{
		return;
	}
	OpProject* opProject = iter.value()->copy();

	QString newName = QString("%1_%2").arg(curItem->text(0)).arg(treeItemToProject.size());
	QTreeWidgetItem* newItem = new OPTreeWidgetItem();
	newItem->setText(0, newName);
	newItem->setCheckState(0, curItem->checkState(0));
	ui.opTreeList->addTopLevelItem(newItem);

	treeItemToProject.insert(newItem, opProject);
}

void RecordOp::deleteTreeItemAction()
{
	QTreeWidgetItem* curItem = ui.opTreeList->currentItem();
	
	if (curItem == nullptr)
	{
		return;
	}

	// 删除逻辑
	deleteOpProject(curItem);

	QTreeWidgetItem* parentItem = curItem->parent();
	if (parentItem == nullptr)
	{
		int index = ui.opTreeList->indexOfTopLevelItem(curItem);
		ui.opTreeList->takeTopLevelItem(index);
	}
	else
	{
		int index = parentItem->indexOfChild(curItem);
		parentItem->takeChild(index);
	}

}
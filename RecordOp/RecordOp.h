#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include <QTime>
#include <QSystemTrayIcon>
#include <QMenu>

#include "OPInfo.h"
#include "ui_RecordOp.h"
#include "windows.h"
#include "XGlobalHook.h"
#include "OpProject.h"
#include "OpExcutor.h"

class RecordOp : public QMainWindow
{
	Q_OBJECT

public:
	RecordOp(QWidget *parent = Q_NULLPTR);
	~RecordOp();

public slots:
	void onStartRecord();
	void onDoOperation();
	void onExcuteOpCompeleted();

	void onNewFile();
	void onOpenFile();
	void onSaveFile();

	void mouseEvent(TRANSFER_PARAM);
	void keyEvent(TRANSFER_PARAM);
	void onActivatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
	void onExitApp();

	// tree widget
	void copyTreeItemAction();
	void deleteTreeItemAction();
private:
	// 初始化托盘程序
	void initTrayIcon();

	void onStopRecord();
	//
	void addMouseOperate(int x, int y, int opCode, const QString& opCodeText);
	void addKeyOperate(int isPressed, int opCode, const QString& opCodeText);
	void addOperate(OPBase* op, int opCode, const QString& opCodeText);
	void addOpProject(OpProject* opProject);

	void getActiveOpProjects(QTreeWidgetItem* item);
	// 显示具体操作
	void showOP();
	// 根据Table生成Operators
	void generateOPFromTable();

	void deleteOpProject(QTreeWidgetItem* item);
	void clearOP();

	// 将所有节点的OP写入Xml中
	void saveXml(QDomDocument& doc, QDomElement& parent);
	void saveXmlRecursion(QDomDocument& doc, QDomElement& parent, QTreeWidgetItem* item);

	QTreeWidgetItem* loadTreeItem(QDomElement& nodeElement);
	void loadXmlRecursion(QTreeWidgetItem* parentItem, QDomElement& parentElement);
	void loadXmlOp(QTreeWidgetItem* parentItem, QDomElement& opsElement);
private:
	Ui::RecordOpClass ui;

	// 托盘程序
	QSystemTrayIcon* sysTrayIcon;
	QMenu* trayIconMenu;

	// 计算两个操作之间的间隔
	QTime* opTimer;
	// TreeWidget Menu
	QMenu* treeWidgetMenu;

	// 当前操作方案
	OpProject* currentOpProject;
	// 执行操作方案的线程
	OpExcutor* opExcutor;

	QMap<QTreeWidgetItem*, OpProject*> treeItemToProject;
};

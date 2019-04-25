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
	// ��ʼ�����̳���
	void initTrayIcon();

	void onStopRecord();
	//
	void addMouseOperate(int x, int y, int opCode, const QString& opCodeText);
	void addKeyOperate(int isPressed, int opCode, const QString& opCodeText);
	void addOperate(OPBase* op, int opCode, const QString& opCodeText);
	void addOpProject(OpProject* opProject);

	void getActiveOpProjects(QTreeWidgetItem* item);
	// ��ʾ�������
	void showOP();
	// ����Table����Operators
	void generateOPFromTable();

	void deleteOpProject(QTreeWidgetItem* item);
	void clearOP();

	// �����нڵ��OPд��Xml��
	void saveXml(QDomDocument& doc, QDomElement& parent);
	void saveXmlRecursion(QDomDocument& doc, QDomElement& parent, QTreeWidgetItem* item);

	QTreeWidgetItem* loadTreeItem(QDomElement& nodeElement);
	void loadXmlRecursion(QTreeWidgetItem* parentItem, QDomElement& parentElement);
	void loadXmlOp(QTreeWidgetItem* parentItem, QDomElement& opsElement);
private:
	Ui::RecordOpClass ui;

	// ���̳���
	QSystemTrayIcon* sysTrayIcon;
	QMenu* trayIconMenu;

	// ������������֮��ļ��
	QTime* opTimer;
	// TreeWidget Menu
	QMenu* treeWidgetMenu;

	// ��ǰ��������
	OpProject* currentOpProject;
	// ִ�в����������߳�
	OpExcutor* opExcutor;

	QMap<QTreeWidgetItem*, OpProject*> treeItemToProject;
};

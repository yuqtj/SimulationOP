#pragma once
#pragma execution_character_set("utf-8")

#include <QList>
#include <QTableWidget>

#include "OPInfo.h"

class OpProject
{
public:
	OpProject();
	~OpProject();

	inline void addOperate(OPBase* op)
	{
		operations.append(op);
	}

	inline static void breakOp()
	{
		isBreak = true;
	}

	OpProject* copy();

	void showOPToTableWidget(QTableWidget*& tableWidget);
	void clearOP();
	void generateOPFromTable(QTableWidget*& tableWidget);
	int excuteOP();

	// 读写Xml
	void saveXml(QDomDocument& doc, QDomElement& parent);
	void loadXml(QDomElement& opsElement);
	
private:
	void doMouseOperate(OPMouse* op);
	void doKeyOperate(OPKeyboard* op);

private:
	QList<OPBase*> operations;
	// 是否被中断操作
	static bool isBreak;
};


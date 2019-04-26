
#include "OpProject.h"

#include "windows.h"

bool OpProject::isBreak = false;

OpProject::OpProject()
{
	projectDes = "";
}


OpProject::~OpProject()
{
	clearOP();
}

OpProject* OpProject::copy()
{
	OpProject* opProject = new OpProject();

	opProject->operations.reserve(this->operations.size());
	for each (auto op in this->operations)
	{
		OPBase* newOp = nullptr;
		if (op->type == OPBase::MOUSE)
		{
			OPMouse* opMouse = new OPMouse();
			*opMouse = *(static_cast<OPMouse*>(op));
			newOp = opMouse;
		}
		else if (op->type == OPBase::KEYBOARD)
		{
			OPKeyboard* opKeyboard = new OPKeyboard();
			*opKeyboard = *(static_cast<OPKeyboard*>(op));
			newOp = opKeyboard;
		}
		
		opProject->operations.append(newOp);
	}

	return opProject;
}

void OpProject::showOPToTableWidget(QTableWidget*& tableWidget)
{
	tableWidget->setColumnCount(7);
	tableWidget->setHorizontalHeaderLabels(QStringList() << "操作事件" << "操作类型" << "时间间隔" << "鼠标X" << "鼠标Y" << "按下状态" << "OpCode");
	int length = operations.size();
	tableWidget->setRowCount(length);
	for (int i = 0; i < length; i++)
	{
		OPBase* opBase = operations[i];

		if (opBase->type == OPBase::MOUSE)
		{
			tableWidget->setItem(i, 0, new QTableWidgetItem("鼠标"));

			OPMouse* opMouse = static_cast<OPMouse*>(opBase);
			tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(opMouse->x)));
			tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(opMouse->y)));
		}
		else if (opBase->type == OPBase::KEYBOARD)
		{
			tableWidget->setItem(i, 0, new QTableWidgetItem("键盘"));
			OPKeyboard* opKeyboard = static_cast<OPKeyboard*>(opBase);
			tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(opKeyboard->isPressed)));
		}

		if (opBase->opCodeText == "")
		{
			tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(opBase->opCode)));
		}
		else
		{
			tableWidget->setItem(i, 1, new QTableWidgetItem(opBase->opCodeText));
		}
		tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(opBase->internelSeconds)));
		tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(opBase->opCode)));
	}


}

void OpProject::clearOP()
{
	projectDes = "";

	for each (OPBase* op in operations)
	{
		delete op;
	}

	operations.clear();
}

void OpProject::generateOPFromTable(QTableWidget*& tableWidget)
{
	clearOP();

	int length = tableWidget->rowCount();
	operations.reserve(length);

	for (int i = 0; i < length; i++)
	{
		OPBase* opBase = nullptr;
		QString opType = tableWidget->item(i, 0)->text();
		if (opType == "鼠标")
		{
			OPMouse* opMouse = new OPMouse();
			QString mouseXText = tableWidget->item(i, 3)->text();
			QString mouseYText = tableWidget->item(i, 4)->text();

			opMouse->x = mouseXText.toInt();
			opMouse->y = mouseYText.toInt();

			opBase = opMouse;
		}
		else if (opType == "键盘")
		{
			OPKeyboard* opKeyboard = new OPKeyboard();
			QString isPressedText = tableWidget->item(i, 5)->text();
			opKeyboard->isPressed = isPressedText.toInt();

			opBase = opKeyboard;
		}

		if (opBase)
		{
			QString internelSecondsText = tableWidget->item(i, 2)->text();
			opBase->internelSeconds = internelSecondsText.toInt();

			QString opCode = tableWidget->item(i, 6)->text();
			opBase->opCode = opCode.toInt();

			operations.push_back(opBase);
		}
	}
}

int OpProject::excuteOP()
{
	for each (OPBase* op in operations)
	{
		if (isBreak)
		{
			isBreak = false;
			return 0;
		}

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

		Sleep(op->internelSeconds);
	}

	return 1;
}

void OpProject::saveXml(QDomDocument& doc, QDomElement& parent)
{
	if (operations.size() == 0)
	{
		return;
	}

	QDomElement opsXml = doc.createElement("OPs");
	opsXml.setAttribute("ProjectDes", projectDes);
	parent.appendChild(opsXml);

	for each (auto op in operations)
	{
		QDomElement opXml = doc.createElement("OP");
		if (op->type == OPBase::MOUSE)
		{
			OPMouse* opMouse = static_cast<OPMouse*>(op);
			opXml.setAttribute("type", "鼠标");
			opXml.setAttribute("mouseX", opMouse->x);
			opXml.setAttribute("mouseY", opMouse->y);
		}
		else if (op->type == OPBase::KEYBOARD)
		{
			OPKeyboard* opKeyboard = static_cast<OPKeyboard*>(op);
			opXml.setAttribute("type", "键盘");
			opXml.setAttribute("isPressed", opKeyboard->isPressed);
		}
		
		opXml.setAttribute("opCode", op->opCode);
		opXml.setAttribute("internelSeconds", op->internelSeconds);
		opXml.setAttribute("opCodeText", op->opCodeText);

		opsXml.appendChild(opXml);
	}
}

void OpProject::loadXml(QDomElement& opsElement)
{
	operations.clear();

	projectDes = opsElement.attribute("ProjectDes");
	QDomElement opElement = opsElement.firstChildElement();
	while (!opElement.isNull())
	{
		QString type = opElement.attribute("type");
		OPBase* opBase = nullptr;
		if (type == "鼠标")
		{
			OPMouse* opMouse = new OPMouse();
			opMouse->x = opElement.attribute("mouseX").toInt();
			opMouse->y = opElement.attribute("mouseY").toInt();

			opBase = opMouse;
		}
		else if (type == "键盘")
		{
			OPKeyboard* opKeyboard = new OPKeyboard();
			opKeyboard->isPressed = opElement.attribute("isPressed").toInt();

			opBase = opKeyboard;
		}
		else
		{
			opElement = opElement.nextSiblingElement();
			continue;
		}

		opBase->opCode = opElement.attribute("opCode").toInt();
		opBase->internelSeconds = opElement.attribute("internelSeconds").toInt();
		opBase->opCodeText = opElement.attribute("opCodeText");

		operations.append(opBase);
		opElement = opElement.nextSiblingElement();
	}
}

void OpProject::doMouseOperate(OPMouse* op)
{
	SetCursorPos(op->x, op->y);
	mouse_event(op->opCode, 0, 0, 0, 0);
}

void OpProject::doKeyOperate(OPKeyboard* op)
{
	keybd_event(op->opCode, 0, op->isPressed, 0);
}
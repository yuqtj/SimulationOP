#pragma once

#include <QtXml>
#include <QString>

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
	QString opCodeText;
};

struct OPMouse : public OPBase
{
	OPMouse()
	{
		type = OPBase::MOUSE;
		x = 0;
		y = 0;
	}

	int x;
	int y;
};

struct OPKeyboard : public OPBase
{
	OPKeyboard()
	{
		type = OPBase::KEYBOARD;
		isPressed = 0;
	}

	int isPressed;
};
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
	// ����ʱ��������ɲ�����ȴ�internelSecondsʱ�䣬Ĭ��1000����
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
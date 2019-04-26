#include "XGlobalHook.h"
#include <QDebug>

/// ��̬��������
QMutex XGlobalHook::mutex;
QSharedPointer<XGlobalHook> XGlobalHook::hook_instance;

/// ȫ�ֱ�������
HINSTANCE g_hInstance = Q_NULLPTR;
HHOOK g_hMouseHook = Q_NULLPTR;  //��깳�� ���
HHOOK g_hKeyHook = Q_NULLPTR;    //���̹��� ���

// ��깳�Ӵ�����
LRESULT CALLBACK MouseProc(int nCode,       // ������
	WPARAM wParam,   // ��ϢID
	LPARAM lParam    // �������
);

// ���̹��Ӵ�����
LRESULT CALLBACK KeyboardProc(int nCode,            // ������
	WPARAM wParam,        // �������
	LPARAM lParam         // ������Ϣ
);


XGlobalHook::~XGlobalHook()
{
	uninstallMouseHook();
	uninstallKeyHook();
}

QSharedPointer<XGlobalHook>&XGlobalHook::instance()
{
	if (hook_instance.isNull())
	{
		QMutexLocker mutexLocker(&mutex);
		if (hook_instance.isNull())
			hook_instance = QSharedPointer<XGlobalHook>(new XGlobalHook());
	}
	return hook_instance;
}

bool XGlobalHook::installMouseHook()
{
	g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseProc, g_hInstance, 0);
	return Q_LIKELY(g_hMouseHook);
}

bool XGlobalHook::uninstallMouseHook()
{
	if (Q_UNLIKELY(!g_hMouseHook)) {
		return true;
	}

	bool success = false;
	success = UnhookWindowsHookEx(g_hMouseHook);
	if (success) {
		g_hMouseHook = Q_NULLPTR;
	}
	return success;
}

bool XGlobalHook::isMouseHookRunning() const
{
	return Q_LIKELY(g_hMouseHook);
}

bool XGlobalHook::installKeyHook()
{
	g_hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, g_hInstance, 0);
	return Q_LIKELY(g_hKeyHook);
}

bool XGlobalHook::uninstallKeyHook()
{
	if (Q_UNLIKELY(!g_hKeyHook)) {
		return true;
	}

	bool success = false;
	success = UnhookWindowsHookEx(g_hKeyHook);
	if (success) {
		g_hKeyHook = Q_NULLPTR;
	}
	return success;
}

bool XGlobalHook::isKeyHookRunning() const
{
	return Q_LIKELY(g_hKeyHook);
}

// DLL ���ӽӿ�
void XGlobalHook::onMouseEvent(TRANSFER_PARAM)
{
	emit mouseEvent(nCode, wParam, lParam);
}

void XGlobalHook::onKeyEvent(TRANSFER_PARAM)
{
	emit keyEvent(nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(TRANSFER_PARAM)
{
	MSLLHOOKSTRUCT* p = (MSLLHOOKSTRUCT*)lParam;

	// p->flags & LLMHF_INJECTED�������ͨ��mouse_event����������Ϣ��Ϊtrue
	// ��p->flags & LLMHF_INJECTED��Ŀ�����ڲ����ڼ䲻ϣ���û��Լ���������Ӱ�쵽����
	if (appState == OPERATING && wParam != WM_MBUTTONDOWN && !(p->flags & LLMHF_INJECTED))
	{
		return 1;
	}

	xHook->onMouseEvent(nCode, wParam, lParam);
	return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(TRANSFER_PARAM)
{
	KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
	if (appState == OPERATING && !(p->flags & 16))
	{
		return 1;
	}

	xHook->onKeyEvent(nCode, wParam, lParam);
	return CallNextHookEx(g_hKeyHook, nCode, wParam, lParam);
}
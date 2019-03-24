#ifndef XGLOBALHOOK_H
#define XGLOBALHOOK_H

#include <QObject>
#include <QtGlobal>
#include <QMutex>
#include <QSharedPointer>
#include "windows.h"

#if defined(GLOBALHOOK_LIBRARY)
#  define GLOBALHOOKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GLOBALHOOKSHARED_EXPORT Q_DECL_IMPORT
#endif

#define xHook XGlobalHook::instance().data()

#define TRANSFER_PARAM int nCode,WPARAM wParam,LPARAM lParam

class XGlobalHook : public QObject
{
	Q_OBJECT

		/// ����
private:
	XGlobalHook(QObject* parent = 0) : QObject(parent) {}
	XGlobalHook(const XGlobalHook& hook) = delete;
	XGlobalHook& operator==(const XGlobalHook&) = delete;

public:
	virtual ~XGlobalHook() final;
	static QSharedPointer<XGlobalHook>& instance();

private:
	static QMutex mutex;
	static QSharedPointer<XGlobalHook> hook_instance;

	/// �û��ӿ�
public:
	// ��깳��
	bool installMouseHook();          // ��װ����
	bool uninstallMouseHook();        // ж�ع���
	bool isMouseHookRunning() const;  // ����״̬
	// ���̹���
	bool installKeyHook();            // ��װ����
	bool uninstallKeyHook();          // ж�ع���
	bool isKeyHookRunning() const;    // ����״̬

signals:
	void mouseEvent(TRANSFER_PARAM);
	void keyEvent(TRANSFER_PARAM);

// DLL ���ӽӿ�
public:
	void onMouseEvent(TRANSFER_PARAM);
	void onKeyEvent(TRANSFER_PARAM);
};

#endif // XGLOBALHOOK_H
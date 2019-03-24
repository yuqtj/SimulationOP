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

		/// 单例
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

	/// 用户接口
public:
	// 鼠标钩子
	bool installMouseHook();          // 安装钩子
	bool uninstallMouseHook();        // 卸载钩子
	bool isMouseHookRunning() const;  // 运行状态
	// 键盘钩子
	bool installKeyHook();            // 安装钩子
	bool uninstallKeyHook();          // 卸载钩子
	bool isKeyHookRunning() const;    // 运行状态

signals:
	void mouseEvent(TRANSFER_PARAM);
	void keyEvent(TRANSFER_PARAM);

// DLL 钩子接口
public:
	void onMouseEvent(TRANSFER_PARAM);
	void onKeyEvent(TRANSFER_PARAM);
};

#endif // XGLOBALHOOK_H
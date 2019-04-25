#pragma once

#include <QTreeWidget>
#include <QMouseEvent>
#include <QMenu>

class OPTreeWidgetItem :
	public QTreeWidgetItem
{
public:
	OPTreeWidgetItem();
	~OPTreeWidgetItem() {};
protected:
	
private:
};

class OPTreeWidget :
	public QTreeWidget
{
public:
	OPTreeWidget(QWidget* parent);
	~OPTreeWidget();

	inline void setMenu(QMenu* menu)
	{
		treeMenu = menu;
	}
protected:
	virtual void mouseReleaseEvent(QMouseEvent *event) override;


private:
	QMenu* treeMenu;
};


#include "OPTreeWidget.h"

OPTreeWidgetItem::OPTreeWidgetItem()
{
	this->setFlags(this->flags() | Qt::ItemIsEditable);
}


OPTreeWidget::OPTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
	treeMenu = nullptr;
}


OPTreeWidget::~OPTreeWidget()
{
}

void OPTreeWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		if (treeMenu == nullptr)
		{
			return;
		}

		if (this->selectedItems().isEmpty())
		{
			return;
		}

		treeMenu->exec(QCursor::pos());
	}

	QTreeWidget::mouseReleaseEvent(event);
}
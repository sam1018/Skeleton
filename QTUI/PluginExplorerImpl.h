#pragma once

#include "../SkeletonInterface/IOutputWindow.h"
#include <QtWidgets\QDockWidget>

class PluginExplorer;
class QTreeWidget;
class QTreeWidgetItem;

class PluginExplorerImpl : public QDockWidget
{
	Q_OBJECT

public:
	PluginExplorerImpl(PluginExplorer *wnd);
	~PluginExplorerImpl();

	public slots:
	void LoadPlugin();
	void ExecuteFunction(QTreeWidgetItem *item, int column);

private:
	void CreateTreeWidget();

private:
	PluginExplorer *pluginExplorer;
	QTreeWidget *treeWidget;
	OutWnd::OutWndCatID outWndId;
};

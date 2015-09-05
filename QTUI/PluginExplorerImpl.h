#pragma once

#include <QtWidgets\QDockWidget>

class PluginExplorer;
class QTreeWidget;
class QTreeWidgetItem;

class PluginExplorerImpl : public QDockWidget
{
	Q_OBJECT

public:
	explicit PluginExplorerImpl(PluginExplorer *wnd);
	~PluginExplorerImpl();

	void AddPluginDataToTree(const std::string &pluginName, const std::vector<std::string> &functions);

	public slots:
	void LoadPlugin();
	void ExecuteFunction(QTreeWidgetItem *item, int column);

private:
	void CreateTreeWidget();

private:
	PluginExplorer *pluginExplorer;
	QTreeWidget *treeWidget;
};

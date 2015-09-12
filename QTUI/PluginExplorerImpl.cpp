#include "PluginExplorer.h"
#include "PluginExplorerImpl.h"
#include "Routines.h"
#include "Vitals\IMessagePrinter.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QTreeWidget>
#include <QtWidgets\QHeaderView>


using namespace std;
using namespace Routines;


constexpr int PluginPathRole = Qt::UserRole + 1;
constexpr int ColWithPluginPath = 0;


void SetPluginPath(QTreeWidgetItem *item, const string &pluginName)
{
	item->setData(ColWithPluginPath, PluginPathRole, QVariant(pluginName.c_str()));
}

string GetPluginPath(QTreeWidgetItem *item)
{
	return item->data(ColWithPluginPath, PluginPathRole).toString().toStdString();
}


///////////////////////////////////////////////////////////////////////////////
/////////////          PluginExplorerImpl Definition               ////////////
///////////////////////////////////////////////////////////////////////////////


PluginExplorerImpl::PluginExplorerImpl(PluginExplorer *wnd) :
	QDockWidget("Plugin Explorer"),
	pluginExplorer{ wnd }
{
	setObjectName("Plugin Explorer");

	QVBoxLayout *mainLayout = new QVBoxLayout;

	mainLayout->setSpacing(0);
	mainLayout->setMargin(0);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	QPushButton *btnLoadPlugin = new QPushButton("Load Plugin");
	btnLoadPlugin->connect(btnLoadPlugin, SIGNAL(clicked()), this, SLOT(LoadPlugin()));
	buttonsLayout->addWidget(btnLoadPlugin);
	mainLayout->addLayout(buttonsLayout);
	CreateTreeWidget();
	mainLayout->addWidget(treeWidget);

	QWidget *widget = new QWidget(this);
	widget->setLayout(mainLayout);
	setWidget(widget);
}


PluginExplorerImpl::~PluginExplorerImpl()
{
}

void PluginExplorerImpl::LoadPlugin()
{
	pluginExplorer->LoadPlugin();
}

void PluginExplorerImpl::AddPluginDataToTree(const string &pluginName, const vector<string> &functions)
{
	if (!functions.empty())
	{
		QTreeWidgetItem *plugin = new QTreeWidgetItem({ QString(GetFileNameFromPath(pluginName).c_str()) });

		SetPluginPath(plugin, pluginName);

		for (auto &funcname : functions)
			plugin->addChild(new QTreeWidgetItem({ funcname.c_str() }));

		treeWidget->addTopLevelItem(plugin);
	}
}

void PluginExplorerImpl::CreateTreeWidget()
{
	treeWidget = new QTreeWidget;
	treeWidget->setColumnCount(1);
	treeWidget->header()->hide();
	treeWidget->connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(ExecuteFunction(QTreeWidgetItem*, int)));
}

void PluginExplorerImpl::ExecuteFunction(QTreeWidgetItem *itemFunc, int column)
{
	QTreeWidgetItem *root = treeWidget->invisibleRootItem();

	// Need some sanity check to make sure user double clickd on function item
	if (itemFunc && itemFunc != root)
	{
		QTreeWidgetItem *itemPlugin = itemFunc->parent();
		if (itemPlugin && itemPlugin != root)
		{
			pluginExplorer->ExecuteFunction(GetPluginPath(itemPlugin), itemFunc->text(0).toStdString());
		}
	}
}

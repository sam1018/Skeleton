#include "PluginExplorerImpl.h"
#include "PluginExplorer.h"
#include "../SkeletonInterface/Routines.h"
#include <iostream>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QTreeWidget>
#include <QtWidgets\QMessageBox>


///////////////////////////////////////////////////////////////////////////////
/////////////          PluginExplorerImpl Definition               ////////////
///////////////////////////////////////////////////////////////////////////////


PluginExplorerImpl::PluginExplorerImpl(PluginExplorer *wnd) :
	QDockWidget("Plugin Explorer"),
	pluginExplorer{ wnd },
	outWndId{ OutWnd::RegisterOutputWindowCategory(OutWnd::OutWndPluginExplorerCategory) }
{
	setObjectName("Plugin Explorer");

	QVBoxLayout *mainLayout = new QVBoxLayout;
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
	QString pluginName = QFileDialog::getOpenFileName(this, "Open As", QDir::currentPath(), ("dll Files (*.dll)"));
	std::vector<std::string> functions;
	pluginExplorer->LoadPlugin(pluginName.toStdString(), functions);

	if (!functions.empty())
	{
		QTreeWidgetItem *plugin = new QTreeWidgetItem({ Routines::GetFileNameFromPath(pluginName.toStdString()).c_str(), pluginName });

		for (auto &funcname : functions)
			plugin->addChild(new QTreeWidgetItem({ funcname.c_str() }));

		treeWidget->addTopLevelItem(plugin);
	}
}

void PluginExplorerImpl::CreateTreeWidget()
{
	treeWidget = new QTreeWidget;
	treeWidget->setColumnCount(1); // we will use column 2 to store plugin path, but it will not be for display purpose
	treeWidget->setHeaderLabels({ "Plugin/Function Name"});
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
			// Clear the output window
			OutWnd::OutputWindowSetText(outWndId, "", false, false);
			
			auto msg{ "Attempting to run function \"" + itemFunc->text(0).toStdString() +
				"\" In plugin \"" + itemPlugin->text(0).toStdString() + "\"\n" };
			
			OutWnd::OutputWindowSetText(outWndId, msg, true, true);

			OutWnd::OutputWindowSetText(outWndId, "Result: ", true, true);

			OutWnd::StdRedirector<> redirOut{ std::cout, outWndId };
			OutWnd::StdRedirector<> redirErr{ std::cerr, outWndId };

			auto success{ true };

			try
			{
				pluginExplorer->ExecuteFunction(itemPlugin->text(1).toStdString(), itemFunc->text(0).toStdString());
			}
			catch (std::exception &e)
			{
				success = false;
				OutWnd::OutputWindowSetText(outWndId, e.what(), true, true);
			}
			catch (...)
			{
				success = false;
				OutWnd::OutputWindowSetText(outWndId, "Something went wrong.\n", true, true);
			}

			if(success)
				OutWnd::OutputWindowSetText(outWndId, "Call to function \"" + itemFunc->text(0).toStdString() + "\" ended successfully.\n", true, true);
		}
	}
}

#include "StepWayPCH.h"
#include "DebugTab.h"
#include "imgui.h"



namespace StepWay
{

	void DbgTab::AddWidget(std::shared_ptr<DbgWidget> widget)
	{
		m_Widgets.push_back(widget);
	}

	void DbgTab::AddWidgets(std::vector<std::shared_ptr<DbgWidget>> widgets)
	{
		for (std::shared_ptr<DbgWidget>& widget : widgets)
		{
			AddWidget(widget);
		}
	}

	void DbgTab::Show()
	{
		for (std::shared_ptr<DbgWidget>& widget : m_Widgets)
		{
			widget->Show();
		}
	}

}

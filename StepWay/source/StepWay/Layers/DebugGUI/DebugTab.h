#pragma once
#include "Core.h"
#include "DebugWidgets.h"
#include <string>


namespace StepWay
{

	
	class DbgTab
	{
	public:
		DbgTab(const std::string& name):m_name(name) {};

		void AddWidget(std::shared_ptr<DbgWidget> widget);
		void AddWidgets(std::vector<std::shared_ptr<DbgWidget>> widgets);

		std::string GetName()const { return m_name; }

		void Show();
	private:
	public:
	private:
		std::vector<std::shared_ptr<DbgWidget>> m_Widgets;
		std::string m_name;
	};


}



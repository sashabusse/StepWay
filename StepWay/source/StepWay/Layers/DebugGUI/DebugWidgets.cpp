#include "StepWayPCH.h"
#include "DebugWidgets.h"
#include "imgui.h"

namespace StepWay
{
	void DbgSliderf::Show()
	{
		ImGui::SliderFloat(m_name.c_str(), m_pvalue, m_min, m_max);
	}

	void DbgSlider2f::Show()
	{
		ImGui::SliderFloat2(m_name.c_str(), m_pvalue, m_min, m_max);
	}

	void DbgSlider3f::Show()
	{
		ImGui::SliderFloat3(m_name.c_str(), m_pvalue, m_min, m_max);
	}

	void DbgSlider4f::Show()
	{
		ImGui::SliderFloat4(m_name.c_str(), m_pvalue, m_min, m_max);
	}

	//Integers------------------------------------------------
	void DbgSlideri::Show()
	{
		ImGui::SliderInt(m_name.c_str(), m_pvalue, m_min, m_max);
		
	}

	void DbgSlider2i::Show()
	{
		ImGui::SliderInt2(m_name.c_str(), m_pvalue, m_min, m_max);
	}
	
	void DbgSlider3i::Show()
	{
		ImGui::SliderInt3(m_name.c_str(), m_pvalue, m_min, m_max);
	}
	
	void DbgSlider4i::Show()
	{
		ImGui::SliderInt4(m_name.c_str(), m_pvalue, m_min, m_max);
	}

	
	//Check box-------------
	void DbgCheckBox::Show()
	{
		ImGui::Checkbox(m_name.c_str(), m_pval);
	}


	//float Inputs -------------
	void DbgInputf::Show()
	{
		ImGui::InputFloat(m_name.c_str(), m_pval, 1, 1, 3);
	}

	void DbgInput2f::Show()
	{
		ImGui::InputFloat2(m_name.c_str(), m_pval, 3);
	}

	void DbgInput3f::Show()
	{
		ImGui::InputFloat3(m_name.c_str(), m_pval, 3);
	}

	void DbgInput4f::Show()
	{
		ImGui::InputFloat4(m_name.c_str(), m_pval, 3);
	}

	void DbgColor4f::Show()
	{
		ImGui::ColorEdit4(m_name.c_str(), m_pval);
	}

}



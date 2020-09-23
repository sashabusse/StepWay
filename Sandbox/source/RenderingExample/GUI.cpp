#include "RenderingExample.h"
#include "imgui.h"

void RenderingExample::OnGuiUpdate()
{
	////for
	////bool opened = true;
	////ImGui::ShowDemoWindow(&opened);

	//// We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
	//ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(350, 400), ImGuiCond_FirstUseEver);


	//if (m_MainMenuState.ShowAppStatistics) { ImGui::ShowMetricsWindow(&(m_MainMenuState.ShowAppStatistics)); }
	//if (m_MainMenuState.ShowStyleEditor) { ImGui::Begin("Style Editor", &(m_MainMenuState.ShowStyleEditor)); ImGui::ShowStyleEditor(); ImGui::End(); }


	//if (!ImGui::Begin("Scene Manager", &m_scene_manager_opened, m_window_flags))
	//{
	//	// Early out if the window is collapsed, as an optimization.
	//	ImGui::End();
	//	return;
	//}

	//if (ImGui::BeginMenuBar())
	//{
	//	if (ImGui::BeginMenu("Help"))
	//	{
	//		ImGui::MenuItem("Metrics", NULL, &(m_MainMenuState.ShowAppStatistics));
	//		ImGui::MenuItem("Style Editor", NULL, &(m_MainMenuState.ShowStyleEditor));
	//		ImGui::EndMenu();
	//	}
	//	ImGui::EndMenuBar();
	//}

	//int no_name_ind = 1;
	//int ind = 0;
	//m_scene.ForEach<TransformComponent>(
	//	[&](Entity& ent, TransformComponent& transform_c)
	//	{
	//		ind++;
	//		ImGui::PushID(ind);
	//		
	//		std::string name = std::string("No name Entity ") + std::to_string(no_name_ind);;
	//		if (ent.HasComponent<NameComponent>())
	//			name = ent.GetComponent<NameComponent>().name;
	//		else
	//			no_name_ind++;

	//		if (ImGui::CollapsingHeader(name.c_str()))
	//		{
	//			if (ImGui::TreeNode("Transform"))
	//			{
	//				ImGui::InputFloat4("##row 1", &transform_c.transform[0][0], 2);
	//				ImGui::InputFloat4("##row 2", &transform_c.transform[1][0], 2);
	//				ImGui::InputFloat4("##row 3", &transform_c.transform[2][0], 2);
	//				ImGui::InputFloat4("##row 4", &transform_c.transform[3][0], 2);
	//				
	//				ImGui::Spacing();

	//				ImGui::Text("Translation");
	//				//ImGui::Checkbox("##Translation",);
	//				ImGui::InputFloat3("##Translation Input", )
	//				if (ImGui::Button("Generate Transform"))
	//				{
	//					ImGui
	//				}

	//				ImGui::TreePop();
	//			}

	//			if (ent.HasComponent<MeshComponent>())
	//			{
	//				MeshComponent& mesh_c = ent.GetComponent<MeshComponent>();
	//				if (ImGui::TreeNode("Mesh"))
	//				{
	//					ImGui::Checkbox("visible", &mesh_c.visible);
	//					ImGui::TreePop();
	//				}
	//			}
	//			if (ent.HasComponent<CameraComponent>())
	//			{
	//				if (ImGui::TreeNode("Camera"))
	//				{
	//					CameraComponent& cam_c = ent.GetComponent<CameraComponent>();

	//					ImGui::DragFloat("FOV", &(cam_c.m_FOV), 1, 1, 180);
	//					ImGui::InputFloat("near", &(cam_c.m_near), 0.1, 0.1, 1);
	//					ImGui::InputFloat("far", &(cam_c.m_far), 1, 10, 0);
	//					ImGui::InputFloat("aspect ratio", &(cam_c.m_AspectRatio), 0.05, 0.1, 2);

	//					ImGui::TreePop();
	//				}
	//				
	//			}

	//		}
	//		ImGui::PopID();
	//	}
	//);



	//ImGui::End();

}



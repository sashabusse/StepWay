#include "CameraControlScript.h"



CameraControlScript::CameraControlScript(Entity& ent):
	NativeScript(ent),
	pos({ 0,0,4.0f }),
	angle({ 0,0 })
{};

void CameraControlScript::OnCreate()
{
	//Mouse::SetCursorMode(StepWay::Input::CursorMode::CAMERA);
}

void CameraControlScript::OnUpdate()
{
	glm::vec2 offset({ 0,0 });
	if (Keyboard::IsKeyPressed(KeyboardKey::KEY_W))
	{
		offset.x += 1.0 / 200.0;
	}
	if (Keyboard::IsKeyPressed(KeyboardKey::KEY_S))
	{
		offset.x -= 1.0 / 200.0;
	}
	if (Keyboard::IsKeyPressed(KeyboardKey::KEY_A))
	{
		offset.y -= 1.0 / 200.0;
	}
	if (Keyboard::IsKeyPressed(KeyboardKey::KEY_D))
	{
		offset.y += 1.0 / 200.0;
	}

	glm::vec2 mouse_delt({ 0,0 });

	if (Mouse::IsButtonDown(MouseKey::L_BUTTON))
		mouse_delt = glm::vec2({ Mouse::GetDX(), Mouse::GetDY() });
	glm::vec2 rot;
	rot.x = -mouse_delt.x / 200;
	rot.y = -mouse_delt.y / 200;

	glm::mat4 old_rod_mat = glm::rotate(glm::mat4(1.0f), angle.x, glm::vec3({ 0,1,0 })) * glm::rotate(glm::mat4(1.0f), angle.y, glm::vec3({ 1,0,0 }));

	glm::vec3 forward = glm::normalize(glm::vec3(old_rod_mat * glm::vec4({ 0,0,-1,0 })));
	glm::vec3 right = glm::normalize(glm::vec3(old_rod_mat * glm::vec4({ 1,0,0,0 })));

	pos += forward * offset.x + right * offset.y;

	angle += rot;
	if (angle.x < 0)
		angle.x += 2 * glm::pi<float>();
	if (angle.x >= 2 * glm::pi<float>())
		angle.x -= 2 * glm::pi<float>();

	angle.y = glm::clamp<float>(angle.y, -glm::pi<float>() / 2, glm::pi<float>() / 2);

	glm::mat4 new_rot_mat = glm::rotate(glm::mat4(1.0f), angle.x, glm::vec3({ 0,1,0 })) * glm::rotate(glm::mat4(1.0f), angle.y, glm::vec3({ 1,0,0 }));
	glm::mat4 new_transl_mat = glm::translate(glm::mat4(1.0f), pos);



	glm::mat4& tr = GetComponent<TransformComponent>().transform;
	tr = new_transl_mat * new_rot_mat;
}

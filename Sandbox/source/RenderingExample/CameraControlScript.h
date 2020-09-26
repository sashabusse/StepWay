#pragma once
#include "../usings.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class CameraControlScript : public NativeScript
{
public:
	CameraControlScript(Entity& ent);
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
private:
	glm::vec3 pos;
	glm::vec2 angle;
};



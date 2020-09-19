#include "StepWayPCH.h"
#include "Entity.h"

void StepWay::Entity::RemoveFrScene()
{
	SW_CORE_ASSERT(IsValid(), "invalid entity on remove");
	m_scene->m_reg.destroy(m_id);
}

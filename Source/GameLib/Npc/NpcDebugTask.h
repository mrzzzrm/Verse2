#pragma once

#include <glm/glm.hpp>

#include <Deliberation/ECS/Entity.h>

#include "GameLib.h"
#include "NpcTask.h"

class NpcDebugTask : public NpcTask
{
public:
    NpcDebugTask();

    void setFireRequest(bool enabled, const glm::vec3 & target);

    void update(
        NpcController & controller,
        RigidBody &     body,
        Equipment &     equipment,
        const UpdateFrame & updateFrame) override;

private:
    bool      m_fireRequestEnabled = false;
    glm::vec3 m_fireRequestDirection;
};
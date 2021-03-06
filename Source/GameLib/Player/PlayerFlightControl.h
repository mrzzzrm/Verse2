#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <Deliberation/ECS/Component.h>

#include "FlightControlConfig.h"
#include "GameLib.h"

namespace deliberation
{
class UpdateFrame;
class RigidBody;
}

class PlayerFlightControl final : public Component<PlayerFlightControl>
{
    DELIBERATION_COMPONENT_NAME("PlayerFlightControl")
public:
    const glm::vec3 & linearThrust() const;
    const glm::vec3 & angularThrust() const;

    void setLinearThrust(const glm::vec3 & linearThrust);
    void setAngularThrust(const glm::vec3 & angularThrust);

    void update(RigidBody & body, FlightControlConfig & config, const UpdateFrame & updateFrame);

private:
    glm::vec3 m_linearThrust;
    glm::vec3 m_angularThrust;
};
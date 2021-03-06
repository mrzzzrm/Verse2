#pragma once

#include <boost/optional.hpp>

#include <glm/glm.hpp>

#include "NpcFlightControl.h"

class NpcSteering
{
public:
    const glm::vec3 & destination() const;

    void setDestination(const glm::vec3 & destination);
    void setStopAtDestination(bool stopAtDestination);

    void update(
        RigidBody &                 body,
        NpcFlightControl &          flightControl,
        const FlightControlConfig & config,
        const UpdateFrame & updateFrame);

private:
    boost::optional<glm::vec3> m_destination;
    bool                       m_stopAtDestination = true;
};
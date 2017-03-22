#include "Weapon.h"

#include <glm/gtx/vector_angle.hpp>

#include <Deliberation/Core/Math/Trajetory.h>

#include "Equipment.h"
#include "HailstormBullet.h"
#include "HailstormManager.h"

Weapon::Weapon(const WeaponConfig & config, HailstormManager & hailstormManager, VoxelObjectWorldUID creatorUID):
    m_config(config),
    m_hailstormManager(hailstormManager),
    m_creatorUID(creatorUID)
{

}

const WeaponConfig & Weapon::config() const
{
    return m_config;
}

void Weapon::setFireRequest(bool active, const glm::vec3 & direction)
{
    Assert(!active || EpsilonEq(glm::length2(direction), 1.0f), "Normalize direction!")

    m_fireRequestActive = active;
    m_fireRequestDirection = direction;
}

void Weapon::setPose(const Pose3D & pose)
{
    m_pose = pose;
}

void Weapon::update(float seconds, const EquipmentUpdateContext & context, const Pose3D & weaponPose, float maxAngle)
{
    if (!m_fireRequestActive)
    {
        m_pose = weaponPose;
        m_cooldown = std::max(0.0f, m_cooldown - seconds);
        return;
    }

    auto timeAccumulator = 0.0f;

    auto baseMillis = (CurrentMillis() - ((TimestampMillis)std::ceil(seconds * 1000.0f)));

    while (seconds > m_cooldown)
    {
        seconds -= m_cooldown;
        timeAccumulator += m_cooldown;

        auto intermediatePose = m_pose.interpolated(weaponPose, timeAccumulator / (seconds + timeAccumulator));

        const auto origin = intermediatePose.position();
        const auto trajectoryLocal = intermediatePose.directionWorldToLocal(m_fireRequestDirection);

        auto angle = glm::angle(trajectoryLocal, glm::vec3(0.0f, 0.0f, -1.0f));

        if (angle <= maxAngle || true)
        {
            VfxParticle particle(
                m_config.meshID,
                origin,
                m_fireRequestDirection * m_config.bulletSpeed + context.linearVelocity,
                baseMillis + ((TimestampMillis)(timeAccumulator * 1000.0f)),
                m_config.bulletLifetime * 1000);

            particle.birthRGBA = glm::vec4(1.0f);
            particle.deathRGBA = glm::vec4(1.0f);

            particle.orientationType = VfxParticleOrientationType::World;

            HailstormBullet bullet(
                particle,
                50.0f,
                3,
                context.entity.id()
            );

            m_hailstormManager.addBullet(bullet);
            m_cooldown = m_config.cooldown;
        }
        else
        {
            seconds -= 0.001f;
        }
    }

    m_pose = weaponPose;
    m_cooldown -= seconds;
}
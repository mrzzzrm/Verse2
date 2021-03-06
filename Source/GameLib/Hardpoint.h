#pragma once

#include <memory>

#include <Deliberation/Core/Math/Pose3D.h>

#include "Attachment.h"
#include "GameLib.h"
#include "Weapon.h"

class EquipmentUpdateContext;
class Weapon;

struct HardpointDesc : AttachmentDesc
{
    float maxAngle = 0.0f;
    std::vector<std::string> compatibleWeapons;
};

class Hardpoint final : public Attachment
{
public:
    explicit Hardpoint(const HardpointDesc & desc);

    const std::shared_ptr<Weapon> & weapon() const;

    void clearFireRequest()
    {
        if (m_weapon) m_weapon->clearFireRequest();
    }
    void setFireRequest(const glm::vec3 & direction);

    /**
     * Only used for warping the Hardpoint, otherwise use update()'s
     * referencePose
     */
    void setReferencePose(const Pose3D & referencePose);

    void setWeapon(std::shared_ptr<Weapon> weapon);

    void update(const UpdateFrame & updateFrame, const EquipmentUpdateContext & context);

protected:
    void onDisabled() override;

private:
    float                   m_maxAngle = glm::half_pi<float>();
    Pose3D                  m_referencePose;
    std::shared_ptr<Weapon> m_weapon;
};
#pragma once

#include <memory>

#include <Deliberation/ECS/System.h>

#include "GameLib.h"
#include "VfxManager.h"

namespace deliberation
{
class Camera3D;
}

class Emitter;
class VfxManager;
class VoxelObjectModification;
class VoxelObjectBulletHit;

class VfxSystem final:
    public System<VfxSystem>
{
public:
    VfxSystem(World & world);

    VfxManager & manager() { return m_vfxManager; }
    const VfxManager & manager() const { return m_vfxManager; }

    void receive(const VoxelObjectModification & modification);
    void receive(const VoxelObjectBulletHit & hit);

protected:
    void onUpdate(float seconds) override;

private:
    VfxManager                  m_vfxManager;
    std::shared_ptr<Emitter>    m_blastEmitter;
    std::shared_ptr<Emitter>    m_smokeEmitter;
};
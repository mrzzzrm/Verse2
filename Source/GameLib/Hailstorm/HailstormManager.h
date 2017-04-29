#pragma once

#include <Deliberation/ECS/System.h>

#include "GameLib.h"
#include "HailstormBullet.h"
#include "HailstormPhysicsWorld.h"
#include "VfxManager.h"

namespace deliberation
{
class PhysicsWorld;
}

class HailstormManager final:
    public System<HailstormManager>
{
public:
    HailstormManager(World & world);

    VfxManager & vfxManager();

    void addBullet(HailstormBullet bullet);

protected:
    void onUpdate(float seconds) override;

private:
    VfxManager              m_vfxManager;
    HailstormPhysicsWorld   m_hailstormPhysicsWorld;
};

#include "HailstormManager.h"

#include <Deliberation/Core/ScopeProfiler.h>

#include <Deliberation/ECS/Systems/ApplicationSystem.h>
#include <Deliberation/ECS/Systems/PhysicsWorldSystem.h>
#include <Deliberation/ECS/World.h>

#include <Deliberation/Scene/Pipeline/RenderManager.h>
#include <Deliberation/Scene/Pipeline/RenderSystem.h>

#include "ResourceManager.h"
#include "VoxelWorld.h"
#include "VoxelObjectBulletHit.h"
#include "VfxSystem.h"

HailstormManager::HailstormManager(World & world)
    : Base(world)
    , m_vfxManager(
          world.systemRef<RenderSystem>().renderManager(),
          world.systemRef<ResourceManager>())
    , m_hailstormPhysicsWorld(
          world.systemRef<PhysicsWorldSystem>().physicsWorld(),
          world.systemRef<VoxelWorld>())
{
    m_vfxManager.meshRenderer().setName("HailstormVfxMesh");
    m_vfxManager.pointLightManager()->pointLightRenderer()->setName("HailstormPointLights");
}

VfxManager & HailstormManager::vfxManager() { return m_vfxManager; }

void HailstormManager::addBullet(HailstormBullet bullet)
{
    bullet.id.particleId = m_vfxManager.addParticle(bullet.particle);
    m_hailstormPhysicsWorld.addBullet(bullet);
}

void HailstormManager::onCreated()
{
    subscribeEvent<VoxelObjectBulletHit>();
}

void HailstormManager::onEvent(const VoxelObjectBulletHit & hit)
{
    auto & vfxManager = world().systemRef<VfxSystem>().manager();

    const auto & transform =
        hit.entity.component<Transform3DComponent>().value();

    const auto position = transform.pointLocalToWorld(glm::vec3(hit.voxel));

    if (hit.bullet.explosionEmitter)
    {
        auto emitterInstance = std::make_shared<EmitterInstance>(hit.bullet.explosionEmitter);
        emitterInstance->setBasePose(Pose3D::atPosition(position));

        vfxManager->addEmitterInstance(emitterInstance);
    }
}


void HailstormManager::onGameUpdate(const UpdateFrame & updateFrame)
{
    m_vfxManager.update(updateFrame);
    m_hailstormPhysicsWorld.update(updateFrame);

    for (const auto & hit : m_hailstormPhysicsWorld.voxelObjectBulletHits())
    {
        world().events()->publishEvent(hit);
    }

    for (auto & bullet : m_hailstormPhysicsWorld.destroyedBullets())
    {
        m_vfxManager.disengageParticle(bullet.particleId);
    }
}

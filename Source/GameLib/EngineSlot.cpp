#include "EngineSlot.h"

#include "Equipment.h"
#include "VfxManager.h"

EngineSlot::EngineSlot(const glm::uvec3 & voxel, const Pose3D & pose):
    ItemSlot(voxel, pose)
{}

const std::shared_ptr<Engine> & EngineSlot::engine() const
{
    return m_engine;
}

void EngineSlot::setEngine(const std::shared_ptr<Engine> & engine)
{
    m_engine = engine;
}

void EngineSlot::setTargetPose(const Pose3D & pose)
{
    if (m_engine)
    {
        auto voxelPose = pose.poseLocalToWorld(Pose3D::atPosition(glm::vec3(m_voxel)));
        m_engine->emitterInstance()->setTargetPose(voxelPose.poseLocalToWorld(m_pose));
    }
}

void EngineSlot::onDisabled()
{
    if (!m_engine) return;

    m_vfxManager->removeEmitterInstance(m_engine->emitterInstance());
}

void EngineSlot::setVfxManager(VfxManager & vfxManager)
{
    m_vfxManager = &vfxManager;
}
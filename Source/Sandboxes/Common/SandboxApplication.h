#include <iostream>
#include <memory>
#include <thread>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Deliberation/Core/Math/FloatUtils.h>
#include <Deliberation/Core/Math/Random.h>
#include <Deliberation/Core/Optional.h>

#include <Deliberation/ECS/Entity.h>
#include <Deliberation/ECS/Systems/PhysicsWorldSystem.h>
#include <Deliberation/ECS/World.h>

#include <Deliberation/Physics/PrimitiveTester.h>
#include <Deliberation/Physics/PhysicsWorld.h>
#include <Deliberation/Physics/RigidBody.h>

#include <Deliberation/Platform/App.h>

#include <Deliberation/Scene/Camera3D.h>
#include <Deliberation/Scene/CameraDolly3D.h>
#include <Deliberation/Scene/Debug/DebugCameraNavigator3D.h>
#include <Deliberation/Scene/Debug/DebugGeometryNode.h>
#include <Deliberation/Scene/Debug/DebugGeometryRenderer.h>
#include <Deliberation/Scene/Debug/DebugGroundPlaneRenderer.h>
#include <Deliberation/Scene/SkyboxRenderer.h>
#include <Deliberation/Scene/UVSphere.h>

#include <Npc/NpcDebugRendererSystem.h>

#include "AimHelper.h"
#include "CollisionShapeTypes.h"
#include "Emitter.h"
#include "Equipment.h"
#include "GameLib.h"
#include "HailstormManager.h"
#include "Hardpoint.h"
#include "NpcAttackTask.h"
#include "NpcController.h"
#include "NpcControllerSystem.h"
#include "NpcFlightControl.h"
#include "NpcSteering.h"
#include "PlayerFlightControl.h"
#include "VfxManager.h"
#include "VoxReader.h"
#include "VoxelClusterContact.h"
#include "VoxelClusterPrimitiveTest.h"
#include "VoxelRenderable.h"
#include "VoxelRigidBodyPayload.h"
#include "VoxelWorld.h"
#include "Weapon.h"

class SandboxApplication : public App
{
public:
    SandboxApplication(const std::string & name);

    void onStartup() final override;
    void onFrame(float seconds) final override;

protected:
    virtual void onSandboxStartup(){};
    virtual void onSandboxUpdate(float seconds){};
    virtual void onSandboxPhysicsUpdate(float physicsSeconds){};
    virtual void onSandboxRender(){};

protected:
    Camera3D                           m_camera;
    Clear                              m_clear;
    PhysicsWorld                       m_physicsWorld;
    Optional<DebugCameraNavigator3D>   m_navigator;
    Optional<VoxelWorld>               m_voxelWorld;
    Optional<DebugGroundPlaneRenderer> m_groundPlane;
    World                              m_world;

    std::shared_ptr<HailstormManager>       m_hailstormManager;
    std::experimental::optional<VfxManager> m_vfxManager;

    std::experimental::optional<DebugGeometryRenderer> m_debugGeometryManager;

    std::shared_ptr<SkyboxRenderer> m_skyboxRenderer;
};

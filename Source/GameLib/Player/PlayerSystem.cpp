#include "PlayerSystem.h"

#include <Deliberation/Core/Math/Trajectory.h>
#include <Deliberation/Core/Math/PrimitiveIntersection.h>
#include <Deliberation/Core/StreamUtils.h>

#include <Deliberation/Draw/DrawContext.h>
#include <Deliberation/Draw/Program.h>

#include <Deliberation/ECS/Components.h>
#include <Deliberation/ECS/Systems/ApplicationSystem.h>
#include <Deliberation/ECS/Systems/DebugGeometrySystem.h>
#include <Deliberation/ECS/Systems/PhysicsWorldSystem.h>
#include <Deliberation/ECS/World.h>

#include <Deliberation/Physics/RigidBody.h>
#include <Deliberation/Physics/PhysicsWorld.h>

#include <Deliberation/Platform/Input.h>
#include <Deliberation/Platform/KeyMap.h>

#include <Deliberation/Scene/Camera3D.h>
#include <Deliberation/Scene/Pipeline/RenderManager.h>

#include "AimHelper.h"
#include "Equipment.h"
#include "PlayerFlightControl.h"
#include "ResourceManager.h"
#include "VoxelObject.h"

PlayerSystem::PlayerSystem(World & world):
    Base(world, ComponentFilter::requires<
        RigidBodyComponent,
        VoxelObject,
        FlightControlConfig,
        PlayerFlightControl,
        Equipment>()),
    InputLayer(0),
    m_input(world.system<ApplicationSystem>().input()),
    m_cameraMode(CameraMode::Normal),
    m_navigator(world.system<RenderManager>().mainCamera(), m_input, 150.0f),
    m_physicsWorld(world.system<PhysicsWorldSystem>().physicsWorld()),
    m_cameraDolly(world.system<RenderManager>().mainCamera())
{

}

void PlayerSystem::onFrameBegin()
{
    m_linearThrust = {};
    m_angularThrust = {};

    if (m_player.isValid())
    {
        auto & equipment = m_player.component<Equipment>();
        equipment.clearFireRequests();
    }
}

void PlayerSystem::onEntityAdded(Entity & entity)
{
    Assert(!m_player.isValid(), "Can't have 2 player identities");
    m_player = entity;
}

void PlayerSystem::onEntityRemoved(Entity & entity)
{
    m_player = Entity();
}

void PlayerSystem::onEntityUpdate(Entity & entity, float seconds)
{
    auto &body = *entity.component<RigidBodyComponent>().value();
    auto &flightControlConfig = entity.component<FlightControlConfig>();
    auto &flightControl = entity.component<PlayerFlightControl>();

    if (m_cameraMode == CameraMode::Normal) {
        if (m_input.keyDown(Key_W)) m_linearThrust += glm::vec3(0.0f, 0.0f, -1.0f);
        if (m_input.keyDown(Key_S)) m_linearThrust += glm::vec3(0.0f, 0.0f, 1.0f);
        if (m_input.keyDown(Key_D)) m_linearThrust += glm::vec3(1.0f, 0.0f, 0.0f);
        if (m_input.keyDown(Key_A)) m_linearThrust += glm::vec3(-1.0f, 0.0f, 0.0f);

        if (m_input.keyDown(Key_Q)) m_angularThrust.z = 1;
        if (m_input.keyDown(Key_E)) m_angularThrust.z = -1;

        flightControl.setLinearThrust(m_linearThrust);
        flightControl.setAngularThrust(m_angularThrust);

        {
//            AimHelper aimHelper(m_camera, m_physicsWorld);
//
//            auto result = aimHelper.getTarget(m_input.mousePosition());
//            m_debugGeometryRenderer.sphere(0).setColor({1.0f, 1.0f, 0.0f});
//            m_debugGeometryRenderer.sphere(0).setRadius(2.0f);
//            m_debugGeometryRenderer.sphere(0).setTransform(Transform3D::atPosition(result.pointOfImpact));
        }
    }

    flightControl.update(body, flightControlConfig, seconds);
}

void PlayerSystem::onEntityPrePhysicsUpdate(Entity & entity, float seconds)
{
    if (m_cameraMode == CameraMode::Normal)
    {
        auto & voxelObject = entity.component<VoxelObject>();
        auto & voxelData = voxelObject.data();

        auto & playerBody = *entity.component<RigidBodyComponent>().value();

        glm::vec3 offset;
        offset.z = voxelData.size().z * 1.4f;
        offset.y = voxelData.size().y * 2;

        Pose3D targetPose(playerBody.transform().position() +
                          playerBody.transform().orientation() * offset,
                          playerBody.transform().orientation());

        auto position = targetPose.pointLocalToWorld({});

        m_cameraDolly.update(position, targetPose.orientation(), seconds);
    }
}

void PlayerSystem::onUpdate(float seconds)
{
    if (m_input.keyPressed(Key_C))
    {
        m_cameraMode = (CameraMode)(((int)m_cameraMode + 1) % (int)CameraMode::Count);
    }
}

void PlayerSystem::onPrePhysicsUpdate(float seconds)
{
    if (m_cameraMode == CameraMode::FreeFlight)
    {
        m_navigator.update(seconds);
    }
}

void PlayerSystem::onMouseButtonDown(MouseButtonEvent & event)
{
    if (!m_player.isValid()) return;

    if (event.button() == MouseButton_Left)
    {
        const auto & mouse = event.mousePosition();

        m_angularThrust.x = mouse.y;
        m_angularThrust.y = -mouse.x;
    }

    if (event.button() == MouseButton_Right)
    {
        auto & renderManager = world().system<RenderManager>();
        AimHelper aimHelper(renderManager.mainCamera(), m_physicsWorld);

        auto result = aimHelper.getTarget(m_input.mousePosition());

        auto & body = *m_player.component<RigidBodyComponent>().value();

        auto & equipment = m_player.component<Equipment>();
        Transform3D equipmentTransform = body.transform();

        equipmentTransform.setScale(m_player.component<VoxelObject>().scale());

        equipment.setFireRequestTargetForAllHardpoints(
            equipmentTransform,
            body.linearVelocity(),
            result.pointOfImpact,
            glm::vec3(0.0f));
    }
}
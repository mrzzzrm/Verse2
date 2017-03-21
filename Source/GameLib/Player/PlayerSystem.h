#pragma once

#include <memory>

#include <Deliberation/Core/Chrono.h>

#include <Deliberation/Draw/Draw.h>

#include <Deliberation/ECS/System.h>

#include <Deliberation/Platform/Input.h>
#include <Deliberation/Platform/InputLayer.h>

#include <Deliberation/Scene/CameraDolly3D.h>
#include <Deliberation/Scene/Debug/DebugCameraNavigator3D.h>

#include "GameLib.h"

namespace deliberation
{
class InputBase;
class Camera3D;
class PhysicsWorld;
class World;
}

class PlayerSystem:
    public std::enable_shared_from_this<PlayerSystem>,
    public System<PlayerSystem>,
    public InputLayer
{
public:
    PlayerSystem(World & world,
                 Camera3D & camera);

    void setPlayerTarget(Entity & entity) { m_playerTarget = entity; }

    void renderUi();

    void onCreated() override { m_input.addLayer(shared_from_this()); }
    void onRemoved() override { m_input.removeLayer(shared_from_this()); }

protected:
    void onFrameBegin() override;
    void onEntityAdded(Entity & entity) override;
    void onEntityRemoved(Entity & entity) override;
    void onEntityUpdate(Entity & entity, float seconds) override;
    void onEntityPrePhysicsUpdate(Entity & entity, float seconds) override;

    void onMouseButtonDown(MouseButtonEvent & event) override;

private:
    enum class CameraMode
    {
        Normal,
        FreeFlight,
        Count
    };

private:
    Context &               m_context;
    InputBase &             m_input;
    Camera3D &              m_camera;
    PhysicsWorld &          m_physicsWorld;

    CameraMode              m_cameraMode;
    DebugCameraNavigator3D  m_navigator;
    CameraDolly3D           m_cameraDolly;

    TimestampMillis         m_leftMousePressedMillis = 0;

    Entity                  m_player;
    Entity                  m_playerTarget;

    Draw                    m_crosshairsDraw;
    Uniform                 m_viewportSizeUniform;
    Uniform                 m_crosshairPositionUniform;

    glm::vec3               m_linearThrust;
    glm::vec3               m_angularThrust;
};
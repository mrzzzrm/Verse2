#include <iostream>

#include <Deliberation/Core/Json.h>
#include <Deliberation/Core/Math/Transform3D.h>

#include <Deliberation/Platform/Application.h>

#include <Deliberation/Physics/PhysicsWorld.h>
#include <Deliberation/Physics/RigidBody.h>
#include <Deliberation/Physics/Narrowphase.h>

#include <Deliberation/Scene/Camera3D.h>
#include <Deliberation/Scene/CameraDolly3D.h>
#include <Deliberation/Scene/Debug/DebugCameraNavigator3D.h>
#include <Deliberation/Scene/Debug/DebugGroundPlaneRenderer.h>
#include <Deliberation/Scene/Debug/DebugGeometryManager.h>
#include <Deliberation/Scene/Debug/DebugGeometryRenderer.h>
#include <Deliberation/Scene/UVSphere.h>

#include <Deliberation/Deliberation.h>


#include <Voxel/VoxelRigidBodyPayload.h>
#include <Voxel/VoxelClusterPrimitiveTest.h>

#include "AimHelper.h"
#include "Emitter.h"
#include "Equipment.h"
#include "EquipmentPrototype.h"
#include "EntityPrototypeManager.h"
#include "EntityPrototypeSystem.h"
#include "CollisionShapeTypes.h"
#include "Hardpoint.h"
#include "VfxRenderer.h"
#include "VoxelClusterMarchingCubesTriangulation.h"
#include "VoxelClusterMarchingCubes.h"
#include "VoxelClusterContact.h"
#include "VoxelObject.h"
#include "VoxelWorld.h"
#include "VoxReader.h"
#include "Player/PlayerFlightControl.h"
#include "VerseApplication.h"
#include "Weapon.h"

using namespace deliberation;

class Game:
    public VerseApplication
{
public:
    Game():
        VerseApplication("Verse")
    {

    }

    void onApplicationStartup() override {
        DisableGLErrorChecks();
        //EnableGLErrorChecksAndLogging();

        auto & entityPrototypeManager = m_world.system<EntityPrototypeSystem>().manager();

        /**
         * Create player
         */
        auto player = entityPrototypeManager.createEntity({"Ship", "Player"}, "PlayerShip");

        player.component<VoxelObject>().setInvincible(true);

        {
            auto &playerBody = player.component<RigidBodyComponent>().value();
            playerBody->transform().setPosition({0.0f, 20.0f, 50.0f});
        }

        /**
         * Create block
         */
//        auto block = entityPrototypeManager.createEntity({"Block8x8x8"}, "Block");
//        {
//            auto &blockBody = player.component<RigidBodyComponent>().value();
//            blockBody->transform().setPosition({0.0f, 20.0f, 150.0f});
//        }

        /**
         * Create station
         */
//        auto station = entityPrototypeManager.createEntity({"Station"}, "MyStation");
//        auto stationBody = station.component<RigidBodyComponent>().value();
//        stationBody->transform().setPosition({0.0f, 40.0f, -100.0f});

        /**
         * Create asteroids
         */
        for (auto i = 0; i < 30; i++) {
            auto asteroid = entityPrototypeManager.createEntity({"Asteroid00"}, "MyAsteroid");
            auto asteroidBody = asteroid.component<RigidBodyComponent>().value();
            asteroidBody->transform().setPosition(RandomUnitVec3() * 250.0f);
        }

//        for (auto i = 0; i < 15; i++) {
//            auto asteroid = entityPrototypeManager.createEntity({"Asteroid01"}, "MyAsteroid");
//            auto asteroidBody = asteroid.component<RigidBodyComponent>().value();
//            asteroidBody->transform().setPosition(RandomUnitVec3() * 1250.0f);
//        }

        /**
         * Create enemies
         */
//        for (auto i = 0; i < 2; i++) {
//            auto npc = entityPrototypeManager.createEntity({"Sting", "Npc", "Pirate"}, "MyNPC");
//            auto npcBody = npc.component<RigidBodyComponent>().value();
//            npcBody->transform().setPosition(glm::vec3(300.0f, 0.0f, 0.0f) + RandomUnitVec3() * 1000.0f);
//        }
//        for (auto i = 0; i < 1; i++) {
//            auto npc = entityPrototypeManager.createEntity({"Drone", "Npc", "Pirate"}, "MyNPC");
//            auto npcBody = npc.component<RigidBodyComponent>().value();
//            npcBody->transform().setPosition(glm::vec3(300.0f, 0.0f, 0.0f) + RandomUnitVec3() * 1000.0f);
//        }
    }
};

int main(int argc, char *argv[])
{
    return Game().run(argc, argv);
}

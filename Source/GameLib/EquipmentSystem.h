#pragma once

#include <Deliberation/ECS/System.h>

#include "GameLib.h"
#include "VoxelObjectModification.h"

class EquipmentSystem : public System<EquipmentSystem>
{
public:
    EquipmentSystem(World & world);

    void onEvent(const VoxelObjectModification & voxelObjectModification);

    void onCreated() override;

protected:
    void onEntityAdded(Entity & entity) override;
    void onEntityRemoved(Entity & entity) override;
    void onEntityGameUpdate(Entity & entity, const UpdateFrame & updateFrame) override;
    void onEntityPostPhysicsUpdate(Entity & entity, const UpdateFrame & updateFrame) override;
};
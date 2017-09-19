#include "VoxelShredderSandbox.h"

#include <Deliberation/Core/Log.h>

#include <Deliberation/ECS/EntityPrototypeManager.h>

#include <Deliberation/Platform/Application.h>
#include <Deliberation/Platform/ApplicationRuntime.h>

#include "VoxelShredder.h"
#include "VoxelClusterSplitSystem.h"

VoxelShredderSandbox::VoxelShredderSandbox()
{
    activateInputLayer(0);
}

void VoxelShredderSandbox::onKeyPressed(KeyEvent & event)
{
    DELIBERATION_LOG_INNER_SCOPE("VoxelShredderSandbox");

    if (event.key() == Key_N)
    {
        Log->info("New scenario");
        for (auto & entity : m_segmentEntities)
        {
            if (entity.isValid()) entity.scheduleRemoval();
        }
        m_segmentEntities.clear();

        if (m_originalEntity.isValid()) m_originalEntity.scheduleRemoval();

        m_originalEntity = Application::instance().runtime()->entityPrototypeManager()->createEntity("Block2x2x2");
    }

    if (event.key() == Key_M && m_originalEntity.isValid())
    {
//        VoxelShredder shredder;
//        m_segmentEntities = shredder.shred(m_originalEntity);
//        m_originalEntity.scheduleRemoval();

        VoxelClusterSegment seg;
        seg.voxels = {glm::uvec3(0, 0, 0)};
        seg.llf = glm::uvec3(0, 0, 0);
        seg.urb = glm::uvec3(0, 0, 0);
        auto entity = VoxelClusterSplitSystem::splitVoxelsOffEntity(m_originalEntity, seg);
    }
}
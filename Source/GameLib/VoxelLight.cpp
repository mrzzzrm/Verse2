#include "VoxelLight.h"

#include <Deliberation/Core/UpdateFrame.h>
#include <Deliberation/Core/Noise.h>
#include <Deliberation/ECS/World.h>

#include <Deliberation/Scene/Lighting/PointLightRenderer.h>

#include "ColorPalette.h"
#include "VoxelObject.h"

VoxelLight::VoxelLight(const VoxelLightDesc & desc)
    : Attachment(desc), m_desc(desc)
{
}

void VoxelLight::onEnabled()
{
//    auto & pointLightRenderer =
//        m_entity.world().systemRef<PointLightSystem>().pointLightRenderer();
//    auto & voxelObject = m_entity.component<VoxelObject>();
//
//    const auto colorIndex = voxelObject.data()->voxelColorIndex(voxel());
//
//    m_color = glm::vec3(voxelObject.data()->palette()->colors()[colorIndex]) / glm::vec3(255.0f);
//    auto intensity = m_color * m_desc.intensity;
//
//    PointLight pointLight;
//    pointLight.intensity = intensity;
//
//    m_pointLight = pointLightRenderer->addPointLight(pointLight);
//
//    voxelObject.data()->palette()->setBrightnessScale(colorIndex, m_desc.intensity);
}

void VoxelLight::onDisabled()
{
//    auto & pointLightRenderer =
//        m_entity.world().systemRef<PointLightSystem>().pointLightRenderer();
//
//    pointLightRenderer->removePointLight(m_pointLight);
}

void VoxelLight::onGameUpdate(const UpdateFrame & updateFrame, const EquipmentUpdateContext & context)
{
//    m_noiseInput += updateFrame.gameSeconds() * 6.0f;
//
//    auto noise = std::sin(m_noiseInput);
//    auto intensity = (m_color + m_color * noise * 0.7f) * m_desc.intensity;
//
//    auto & pointLightRenderer =
//        m_entity.world().systemRef<PointLightSystem>().pointLightRenderer();
//    auto & voxelObject = m_entity.component<VoxelObject>();
//
//    auto & pointLight = pointLightRenderer->pointLight(m_pointLight);
//    pointLight.position = worldPose().position();
//    pointLight.intensity = intensity;
//
//    const auto colorIndex = voxelObject.data()->voxelColorIndex(voxel());
//    voxelObject.data()->palette()->setBrightnessScale(colorIndex, m_desc.intensity);
}
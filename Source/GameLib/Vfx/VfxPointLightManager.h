#pragma once

#include <memory>

#include <Deliberation/Core/SparseVector.h>

#include "GameLib.h"
#include "VfxParticle.h"
#include "VfxPointLight.h"

namespace deliberation
{
class PointLightRenderer;
}

class VfxPointLightManager
{
public:
    explicit VfxPointLightManager(const std::shared_ptr<PointLightRenderer> & pointLightRenderer);
    virtual ~VfxPointLightManager() = default;

    const std::shared_ptr<PointLightRenderer> & pointLightRenderer() { return m_pointLightRenderer; }
    std::shared_ptr<const PointLightRenderer> pointLightRenderer() const { return m_pointLightRenderer; }

    size_t addParticlePointLight(const VfxParticle & particle, const VfxPointLightDesc & particlePointLight);
    void removeParticlePointLight(size_t index);
    void disengageParticlePointLight(size_t index);

    void update(const UpdateFrame & updateFrame);

private:
    std::shared_ptr<PointLightRenderer> m_pointLightRenderer;
    SparseVector<VfxPointLight>         m_pointLights;
};


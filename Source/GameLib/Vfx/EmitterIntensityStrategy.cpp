#include "EmitterIntensityStrategy.h"

#include "EmitterInstance.h"

std::shared_ptr<EmitterIntensityContext>
EmitterIntensityStrategy::createContext() const
{
    return std::make_shared<EmitterIntensityContext>();
}

EmitterNoisyIntensity::EmitterNoisyIntensity(
    float frequency, float standardDeviation)
    : m_dist(1.0f / frequency, (1.0f / frequency) * standardDeviation)
{
}

float EmitterNoisyIntensity::generateInterval(EmitterInstance & instance, EmitterInstanceContext & context) const
{
    return std::max(0.0f, m_dist(m_engine));
}

EmitterBurstIntensity::EmitterBurstIntensity(
    float mean, float standardDeviation)
    : m_engine(), m_dist(mean, standardDeviation)
{
}

float EmitterBurstIntensity::generateInterval(EmitterInstance & instance, EmitterInstanceContext & context) const
{
    auto intensityContext =
        std::dynamic_pointer_cast<Context>(context.intensityContext);

    if (intensityContext->countdown > 0)
    {
        intensityContext->countdown--;
        return 0.0f;
    }
    else
    {
        return NO_FURTHER_EMISSIONS;
    }
}

std::shared_ptr<EmitterIntensityContext>
EmitterBurstIntensity::createContext() const
{
    auto context = std::make_shared<Context>();
    context->countdown = (u32)m_dist(m_engine);
    return context;
}
#include <core/util/Log.hpp>
#include <core/math/math.hpp>
#include "QuadTreeSettings.hpp"

namespace sn
{

void QuadTreeSettings::setMaxDepth(u32 maxDepth)
{
    m_maxDepth = maxDepth;
}

void QuadTreeSettings::setRootSize(s32 rootSize)
{
    m_rootSize = rootSize;
}

void QuadTreeSettings::fix()
{
    if (!math::isPowerOfTwo(m_rootSize))
    {
        SN_WARNING("QuadTreeSettings rootSize is not a power of two. Adjusting...");
        m_rootSize = math::upperPowerOfTwo(m_rootSize);
        SN_DLOG("rootSize=" << m_rootSize);
    }

    if ((m_rootSize >> m_maxDepth) < 1)
    {
        SN_WARNING("QuadTreeSettings rootSize is not valid for integer representation. Adjusting...");

        s32 scale = 1;
        while ((m_rootSize >> m_maxDepth) < 1)
        {
            ++scale;
        }

        m_worldScale *= static_cast<f32>(scale);
        m_rootSize *= scale;

        SN_DLOG("rootSize=" << m_rootSize << ", m_worldScale=" << m_worldScale);
    }
}


} // namespace sn


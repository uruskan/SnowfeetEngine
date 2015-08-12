#ifndef __HEADER_SN_RENDER_MATERIAL__
#define __HEADER_SN_RENDER_MATERIAL__

#include <core/asset/base/Material.h>
#include <core/util/SharedRef.h>
#include <core/math/Vector4.h>

#include "ShaderProgram.h"
#include "RenderTexture.h"
#include "BlendMode.h"

namespace sn {
namespace render {

class Material : public sn::Material
{
public:
    SN_SCRIPT_OBJECT(sn::render::Material, sn::Material)

    Material() :
        sn::Material(),
        m_shader(nullptr),
        m_depthTest(false)
    {}

    //------------------------------------
    // Material Methods (see generic Material for other parameters)
    //------------------------------------

    void setShader(ShaderProgram * shader);
    inline ShaderProgram * getShader() const { return m_shader.get(); }

    // Depth buffer requirement
    bool isDepthTest() const { return m_depthTest; }
    void setDepthTest(bool zTest) { m_depthTest = zTest; }

    BlendMode getBlendMode() const { return m_blendMode; }
    void setBlendMode(BlendMode mode) { m_blendMode = mode; }

    // Note: "setParam" was not used here because C++ method overloads are limited to the scope where they are defined.
    // If setParam was used, those defined in the base class could not be resolved.

    void setRenderTexture(const std::string & name, RenderTexture * tex);

    void apply();

private:
    ~Material();

private:
    SharedRef<ShaderProgram> m_shader;

    bool m_depthTest;
    BlendMode m_blendMode;

};

} // namespace render
} // namespace sn

#endif // __HEADER_SN_RENDER_MATERIAL__

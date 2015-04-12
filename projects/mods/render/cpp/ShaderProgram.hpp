﻿/*
Shader.hpp
Copyright (C) 2010-2014 Marc GILLERON
This file is part of the SnowfeetEngine project.
*/

#ifndef __HEADER_SN_RENDER_SHADERPROGRAM__
#define __HEADER_SN_RENDER_SHADERPROGRAM__

#include <core/asset/Asset.hpp>
#include <unordered_map>
#include <GL/glew.h>

#include "Vertex.hpp"
#include "Texture.hpp"

namespace sn {
namespace render {

enum ShaderType
{
    SNR_ST_VERTEX = 0,
    SNR_ST_FRAGMENT,
    SNR_ST_GEOMETRY,
    //...
    SNR_ST_COUNT // Keep last
};

std::string toString(ShaderType st);

class SN_API ShaderProgram : public Asset
{
public:
    SN_SCRIPT_OBJECT(sn::render::ShaderProgram, sn::Asset)

    // Constructs an empty program.
    ShaderProgram():
        Asset(),
        m_programID(0)
    {}

	//----------------------------------
	// Asset interface
	//----------------------------------

    bool canLoad(const AssetMetadata & meta) const override;
    bool loadFromStream(std::ifstream & ifs) override;

	//----------------------------------
	// ShaderProgram interface
	//----------------------------------

    bool loadFromSourceCode(const std::unordered_map<ShaderType, std::string> & sources);

    // Deletes the program and its shaders.
    void unload();

    // Returns the program's ID.
    inline GLuint getID() const { return m_programID; }

    void setParam(const std::string & name, f32 x);
    void setParam(const std::string & name, f32 x, f32 y);
    void setParam(const std::string & name, f32 x, f32 y, f32 z);
    void setParam(const std::string & name, f32 x, f32 y, f32 z, f32 w);
    void setParam(const std::string & name, const f32 matrixValues[16], bool transpose=false);
    void setParam(const std::string & name, s32 i);

    bool hasParameter(const std::string & name);

protected:
    // Destroys the program and its shaders.
    ~ShaderProgram();

private:

    // Finds the location of an uniform using internal index.
    // If not found in the index, the program is queried.
    // Undefined uniform name leads to an undefined behavior.
    GLint getUniformLocation(const std::string & name);

    // Loads a shader from a source file,
    // and returns its ID in outShaderID.
    // Returns true if success, false if not.
    static bool loadShaderFromSourceCode(GLuint & outShaderID, ShaderType typeGeneric, const std::string & source);

    struct Shader
    {
        GLuint ID;
        Shader(GLuint sID):
            ID(sID)
        {}
    };

    GLuint m_programID;

    // Note: Uniforms affect a geometry (while attribs affect vertices)
    std::unordered_map<std::string, GLint> m_uniforms;

    // List of compiled shaders, indexed by ShaderType.
    // Entries can be null, except required shaders such as vertex and fragment.
    std::vector<Shader*> m_shaders;

};

} // namespace render
} // namespace sn

#endif // __HEADER_SN_RENDER_SHADERPROGRAM__


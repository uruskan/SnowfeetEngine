#include <core/asset/base/Mesh.hpp>
#include <core/util/stringutils.hpp>
#include <core/util/typecheck.hpp>

#include "BasicMeshLoader.hpp"
#include "ply/PLYLoader.hpp"

namespace sn {
namespace render {

const ObjectType & BasicMeshLoader::getAssetType() const
{
    return Mesh::__sGetObjectType();
}

bool BasicMeshLoader::canLoad(const AssetMetadata & meta) const
{
    String ext = sn::getFileExtension(meta.path);
    return ext == L".ply";
}

bool BasicMeshLoader::load(std::ifstream & ifs, Asset & asset) const
{
    Mesh * mesh = checked_cast<Mesh*>(&asset);
    PLYLoader loader(ifs);
    return loader.loadMesh(*mesh);
}

} // namespace render
} // namespace sn


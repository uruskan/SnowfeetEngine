#ifndef __HEADER_SN_SPACE_QUADTREE__
#define __HEADER_SN_SPACE_QUADTREE__

#include <core/space/QuadTreeNode.hpp>
#include <core/space/SpaceTreeSettings.hpp>
#include <core/math/Vector2.hpp>
#include <unordered_map>

namespace sn
{

/// \brief QuadTree structure with unlimited bounds (my first implementation ever).
/// It implements a quad grid where each bucket can subdivide to a tree, depending on choosen settings.
class SN_API QuadTree : public ISpacePartitioner, public NonCopyable
{
public:
    typedef ISpacePartitioner::Userdata Userdata;

    QuadTree();
    ~QuadTree();

    void add(Userdata obj, const FloatRect & bounds) override;
    void remove(Userdata obj, const FloatRect & bounds) override;
    void query(const FloatRect & bounds, std::vector<Userdata> & results) override;
    void clear();

    inline const SpaceTreeSettings & getSettings() const { return m_settings; }

    // TODO setSettings(QuadTreeSettings)

#ifdef SN_BUILD_DEBUG    
    void debugPrint(std::ostream & os);
#endif

private:
    struct Boundaries
    {
        s32 minX;
        s32 minY;
        s32 maxX;
        s32 maxY;
    };

    Boundaries getConvertedBoundaries(const FloatRect & bounds);

    void getNodes(const FloatRect & bounds, std::vector<QuadTreeNode*> & outNodes);
    void getOrCreateNodes(const FloatRect & bounds, std::vector<QuadTreeNode*> & outNodes);

    IntRect calculateTotalKeyBounds();

    void applySettings(const SpaceTreeSettings & newSettings);
    IntRect convertObjectBounds(const FloatRect & bounds);

private:
    SpaceTreeSettings m_settings;
    std::unordered_map<Vector2i,QuadTreeNode*> m_roots;

};

} // namespace sn

#endif // __HEADER_SN_SPACE_QUADTREE__


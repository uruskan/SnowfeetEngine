#ifndef __HEADER_SN_SCENE__
#define __HEADER_SN_SCENE__

#include <core/scene/Entity.hpp>
#include <core/util/RefCounted.hpp>
#include <map>

namespace sn
{

// SUGG: getScene() return the first parent scene, getRoot() returns the top-most,
// that can be either the game scene or editor's scene?

/// \brief The scene is the top-level object of the game world.
/// It cannot have a parent and cannot be destroyed.
/// Its semantic is like an Application, it exists as long as the program runs.
/// (Each entity is a scene, in some way. But the actual Scene is the only one root).
/// \note: you can still nest scenes by creating some in your entities, to make an editor for instance.
/// However, sub-scenes cannot interact with their parent unless custom access is given.
class SN_API Scene : public Entity
{
public:

    SN_OBJECT(sn::Scene, sn::Object)

    Scene() : 
        Entity(), 
        m_quitFlag(false)
    {
        setName("Scene");
    }

    void registerUpdatableEntity(Entity::Ref e, s16 order, s16 layer);
    void unregisterUpdatableEntity(Entity::Ref e);

    void registerTaggedEntity(Entity::Ref e, const std::string & tag);
    void unregisterTaggedEntity(Entity::Ref e, const std::string & tag);

    void setParent(Entity::Ref newParent) override;

    void destroy() override;
    void destroyLater() override;

    void onUpdate() override;

    inline void quit() { m_quitFlag = true; }
    inline bool getQuitFlag() const { return m_quitFlag; }

    void loadFromFile(const std::string & filePath);
    void saveToFile(const std::string & filePath);

private:
    std::unordered_map<std::string, std::unordered_set<Entity::Ref>> m_taggedEntities;
    std::map<s32, std::unordered_set<Entity::Ref>> m_updatableEntities;
    bool m_quitFlag;

};

} // namespace sn

#endif // __HEADER_SN_SCENE__



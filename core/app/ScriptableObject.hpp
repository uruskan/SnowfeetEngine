/*
ScriptableObject.hpp
Copyright (C) 2014-2015 Marc GILLERON
This file is part of the SnowfeetEngine project.
*/

#ifndef __HEADER_SN_SCRIPTABLEOBJECT__
#define __HEADER_SN_SCRIPTABLEOBJECT__

#include <core/reflect/Object.hpp>
#include <core/util/RefCounted.hpp>
#include <core/squirrel/ScriptInstance.hpp>
#include <core/squirrel/ScriptClass.h>
#include <core/squirrel/ScriptTable.h>
#include <type_traits>

#define SN_SCRIPT_OBJECT(_className, _baseName) SN_OBJECT(_className, _baseName)

namespace sn
{

// TODO Move to the squirrel/ folder?
/// \brief All classes accessible and creatable from scripts should inherit this class.
/// It is an Object because reflection is currently used to get the class name used in scripts.
/// It is RefCounted because of shared ownership between C++ and scripts.
class SN_API ScriptableObject : public RefCounted, public Object
{
public:
    SN_SCRIPT_OBJECT(sn::ScriptableObject, sn::Object)

    ScriptableObject();

    /// \brief Pushes the C++ instance on the Squirrel stack.
    /// Several calls should return the same Squirrel instance, as long as at least one stays referenced.
    /// If no class instance is referenced by Squirrel at the time, a new one will be created.
    void pushScriptObject(HSQUIRRELVM vm);

    /// \brief Auto-binds a ScriptableObject class to Squirrel with just a constructor and destructor,
    /// and returns it to let binding the other specific members.
    template <typename T>
    static ScriptClass bindBase(HSQUIRRELVM vm)
    {
        // Get the class name
        const ObjectType & ot = sn::getObjectType<T>();
        const std::string & sqName = ot.getScriptName();

        // Get the base class name
        std::string sqBaseName;
        const ObjectType * base = ot.getBase();
        const ObjectType & rootType = sn::getObjectType<ScriptableObject>();
        if (base && !base->isAbstract() && *base != rootType)
        {
            sqBaseName = base->getScriptName();
        }

        // Create the class
        ScriptClass c(vm, sqName, sqBaseName);

        // Bind constructor
        c.setConstructor(cb_scriptConstructor<T>);

        // Make it accessible from the root table
        ScriptRootTable(vm).setObject(sqName.c_str(), c);

        return c;
    }

protected:
    ~ScriptableObject();

private:
    /// \brief This should be called when the ScriptableObject is created from a script.
    void onCreateFromScript(HSQUIRRELVM vm, HSQOBJECT obj);

    /// \brief This should be called when the ScriptableObject is released from a script.
    void onReleaseFromScript();

    /// \brief Applies inheritance from base classes if they were bound already
    void bindBaseClasses(ScriptClass & c);

    /// \brief Must be bound as native constructor of the class in Squirrel
    template <typename T>
    static SQInteger cb_scriptConstructor(HSQUIRRELVM vm)
    {
        typedef std::is_base_of<ScriptableObject, T> TestBaseOfT;
        SN_STATIC_ASSERT_MSG(TestBaseOfT::value, "Class does not derives from ScriptableObject");
        T * p = new T();
        sq_setinstanceup(vm, -1, p);
        sq_setreleasehook(vm, -1, cb_releaseHook);
        return 0;
    }

    /// \brief Must be bound as release hook of instances in Squirrel
    static SQInteger cb_releaseHook(SQUserPointer ptr, SQInteger size);

private:
    /// \brief VM owning the object. Can be null if the object is not referenced in a script.
    HSQUIRRELVM m_vm;

    /// \brief This is the Squirrel side of the object.
    /// It becomes non-null when the C++ class is instantiated from a script,
    /// or when it needs to be pushed on the Squirrel stack for the first time.
    /// It allows the engine to ensure the Squirrel world will get the same
    /// instance when it needs to be pushed by C++.
    /// It also enables inheriting the native class in Squirrel,
    /// however virtual calls from C++ are not guaranteed at all. 
    /// It all depends on the scriptable API of the class.
    HSQOBJECT m_scriptSide;

};

} // namespace sn

#endif // __HEADER_SN_SCRIPTABLEOBJECT__

﻿#include "as_math.hpp"
#include "../../app/ScriptEngine.hpp"
#include "../math.hpp"
#include "../Vector2.hpp"
#include "../Color.hpp"

namespace sn
{

//------------------------------------------------------------------------------
f32 asRand() { return math::randf(); }
f32 asRandMinMax(f32 min, f32 max) { return math::randf(min, max); }
s32 asRandIntMinMax(s32 min, s32 max) { return math::rand(min, max); }

//------------------------------------------------------------------------------
void register_math(asIScriptEngine & e)
{
    asCheck(e.RegisterGlobalFunction("float rand()", asFUNCTIONPR(asRand, (), f32), asCALL_CDECL));
    asCheck(e.RegisterGlobalFunction("float rand(float, float)", asFUNCTIONPR(asRandMinMax, (f32, f32), f32), asCALL_CDECL));
    asCheck(e.RegisterGlobalFunction("int randint(int, int)", asFUNCTIONPR(asRandIntMinMax, (s32, s32), s32), asCALL_CDECL));

    register_Vector2i(e);
    register_Color(e);
    register_IntRect(e);
    register_FloatRect(e);
}

} // namespace sn




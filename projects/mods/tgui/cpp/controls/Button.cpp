#include <core/util/Profiler.h>

#include "Button.h"
#include "../GUI.h"
#include "../DrawBatch.h"

using namespace sn;

namespace tgui
{

//------------------------------------------------------------------------------
void Button::onMousePress(Event & e)
{
	if (!getScript().isNull())
	{
		getScript().callMethod("onButtonPress");
	}
}

//------------------------------------------------------------------------------
void Button::onMouseRelease(Event & e)
{
}

//------------------------------------------------------------------------------
void Button::onDrawSelf(DrawBatch & batch)
{
    GUI * gui = getGUI();
    if (gui == nullptr)
        return;
    const Theme & theme = gui->getTheme();
    const ControlTheme & ct = theme.controlTheme;

    SN_BEGIN_PROFILE_SAMPLE_NAMED("TGUI draw Button");

    IntRect bounds = getClientBounds();

    u32 state = ControlTheme::STATE_NORMAL;
    if (isPressed())
        state = ControlTheme::STATE_PRESSED;
    else if (isHovered())
        state = ControlTheme::STATE_HOVERED;

    const IntRect & uvRect = ct.statesUV[state];
    Vector2u ts = theme.getTextureAtlasSize();

    batch.fillNineSlices(bounds, ct.slicing, uvRect, ts);

    SN_END_PROFILE_SAMPLE();
}

//------------------------------------------------------------------------------
void Button::serializeState(JsonBox::Value & o, const SerializationContext & ctx)
{
    Control::serializeState(o, ctx);

}

//------------------------------------------------------------------------------
void Button::unserializeState(JsonBox::Value & o, const SerializationContext & ctx)
{
    Control::unserializeState(o, ctx);

}

} // namespace tgui




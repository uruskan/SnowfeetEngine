#ifndef __HEADER_TGUI_RENDERER__
#define __HEADER_TGUI_RENDERER__

#include <core/scene/Drawable.hpp>

namespace tgui
{

class Renderer : public sn::Drawable
{
public:
    SN_ENTITY(tgui::Renderer, sn::Drawable)

protected:
    void onDraw(sn::IDrawContext & dc) override;
};

} // namespace tgui

#endif // __HEADER_TGUI_RENDERER__

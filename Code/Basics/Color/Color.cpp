
#define USES_ENGINE_COLOR
#include "EngineDeps.h"

//*****************************************************************************
//
// Color
//
//*****************************************************************************

const Color Color::White   = {1.0f, 1.0f, 1.0f};
const Color Color::Black   = {0.0f, 0.0f, 0.0f};
const Color Color::Red     = {1.0f, 0.0f, 0.0f};
const Color Color::Green   = {0.0f, 1.0f, 0.0f};
const Color Color::Blue    = {0.0f, 0.0f, 1.0f};
const Color Color::Yellow  = {1.0f, 1.0f, 0.0f};
const Color Color::Aqua    = {0.0f, 1.0f, 1.0f};
const Color Color::Magenta = {1.0f, 0.0f, 1.0f};

//=============================================================================
Color::Color (const Hsl & hsl) :
    TColorBase()
{
    ASSERT(false);
}



//*****************************************************************************
//
// Hsl
//
//*****************************************************************************

//=============================================================================
Hsl::Hsl (const Color & color) :
    a(color.a)
{
    const float32 max = Max(color.r, color.g, color.b);
    const float32 min = Min(color.r, color.g, color.b);

    // Luminance
    l = (min + max) * 0.5f;

    if (min == max)
    {
        h = 0;
        s = 0;
    }
    else
    {
        const float32 d = max - min;

        // Saturation
        s = (l > 0.5f) ? (d / (2.0f - max - min)) : (d / (max + min));

        // Hue
        if (max == color.r)
            h = (color.g - color.b) / d + (color.g < color.b ? 6 : 0);
        else if (max == color.g)
            h = (color.b - color.r) / d + 2.0f;
        else
            h = (color.r - color.g) / d + 4.0f;
        h /= 6.0f;
    }
}
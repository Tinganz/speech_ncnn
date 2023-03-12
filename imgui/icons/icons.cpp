#include "imgui.h"
#include "imgui_internal.h"

extern const char StepMath_compressed_data_base85[];
#define ICON_MIN_MATH 0x2000
#define ICON_MAX_MATH 0x2A80

bool ImGui::LoadInternalIcons(ImFontAtlas* atlas)
{
    float icons_size = 16.0f * FONTS_SCALE;
    ImFontConfig icons_config;
    icons_config.OversampleH    = 1;
    icons_config.OversampleV    = 1;
    icons_config.MergeMode      = true; 
    icons_config.PixelSnapH     = true;
    icons_config.SizePixels     = icons_size * 1.0f;
    icons_config.EllipsisChar   = (ImWchar)0x0085;
    
    icons_config.GlyphOffset.y = FONTS_SCALE * 2.0f * IM_FLOOR(icons_config.SizePixels / icons_size);  // Add +2 offset per 16 units
    // FileDialog Icons
    static const ImWchar icons_ranges[] = { ICON_MIN_IGFD, ICON_MAX_IGFD, 0 };
	atlas->AddFontFromMemoryCompressedBase85TTF(FONT_ICON_BUFFER_NAME_IGFD, icons_size, &icons_config, icons_ranges);

    // Awesome Icons
    static const ImWchar fa_icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	atlas->AddFontFromMemoryCompressedBase85TTF(fa_regular_compressed_data_base85, icons_size, &icons_config, fa_icons_ranges);
    atlas->AddFontFromMemoryCompressedBase85TTF(fa_solid_compressed_data_base85, icons_size, &icons_config, fa_icons_ranges);

    return true;
}
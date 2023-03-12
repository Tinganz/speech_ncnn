#pragma once
#ifndef NO_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#define STBIDEF inline
#define STBIWDEF inline
#define STBIRDEF inline
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"

namespace ImGui
{
    IMGUI_API void  LoadingIndicatorCircle(const char* label, float indicatorRadiusFactor=1.f,
                                            const ImVec4* pOptionalMainColor=NULL, const ImVec4* pOptionalBackdropColor=NULL,
                                            int circle_count=8, const float speed=1.f);
    IMGUI_API int   PlotEx(int plot_type, const char* label, float (*values_getter)(void* data, int idx), 
                            void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 frame_size, bool b_tooltops, bool b_comband);

    IMGUI_API void  PlotLinesEx(const char* label, const float* values, int values_count, int values_offset = 0,
                                const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX,
                                ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float), bool b_tooltips = true, bool b_comband = false);

}
#endif
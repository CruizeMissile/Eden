#pragma once
#include "Core/Types.h"
#include <vector>
#include <memory>

namespace edn::rendering
{
    constexpr u32 max_color_attachments = 4u;
    class RenderTarget
    {
    public:
        struct Attachment
        {
            // texture handle
            u32 slice = 0u;
            u32 level = 0u;
            Attachment() = default;
            Attachment(/*texturehandle*/ u32 slice = 0u, u32 level = 0u);
        };

        struct Info
        {
            std::vector<Attachment> color_attachment;
            Attachment depth_attachment;
            Info() = default;
        };

        RenderTarget(const Info& info);
        virtual ~RenderTarget() = default;

        u32 get_width() const { return width; }
        u32 get_height() const { return height; }

    protected:
        std::vector<Attachment> color_attachments;
        Attachment depth_attachment;
        u32 width;
        u32 height;
    };

    using RenderTargetPtr = std::shared_ptr<RenderTarget>;
}
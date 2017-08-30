#include "Precompiled.h"
#include "RenderTarget.h"

namespace edn::rendering
{
    RenderTarget::RenderTarget(const RenderTarget::Info& info)
        : color_attachments(info.color_attachment)
        , depth_attachment(info.depth_attachment)
        , width(0u)
        , height(0u)
    {
        ASSERT(info.color_attachment.size() <= max_color_attachments, "Too many color attachments");
        
        if (info.color_attachment.size())
        {
            // get the width and the height of the texture from color attachment 0 location
        }

        #if defined(EDN_DEBUG)
        for (auto it : info.color_attachment)
        {
            // assert that all the color attachments are the same size as the first one
        }
        #endif

        // if there is a depth_attachment texture
        {
            if (info.color_attachment.empty())
            {
                // set the width and height to the depth texture width and height
            }
            else
            {
                // check that the depth texture is the same size as the depth texture
            }
        }

        ASSERT(width, "RenderTarget width cannot be 0");
        ASSERT(height, "RenderTarget height cannot be 0");
    }

    
}
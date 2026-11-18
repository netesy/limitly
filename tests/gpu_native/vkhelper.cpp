#include <vulkan/vulkan.h>
#include <cstdint>
extern "C" __declspec(dllexport) uint64_t vk_make_rp(uint64_t dev, uint64_t fmt) {
    VkAttachmentDescription att{};
    att.format=(VkFormat)fmt; att.samples=VK_SAMPLE_COUNT_1_BIT;
    att.loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR; att.storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    att.stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE; att.stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED; att.finalLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    VkAttachmentReference aref{0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sub{};
    sub.pipelineBindPoint=VK_PIPELINE_BIND_POINT_GRAPHICS;
    sub.colorAttachmentCount=1; sub.pColorAttachments=&aref;
    VkSubpassDependency dep{};
    dep.srcSubpass=VK_SUBPASS_EXTERNAL; dep.dstSubpass=0;
    dep.srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstAccessMask=VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    VkRenderPassCreateInfo rpci{VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
    rpci.attachmentCount=1; rpci.pAttachments=&att;
    rpci.subpassCount=1; rpci.pSubpasses=&sub;
    rpci.dependencyCount=1; rpci.pDependencies=&dep;
    VkRenderPass rp=VK_NULL_HANDLE;
    VkResult r=vkCreateRenderPass((VkDevice)dev,&rpci,nullptr,&rp);
    if(r||!rp) return 0xDEAD000000000000ULL|(uint64_t)(uint32_t)r|((uint64_t)(rp==VK_NULL_HANDLE)<<32);
    return (uint64_t)rp;
}
extern "C" __declspec(dllexport) uint64_t vk_make_fb(uint64_t dev, uint64_t rp, uint64_t view, uint64_t w, uint64_t h) {
    VkImageView v=(VkImageView)view;
    VkFramebufferCreateInfo fbci{VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
    fbci.renderPass=(VkRenderPass)rp; fbci.attachmentCount=1; fbci.pAttachments=&v;
    fbci.width=(uint32_t)w; fbci.height=(uint32_t)h; fbci.layers=1;
    VkFramebuffer fb=VK_NULL_HANDLE;
    VkResult r=vkCreateFramebuffer((VkDevice)dev,&fbci,nullptr,&fb);
    if(r||!fb) return 0xDEAD000000000000ULL|(uint64_t)(uint32_t)r|((uint64_t)(fb==VK_NULL_HANDLE)<<32);
    return (uint64_t)fb;
}

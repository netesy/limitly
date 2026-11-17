// Reference probe: does vkCreateComputePipelines produce a handle for the
// same SPIR-V + descriptor layout that std/native/vulkan.lm builds?
#include <vulkan/vulkan.h>
#include <cstdio>
#include <cstring>
typedef PFN_vkVoidFunction (VKAPI_PTR *PFN_vkGetInstanceProcAddr)(VkInstance, const char*);
typedef PFN_vkVoidFunction (VKAPI_PTR *PFN_vkGetDeviceProcAddr)(VkDevice, const char*);

static uint32_t spv[] = {
#include "spv_words.inc"
};

int main() {
    VkApplicationInfo app{};
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.apiVersion = VK_API_VERSION_1_1;
    VkInstanceCreateInfo ici{};
    ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ici.pApplicationInfo = &app;
    VkInstance inst;
    VkResult r = vkCreateInstance(&ici, nullptr, &inst);
    printf("instance=%d\n", r);
    if (r) return 1;

    uint32_t np = 0;
    vkEnumeratePhysicalDevices(inst, &np, nullptr);
    VkPhysicalDevice pdevs[8];
    vkEnumeratePhysicalDevices(inst, &np, pdevs);
    VkPhysicalDevice phys = VK_NULL_HANDLE;
    uint32_t qf = 0;
    for (uint32_t i = 0; i < np && !phys; i++) {
        uint32_t nq = 8;
        VkQueueFamilyProperties qp[8];
        vkGetPhysicalDeviceQueueFamilyProperties(pdevs[i], &nq, qp);
        for (uint32_t q = 0; q < nq; q++)
            if (qp[q].queueFlags & VK_QUEUE_COMPUTE_BIT) { phys = pdevs[i]; qf = q; break; }
    }
    VkPhysicalDeviceProperties pp{};
    vkGetPhysicalDeviceProperties(phys, &pp);
    printf("dev api=%u.%u.%u name=%s qf=%u\n",
           VK_API_VERSION_MAJOR(pp.apiVersion), VK_API_VERSION_MINOR(pp.apiVersion),
           VK_API_VERSION_PATCH(pp.apiVersion), pp.deviceName, qf);

    float prio = 1.f;
    VkDeviceQueueCreateInfo qci{VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
    qci.queueFamilyIndex = qf; qci.queueCount = 1; qci.pQueuePriorities = &prio;
    const char* exts[] = {"VK_KHR_storage_buffer_storage_class"};
    VkDeviceCreateInfo dci{VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
    dci.queueCreateInfoCount = 1; dci.pQueueCreateInfos = &qci;
    dci.enabledExtensionCount = 1; dci.ppEnabledExtensionNames = exts;
    VkDevice dev;
    r = vkCreateDevice(phys, &dci, nullptr, &dev);
    printf("device=%d\n", r);
    if (r) return 1;

    VkShaderModuleCreateInfo smci{VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};
    smci.codeSize = sizeof(spv); smci.pCode = spv;
    VkShaderModule sm;
    r = vkCreateShaderModule(dev, &smci, nullptr, &sm);
    printf("shader=%d mod=%p\n", r, (void*)sm);

    VkDescriptorSetLayoutBinding bind{};
    bind.binding = 0; bind.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bind.descriptorCount = 1; bind.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    VkDescriptorSetLayoutCreateInfo dslci{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO};
    dslci.bindingCount = 1; dslci.pBindings = &bind;
    VkDescriptorSetLayout dsl;
    r = vkCreateDescriptorSetLayout(dev, &dslci, nullptr, &dsl);
    printf("dsl=%d\n", r);

    VkDescriptorSetLayout sets_[1] = {dsl};
    VkPipelineLayoutCreateInfo plci{VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
    plci.setLayoutCount = 1; plci.pSetLayouts = sets_;
    VkPipelineLayout pl;
    r = vkCreatePipelineLayout(dev, &plci, nullptr, &pl);
    printf("pl=%d\n", r);

    VkDescriptorPoolSize dps{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 16};
    VkDescriptorPoolCreateInfo dpci{VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
    dpci.maxSets = 16; dpci.poolSizeCount = 1; dpci.pPoolSizes = &dps;
    VkDescriptorPool dp;
    r = vkCreateDescriptorPool(dev, &dpci, nullptr, &dp);
    printf("dp=%d\n", r);

    VkDescriptorSetAllocateInfo dsai{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO};
    dsai.descriptorPool = dp; dsai.descriptorSetCount = 1; dsai.pSetLayouts = sets_;
    VkDescriptorSet ds;
    r = vkAllocateDescriptorSets(dev, &dsai, &ds);
    printf("sets=%d\n", r);

    VkComputePipelineCreateInfo cpci{VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO};
    cpci.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    cpci.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    cpci.stage.module = sm; cpci.stage.pName = "main";
    cpci.layout = pl;
    { FILE* f=fopen("cpci_cpp.bin","wb"); fwrite(&cpci,1,sizeof(cpci),f); fclose(f);
      FILE* g=fopen("dsl_cpp.bin","wb"); fwrite(&bind,1,sizeof(bind),f); fclose(g); }
    typedef VkResult (VKAPI_PTR *PCP)(VkDevice, VkPipelineCache, uint32_t,
        const VkComputePipelineCreateInfo*, const VkAllocationCallbacks*, VkPipeline*);
    auto gipa = (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr;
    auto gdpa = (PFN_vkGetDeviceProcAddr)vkGetDeviceProcAddr;
    PCP viaIpa = (PCP)gipa(inst, "vkCreateComputePipelines");
    PCP viaGdpa = gdpa ? (PCP)gdpa(dev, "vkCreateComputePipelines") : nullptr;
    printf("ipa=%p gdpa=%p", (void*)viaIpa, (void*)viaGdpa);
    VkPipeline pipe = VK_NULL_HANDLE;
    VkResult rr = viaGdpa(dev, VK_NULL_HANDLE, 1, &cpci, nullptr, &pipe);
    printf("pipes_gdpa=%d pipe=%p", rr, (void*)pipe);
    pipe = VK_NULL_HANDLE;
    rr = viaIpa(dev, VK_NULL_HANDLE, 1, &cpci, nullptr, &pipe);
    printf("pipes_ipa=%d pipe=%p", rr, (void*)pipe);
    return 0;
}

// Copyright (c) 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_VULKAN_VULKAN_INSTANCE_H_
#define GPU_VULKAN_VULKAN_INSTANCE_H_

#include <vulkan/vulkan.h>
#include <memory>

#include "base/logging.h"
#include "base/macros.h"
#include "gpu/vulkan/vulkan_export.h"
#include "ui/gfx/extension_set.h"

namespace gpu {

class VULKAN_EXPORT VulkanInstance {
 public:
  VulkanInstance();

  ~VulkanInstance();

  // Creates the vulkan instance.
  //
  // The extensions in |required_extensions| and the layers in |required_layers|
  // will be enabled in the created instance. See the "Extended Functionality"
  // section of vulkan specification for more information.
  // TODO(samans): Remove |using_swiftshader| once Vulkan Swiftshader is more
  // developed and the workarounds that were added can be deleted.
  // https://crbug.com/963988
  bool Initialize(const std::vector<const char*>& required_extensions,
                  const std::vector<const char*>& required_layers,
                  bool using_swiftshader = false);

  // VkApplicationInfo.apiVersion value used to initialize the instance.
  uint32_t api_version() const { return api_version_; }

  const gfx::ExtensionSet& enabled_extensions() const {
    return enabled_extensions_;
  }

  VkInstance vk_instance() { return vk_instance_; }

 private:
  void Destroy();

  uint32_t api_version_;

  VkInstance vk_instance_ = VK_NULL_HANDLE;
  gfx::ExtensionSet enabled_extensions_;
  bool debug_report_enabled_ = false;
#if DCHECK_IS_ON()
  VkDebugReportCallbackEXT error_callback_ = VK_NULL_HANDLE;
  VkDebugReportCallbackEXT warning_callback_ = VK_NULL_HANDLE;
#endif

  DISALLOW_COPY_AND_ASSIGN(VulkanInstance);
};

}  // namespace gpu

#endif  // GPU_VULKAN_VULKAN_INSTANCE_H_

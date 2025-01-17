// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "media/gpu/format_utils.h"
#include "base/logging.h"
#include "ui/gfx/buffer_format_util.h"

namespace media {

VideoPixelFormat GfxBufferFormatToVideoPixelFormat(gfx::BufferFormat format) {
  switch (format) {
    case gfx::BufferFormat::BGRX_8888:
      return PIXEL_FORMAT_XRGB;

    case gfx::BufferFormat::BGRA_8888:
      return PIXEL_FORMAT_ARGB;

    // There is no PIXEL_FORMAT_XBGR which would have been the right mapping.
    // See ui/ozone drm_util.cc::GetFourCCFormatFromBufferFormat as reference.
    // But here it is only about indicating to not consider the alpha channel.
    // Useful for the compositor to avoid drawing behind as mentioned in
    // https://chromium-review.googlesource.com/590772.
    case gfx::BufferFormat::RGBX_8888:
      return PIXEL_FORMAT_XRGB;

    case gfx::BufferFormat::YVU_420:
      return PIXEL_FORMAT_YV12;

    case gfx::BufferFormat::YUV_420_BIPLANAR:
      return PIXEL_FORMAT_NV12;

    default:
      LOG(FATAL) << "Unsupported BufferFormat: "
                 << gfx::BufferFormatToString(format);
      return PIXEL_FORMAT_UNKNOWN;
  }
}

gfx::BufferFormat VideoPixelFormatToGfxBufferFormat(
    VideoPixelFormat pixel_format) {
  switch (pixel_format) {
    case PIXEL_FORMAT_ARGB:
      return gfx::BufferFormat::BGRA_8888;

    case PIXEL_FORMAT_XRGB:
      return gfx::BufferFormat::BGRX_8888;

    case PIXEL_FORMAT_YV12:
      return gfx::BufferFormat::YVU_420;

    case PIXEL_FORMAT_NV12:
      return gfx::BufferFormat::YUV_420_BIPLANAR;

    case PIXEL_FORMAT_ABGR:
      return gfx::BufferFormat::RGBA_8888;

    case PIXEL_FORMAT_XBGR:
      return gfx::BufferFormat::RGBX_8888;

    default:
      LOG(FATAL) << "Unsupported VideoPixelFormat: " << pixel_format;
      return gfx::BufferFormat::BGRX_8888;
  }
}

}  // namespace media

// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "services/device/usb/usb_endpoint_android.h"

#include "jni/ChromeUsbEndpoint_jni.h"

namespace device {

// static
UsbEndpointDescriptor UsbEndpointAndroid::Convert(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& usb_endpoint) {
  base::android::ScopedJavaLocalRef<jobject> wrapper =
      Java_ChromeUsbEndpoint_create(env, usb_endpoint);

  UsbEndpointDescriptor endpoint(
      Java_ChromeUsbEndpoint_getAddress(env, wrapper),
      Java_ChromeUsbEndpoint_getAttributes(env, wrapper),
      Java_ChromeUsbEndpoint_getMaxPacketSize(env, wrapper),
      Java_ChromeUsbEndpoint_getInterval(env, wrapper));

  return endpoint;
}

}  // namespace device

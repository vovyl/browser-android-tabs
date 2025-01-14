// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/system/network/network_info.h"

namespace ash {

NetworkInfo::NetworkInfo() = default;

NetworkInfo::NetworkInfo(const std::string& guid) : guid(guid) {}

NetworkInfo::~NetworkInfo() = default;

bool NetworkInfo::operator==(const NetworkInfo& other) const {
  return guid == other.guid && label == other.label &&
         tooltip == other.tooltip && image.BackedBySameObjectAs(other.image) &&
         type == other.type && disable == other.disable &&
         connection_state == other.connection_state && source == other.source &&
         battery_percentage == other.battery_percentage &&
         captive_portal_provider_name == other.captive_portal_provider_name;
}

}  // namespace ash

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SERVICES_QUARANTINE_QUARANTINE_IMPL_H_
#define COMPONENTS_SERVICES_QUARANTINE_QUARANTINE_IMPL_H_

#include <memory>

#include "components/services/quarantine/public/mojom/quarantine.mojom.h"
#include "services/service_manager/public/cpp/service_context_ref.h"

namespace quarantine {

class QuarantineImpl : public mojom::Quarantine {
 public:
  explicit QuarantineImpl(
      std::unique_ptr<service_manager::ServiceContextRef> service_ref);
  ~QuarantineImpl() override;

 private:
  const std::unique_ptr<service_manager::ServiceContextRef> service_ref_;
};

}  // namespace quarantine

#endif  // COMPONENTS_SERVICES_QUARANTINE_QUARANTINE_IMPL_H_

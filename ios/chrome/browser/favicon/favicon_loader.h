// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_CHROME_BROWSER_FAVICON_FAVICON_LOADER_H_
#define IOS_CHROME_BROWSER_FAVICON_FAVICON_LOADER_H_

#import <Foundation/Foundation.h>

#include "base/macros.h"
#include "base/task/cancelable_task_tracker.h"
#include "components/keyed_service/core/keyed_service.h"

class GURL;
@class FaviconAttributes;

namespace favicon {
class LargeIconService;
}

// A class that manages asynchronously loading favicons or fallback attributes
// from LargeIconService and caching them, given a URL.
class FaviconLoader : public KeyedService {
 public:
  // Type for completion block for FaviconForURL().
  typedef void (^FaviconAttributesCompletionBlock)(FaviconAttributes*);

  explicit FaviconLoader(favicon::LargeIconService* large_icon_service);
  ~FaviconLoader() override;

  // Tries to find a FaviconAttributes in |favicon_cache_| with |page_url|:
  // If found, returns it.
  // If not found, returns a default favicon, and invokes |block| asynchronously
  // with the favicon fetched by trying following methods:
  //   1. Use |large_icon_service_| to fetch from local DB managed by
  //      HistoryService;
  //   2. Use |large_icon_service_| to fetch from Google Favicon server if
  //      |fallback_to_google_server|=YES;
  //   3. Create a favicon base on the fallback style from |large_icon_service|.
  FaviconAttributes* FaviconForPageUrl(const GURL& page_url,
                                       float size_in_points,
                                       float min_size_in_points,
                                       bool fallback_to_google_server,
                                       FaviconAttributesCompletionBlock block);

  // Tries to find a FaviconAttributes in |favicon_cache_| with |icon_url|:
  // If found, returns it.
  // If not found, returns a default favicon, and invokes |block| asynchronously
  // with the favicon fetched by trying following methods:
  //   1. Use |large_icon_service_| to fetch from local DB managed by
  //      HistoryService;
  //   2. Create a favicon base on the fallback style from |large_icon_service|.
  FaviconAttributes* FaviconForIconUrl(const GURL& icon_url,
                                       float size_in_points,
                                       float min_size_in_points,
                                       FaviconAttributesCompletionBlock block);

  // Cancel all incomplete requests.
  void CancellAllRequests();

 private:
  // The LargeIconService used to retrieve favicon.
  favicon::LargeIconService* large_icon_service_;

  // Tracks tasks sent to FaviconService.
  base::CancelableTaskTracker cancelable_task_tracker_;
  // Holds cached favicons. This NSCache is populated as favicons or fallback
  // attributes are retrieved from |large_icon_service_|. Contents will be
  // removed during low-memory conditions based on its inherent LRU removal
  // algorithm. Keyed by NSString of URL (page URL or icon URL) spec.
  NSCache<NSString*, FaviconAttributes*>* favicon_cache_;

  DISALLOW_COPY_AND_ASSIGN(FaviconLoader);
};

#endif  // IOS_CHROME_BROWSER_FAVICON_FAVICON_LOADER_H_

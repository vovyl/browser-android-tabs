// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"

#include "base/logging.h"

using content::WebContents;

TabStripModelChange::Insert::Insert() = default;
TabStripModelChange::Insert::Insert(Insert&& other) = default;
TabStripModelChange::Insert& TabStripModelChange::Insert::operator=(Insert&&) =
    default;
TabStripModelChange::Insert::~Insert() = default;

TabStripModelChange::Remove::Remove() = default;
TabStripModelChange::Remove::Remove(Remove&& other) = default;
TabStripModelChange::Remove& TabStripModelChange::Remove::operator=(Remove&&) =
    default;
TabStripModelChange::Remove::~Remove() = default;

////////////////////////////////////////////////////////////////////////////////
// TabStripModelChange
//
TabStripModelChange::TabStripModelChange() = default;

TabStripModelChange::GroupChange::GroupChange() = default;

TabStripModelChange::GroupChange::GroupChange(const GroupChange& other) =
    default;

TabStripModelChange::GroupChange& TabStripModelChange::GroupChange::operator=(
    const GroupChange& other) = default;

TabStripModelChange::GroupChange::~GroupChange() = default;

TabStripModelChange::TabStripModelChange(Insert delta)
    : TabStripModelChange(Type::kInserted,
                          std::make_unique<Insert>(std::move(delta))) {}

TabStripModelChange::TabStripModelChange(Remove delta)
    : TabStripModelChange(Type::kRemoved,
                          std::make_unique<Remove>(std::move(delta))) {}

TabStripModelChange::TabStripModelChange(Move delta)
    : TabStripModelChange(Type::kMoved,
                          std::make_unique<Move>(std::move(delta))) {}

TabStripModelChange::TabStripModelChange(Replace delta)
    : TabStripModelChange(Type::kReplaced,
                          std::make_unique<Replace>(std::move(delta))) {}

TabStripModelChange::TabStripModelChange(GroupChange delta)
    : TabStripModelChange(Type::kGroupChanged,
                          std::make_unique<GroupChange>(std::move(delta))) {}

TabStripModelChange::~TabStripModelChange() = default;

const TabStripModelChange::Insert* TabStripModelChange::GetInsert() const {
  DCHECK_EQ(type_, Type::kInserted);
  return static_cast<const Insert*>(delta_.get());
}

const TabStripModelChange::Remove* TabStripModelChange::GetRemove() const {
  DCHECK_EQ(type_, Type::kRemoved);
  return static_cast<const Remove*>(delta_.get());
}

const TabStripModelChange::Move* TabStripModelChange::GetMove() const {
  DCHECK_EQ(type_, Type::kMoved);
  return static_cast<const Move*>(delta_.get());
}

const TabStripModelChange::Replace* TabStripModelChange::GetReplace() const {
  DCHECK_EQ(type_, Type::kReplaced);
  return static_cast<const Replace*>(delta_.get());
}

const TabStripModelChange::GroupChange* TabStripModelChange::GetGroupChange()
    const {
  DCHECK_EQ(type_, Type::kGroupChanged);
  return static_cast<const GroupChange*>(delta_.get());
}

TabStripModelChange::TabStripModelChange(Type type,
                                         std::unique_ptr<Delta> delta)
    : type_(type), delta_(std::move(delta)) {}

////////////////////////////////////////////////////////////////////////////////
// TabStripSelectionChange
//
TabStripSelectionChange::TabStripSelectionChange() = default;

TabStripSelectionChange::TabStripSelectionChange(
    content::WebContents* contents,
    const ui::ListSelectionModel& selection_model)
    : old_contents(contents),
      new_contents(contents),
      old_model(selection_model),
      new_model(selection_model),
      reason(0) {}

TabStripSelectionChange::~TabStripSelectionChange() = default;

TabStripSelectionChange::TabStripSelectionChange(
    const TabStripSelectionChange& other) = default;

TabStripSelectionChange& TabStripSelectionChange::operator=(
    const TabStripSelectionChange& other) = default;

////////////////////////////////////////////////////////////////////////////////
// TabStripModelObserver
//
TabStripModelObserver::TabStripModelObserver() {
}

void TabStripModelObserver::OnTabStripModelChanged(
    TabStripModel* tab_strip_model,
    const TabStripModelChange& change,
    const TabStripSelectionChange& selection) {}

void TabStripModelObserver::TabChangedAt(WebContents* contents,
                                         int index,
                                         TabChangeType change_type) {
}

void TabStripModelObserver::TabPinnedStateChanged(
    TabStripModel* tab_strip_model,
    WebContents* contents,
    int index) {
}

void TabStripModelObserver::TabBlockedStateChanged(WebContents* contents,
                                                   int index) {
}

void TabStripModelObserver::TabStripEmpty() {
}

void TabStripModelObserver::WillCloseAllTabs(TabStripModel* tab_strip_model) {}

void TabStripModelObserver::CloseAllTabsStopped(TabStripModel* tab_strip_model,
                                                CloseAllStoppedReason reason) {}
void TabStripModelObserver::SetTabNeedsAttentionAt(int index, bool attention) {}

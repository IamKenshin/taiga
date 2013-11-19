/*
** Taiga, a lightweight client for MyAnimeList
** Copyright (C) 2010-2012, Eren Okka
** 
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DLG_SETTINGS_H
#define DLG_SETTINGS_H

#include "base/std.h"
#include "dlg_settings_page.h"
#include "track/feed.h"
#include "win/ctrl/win_ctrl.h"
#include "win/win_dialog.h"

enum SettingsSections {
  SECTION_SERVICES = 1,
  SECTION_LIBRARY,
  SECTION_APPLICATION,
  SECTION_RECOGNITION,
  SECTION_SHARING,
  SECTION_TORRENTS
};
// =============================================================================

class SettingsDialog : public win::Dialog {
public:
  SettingsDialog();
  virtual ~SettingsDialog() {}

  friend class SettingsPage;

  INT_PTR DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  void OnHelp(LPHELPINFO lphi);
  BOOL OnInitDialog();
  LRESULT OnNotify(int idCtrl, LPNMHDR pnmh);
  void OnOK();

  void SetCurrentSection(int index);
  void SetCurrentPage(int index);

  int AddTorrentFilterToList(HWND hwnd_list, const FeedFilter& filter);
  void RefreshCache();
  void RefreshTorrentFilterList(HWND hwnd_list);
  void RefreshTwitterLink();

private:
  class TreeView : public win::TreeView {
  public:
    LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    std::map<int, HTREEITEM> items;
  } tree_;
  win::Tab tab_;

private:
  int current_section_;
  int current_page_;
  vector<FeedFilter> feed_filters_;
  vector<SettingsPage> pages;
};

extern class SettingsDialog SettingsDialog;

#endif // DLG_SETTINGS_H
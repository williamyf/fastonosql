/*  Copyright (C) 2014-2017 FastoGT. All right reserved.

    This file is part of FastoNoSQL.

    FastoNoSQL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoNoSQL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoNoSQL.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gui/db/leveldb/connection_widget.h"

#include <QCheckBox>

#include "proxy/db/leveldb/connection_settings.h"

namespace fastonosql {
namespace gui {
namespace leveldb {

ConnectionWidget::ConnectionWidget(QWidget* parent)
    : ConnectionLocalWidget(true, trDBPath, trCaption, trFilter, parent) {
  createDBIfMissing_ = new QCheckBox;
  addWidget(createDBIfMissing_);
}

void ConnectionWidget::syncControls(proxy::IConnectionSettingsBase* connection) {
  proxy::leveldb::ConnectionSettings* lev = static_cast<proxy::leveldb::ConnectionSettings*>(connection);
  if (lev) {
    core::leveldb::Config config = lev->Info();
    createDBIfMissing_->setChecked(config.create_if_missing);
  }
  ConnectionLocalWidget::syncControls(lev);
}

void ConnectionWidget::retranslateUi() {
  createDBIfMissing_->setText(trCreateDBIfMissing);
  ConnectionLocalWidget::retranslateUi();
}

proxy::IConnectionSettingsLocal* ConnectionWidget::createConnectionLocalImpl(
    const proxy::connection_path_t& path) const {
  proxy::leveldb::ConnectionSettings* conn = new proxy::leveldb::ConnectionSettings(path);
  core::leveldb::Config config = conn->Info();
  config.create_if_missing = createDBIfMissing_->isChecked();
  conn->SetInfo(config);
  return conn;
}

}  // namespace leveldb
}  // namespace gui
}  // namespace fastonosql

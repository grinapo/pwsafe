/*
* Copyright (c) 2003-2011 Rony Shapiro <ronys@users.sourceforge.net>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/
// ExpiredList.h
//-----------------------------------------------------------------------------

#ifndef __EXPIREDLIST_H
#define __EXPIREDLIST_H

#include "StringX.h"
#include "os/UUID.h"
#include "ItemData.h"

#include <vector>

struct ExpPWEntry {
  ExpPWEntry(const CItemData &ci);
  ExpPWEntry(const ExpPWEntry &ee) : uuid(ee.uuid), expirytttXTime(ee.expirytttXTime) {}
  ExpPWEntry &operator=(const ExpPWEntry &that) {
    if (this != &that) {
      expirytttXTime = that.expirytttXTime;
      uuid = that.uuid;
    }
    return *this;
  };

  pws_os::CUUID uuid;
  time_t expirytttXTime;
};

class ExpiredList: public std::vector<ExpPWEntry>
{
public:
  void Add(const CItemData &ci);
  void Update(const CItemData &ci) {Remove(ci); Add(ci);}
  void Remove(const CItemData &ci);
  ExpiredList GetExpired(const int &idays); // return a subset
};

struct ee_equal_uuid {
  ee_equal_uuid(const pws_os::CUUID &uuid) : m_uuid(uuid) {}

  bool operator()(const ExpPWEntry &ee) const
  { return m_uuid == ee.uuid; }

  ee_equal_uuid& operator=(const ee_equal_uuid&); // Do not implement
  const pws_os::CUUID m_uuid;
};

#endif /* __EXPIREDLIST_H */

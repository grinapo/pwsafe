/*
* Copyright (c) 2003-2016 Rony Shapiro <ronys@pwsafe.org>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/

#ifndef __FILE_H
#define __FILE_H
#include "typedefs.h"
#include <vector>

#include <collection.h>
#include <pplawait.h>

using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Storage::Pickers;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

namespace pws_os {
  extern task<bool> FileExists(const stringT &filename);

  extern task<IRandomAccessStream^> FOpen(const stringT &filename, const TCHAR *mode);
  extern ulong64 fileLength(IRandomAccessStream^ fp);
  extern const TCHAR PathSeparator; // slash for Unix, backslash for Windows
}
#endif /* __FILE_H */
//-----------------------------------------------------------------------------
// Local variables:
// mode: c++
// End:

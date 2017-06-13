/*
* Copyright (c) 2003-2016 Rony Shapiro <ronys@pwsafe.org>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/

/**
 * \file Windows-specific implementation of file.h
 */


#include "../typedefs.h"
#include "../file.h"

#include "../../core/StringX.h"
#include "../../core/core.h"

const TCHAR pws_os::PathSeparator = _T('\\');

task<bool> pws_os::FileExists(const stringT &filename)
{
  struct _stat statbuf;
  bool status = false;

  Platform::String^ s = ref new Platform::String(filename.c_str());

  auto t = co_await Windows::Storage::StorageFile::GetFileFromPathAsync(s);
  
  if (t!=nullptr) status = true;

  return status;
}

task<IRandomAccessStream^> pws_os::FOpen(const stringT &filename, const TCHAR *mode)
{
  IRandomAccessStream^ ret = nullptr;
  String ^ s = ref new String(filename.c_str());
  StorageFile^ file = co_await Windows::Storage::StorageFile::GetFileFromPathAsync(s);

  try
  {
    FileAccessMode m = FileAccessMode::Read;
    /*switch (mode)
    {
    case 'r':
    m = FileAccessMode::Read;
    break;
    case 'w':
    m = FileAccessMode::ReadWrite;
    break;
    }*/

    ret = co_await file->OpenAsync(m);
  }
  catch (Exception^ e)
  {
    ret = nullptr;
  }

  return ret;
}

ulong64 pws_os::fileLength(IRandomAccessStream^ fp) {

  if (fp != nullptr) {
    return fp->Size;
  } else
    return 0;
}


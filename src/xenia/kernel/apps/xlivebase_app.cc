/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2015 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/kernel/apps/xlivebase_app.h"

#include "poly/threading.h"

namespace xe {
namespace kernel {
namespace apps {

XXLiveBaseApp::XXLiveBaseApp(KernelState* kernel_state)
    : XApp(kernel_state, 0xFC) {}

// http://mb.mirage.org/bugzilla/xliveless/main.c

X_RESULT XXLiveBaseApp::DispatchMessageSync(uint32_t message,
                                            uint32_t buffer_ptr,
                                            uint32_t buffer_length) {
  // NOTE: buffer_length may be zero or valid.
  switch (message) {
    case 0x00058004: {
      // Called on startup, seems to just return a bool in the buffer.
      assert_true(!buffer_length || buffer_length == 4);
      XELOGD("XLiveBaseGetLogonId(%.8X)", buffer_ptr);
      poly::store_and_swap<uint32_t>(membase_ + buffer_ptr + 0, 1);  // ?
      return X_ERROR_SUCCESS;
    }
    case 0x00058020: {
      // 0x00058004 is called right before this.
      // We should create a XamEnumerate-able empty list here, but I'm not
      // sure of the format.
      // buffer_length seems to be the same ptr sent to 0x00058004.
      XELOGD("XLiveBaseFriendsCreateEnumerator(%.8X, %.8X) unimplemented",
             buffer_ptr, buffer_length);
      return X_ERROR_FUNCTION_FAILED;
    }
    case 0x00058023: {
      XELOGD("XliveBaseUnk58023(%.8X, %.8X) unimplemented", buffer_ptr,
             buffer_length);
      return X_ERROR_FUNCTION_FAILED;
    }
  }
  XELOGE(
      "Unimplemented XLIVEBASE message app=%.8X, msg=%.8X, arg1=%.8X, "
      "arg2=%.8X",
      app_id(), message, buffer_ptr, buffer_length);
  return X_ERROR_NOT_FOUND;
}

}  // namespace apps
}  // namespace kernel
}  // namespace xe

/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <xenia/xenia.h>


int xenia_run(int argc, xechar_t **argv) {
  do_cpu_stuff();
  do_gpu_stuff();
  return 0;
}
XE_MAIN_THUNK(xenia_run);

/* Copyright 2016 Google Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License. */

#include "headers.h"

NSYNC_CPP_START_

int clock_gettime(clockid_t clk_id UNUSED, struct timespec *tp) {
	struct timeval tv;
	int rc = gettimeofday(&tv, NULL);
	if (rc == 0) {
		tp->tv_sec = tv.tv_sec;
		tp->tv_nsec = tv.tv_usec * 1000;
	}
	return (rc);
}

NSYNC_CPP_END_

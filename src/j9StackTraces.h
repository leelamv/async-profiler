/*
 * Copyright 2021 Andrei Pangin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _J9STACKTRACES_H
#define _J9STACKTRACES_H

#include <pthread.h>
#include "arch.h"
#include "arguments.h"


class J9StackTraces {
  private:
    pthread_t _thread;
    int _max_stack_depth;
    bool _cstack;
    int _pipe[2];

    void timerLoop();

    static void* threadEntry(void* instance) {
        ((J9StackTraces*)instance)->timerLoop();
        return NULL;
    }

  public:
    J9StackTraces() : _thread(0) {
    }

    Error start(Arguments& args);
    void stop();

    void checkpoint(void* pc, u64 counter);
};

#endif // _J9STACKTRACES_H

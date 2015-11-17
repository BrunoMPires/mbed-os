/****************************************************************************
 * Copyright (c) 2015, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************
 */

 #include "mbed-test-async/default_handlers.h"
 #include "mbed-test-async/case.h"

using namespace mbed::test::v0;

status_t mbed::test::v0::verbose_test_setup_handler(const size_t number_of_cases)
{
    printf(">>> Running %u test cases...\n", number_of_cases);
    return STATUS_CONTINUE;
}

void mbed::test::v0::verbose_test_teardown_handler(const size_t passed, const size_t failed, const failure_t failure)
{
    printf("\n>>> Test cases: %u passed, %u failed", passed, failed);
    if (failure == FAILURE_NONE) {
        printf("\n");
    } else  {
        printf(" with reason '%s'\n", stringify(failure));
    }
    if (failed) printf(">>> TESTS FAILED!\n");
}

status_t mbed::test::v0::verbose_case_setup_handler(const Case *const source, const size_t index_of_case)
{
    printf("\n>>> Running case #%u: '%s'...\n", index_of_case + 1, source->get_description());
    return STATUS_CONTINUE;
}

status_t mbed::test::v0::verbose_case_teardown_handler(const Case *const source, const size_t passed, const size_t failed, const failure_t failure)
{
    printf(">>> '%s': %u passed, %u failed", source->get_description(), passed, failed);
    if (failure == FAILURE_NONE) {
        printf("\n");
    } else  {
        printf(" with reason '%s'\n", stringify(failure));
    }
    return STATUS_CONTINUE;
}

status_t mbed::test::v0::verbose_case_failure_handler(const Case *const /*source*/, const failure_t reason)
{
    if (reason == FAILURE_ASSERTION) {
        printf("\n");
    } else {
        printf(">>> failed with reason '%s'\n", stringify(reason));
    }
    return (reason == FAILURE_TEARDOWN) ? STATUS_ABORT : STATUS_CONTINUE;
}



status_t mbed::test::v0::greentea_test_setup_handler(const size_t /*number_of_cases*/)
{
    printf(">>> I do not know how to tell greentea that the test started, since\n");
    printf(">>> you forgot to override the `test_setup_handler` in your specification.\n");

    return STATUS_ABORT;
}

void mbed::test::v0::greentea_test_teardown_handler(const size_t passed, const size_t failed, const failure_t failure)
{
    verbose_test_teardown_handler(passed, failed, failure);
    if (failed || failure != FAILURE_NONE) {
        printf("{{failure}}\n");
    } else {
        printf("{{success}}\n");
    }
    printf("{{end}}\n");
}

status_t mbed::test::v0::greentea_case_failure_handler(const Case *const source, const failure_t reason)
{
    verbose_case_failure_handler(source, reason);
    return STATUS_ABORT;
}

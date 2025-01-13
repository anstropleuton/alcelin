/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of Alcelin.
 *
 *  @copyright  Copyright (c) 2024 Anstro Pleuton
 *
 *      _    _          _ _
 *     / \  | | ___ ___| (_)_ __
 *    / _ \ | |/ __/ _ \ | | '_ \
 *   / ___ \| | (_|  __/ | | | | |
 *  /_/   \_\_|\___\___|_|_|_| |_|
 *
 *  Alcelin is a collection of utils for Anstro Pleuton's programs.
 *
 *  This software is licensed under the terms of MIT License.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 *
 *  Credits where credit's due:
 *  - ASCII Art generated using https://www.patorjk.com/software/taag with font
 *    "Standard".
 */

#include <cstddef>

#include "confer.hpp"

/**
 *  @brief  Test String Manipulators' to_string.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_sm_to_string);

/**
 *  @brief  Test... copper?  No wait, test Container Utilities.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cu);

/**
 *  @brief  Test String Manipulators.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_sm);

/**
 *  @brief  Test ANSI Escape Codes.
 *  @return  Zero.
 */
[[nodiscard]] CT_TESTER_FN(test_aec);

/**
 *  @brief  Test File Utilities.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_file);

/**
 *  @brief  The biggie.
 *  @return  Zero on success.
 */
auto main() -> int try
{
    // Test String Manipulators' to_string function before anything else.
    log_file.open("test_sm_to_string.log");
    if (auto errors = test_sm_to_string(); errors != 0)
    {
        std::println("String Manipulators' to_string functions failed, "
            "cannot continue further tests.");
        return errors;
    }
    log_file.close();

    test_case cu_test  = {
        .title         = "Test Container Utilities",
        .function_name = "test_cu",
        .function      = test_cu
    };

    test_case sm_test  = {
        .title         = "Test String Manipulators",
        .function_name = "test_sm",
        .function      = test_sm
    };

    test_case aec_test = {
        .title         = "Test ANSI Escape Codes",
        .function_name = "test_aec",
        .function      = test_aec
    };

    test_case file_test = {
        .title          = "Test File Utilities",
        .function_name  = "test_file",
        .function       = test_file
    };

    test_suite suite = {
        .tests       = { &cu_test, &sm_test, &aec_test, &file_test },
        .pre_run     = [&](const test_case *test)
        {
            log_file.open(test->function_name + ".log");
            default_pre_runner('=', 5)(test);
        },
        .post_run    = [&](const test_case *test, std::size_t errors)
        {
            default_post_runner('=', 5)(test, errors);
            log_file.close();
        }
    };

    auto failed_tests = suite.run();
    log_file.open("tester.log");

    print_failed_tests(failed_tests);

    return sum_failed_tests_errors(failed_tests) != 0;
}
catch (const std::exception &e)
{
    log_file.open("tester.log");
    std::println("Exception occurred during testing: {}", e.what());
    return 1;
}
catch (...)
{
    log_file.open("tester.log");
    std::println("Unknown exception occurred during testing");
    return 1;
}

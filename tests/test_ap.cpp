/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of Argument Parser in Alcelin.
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
 *  Never-nesters are advised to not take a look at this source file.
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

#include "test_ap.hpp"

/**
 *  @brief  AP Test 0: No arguments test.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_0);

/**
 *  @brief  AP Test 1: Option recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_1);

/**
 *  @brief  AP Test 2: Subcommand recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_2);

/**
 *  @brief  AP Test 3: Nested subcommand recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_3);

/**
 *  @brief  AP Test 4: Nested option recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_4);

/**
 *  @brief  AP Test 5: Option parameter recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_5);

/**
 *  @brief  AP Test 6: Subcommand parameter recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_6);

/**
 *  @brief  AP Test 7: Option parameter with defaults recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_7);

/**
 *  @brief  AP Test 8: Subcommand parameter with defaults recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_8);

/**
 *  @brief  AP Test 9: Argument split tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_9);

/**
 *  @brief  AP Test 10: Variadic parameter recognition tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_10);

/**
 *  @brief  AP Test 11: Throw tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_11);

/**
 *  @brief  AP Test 12: Misc. edge case tests.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap_12);

/**
 *  @brief  Test Argument Parser.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_ap)
{
    test_suite suite;
    suite.pre_run  = default_pre_runner('=', 3);
    suite.post_run = default_post_runner('=', 3);
    // suite.run_failed = default_run_failed_quitter();

    // Scary memory management

    suite.tests.emplace_back(new test {
        "AP Test 0: No arguments test",
        "test_ap_0",
        test_ap_0
    });

    suite.tests.emplace_back(new test {
        "AP Test 1: Option recognition tests",
        "test_ap_1",
        test_ap_1
    });

    suite.tests.emplace_back(new test {
        "AP Test 2: Subcommand recognition tests",
        "test_ap_2",
        test_ap_2
    });

    suite.tests.emplace_back(new test {
        "AP Test 3: Nested subcommand recognition tests",
        "test_ap_3",
        test_ap_3
    });

    suite.tests.emplace_back(new test {
        "AP Test 4: Nested option recognition tests",
        "test_ap_4",
        test_ap_4
    });

    suite.tests.emplace_back(new test {
        "AP Test 5: Option parameter recognition tests",
        "test_ap_5",
        test_ap_5
    });

    suite.tests.emplace_back(new test {
        "AP Test 6: Subcommand parameter recognition tests",
        "test_ap_6",
        test_ap_6
    });

    suite.tests.emplace_back(new test {
        "AP Test 7: Option parameter with defaults recognition tests",
        "test_ap_7",
        test_ap_7
    });

    suite.tests.emplace_back(new test {
        "AP Test 8: Subcommand parameter with defaults recognition tests",
        "test_ap_8",
        test_ap_8
    });

    suite.tests.emplace_back(new test {
        "AP Test 9: Argument split tests",
        "test_ap_9",
        test_ap_9
    });

    suite.tests.emplace_back(new test {
        "AP Test 10: Variadic parameter recognition tests",
        "test_ap_10",
        test_ap_10
    });

    suite.tests.emplace_back(new test {
        "AP Test 11: Throw tests",
        "test_ap_11",
        test_ap_11
    });

    suite.tests.emplace_back(new test {
        "AP Test 12: Misc. edge case tests",
        "test_ap_12",
        test_ap_12
    });

    std::size_t errors = (std::size_t)-1;
    try
    {
        auto failed_tests = suite.run();

        print_failed_tests(failed_tests);
        errors = sum_failed_tests_errors(failed_tests);
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred during test: {}", e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred during test");
    }

    for (auto &test : suite.tests)
    {
        delete test;
    }

    return errors;
}

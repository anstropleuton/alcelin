/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all the @c to_string functions from String Manipulator.
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
#include <format>
#include <string>
#include <string_view>

#include "alcelin_string_manipulators.hpp"
#include "confer.hpp"

using namespace alcelin;
using namespace std::string_literals;

/**
 *  @brief   Test SM's @c to_string function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_sm_to_string_1) {
    CT_BEGIN;

    std::vector vector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto        converter = [](int i) { return std::format("#{}#", i); };
    std::string expected = "<#1#>... <#2#>... <#3#>... <#4#>... <#5#>... "
                           "<#6#>... <#7#>... <#8#>... <#9#>... <#10#>";

    auto string = sm::to_string(vector, converter, "... ", "<", ">");

    logln("string: {}",   string);
    logln("expected: {}", expected);

    CT_ASSERT_CTR(string, expected);

    return errors;
}

/**
 *  @brief   Test SM's @c to_string function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_sm_to_string_2) {
    CT_BEGIN;

    std::vector vector   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::string expected = "1, 2, 3, 4, 5, 6, 7, 8, 9, 10";

    auto string = sm::to_string(vector);

    logln("string: {}",   string);
    logln("expected: {}", expected);

    CT_ASSERT_CTR(string, expected);

    CT_END;
}

/**
 *  @brief   Test SM's @c to_string function (overload 3).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_sm_to_string_3) {
    CT_BEGIN;

    std::vector vector   = { 'a', 'b', 'c', 'd', 'e' };
    std::string expected = "'a', 'b', 'c', 'd', 'e'";

    auto string = sm::to_string(vector);

    logln("string: {}",   string);
    logln("expected: {}", expected);

    CT_ASSERT_CTR(string, expected);

    CT_END;
}

/**
 *  @brief   Test SM's @c to_string function (overload 4).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_sm_to_string_4) {
    CT_BEGIN;

    std::vector vector = { "Well"s, "Hello"s, "There"s, "General"s,
        "Kenobi"s };
    std::string expected = "\"Well\", \"Hello\", \"There\", \"General\", "
                           "\"Kenobi\"";

    auto string = sm::to_string(vector);

    logln("string: {}",   string);
    logln("expected: {}", expected);

    CT_ASSERT_CTR(string, expected);

    CT_END;
}

/**
 *  @brief   Test SM's chars_to_string function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_sm_chars_to_string) {
    CT_BEGIN;

    std::vector vector = {
        'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'
    };
    std::string expected = "Hello, World!";

    auto string = sm::chars_to_string(vector);

    logln("string: {}",   string);
    logln("expected: {}", expected);

    CT_ASSERT_CTR(string, expected);

    CT_END;
}

/**
 *  @brief   Test SM's @c to_string.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_sm_to_string) try
{
    test_case sm_to_string_1_test_case {
        .title         = "Test SM's @c to_string function (overload 1)",
        .function_name = "test_sm_to_string_1",
        .function      = test_sm_to_string_1
    };

    test_case sm_to_string_2_test_case {
        .title         = "Test SM's @c to_string function (overload 2)",
        .function_name = "test_sm_to_string_2",
        .function      = test_sm_to_string_2
    };

    test_case sm_to_string_3_test_case {
        .title         = "Test SM's @c to_string function (overload 3)",
        .function_name = "test_sm_to_string_3",
        .function      = test_sm_to_string_3
    };

    test_case sm_to_string_4_test_case {
        .title         = "Test SM's @c to_string function (overload 4)",
        .function_name = "test_sm_to_string_4",
        .function      = test_sm_to_string_4
    };

    test_case sm_chars_to_string_test_case {
        .title         = "Test SM's chars_to_string function",
        .function_name = "test_sm_chars_to_string",
        .function      = test_sm_chars_to_string
    };


    test_suite suite = {
        .tests       = {
            &sm_to_string_1_test_case,
            &sm_to_string_2_test_case,
            &sm_to_string_3_test_case,
            &sm_to_string_4_test_case,
            &sm_chars_to_string_test_case
        },
        .pre_run    = default_pre_runner('=', 3),
        .post_run   = default_post_runner('=', 3),
        .run_failed = default_run_failed_quitter()
    };

    auto failed_tests = suite.run();
    print_failed_tests(failed_tests);
    return sum_failed_tests_errors(failed_tests);
}
catch (const std::exception &e)
{
    logln("Exception occurred during test: {}", e.what());
    return 1;
}
catch (...)
{
    logln("Unknown exception occurred during test");
    return 2;
}

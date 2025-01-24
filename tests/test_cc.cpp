/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test custom containers in Container Utilities.
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

#include <vector>

#include "alcelin_custom_containers.hpp"
#include "confer.hpp"

using namespace alcelin;

/**
 *  @brief   Test CC' @c boundless_access function.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cc_boundless_access) {
    CT_BEGIN;

    std::vector values { 1, 2, 3, 4, 5 };

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }

        for (std::size_t i = -values.size(); i != values.size(); i++)
        {
            cc::boundless_access(values, i) = i;

            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            if (i < values.size())
            {
                expected = values[i];
            }

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cc_boundless_access: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cc_boundless_access");
    }

    CT_END;
}

/**
 *  @brief   Test CC' @c boundless_vector struct.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cc_boundless_vector) {
    CT_BEGIN;

    cc::boundless_vector values = { 1, 2, 3, 4, 5 };

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }

        for (std::size_t i = -values.size(); i != values.size(); i++)
        {
            cc::boundless_access(values, i) = i;

            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            if (i < values.size())
            {
                expected = values[i];
            }

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cc_boundless_vector: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cc_boundless_vector");
    }

    CT_END;
}

/**
 *  @brief   Test CC' @c boundless_array struct.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cc_boundless_array) {
    CT_BEGIN;

    cc::boundless_array values = { 1, 2, 3, 4, 5 };

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }

        for (std::size_t i = -values.size(); i != values.size(); i++)
        {
            cc::boundless_access(values, i) = i;

            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            if (i < values.size())
            {
                expected = values[i];
            }

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cc_boundless_array: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cc_boundless_array");
    }

    CT_END;
}

/**
 *  @brief   Test CC' @c boundless_span struct.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cc_boundless_span) {
    CT_BEGIN;

    cc::boundless_vector    vec    = { 1, 2, 3, 4, 5 };
    cc::boundless_span<int> values = vec;

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = 0;

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cc_boundless_span: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cc_boundless_span");
    }

    CT_END;
}

/**
 *  @brief   Test CC' @c boundless_string struct.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cc_boundless_string) {
    CT_BEGIN;

    cc::boundless_string values = "String test #9999";

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = '\0';

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = '\0';

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }

        for (std::size_t i = -values.size(); i != values.size(); i++)
        {
            cc::boundless_access(values, i) = i % ('z' - 'a') + 'a';

            auto value    = cc::boundless_access(values, i);
            auto expected = '\0';

            if (i < values.size())
            {
                expected = values[i];
            }

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln("Exception occurred in test_cc_boundless_string: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cc_boundless_string");
    }

    CT_END;
}

/**
 *  @brief   Test CC' @c boundless_string_view struct.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cc_boundless_string_view) {
    CT_BEGIN;

    cc::boundless_string_view values = "String test #9999";

    try
    {
        for (std::size_t i = 0; i < values.size(); i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = values[i];

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = values.size(); i < values.size() * 2; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = '\0';

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
        for (std::size_t i = -values.size(); i != 0; i++)
        {
            auto value    = cc::boundless_access(values, i);
            auto expected = '\0';

            logln("- - - - -");
            logln("i: {}",        i);
            logln("value: {}",    value);
            logln("expected: {}", expected);
            CT_ASSERT(value, expected,
                "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln(
            "Exception occurred in test_cc_boundless_string_view: {}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cc_boundless_string_view");
    }

    CT_END;
}

/**
 *  @brief   Test CC' @c enumerated_array struct.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cc_enumerated_array) {
    CT_BEGIN;

    enum class enumerator {
        unknown = -1,
        zeroth,
        first,
        second,
        third,
        fourth,
        fifth,
        sixth,
        seventh,
        eighth,
        ninth,
        max
    };

    // Best name ever
    std::vector values = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cc::erray<enumerator, int> erray = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    try
    {
        using enum enumerator;

        erray[zeroth]  += 10;
        erray[first]   += 10;
        erray[second]  += 10;
        erray[third]   += 10;
        erray[fourth]  += 10;
        erray[fifth]   += 10;
        erray[sixth]   += 10;
        erray[seventh] += 10;
        erray[eighth]  += 10;
        erray[ninth]   += 10;

        for (std::size_t i = 0; i < erray.size(); i++)
        {
            auto value    = erray[static_cast<enumerator>(i)];
            auto expected = values[i] + 10;

            CT_ASSERT(value, expected, "Invalid element");
        }
    }
    catch (const std::exception &e)
    {
        logln(
            "Exception occurred in test_cc_boundless_string_view: "
            "{}",
            e.what());
    }
    catch (...)
    {
        logln("Unknown exception occurred in "
            "test_cc_boundless_string_view");
    }

    CT_END;
}

/**
 *  @brief   Test CC.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cc) try
{
    test_case cc_boundless_access_test_case {
        .title         = "Test CC' boundless_access function.",
        .function_name = "test_cc_boundless_access",
        .function      = test_cc_boundless_access
    };

    test_case cc_boundless_vector_test_case {
        .title         = "Test CC' boundless_vector struct.",
        .function_name = "test_cc_boundless_vector",
        .function      = test_cc_boundless_vector
    };

    test_case cc_boundless_array_test_case {
        .title         = "Test CC' boundless_array struct.",
        .function_name = "test_cc_boundless_array",
        .function      = test_cc_boundless_array
    };

    test_case cc_boundless_span_test_case {
        .title         = "Test CC' boundless_span struct.",
        .function_name = "test_cc_boundless_span",
        .function      = test_cc_boundless_span
    };

    test_case cc_boundless_string_test_case {
        .title         = "Test CC' boundless_string struct.",
        .function_name = "test_cc_boundless_string",
        .function      = test_cc_boundless_string
    };

    test_case cc_boundless_string_view_test_case {
        .title         = "Test CC' boundless_string_view struct.",
        .function_name = "test_cc_boundless_string_view",
        .function      = test_cc_boundless_string_view
    };

    test_case cc_enumerated_array_test_case {
        .title         = "Test CC' enumerated_array struct.",
        .function_name = "test_cc_enumerated_array",
        .function      = test_cc_enumerated_array
    };

    test_suite suite = {
        .tests       = {
            &cc_boundless_access_test_case,
            &cc_boundless_vector_test_case,
            &cc_boundless_array_test_case,
            &cc_boundless_span_test_case,
            &cc_boundless_string_test_case,
            &cc_boundless_string_view_test_case,
            &cc_enumerated_array_test_case
        },
        .pre_run  = default_pre_runner('=', 3),
        .post_run = default_post_runner('=', 3)
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
    return 1;
}

/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of Properties in Alcelin.
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

#include <exception>

#include "alcelin_property.hpp"
#include "confer.hpp"

using namespace alcelin;
using namespace std::string_literals;

/**
 *  @brief  Dummy type with operators to test operators in properties.
 */
struct type_with_operators {

    /**
     *  @brief  Dummy constant to test @c operator-> in properties.
     */
    static constexpr int dummy = 42;

    /**
     *  @brief  @c operator() to test @c operator() in properties.
     */
    [[nodiscard]] inline constexpr auto operator() (int num)
    {
        logln("type_with_operators::operator() called with value: {}", num);
        return num * 2;
    }

    /**
     *  @brief  @c operator[] to test @c operator[] in properties.
     */
    [[nodiscard]] inline constexpr auto operator[] (int num)
    {
        logln("type_with_operators::operator[] called with value: {}", num);
        return num * 3;
    }

    /**
     *  @brief  @c operator-> to test @c operator-> in properties.
     */
    [[nodiscard]] inline constexpr auto operator-> ()
    {
        logln("type_with_operators::operator-> called");
        return this;
    }
};

/**
 *  @brief   Test Prop's Read-only property.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_prop_property_readonly) {
    CT_BEGIN;

    int prop_value = 42;
    prop::property_readonly<int> prop([&]() {
        logln("Getter called");
        return prop_value;
    });

    // uncrustify:off
    std::vector values = {
        (int)prop,
        prop + 1,
        prop - 1,
        prop * 2,
        prop / 2,
        prop % 5,
        prop ^ 2,
        prop & 2,
        prop | 2,
        prop << 2,
        prop >> 2,
        (int)(prop == 42),
        (int)(prop != 42),
        (int)(prop < 42),
        (int)(prop <= 42),
        (int)(prop > 42),
        (int)(prop >= 42)
    };

    std::vector expected = {
        42,  // (int)prop
        43,  // prop + 1
        41,  // prop - 1
        84,  // prop * 2
        21,  // prop / 2
        2,   // prop % 5
        40,  // prop ^ 2
        2,   // prop & 2
        42,  // prop | 2
        168, // prop << 2
        10,  // prop >> 2
        1,   // (int)(prop == 42)
        0,   // (int)(prop != 42)
        0,   // (int)(prop < 42)
        1,   // (int)(prop <= 42)
        0,   // (int)(prop > 42)
        1    // (int)(prop >= 42)
    };
    // uncrustify:on

    CT_ASSERT_CTR(values, expected);

    CT_END;
}

/**
 *  @brief   Test Prop's read-write property.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_prop_property) {
    CT_BEGIN;

    int prop_value = 42;
    prop::property<int> prop([&]() {
        logln("Getter called");
        return prop_value;
    }, [&](int value) {
        logln("Setter called with value: {}", value);
        prop_value = value;
    });

    // uncrustify:off
    std::vector values = {
        (int)prop,
        prop + 1,
        prop - 1,
        prop * 2,
        prop / 2,
        prop % 5,
        prop ^ 2,
        prop & 2,
        prop | 2,
        prop << 2,
        prop >> 2,
        (int)(prop == 42),
        (int)(prop != 42),
        (int)(prop < 42),
        (int)(prop <= 42),
        (int)(prop > 42),
        (int)(prop >= 42),
        (int)(prop = 42),
        (int)(prop += 1),
        (int)(prop -= 1),
        (int)(prop *= 2),
        (int)(prop /= 2),
        (int)(prop %= 5),
        (int)(prop ^= 2),
        (int)(prop &= 2),
        (int)(prop |= 2),
        (int)(prop <<= 2),
        (int)(prop >>= 2),
        (int)(prop++),
        (int)(++prop),
        (int)(prop--),
        (int)(--prop)
    };

    std::vector expected = {
        42,  // (int)prop
        43,  // prop + 1
        41,  // prop - 1
        84,  // prop * 2
        21,  // prop / 2
        2,   // prop % 5
        40,  // prop ^ 2
        2,   // prop & 2
        42,  // prop | 2
        168, // prop << 2
        10,  // prop >> 2
        1,   // (int)(prop == 42)
        0,   // (int)(prop != 42)
        0,   // (int)(prop < 42)
        1,   // (int)(prop <= 42)
        0,   // (int)(prop > 42)
        1,   // (int)(prop >= 42)
        42,  // (int)(prop = 42)
        43,  // (int)(prop += 1)
        42,  // (int)(prop -= 1)
        84,  // (int)(prop *= 2)
        42,  // (int)(prop /= 2)
        2,   // (int)(prop %= 5)
        0,   // (int)(prop ^= 2)
        0,   // (int)(prop &= 2)
        2,   // (int)(prop |= 2)
        8,   // (int)(prop <<= 2)
        2,   // (int)(prop >>= 2)
        2,   // (int)(prop++)
        4,   // (int)(++prop)
        4,   // (int)(prop--)
        2    // (int)(--prop)
    };
    // uncrustify:on

    CT_ASSERT_CTR(values, expected);

    CT_END;
}

/**
 *  @brief   Test Prop's properties' additional operators.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_prop_property_additional_operators) {
    CT_BEGIN;

    prop::property<type_with_operators> prop([]() {
        logln("Getter called");
        return type_with_operators();
    }, [](type_with_operators value) {
        logln("Setter called");
    });

    std::vector values = {
        prop(2),
        prop[2],
        prop->dummy
    };

    std::vector expected = {
        4,
        6,
        42
    };

    CT_ASSERT_CTR(values, expected);

    CT_END;
}

/**
 *  @brief   Test Prop's observable.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_prop_observable) {
    CT_BEGIN;

    int observed_count = 0;
    prop::observable<int> observable([&](int value) {
        logln("Observer called with value: {}", value);
        observed_count++;
    });

    // Perform actions that cause observer to be called.
    observable   = 42;
    observable  += 1;
    observable  -= 1;
    observable  *= 2;
    observable  /= 2;
    observable  %= 5;
    observable  ^= 2;
    observable  &= 2;
    observable  |= 2;
    observable <<= 2;
    observable >>= 2;
    observable++;
    ++observable;
    observable--;
    --observable;

    int expected_count = 15;

    CT_ASSERT(observed_count, expected_count, "Observer counter must match");

    CT_END;
}

/**
 *  @brief   Test Prop.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_prop) try
{
    test_case prop_property_readonly_test_case {
        .title         = "Test Prop's Read-only property",
        .function_name = "test_prop_property_readonly",
        .function      = test_prop_property_readonly
    };

    test_case prop_property_test_case {
        .title         = "Test Prop's read-write property",
        .function_name = "test_prop_property",
        .function      = test_prop_property
    };

    test_case prop_property_additional_operators_test_case {
        .title         = "Test Prop's properties' additional operators",
        .function_name = "test_prop_property_additional_operators",
        .function      = test_prop_property_additional_operators
    };

    test_case prop_observable_test_case {
        .title         = "Test Prop's observable",
        .function_name = "test_prop_observable",
        .function      = test_prop_observable
    };

    test_suite suite = {
        .tests       = {
            &prop_property_readonly_test_case,
            &prop_property_test_case,
            &prop_property_additional_operators_test_case,
            &prop_observable_test_case
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

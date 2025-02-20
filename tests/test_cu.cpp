/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test everything in Container Utilities.
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

#include "alcelin_container_utilities.hpp"
#include "alcelin_string_manipulators.hpp"
#include "confer.hpp"

using namespace alcelin;
using namespace cu_operators;

/**
 *  @brief   Test CU's @c subordinate function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_subordinate) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::size_t first     = 2;
    std::size_t last      = 7;
    std::vector expected  = { 3, 4, 5, 6, 7 };

    auto subbed = cu::subordinate(container, first, last);

    logln("container: {}", sm::to_string(container));
    logln("first: {}",     first);
    logln("last: {}",      last);
    logln("subbed: {}",    sm::to_string(subbed));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(subbed, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c combine function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_combine_1) {
    CT_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    std::vector b        = { 6, 7, 8, 9, 10 };
    std::vector expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto combined = cu::combine(a, b);

    logln("a: {}",        sm::to_string(a));
    logln("b: {}",        sm::to_string(b));
    logln("combined: {}", sm::to_string(combined));
    logln("expected: {}", sm::to_string(expected));

    CT_ASSERT_CTR(combined, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c combine function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_combine_2) {
    CT_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    int         b        = 6;
    std::vector expected = { 1, 2, 3, 4, 5, 6 };

    auto combined = cu::combine(a, b);

    logln("a: {}",        sm::to_string(a));
    logln("b: {}",        b);
    logln("combined: {}", sm::to_string(combined));
    logln("expected: {}", sm::to_string(expected));

    CT_ASSERT_CTR(combined, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c filter_out_seq function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_filter_out_seq) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector filter    = { 4, 5, 6 };
    std::vector expected  = { 1, 2, 3, 7, 8, 9, 10 };

    auto filtered = cu::filter_out_seq(container, filter);

    logln("container: {}", sm::to_string(container));
    logln("filter: {}",    sm::to_string(filter));
    logln("filtered: {}",  sm::to_string(filtered));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(filtered, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c filter_out_occ function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_filter_out_occ) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector filter    = { 1, 3, 5, 7, 9 };
    std::vector expected  = { 2, 4, 6, 8, 10 };

    auto filtered = cu::filter_out_occ(container, filter);

    logln("container: {}", sm::to_string(container));
    logln("filter: {}",    sm::to_string(filter));
    logln("filtered: {}",  sm::to_string(filtered));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(filtered, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c filter_out_occ_seq function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_filter_out_occ_seq) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9, 10 };
    std::vector<std::vector<int>> filter = { { 4, 4 }, { 7, 7 } };
    std::vector expected = { 1, 2, 3, 5, 6, 8, 9, 10 };

    auto filtered = cu::filter_out_occ_seq(container, filter);

    logln("container: {}", sm::to_string(container));
    logln("filter[0]: {}", sm::to_string(filter[0]));
    logln("filter[1]: {}", sm::to_string(filter[1]));
    logln("filtered: {}",  sm::to_string(filtered));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(filtered, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c filter_out function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_filter_out) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         filter    = 3;
    std::vector expected  = { 1, 2, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered = cu::filter_out(container, filter);

    logln("container: {}", sm::to_string(container));
    logln("filter: {}",    filter);
    logln("filtered: {}",  sm::to_string(filtered));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(filtered, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c repeat function (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_repeat_1) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    std::size_t times     = 3;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };

    auto repeated = cu::repeat(container, times);

    logln("container: {}", sm::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  sm::to_string(repeated));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(repeated, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c repeat function (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_repeat_2) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    long double times     = 3.6;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
        3 };

    auto repeated = cu::repeat(container, times);

    logln("container: {}", sm::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  sm::to_string(repeated));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(repeated, expected);

    CT_END;
}

/**
 *  @brief   Test CU's @c split_seq function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_split_seq) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector splitter  = { 5, 6, 7 };
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3, 4 },
        { 8, 9, 10 }
    };

    auto splitted = cu::split_seq(container, splitter);

    logln("container: {}", sm::to_string(container));
    logln("splitter: {}",  sm::to_string(splitter));

    CT_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", sm::to_string(splitted[0]));
    logln("splitted[1]: {}", sm::to_string(splitted[1]));
    logln("expected[0]: {}", sm::to_string(expected[0]));
    logln("expected[1]: {}", sm::to_string(expected[1]));

    CT_ASSERT_SUB_SIZE(splitted, expected, 0);

    CT_ASSERT_SUB_SIZE(splitted, expected, 1);

    CT_END;
}

/**
 *  @brief   Test CU's @c split_occ function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_split_occ) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector splitter  = { 4, 8 };
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3 },
        { 5, 6, 7 },
        { 9, 10 }
    };

    auto splitted = cu::split_occ(container, splitter);

    logln("container: {}", sm::to_string(container));
    logln("splitter: {}",  sm::to_string(splitter));

    CT_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", sm::to_string(splitted[0]));
    logln("splitted[1]: {}", sm::to_string(splitted[1]));
    logln("splitted[2]: {}", sm::to_string(splitted[2]));
    logln("expected[0]: {}", sm::to_string(expected[0]));
    logln("expected[1]: {}", sm::to_string(expected[1]));
    logln("expected[2]: {}", sm::to_string(expected[2]));

    CT_ASSERT_SUB_SIZE(splitted, expected, 0);

    CT_ASSERT_SUB_SIZE(splitted, expected, 1);

    CT_ASSERT_SUB_SIZE(splitted, expected, 2);

    CT_END;
}

/**
 *  @brief   Test CU's @c split_occ_seq function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_split_occ_seq) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 3, 4, 5, 6, 7, 8, 8, 9, 10 };
    std::vector<std::vector<int>> splitter = { { 3, 3 }, { 8, 8 } };
    std::vector<std::vector<int>> expected = {
        { 1, 2  },
        { 4, 5, 6, 7},
        { 9, 10 }
    };

    auto splitted = cu::split_occ_seq(container, splitter);

    logln("container: {}",   sm::to_string(container));
    logln("splitter[0]: {}", sm::to_string(splitter[0]));
    logln("splitter[1]: {}", sm::to_string(splitter[1]));

    CT_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", sm::to_string(splitted[0]));
    logln("splitted[1]: {}", sm::to_string(splitted[1]));
    logln("splitted[2]: {}", sm::to_string(splitted[2]));
    logln("expected[0]: {}", sm::to_string(expected[0]));
    logln("expected[1]: {}", sm::to_string(expected[1]));
    logln("expected[2]: {}", sm::to_string(expected[2]));

    CT_ASSERT_SUB_SIZE(splitted, expected, 0);

    CT_ASSERT_SUB_SIZE(splitted, expected, 1);

    CT_ASSERT_SUB_SIZE(splitted, expected, 2);

    CT_END;
}

/**
 *  @brief   Test CU's @c split function.
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_split) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         splitter  = 7;
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3, 4, 5, 6 },
        { 8, 9, 10 }
    };

    auto splitted = cu::split(container, splitter);

    logln("container: {}", sm::to_string(container));
    logln("splitter: {}",  splitter);

    CT_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", sm::to_string(splitted[0]));
    logln("splitted[1]: {}", sm::to_string(splitted[1]));
    logln("expected[0]: {}", sm::to_string(expected[0]));
    logln("expected[1]: {}", sm::to_string(expected[1]));

    CT_ASSERT_SUB_SIZE(splitted, expected, 0);

    CT_ASSERT_SUB_SIZE(splitted, expected, 1);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator+ (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_plus_1) {
    CT_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    std::vector b        = { 6, 7, 8, 9, 10 };
    std::vector expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto combined = a + b;

    logln("a: {}",        sm::to_string(a));
    logln("b: {}",        sm::to_string(b));
    logln("combined: {}", sm::to_string(combined));
    logln("expected: {}", sm::to_string(expected));

    CT_ASSERT_CTR(combined, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator+ (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_plus_2) {
    CT_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    int         b        = 6;
    std::vector expected = { 1, 2, 3, 4, 5, 6 };

    auto combined = a + b;

    logln("a: {}",        sm::to_string(a));
    logln("b: {}",        b);
    logln("combined: {}", sm::to_string(combined));
    logln("expected: {}", sm::to_string(expected));

    CT_ASSERT_CTR(combined, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator- (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_minus_1) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector filter    = { 4, 5, 6 };
    std::vector expected  = { 1, 2, 3, 7, 8, 9, 10 };

    auto filtered = container - filter;

    logln("container: {}", sm::to_string(container));
    logln("filter: {}",    sm::to_string(filter));
    logln("filtered: {}",  sm::to_string(filtered));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(filtered, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator- (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_minus_2) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         filter    = 3;
    std::vector expected  = { 1, 2, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered = container - filter;

    logln("container: {}", sm::to_string(container));
    logln("filter: {}",    filter);
    logln("filtered: {}",  sm::to_string(filtered));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(filtered, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator* (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_star_1) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    std::size_t times     = 3;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };

    auto repeated = container * times;

    logln("container: {}", sm::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  sm::to_string(repeated));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(repeated, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator* (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_star_2) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    long double times     = 3.6;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
        3 };

    auto repeated = container * times;

    logln("container: {}", sm::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  sm::to_string(repeated));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(repeated, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator/ (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_slash_1) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector splitter  = { 5, 6, 7 };
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3, 4 },
        { 8, 9, 10 }
    };

    auto splitted = container / splitter;

    logln("container: {}", sm::to_string(container));
    logln("splitter: {}",  sm::to_string(splitter));

    CT_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", sm::to_string(splitted[0]));
    logln("splitted[1]: {}", sm::to_string(splitted[1]));
    logln("expected[0]: {}", sm::to_string(expected[0]));
    logln("expected[1]: {}", sm::to_string(expected[1]));

    CT_ASSERT_SUB_SIZE(splitted, expected, 0);

    CT_ASSERT_SUB_SIZE(splitted, expected, 1);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator/ (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_slash_2) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         splitter  = 7;
    std::vector<std::vector<int>> expected = {
        { 1, 2, 3, 4, 5, 6 },
        { 8, 9, 10 }
    };

    auto splitted = container / splitter;

    logln("container: {}", sm::to_string(container));
    logln("splitter: {}",  splitter);

    CT_ASSERT_SIZE(splitted, expected);

    logln("splitted[0]: {}", sm::to_string(splitted[0]));
    logln("splitted[1]: {}", sm::to_string(splitted[1]));
    logln("expected[0]: {}", sm::to_string(expected[0]));
    logln("expected[1]: {}", sm::to_string(expected[1]));

    CT_ASSERT_SUB_SIZE(splitted, expected, 0);

    CT_ASSERT_SUB_SIZE(splitted, expected, 1);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator+= (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_plus_equals_1) {
    CT_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    std::vector b        = { 6, 7, 8, 9, 10 };
    std::vector expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto combined = a;
    combined += b;

    logln("a: {}",        sm::to_string(a));
    logln("b: {}",        sm::to_string(b));
    logln("combined: {}", sm::to_string(combined));
    logln("expected: {}", sm::to_string(expected));

    CT_ASSERT_CTR(combined, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator+= (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_plus_equals_2) {
    CT_BEGIN;

    std::vector a        = { 1, 2, 3, 4, 5 };
    int         b        = 6;
    std::vector expected = { 1, 2, 3, 4, 5, 6 };

    auto combined = a;
    combined += b;

    logln("a: {}",        sm::to_string(a));
    logln("b: {}",        b);
    logln("combined: {}", sm::to_string(combined));
    logln("expected: {}", sm::to_string(expected));

    CT_ASSERT_CTR(combined, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator-= (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_minus_equals_1) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector filter    = { 4, 5, 6 };
    std::vector expected  = { 1, 2, 3, 7, 8, 9, 10 };

    auto filtered = container;
    filtered -= filter;

    logln("container: {}", sm::to_string(container));
    logln("filter: {}",    sm::to_string(filter));
    logln("filtered: {}",  sm::to_string(filtered));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(filtered, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator-= (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_minus_equals_2) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int         filter    = 3;
    std::vector expected  = { 1, 2, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered = container;
    filtered -= filter;

    logln("container: {}", sm::to_string(container));
    logln("filter: {}",    filter);
    logln("filtered: {}",  sm::to_string(filtered));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(filtered, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator*= (overload 1).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_star_equals_1) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    std::size_t times     = 3;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };

    auto repeated = container;
    repeated *= times;

    logln("container: {}", sm::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  sm::to_string(repeated));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(repeated, expected);

    CT_END;
}

/**
 *  @brief   Test CU operators' @c operator*= (overload 2).
 *  @return  Number of errors.
 */
[[nodiscard]] static CT_TESTER_FN(test_cu_operator_star_equals_2) {
    CT_BEGIN;

    std::vector container = { 1, 2, 3, 4, 5 };
    long double times     = 3.6;
    std::vector expected  = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
        3 };

    auto repeated = container;
    repeated *= times;

    logln("container: {}", sm::to_string(container));
    logln("times: {}",     times);
    logln("repeated: {}",  sm::to_string(repeated));
    logln("expected: {}",  sm::to_string(expected));

    CT_ASSERT_CTR(repeated, expected);

    CT_END;
}

/**
 *  @brief   Test CU.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_cu) try
{
    test_case cu_subordinate_test_case {
        .title         = "Test CU's subordinate function",
        .function_name = "test_cu_subordinate",
        .function      = test_cu_subordinate
    };

    test_case cu_combine_1_test_case {
        .title         = "Test CU's combine function (overload 1)",
        .function_name = "test_cu_combine_1",
        .function      = test_cu_combine_1
    };

    test_case cu_combine_2_test_case {
        .title         = "Test CU's combine function (overload 2)",
        .function_name = "test_cu_combine_2",
        .function      = test_cu_combine_2
    };

    test_case cu_filter_out_seq_test_case {
        .title         = "Test CU's filter_out_seq function",
        .function_name = "test_cu_filter_out_seq",
        .function      = test_cu_filter_out_seq
    };

    test_case cu_filter_out_occ_test_case {
        .title         = "Test CU's filter_out_occ function",
        .function_name = "test_cu_filter_out_occ",
        .function      = test_cu_filter_out_occ
    };

    test_case cu_filter_out_occ_seq_test_case {
        .title         = "Test CU's filter_out_occ_seq function",
        .function_name = "test_cu_filter_out_occ_seq",
        .function      = test_cu_filter_out_occ_seq
    };

    test_case cu_filter_out_test_case {
        .title         = "Test CU's filter_out function",
        .function_name = "test_cu_filter_out",
        .function      = test_cu_filter_out
    };

    test_case cu_repeat_1_test_case {
        .title         = "Test CU's repeat function (overload 1)",
        .function_name = "test_cu_repeat_1",
        .function      = test_cu_repeat_1
    };

    test_case cu_repeat_2_test_case {
        .title         = "Test CU's repeat function (overload 2)",
        .function_name = "test_cu_repeat_2",
        .function      = test_cu_repeat_2
    };

    test_case cu_split_seq_test_case {
        .title         = "Test CU's split_seq function",
        .function_name = "test_cu_split_seq",
        .function      = test_cu_split_seq
    };

    test_case cu_split_occ_test_case {
        .title         = "Test CU's split_occ function",
        .function_name = "test_cu_split_occ",
        .function      = test_cu_split_occ
    };

    test_case cu_split_occ_seq_test_case {
        .title         = "Test CU's split_occ_seq function",
        .function_name = "test_cu_split_occ_seq",
        .function      = test_cu_split_occ_seq
    };

    test_case cu_split_test_case {
        .title         = "Test CU's split function",
        .function_name = "test_cu_split",
        .function      = test_cu_split
    };

    test_case cu_operator_plus_1_test_case {
        .title         = "Test CU operators' operator+ (overload 1)",
        .function_name = "test_cu_operator_plus_1",
        .function      = test_cu_operator_plus_1
    };

    test_case cu_operator_plus_2_test_case {
        .title         = "Test CU operators' operator+ (overload 2)",
        .function_name = "test_cu_operator_plus_2",
        .function      = test_cu_operator_plus_2
    };

    test_case cu_operator_minus_1_test_case {
        .title         = "Test CU operators' operator- (overload 1)",
        .function_name = "test_cu_operator_minus_1",
        .function      = test_cu_operator_minus_1
    };

    test_case cu_operator_minus_2_test_case {
        .title         = "Test CU operators' operator- (overload 2)",
        .function_name = "test_cu_operator_minus_2",
        .function      = test_cu_operator_minus_2
    };

    test_case cu_operator_star_1_test_case {
        .title         = "Test CU operators' operator* (overload 1)",
        .function_name = "test_cu_operator_star_1",
        .function      = test_cu_operator_star_1
    };

    test_case cu_operator_star_2_test_case {
        .title         = "Test CU operators' operator* (overload 2)",
        .function_name = "test_cu_operator_star_2",
        .function      = test_cu_operator_star_2
    };

    test_case cu_operator_slash_1_test_case {
        .title         = "Test CU operators' operator/ (overload 1)",
        .function_name = "test_cu_operator_slash_1",
        .function      = test_cu_operator_slash_1
    };

    test_case cu_operator_slash_2_test_case {
        .title         = "Test CU operators' operator/ (overload 2)",
        .function_name = "test_cu_operator_slash_2",
        .function      = test_cu_operator_slash_2
    };

    test_case cu_operator_plus_equals_1_test_case {
        .title         = "Test CU operators' operator+= (overload 1)",
        .function_name = "test_cu_operator_plus_equals_1",
        .function      = test_cu_operator_plus_equals_1
    };

    test_case cu_operator_plus_equals_2_test_case {
        .title         = "Test CU operators' operator+= (overload 2)",
        .function_name = "test_cu_operator_plus_equals_2",
        .function      = test_cu_operator_plus_equals_2
    };

    test_case cu_operator_minus_equals_1_test_case {
        .title         = "Test CU operators' operator-= (overload 1)",
        .function_name = "test_cu_operator_minus_equals_1",
        .function      = test_cu_operator_minus_equals_1
    };

    test_case cu_operator_minus_equals_2_test_case {
        .title         = "Test CU operators' operator-= (overload 2)",
        .function_name = "test_cu_operator_minus_equals_2",
        .function      = test_cu_operator_minus_equals_2
    };

    test_case cu_operator_star_equals_1_test_case {
        .title         = "Test CU operators' operator*= (overload 1)",
        .function_name = "test_cu_operator_star_equals_1",
        .function      = test_cu_operator_star_equals_1
    };

    test_case cu_operator_star_equals_2_test_case {
        .title         = "Test CU operators' operator*= (overload 2)",
        .function_name = "test_cu_operator_star_equals_2",
        .function      = test_cu_operator_star_equals_2
    };

    test_suite suite = {
        .tests       = {
            &cu_subordinate_test_case,
            &cu_combine_1_test_case,
            &cu_combine_1_test_case,
            &cu_combine_2_test_case,
            &cu_filter_out_seq_test_case,
            &cu_filter_out_occ_test_case,
            &cu_filter_out_occ_seq_test_case,
            &cu_filter_out_test_case,
            &cu_repeat_1_test_case,
            &cu_repeat_2_test_case,
            &cu_split_seq_test_case,
            &cu_split_occ_test_case,
            &cu_split_occ_seq_test_case,
            &cu_split_test_case,
            &cu_operator_plus_1_test_case,
            &cu_operator_plus_2_test_case,
            &cu_operator_minus_1_test_case,
            &cu_operator_minus_2_test_case,
            &cu_operator_star_1_test_case,
            &cu_operator_star_2_test_case,
            &cu_operator_slash_1_test_case,
            &cu_operator_slash_2_test_case,
            &cu_operator_plus_equals_1_test_case,
            &cu_operator_plus_equals_2_test_case,
            &cu_operator_minus_equals_1_test_case,
            &cu_operator_minus_equals_2_test_case,
            &cu_operator_star_equals_1_test_case,
            &cu_operator_star_equals_2_test_case
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

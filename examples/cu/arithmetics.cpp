/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   How to use CU's container arithmetic functions.
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

#include <print>

#include "alcelin.hpp" // IWYU pragma: export

using namespace alcelin;

// This example is meant to be a kick-starter to start using my library, but
// they do not teach everything.  Refer to the documentation for more details
auto main() -> int
{
    std::vector a = { 1, 2, 3, 4, 5 };
    std::vector b = { 6, 7, 8, 9, 10 };
    std::vector c = { 1, 2, 3, 6, 5, 4, 1, 2, 3, 6, 5, 4 };

    // Combining containers of same element type
    auto d = cu::combine(a, b); // d is { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }

    // Filtering out occurrences the elements
    // Note: we are using c
    auto e = cu::filter_out_occ(c, { 1, 2 }); // e is { 3, 6, 5, 4, 3, 6, 5, 4 }

    // Repeating the container
    // Note: we are using a
    auto f = cu::repeat(a, 2); // f is { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 }

    // Splitting the container into sub containers
    // Note: we are using c
    auto g = cu::split_seq(c, { 3, 6 }); // g is { { 1, 2 }, { 5, 4 }, { 1, 2 },
                                         // { 5, 4 } }

    // How is that "arithmetic"?  Try out operators to make it obvious
    using namespace cu_operators;

    // Same examples using operators

    // Combining
    d = a + b;

    // Filtering out
    e = c - std::vector { 1, 2 };

    // Repeating
    f = a * 2;

    // Splitting
    g = c / std::vector { 3, 6 };

    // Use std::formatter overload for any containers from alcelin::sm !
    std::println("d: {}", d);
    std::println("e: {}", e);
    std::println("f: {}", f);
    std::println("g: {}", g);
    // The above prints
    // d: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    // e: [3, 6, 5, 4, 3, 6, 5, 4]
    // f: [1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
    // g: [[1, 2], [5, 4], [1, 2], [5, 4]]



    // Still hard to wrap your head around these numbers?  No worries!  A string
    // version in examples/sm/arithmetics.cpp is here for you!
}

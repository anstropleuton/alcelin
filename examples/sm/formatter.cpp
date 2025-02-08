/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   How to use SM's @c std::formatter as I use in other examples.
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
#include <vector>

#include "alcelin_string_manipulators.hpp"

using namespace alcelin;
using namespace std::string_literals;

// This example is meant to be a kick-starter to start using my library, but
// they do not teach everything.  Refer to the documentation for more details
auto main() -> int
{
    // Know how std::formatter overloader for containers work before checking
    // other examples
    std::vector vector = { 1, 2, 3, 4, 5 };

    // Print the vector using the formatter
    std::println("Formatted vector: {}", vector);
    // This will print
    //  Formatted vector: [1, 2, 3, 4, 5]

    // Customize container prefix and suffix
    // Here, p stands for *p*refix and s stands for *s*uffix
    std::println("Formatted vector with prefix and suffix: {:p'<'s'>'}",
        vector);
    // This will print
    //  Formatted vector with prefix and suffix: <1, 2, 3, 4, 5>

    // Print with customized prefix and suffix for each elements
    // Here, r stands for element p*r*efix and u stands for element s*u*ffix
    std::println("Formatted vector with element prefix and suffix: {:r'<'u'>'}",
        vector);
    // This will print
    //  Formatted vector with element prefix and suffix:
    //  [<1>, <2>, <3>, <4>, <5>]

    // Print with customized separator
    // Here, e stands for s*e*parator
    std::println("Formatted vector with separator: {:e' -- '}",
        vector);
    // This will print
    //  Formatted vector with separator: [1 -- 2 -- 3 -- 4 -- 5]

    // Wanna format the elements too?
    // Here, f stands for *f*ormat specifier
    std::println("Formatted vector with element format specifier: {:f'0>2'}",
        vector);
    // This will print
    //  Formatted vector with element format specifier: [01, 02, 03, 04, 05]

    // Some edge cases

    // Wanna print with single quotes as element prefix and suffix?
    std::println("Formatted vector with single quotes as element prefix and "
        "suffix: {:r'\\''u'\\''}", vector);
    // This will print
    //  Formatted vector with single quotes as element prefix and suffix:
    //  ['1', '2', '3', '4', '5']

    // Wanna print with '{ ' and ' }' as container prefix and suffix?
    std::println("Formatted vector with curly braces as prefix and suffix: "
        "{:p'\\{ 's' \\}'}", vector);
    // This will print
    //  Formatted vector with curly braces as prefix and suffix:
    //  { 1, 2, 3, 4, 5 }

    // Got nested containers and want to format the nested containers?
    std::vector<std::vector<int>> nested_vector = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    // Print the nested vector
    std::println("Formatted nested vector: {}", nested_vector);
    // This will print
    //  Formatted nested vector: [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

    // Wanna format the nested container?
    std::println("Formatted nested vector with element format specifier: "
        "{:f'p\\'<\\'s\\'>\\''}", nested_vector);
    // This will print
    //  Formatted nested vector with element format specifier:
    //  [<1, 2, 3>, <4, 5, 6>, <7, 8, 9>]

    // Wanna format the nested elements too?
    std::println("Formatted nested vector with element format specifier: "
        "{:p'['s']'f'f\\'0>2\\''}", nested_vector);
    // This will print
    //  Formatted nested vector with element format specifier:
    //  [[01, 02, 03], [04, 05, 06], [07, 08, 09]]

    // Triple nested container? :grimacing:
    std::vector<std::vector<std::vector<int>>> triple_nested_vector = {
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        },
        {
            { 10, 11, 12 },
            { 13, 14, 15 },
            { 16, 17, 18 }
        },
        {
            { 19, 20, 21 },
            { 22, 23, 24 },
            { 25, 26, 27 }
        }
    };

    // Let's just do one example of printing the triple nested container
    // Because... you know... it's a triple nested container
    // Does this look scary?  It should
    std::println("Formatted triple nested vector with element format specifier:"
        " {:r'('u')'f'r\\'<\\'u\\'>\\'f\\'r\\\\\\'\\\\\\\\\\\\\\{\\\\\\'u\\\\\\"
        "'\\\\\\\\\\\\\\}\\\\\\'f\\\\\\'0>2\\\\\\'\\''}", triple_nested_vector);
    // This will print
    //  Formatted triple nested vector with element format specifier:
    //  [([<[{01}, {02}, {03}]>, <[{04}, {05}, {06}]>, <[{07}, {08}, {09}]>]),
    //   ([<[{10}, {11}, {12}]>, <[{13}, {14}, {15}]>, <[{16}, {17}, {18}]>]),
    //   ([<[{19}, {20}, {21}]>, <[{22}, {23}, {24}]>, <[{25}, {26}, {27}]>])]
    // Is that satisfying?  I hope so, because, debugging this was a trajedy
    // of its own

    // So, what the heck is going on here?  Let me break it down
    // First, let's escape the C++ escapes (\\ -> \)
    //  r'('u')'f'r\'<\'u\'>\'f\'r\\\'\\\\\\\{\\\'u\\\'\\\\\\\}\\\'f\\\'0>2\\\'\''
    // Let's isolate the format for the top-level formatter
    //  r\'<\'u\'>\'f\'r\\\'\\\\\\\{\\\'u\\\'\\\\\\\}\\\'f\\\'0>2\\\'\'
    // And escape characters
    //  r'<'u'>'f'r\'\\\{\'u\'\\\}\'f\'0>2\''
    // This is the format for the second-level formatter
    // Let's isolate the format for second-level formatter
    //  r\'\\\{\'u\'\\\}\'f\'0>2\'
    // And escape characters
    //  r'\{'u'\}'f'0>2'
    // This is the format for the third-level formatter
    // Let's isolate the format for third-level formatter
    //  0>2
    // This is the format for the elements
    // And there you have it.  But I have one question for you,
    // would you do it?  I hope not, you better use whatever the default is
    // at this point

    // Ok let me show you the "default" format for the triple nested container
    std::println("Formatted triple nested vector: {}", triple_nested_vector);
    // This will print
    //  Formatted triple nested vector:
    //  [[[1, 2, 3], [4, 5, 6], [7, 8, 9]],
    //  [[10, 11, 12], [13, 14, 15], [16, 17, 18]],
    //  [[19, 20, 21], [22, 23, 24], [25, 26, 27]]]
    // Look how much cleaner that is
}

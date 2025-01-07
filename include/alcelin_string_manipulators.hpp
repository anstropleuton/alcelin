/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Functionality to manipulate and format strings.
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

#pragma once

#include <cctype>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <string>
#include <type_traits>
#include <vector>

#include "alcelin_container_utilities.hpp"

/**
 *  @brief  All Alcelin's contents in this namespace.  Just do
 *          `using namespace alcelin` to make your life easier.
 */
namespace alcelin {

/**
 *  @brief  String Manipulators.
 */
namespace sm {

/**
 *  @brief  A container of strings compatible for String Manipulators.
 *
 *  A container that is CU Compatible with elements type being @c std::string or
 *  @c std::string_view .
 *
 *  @tparam  container  The container type.
 */
template<typename container>
concept sm_compatible = cu::cu_compatible<container>
    && (std::is_same_v<cu::value_type<container>, std::string>
     || std::is_same_v<cu::value_type<container>, std::string_view>);

/**
 *  @brief  Many String Manipulators return this type.
 */
using result_string_nested = std::vector<std::string>;

/**
 *  @brief  Convert a container to comma separated string.
 *
 *  @tparam  container  A compatible container type.
 *  @tparam  converter  The type of element stringify function.
 *  @param   ctr        A container.
 *  @param   conv       Element conversion function.
 *  @param   separator  The separator between elements (optional).
 *  @param   prefix     The prefix to the element (optional).
 *  @param   suffix     The suffix to the element (optional).
 *  @return  String representation of all elements.
 *
 *  @note  The string is comma AND space separated by default.
 */
template<cu::cu_compatible container, typename converter>
requires(!std::is_same_v<converter, std::string>)
[[nodiscard]] inline constexpr auto to_string(
    const container &ctr,
    converter        conv,
    std::string_view separator = ", ",
    std::string_view prefix    = "",
    std::string_view suffix    = ""
)
{
    auto transformer = [&](const cu::value_type<container> &element)
    {
        ///  @todo  Remove this cast when C++26 comes out.
        return std::string(prefix) + conv(element) + std::string(suffix);
    };

    return std::views::transform(ctr, transformer)
         | std::views::join_with(std::string(separator))
         | std::ranges::to<std::string>();
}

/**
 *  @brief  Convert a container to comma separated string.
 *
 *  @tparam  container  A compatible container type.
 *  @param   ctr        A container.
 *  @param   separator  The separator between elements (optional).
 *  @param   prefix     The prefix to the element (optional).
 *  @param   suffix     The suffix to the element (optional).
 *  @return  String representation of all elements.
 *
 *  @note  The string is comma AND space separated by default.
 */
template<cu::cu_compatible container>
[[nodiscard]] inline constexpr auto to_string(
    const container &ctr,
    std::string_view separator = ", ",
    std::string_view prefix    = "",
    std::string_view suffix    = ""
)
{
    return to_string<container, std::string (*)(cu::value_type<container>)>(
        ctr, std::to_string, separator, prefix, suffix);
}

/**
 *  @brief  Convert a container of char to string with single-quoted elements
 *          separated by comma.
 *
 *  @tparam  container  A compatible container type.
 *  @param   ctr        A container.
 *  @param   separator  The separator between elements (optional).
 *  @param   prefix     The prefix to the element (optional).
 *  @param   suffix     The suffix to the element (optional).
 *  @return  String representation of all elements.
 *
 *  @note  The string is comma AND space separated by default.
 */
template<cu::cu_compatible container>
requires std::is_same_v<cu::value_type<container>, char>
[[nodiscard]] inline constexpr auto to_string(
    const container &ctr,
    std::string_view separator = ", ",
    std::string_view prefix    = "\'",
    std::string_view suffix    = "\'"
)
{
    auto converter = [&](const cu::value_type<container> &element)
    {
        return std::string(1, element);
    };

    return to_string(ctr, converter, separator, prefix, suffix);
}

/**
 *  @brief  Convert a container of @c std::string to string with double-quoted
 *          elements separated by comma.
 *
 *  @tparam  container  A compatible container type.
 *  @param   ctr        A container.
 *  @param   separator  The separator between elements (optional).
 *  @param   prefix     The prefix to the element (optional).
 *  @param   suffix     The suffix to the element (optional).
 *  @return  String representation of all elements.
 *
 *  @note  The string is comma AND space separated by default.
 */
template<cu::cu_compatible container>
requires std::is_same_v<cu::value_type<container>, std::string>
[[nodiscard]] inline constexpr auto to_string(
    const container &ctr,
    std::string_view separator = ", ",
    std::string_view prefix    = "\"",
    std::string_view suffix    = "\""
)
{
    return to_string(ctr, std::identity {}, separator, prefix, suffix);
}

/**
 *  @brief  Convert a container of char to a regular string.
 *
 *  @tparam  container  A compatible container type with char element type.
 *  @param   ctr        A container.
 *  @return  String of all chars.
 */
template<cu::cu_compatible container>
requires std::is_same_v<cu::value_type<container>, char>
[[nodiscard]] inline constexpr auto chars_to_string(const container &ctr)
{
    return std::string(std::begin(ctr), std::end(ctr));
}

/**
 *  @brief  Convert a character to a string.
 *
 *  @param  character  A character.
 *  @return  String of one character.
 */
[[nodiscard]] inline constexpr auto to_string(char character)
{
    // Maybe pretty useless after all
    return std::string(1, character);
}

/**
 *  @brief  Word-wrap a string at width or before width depending on the delim.
 *
 *  The string is tried to be split at the width if the character at the width
 *  is one of the delimiter.  If not, the split occurs at the character before
 *  the width that is one of the delimiter.  This process is repeated until the
 *  string is less than the size of width.  If a word is longer than the
 *  specified width, the word is kept as is.  If you use force, the word will be
 *  split.
 *
 *  @param  string  A string to word-wrap.
 *  @param  width   The max word-wrap width.
 *  @param  force   Whether to force the string to always be less than or equal
 *                  to the width (optional).
 *  @param  delims  The delimiters, usually whitespace (optional).
 *  @return  @c result_string_nested of word-wrapped lines.
 *
 *  @note  word-wrapped lines can be larger than width.
 */
[[nodiscard]] inline constexpr auto word_wrap(
    std::string_view string,
    std::size_t      width,
    bool             force = false,
    std::string_view delims = " \t\r\n\f\v\b"
)
{
    result_string_nested lines = {};

    // Functions expect inclusive width, and also works as a measure to have at
    // least one as width (as a side effect)
    width++;

    while (string.size() > width)
    {
        // First non-delim character before or at width
        auto pos = string.substr(0, width).find_last_of(delims);
        if (pos == std::string_view::npos)
        {
            // Split without consuming character
            if (force)
            {
                pos       = string.substr(0, width).size() - 1;
                auto line = string.substr(0, pos);
                string    = string.substr(pos);
                lines.emplace_back(std::string(line));
                continue;
            }

            // If not, first non-delim character after width
            pos = string.substr(width + 1).find_first_of(delims);

            // If still not, eof reached?  Prevent overflow
            if (pos == std::string_view::npos) pos--;
            else pos += width + 1;
        }

        auto line = string.substr(0, pos);
        string    = string.substr(pos + 1);
        lines.emplace_back(std::string(line));
    }

    if (!string.empty())
    {
        lines.emplace_back(std::string(string));
    }

    return lines;
}

/**
 *  @brief  Trim a string (only from left side) using delimiters (usually
 *          whitespace).
 *
 *  @param  string  A string to trim from left.
 *  @param  delims  The delimiters, usually whitespace (optional).
 *  @return  Trimmed string.
 */
[[nodiscard]] inline constexpr auto trim_left(
    std::string_view string,
    std::string_view delims = " \t\r\n\f\v\b"
)
{
    auto pos = string.find_first_not_of(delims);
    if (pos == std::string_view::npos)
    {
        return string;
    }
    return string.substr(pos);
}

/**
 *  @brief  Trim a string (only from right side) using delimiters (usually
 *          whitespace).
 *
 *  @param  string  A string to trim from right.
 *  @param  delims  The delimiters, usually whitespace (optional).
 *  @return  Trimmed string.
 */
[[nodiscard]] inline constexpr auto trim_right(
    std::string_view string,
    std::string_view delims = " \t\r\n\f\v\b"
)
{
    auto pos = string.find_last_not_of(delims);
    if (pos == std::string_view::npos)
    {
        return string;
    }
    return string.substr(0, pos + 1);
}

/**
 *  @brief  Trim a string using delimiters (usually whitespace).
 *
 *  @param  string  A string to trim.
 *  @param  delims  The delimiters, usually whitespace (optional).
 *  @return  Trimmed string.
 */
[[nodiscard]] inline constexpr auto trim(
    std::string_view string,
    std::string_view delims = " \t\r\n\f\v\b"
)
{
    return trim_left(trim_right(string, delims), delims);
}

/**
 *  @brief  Convert string to uppercase.
 *
 *  @param  string  A string to convert.
 *  @return  Uppercase string.
 */
[[nodiscard]] inline constexpr auto to_upper(std::string_view string)
{
    std::string str;
    std::ranges::transform(string, std::back_inserter(str), ::toupper);
    return str;
}

/**
 *  @brief  Convert string to lowercase.
 *
 *  @param  string  A string to convert.
 *  @return  Lowercase string.
 */
[[nodiscard]] inline constexpr auto to_lower(std::string_view string)
{
    std::string str;
    std::ranges::transform(string, std::back_inserter(str), ::tolower);
    return str;
}

/**
 *  @brief  Convert character to uppercase (exists for consistency).
 *
 *  @param  character  A character to convert.
 *  @return  Uppercase character.
 */
[[nodiscard]] inline constexpr auto to_upper(char character)
{
    return ::toupper(character);
}

/**
 *  @brief  Convert character to lowercase (exists for consistency).
 *
 *  @param  character  A character to convert.
 *  @return  Lowercase character.
 */
[[nodiscard]] inline constexpr auto to_lower(char character)
{
    return ::tolower(character);
}

/**
 *  @brief  Compare string, case insensitivity.
 *
 *  @param  a  The first string.
 *  @param  b  The second string.
 *  @return  True if they are equal, case insensitively.
 */
[[nodiscard]] inline constexpr auto is_equal_ins(
    std::string_view a,
    std::string_view b
)
{
    // Either of them will do...
    return to_lower(a) == to_lower(b);
}

/**
 *  @brief  Compare character, case insensitivity (exists for consistency).
 *
 *  @param  a  The first character.
 *  @param  b  The second character.
 *  @return  True if they are equal, case insensitively.
 */
[[nodiscard]] inline constexpr auto is_equal_ins(char a, char b)
{
    // Either of them will do...
    return ::tolower(a) == ::tolower(b);
}

/**
 *  @brief  Filter out the occurrences of sequence from the string.
 *
 *  @param  string   A string.
 *  @param  pattern  A sequence to remove.
 *  @return  Filtered string as @c std::string .
 *
 *  @see  cu::filter_out_seq.
 */
[[nodiscard]] inline constexpr auto filter_out_seq(
    std::string_view string,
    std::string_view pattern
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    std::vector<char> values_vec(pattern.begin(), pattern.end());
    return sm::chars_to_string(cu::filter_out_seq(string_vec, values_vec));
}

/**
 *  @brief  Filter out the occurrences of any of characters from the string.
 *
 *  @param  string      A string.
 *  @param  characters  The characters to remove.
 *  @return  Filtered string as @c std::string .
 *
 *  @see  cu::filter_out_occ.
 */
[[nodiscard]] inline constexpr auto filter_out_occ(
    std::string_view string,
    std::string_view characters
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    std::vector<char> values_vec(characters.begin(), characters.end());
    return sm::chars_to_string(cu::filter_out_occ(string_vec, values_vec));
}

/**
 *  @brief  Filter out the occurrences of any of sequences from the string.
 *
 *  @tparam  strings   A CU compatible container with string elements.
 *  @param   string    A string.
 *  @param   patterns  The sequences to remove.
 *  @return  Filtered string as @c std::string .
 *
 *  @see  cu::filter_out_occ_seq.
 */
template<sm_compatible strings>
[[nodiscard]] inline constexpr auto filter_out_occ_seq(
    std::string_view string,
    const strings   &patterns
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    std::vector<std::vector<char>> patterns_vec = {};
    for (auto &pattern : patterns)
    {
        patterns_vec.emplace_back(pattern.begin(), pattern.end());
    }
    return sm::chars_to_string(cu::filter_out_occ_seq(string_vec,
        patterns_vec));
}

/**
 *  @brief  Filter out the occurrences of character from the string.
 *
 *  @param  string     A string.
 *  @param  character  A character to remove.
 *  @return  Filtered string as @c std::string .
 *
 *  @see  cu::filter_out.
 */
[[nodiscard]] inline constexpr auto filter_out(
    std::string_view string,
    char             character
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::filter_out(string_vec, character));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view string,
    std::size_t      n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view string,
    int              n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view string,
    unsigned         n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view string,
    long             n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view string,
    long long        n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view   string,
    unsigned long long n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view string,
    long double      n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view string,
    float            n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  cu::repeat.
 */
[[nodiscard]] inline constexpr auto repeat(
    std::string_view string,
    double           n
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    return sm::chars_to_string(cu::repeat(string_vec, n));
}

/**
 *  @brief  Split the string with pattern.
 *
 *  @param  string   A string.
 *  @param  pattern  A pattern to split with.
 *  @return  Split string as @c result_string_nested .
 *
 *  @see  cu::split_seq.
 */
[[nodiscard]] inline constexpr auto split_seq(
    std::string_view string,
    std::string_view pattern
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    std::vector<char> pattern_vec(pattern.begin(), pattern.end());
    auto result = cu::split_seq(string_vec, pattern_vec);
    return std::views::transform(result, sm::chars_to_string<std::vector<char>>)
         | std::ranges::to<result_string_nested>();
}

/**
 *  @brief  Split the string with occurrences of value.
 *
 *  @param  string      A string.
 *  @param  characters  The characters to split with.
 *  @return  Split string as @c result_string_nested .
 *
 *  @see  cu::split_occ.
 */
[[nodiscard]] inline constexpr auto split_occ(
    std::string_view string,
    std::string_view characters
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    std::vector<char> pattern_vec(characters.begin(), characters.end());
    auto result = cu::split_occ(string_vec, pattern_vec);
    return std::views::transform(result, sm::chars_to_string<std::vector<char>>)
         | std::ranges::to<result_string_nested>();
}

/**
 *  @brief  Split the string with occurrences of any of pattern.
 *
 *  @tparam  strings   A CU compatible string with string elements.
 *  @param   string    A string.
 *  @param   patterns  The patterns to split with.
 *  @return  Split string as @c result_string_nested .
 *
 *  @see  cu::split_occ_seq.
 */
template<sm_compatible strings>
[[nodiscard]] inline constexpr auto split_occ_seq(
    std::string_view string,
    const strings   &patterns
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    std::vector<std::vector<char>> patterns_vec = {};
    for (auto &pattern : patterns)
    {
        patterns_vec.emplace_back(pattern.begin(), pattern.end());
    }
    auto result = cu::split_occ_seq(string_vec, patterns_vec);
    return std::views::transform(result, sm::chars_to_string<std::vector<char>>)
         | std::ranges::to<result_string_nested>();
}

/**
 *  @brief  Split the string with value.
 *
 *  @param   string  A string.
 *  @param   value   A value to split with.
 *  @return  Split string as @c result_container_nested .
 *
 *  @see  cu::split.
 */
[[nodiscard]] inline constexpr auto split(
    std::string_view string,
    char             character
)
{
    std::vector<char> string_vec(string.begin(), string.end());
    auto result = cu::split(string_vec, character);
    return std::views::transform(result, sm::chars_to_string<std::vector<char>>)
         | std::ranges::to<result_string_nested>();
}

} // namespace sm

/**
 *  @brief  String Manipulators, operators version.
 */
namespace sm_operators {

/**
 *  @brief  Filter out the occurrences of sequence from the string.
 *
 *  @param  string   A string.
 *  @param  pattern  A sequence to remove.
 *  @return  Filtered string as @c std::string .
 *
 *  @see  sm::filter_out_seq.
 */
[[nodiscard]] inline constexpr auto operator- (
    std::string_view string,
    std::string_view pattern
)
{
    return sm::filter_out_seq(string, pattern);
}

/**
 *  @brief  Filter out the occurrences of character from the string.
 *
 *  @param  string     A string.
 *  @param  character  A character to remove.
 *  @return  Filtered string as @c std::string .
 *
 *  @see  sm::filter_out.
 */
[[nodiscard]] inline constexpr auto operator- (
    std::string_view string,
    char             character
)
{
    return sm::filter_out(string, character);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    std::size_t      n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    int              n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    unsigned         n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    long             n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    long long        n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view   string,
    unsigned long long n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    long double      n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    float            n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Repeat string @c n times.
 *
 *  @param  string  A string.
 *  @param  n       The number of times to repeat.
 *  @return  Repeated string as @c std::string .
 *
 *  @see  sm::repeat.
 */
[[nodiscard]] inline constexpr auto operator* (
    std::string_view string,
    double           n
)
{
    return sm::repeat(string, n);
}

/**
 *  @brief  Split the string with pattern.
 *
 *  @param  string   A string.
 *  @param  pattern  A pattern to split with.
 *  @return  Split string as @c sm::result_string_nested .
 *
 *  @see  sm::split_seq.
 */
[[nodiscard]] inline constexpr auto operator/ (
    std::string_view string,
    std::string_view pattern
)
{
    return sm::split_seq(string, pattern);
}

/**
 *  @brief  Split the string with value.
 *
 *  @param   string  A string.
 *  @param   value   A value to split with.
 *  @return  Split string as @c result_container_nested .
 *
 *  @see  sm::split.
 */
[[nodiscard]] inline constexpr auto operator/ (
    std::string_view string,
    char             character
)
{
    return sm::split(string, character);
}

} // namespace sm_operators

} // namespace alcelin

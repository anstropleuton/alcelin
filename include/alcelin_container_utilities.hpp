/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   General functionality for container types with operators.
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

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

/**
 *  @brief  All Alcelin's contents in this namespace.
 */
namespace alcelin {

/**
 *  @brief  Copper...?  No wait, Container Utilities.
 */
namespace cu {

/**
 *  @brief   Container compatible for Container Utilities.
 *
 *  Container type must have @c begin() and @c end() in either member or
 *  free-standing function which return contiguous iterators, and a
 *  @c value_type member.
 *
 *  @tparam  container  Container type.
 */
template<typename container>
concept cu_compatible = requires {
    { container().begin() } -> std::contiguous_iterator;
    { container().end() } -> std::contiguous_iterator;
    { std::declval<typename container::value_type>() };
};

/**
 *  @brief   Container's value_type member.
 *  @tparam  container  Compatible container type.
 */
template<cu_compatible container>
using value_type = container::value_type;

/**
 *  @brief   Many Container Utilities return this container.
 *  @tparam  container  Compatible container type.
 */
template<cu_compatible container>
using result_container = std::vector<value_type<container>>;

/**
 *  @brief   Many Container Utilities return this container if the result is
 *           nested.
 *  @tparam  container  Compatible container type.
 */
template<cu_compatible container>
using result_container_nested = std::vector<std::vector<value_type<container>>>;

/**
 *  @brief   Nested container compatible for Container Utilities.
 *
 *  The container and it's value type must satisfy @c cu_compatible .
 *
 *  @tparam  container  Container type.
 */
template<typename container>
concept cu_compatible_nested =
    cu_compatible<container>
 && cu_compatible<value_type<container>>;

/**
 *  @brief   Container Utilities compatible enumerator for @c enumerated_array .
 *
 *  The type must be an enumerator with a @c max as a member.  The @c max member
 *  must be the largest member in the enumerator (Implementation pending).
 *
 *  @tparam  enum_type  Enumerator type.
 *
 *  @todo    After reflection support is introduced, iterate over all the
 *           members and determine that the @c max member is the largest member.
 */
template<typename enum_type>
concept cu_compatible_enum = std::is_enum_v<enum_type> &&
                             requires { { enum_type::max }; };

/**
 *  @brief   Integral constant for the enumerator's @c max member.
 *  @tparam  enum_type  Container Utilities compatible enumerator type.
 */
template<cu_compatible_enum enum_type>
struct enum_max : std::integral_constant<std::underlying_type_t<enum_type>,
        std::to_underlying (enum_type::max)> {};

/**
 *  @brief   Helper to get the value of the enumerator's @c max member.
 *  @tparam  enum_type  Container Utilities compatible enumerator type.
 */
template<cu_compatible_enum enum_type>
inline constexpr auto enum_max_v = enum_max<enum_type>::value;

/**
 *  @brief   Get the subset of the container's elements.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   first      First index (inclusive).
 *  @param   last       Last index (exclusive).
 *  @return  Subset of the container as @c result_container .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto subordinate(
    const container &ctr,
    std::size_t      first,
    std::size_t      last
)
{
    return result_container<container>(
        ctr.begin() + first,
        ctr.begin() + last);
}

/**
 *  @brief   Copy containers into one container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr_a      First container.
 *  @param   ctr_b      Second container.
 *  @return  Combined container as @c result_container .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto combine(
    const container &ctr_a,
    const container &ctr_b
)
{
    return result_container_nested<container> {
        result_container<container>(ctr_a.begin(), ctr_a.end()),
        result_container<container>(ctr_b.begin(), ctr_b.end())
    } | std::views::join
      | std::ranges::to<result_container<container>>();
}

/**
 *  @brief   Copy container and value into one container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   value      Value of container's value type.
 *  @return  Value-appended container as @c result_container .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto combine(
    const container             &ctr,
    const value_type<container> &value
)
{
    return combine(ctr, result_container<container> { value });
}

/**
 *  @brief   Filter out the occurrences of sequence from the container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   pattern    Sequence to remove.
 *  @return  Filtered container as @c result_container .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto filter_out_seq(
    const container &ctr,
    const container &pattern
)
{
    return std::views::split(ctr, pattern)
         | std::views::join
         | std::ranges::to<result_container<container>>();
}

/**
 *  @brief   Filter out the occurrences of any of values from the container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   values     Elements to remove.
 *  @return  Filtered container as @c result_container .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto filter_out_occ(
    const container &ctr,
    const container &values
)
{
    auto filterer = [&](const cu::value_type<container> &element) {
        return std::ranges::find(values, element) == values.end();
    };

    return std::views::filter(ctr, filterer)
         | std::ranges::to<result_container<container>>();
}

/**
 *  @brief   Filter out the occurrences of any of sequences from the container.
 *
 *  @tparam  container         Compatible container type.
 *  @tparam  nested_container  Compatible nested container type.
 *  @param   ctr               Container.
 *  @param   patterns          Sequences to remove.
 *  @return  Filtered container as @c result_container .
 */
template<cu_compatible container, cu_compatible_nested nested_container>
[[nodiscard]] inline constexpr auto filter_out_occ_seq(
    const container        &ctr,
    const nested_container &patterns
)
{
    result_container<container> result = ctr;
    for (auto &pattern : patterns)
    {
        result = filter_out_seq(result, pattern);
    }
    return result;
}

/**
 *  @brief   Filter out the occurrences of value from the container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   value      Value to remove.
 *  @return  Filtered container as @c result_container .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto filter_out(
    const container             &ctr,
    const value_type<container> &value
)
{
    return filter_out_seq(ctr, result_container<container> { value });
}

/**
 *  @brief   Repeat container @c n times.
 *
 *  @tparam  container  Compatible container type.
 *  @tparam  count      Integral type for repeat count.
 *  @param   ctr        Container.
 *  @param   n          Number of times to repeat.
 *  @return  Repeated container as @c result_container .
 */
template<cu_compatible container, typename count>
requires(std::is_integral_v<count> && !std::is_floating_point_v<count>)
[[nodiscard]] inline constexpr auto repeat(
    const container &ctr,
    count            n
)
{
    return std::views::repeat(ctr, n)
         | std::views::join
         | std::ranges::to<result_container<container>>();
}

/**
 *  @brief   Repeat container @c n times.
 *
 *  Considering integer part of the number @c n as @c i, and fraction part as
 *  @c f. The container is repeated @c i.0 times, and then the container is
 *  added with subordinate container with `floor(0.f * container.size())`
 *  elements from the beginning.
 *
 *  @tparam  container  Compatible container type.
 *  @tparam  count      Floating type for repeat count.
 *  @param   ctr        Container.
 *  @param   n          Number of times to repeat.
 *  @return  Repeated container as @c result_container .
 *
 *  @note    This is scuffed.
 */
template<cu_compatible container, typename count>
requires(!std::is_integral_v<count> && std::is_floating_point_v<count>)
[[nodiscard]] inline constexpr auto repeat(
    const container &ctr,
    count            n
)
{
    // Performance-critical, don't use exceptions
    if (n < 0.0l) n = 0.0l;

    count       i_part         = 0.0l;
    count       f_part         = std::modf(n, &i_part);
    std::size_t regular_repeat = i_part;
    std::size_t sub_size       = std::floor(f_part * ctr.size());
    container   sub = subordinate(ctr, 0, sub_size);

    return combine(repeat(ctr, regular_repeat), sub);
}

/**
 *  @brief   Split the container with pattern.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   pattern    Pattern to split with.
 *  @return  Split container as @c result_container_nested .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto split_seq(
    const container &ctr,
    const container &pattern
)
{
    return std::views::split(ctr, pattern)
         | std::ranges::to<result_container_nested<container>>();
}

/**
 *  @brief   Split the container with occurrences of value.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   values     Values to split with.
 *  @return  Split container as @c result_container_nested .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto split_occ(
    const container &ctr,
    const container &values
)
{
    // Couldn't find standard library to do this heavy job, so...
    result_container_nested<container> result;
    auto it = ctr.begin();

    while (it != ctr.end())
    {
        auto next_it = std::find_first_of(it, ctr.end(), values.begin(),
            values.end());
        result.emplace_back(result_container<container>(it, next_it));
        it = next_it;
        if (it != ctr.end()) ++it;
    }

    return result;
}

/**
 *  @brief   Split the container with occurrences of any of pattern.
 *
 *  @tparam  container        Compatible container type.
 *  @tparam  nested_container  Compatible container type nested container type.
 *  @param   ctr              Container.
 *  @param   patterns         Patterns to split with.
 *  @return  Split container as @c result_container_nested .
 */
template<cu_compatible container, cu_compatible_nested nested_container>
[[nodiscard]] inline constexpr auto split_occ_seq(
    const container        &ctr,
    const nested_container &patterns
)
{
    // Again couldn't find standard library to do this heavy job, so...
    result_container_nested<container> result;
    auto it = ctr.begin();

    while (it != ctr.end())
    {
        auto        next_it      = ctr.end();
        std::size_t pattern_size = (std::size_t)-1;
        for (auto &pattern : patterns)
        {
            // Use std::search instead of std::find_first_of to find sequence
            auto tmp = std::search(it, ctr.end(), pattern.begin(),
                pattern.end());

            if (next_it > tmp)
            {
                next_it      = tmp;
                pattern_size = pattern.size();
            }
        }

        result.emplace_back(result_container<container>(it, next_it));
        it = next_it;
        if (it != ctr.end()) it += pattern_size;
    }

    return result;
}

/**
 *  @brief   Split the container with value.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   value      Value to split with.
 *  @return  Split container as @c result_container_nested .
 */
template<cu_compatible container>
[[nodiscard]] inline constexpr auto split(
    const container             &ctr,
    const value_type<container> &value
)
{
    return split_seq(ctr, result_container<container> { value });
}

} // namespace cu

/**
 *  @brief  Container Utilities, operators version.
 */
namespace cu_operators {

/**
 *  @brief   Copy containers into one container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr_a      First container.
 *  @param   ctr_b      Second container.
 *  @return  Combined container as @c result_container .
 *
 *  @see     cu::combine.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
[[nodiscard]] inline constexpr auto operator+ (
    const container &ctr_a,
    const container &ctr_b
)
{
    return cu::combine(ctr_a, ctr_b);
}

/**
 *  @brief   Copy container and value into one container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   value      Value of container's value type.
 *  @return  Value-appended container as @c result_container .
 *
 *  @see     cu::combine.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
[[nodiscard]] inline constexpr auto operator+ (
    const container                 &ctr_a,
    const cu::value_type<container> &value
)
{
    return cu::combine(ctr_a, value);
}

/**
 *  @brief   Filter out the occurrences of sequence from the container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   pattern    Sequence to remove.
 *  @return  Filtered container as @c result_container .
 *
 *  @note    Use String Manipulators' operators for @c std::string or
 *           @c std::basic_string_view .
 *
 *  @see     cu::filter_out_seq.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
[[nodiscard]] inline constexpr auto operator- (
    const container &ctr,
    const container &pattern
)
{
    return cu::filter_out_seq(ctr, pattern);
}

/**
 *  @brief   Filter out the occurrences of value from the container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   value      Value to remove.
 *  @return  Filtered container as @c result_container .
 *
 *  @note    Use String Manipulators' operators for @c std::string or
 *           @c std::basic_string_view .
 *
 *  @see     cu::filter_out.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
[[nodiscard]] inline constexpr auto operator- (
    const container                 &ctr,
    const cu::value_type<container> &value
)
{
    return cu::filter_out(ctr, value);
}

/**
 *  @brief   Repeat container @c n times.
 *
 *  @tparam  container  Compatible container type.
 *  @tparam  count      Integral or floating type for repeat count.
 *  @param   ctr        Container.
 *  @param   n          Number of times to repeat.
 *  @return  Repeated container as @c result_container .
 *
 *  @note    Use String Manipulators' operators for @c std::string or
 *           @c std::basic_string_view .
 *
 *  @see     cu::repeat.
 */
template<cu::cu_compatible container, typename count>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
[[nodiscard]] inline constexpr auto operator* (
    const container &ctr,
    count            n
)
{
    return cu::repeat(ctr, n);
}

/**
 *  @brief   Split the container with pattern.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   pattern    Pattern to split with.
 *  @return  Split container as @c result_container_nested .
 *
 *  @note    Use String Manipulators' operators for @c std::string or
 *           @c std::basic_string_view .
 *
 *  @see     cu::split_seq.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
[[nodiscard]] inline constexpr auto operator/ (
    const container &ctr,
    const container &pattern
)
{
    return cu::split_seq(ctr, pattern);
}

/**
 *  @brief   Split the container with value.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   value      Value to split with.
 *  @return  Split container as @c result_container_nested .
 *
 *  @note    Use String Manipulators' operators for @c std::string or
 *           @c std::basic_string_view .
 *
 *  @see     cu::split.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
[[nodiscard]] inline constexpr auto operator/ (
    const container                 &ctr,
    const cu::value_type<container> &value
)
{
    return cu::split(ctr, value);
}

/**
 *  @brief   Copy second container at the end of first container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr_a      First container.
 *  @param   ctr_b      Second container.
 *  @return  Combined container as @c result_container .
 *
 *  @see     cu::combine.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
inline constexpr auto operator+= (
    container       &ctr_a,
    const container &ctr_b
) -> container &
{
    ctr_a = ctr_a + ctr_b;
    return ctr_a;
}

/**
 *  @brief   Copy value at the end of first container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   value      Value of container's value type.
 *  @return  Value-appended container as @c result_container .
 *
 *  @see     cu::combine.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
inline constexpr auto operator+= (
    container                       &ctr_a,
    const cu::value_type<container> &value
) -> container &
{
    ctr_a = ctr_a + value;
    return ctr_a;
}

/**
 *  @brief   Filter out the occurrences of sequence from the container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   pattern    Sequence to remove.
 *  @return  Filtered container as @c result_container .
 *
 *  @note    Use String Manipulators' operators for @c std::string or
 *           @c std::basic_string_view .
 *
 *  @see     cu::filter_out_seq.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
inline constexpr auto operator-= (
    container       &ctr,
    const container &pattern
) -> container &
{
    ctr = ctr - pattern;
    return ctr;
}

/**
 *  @brief   Filter out the occurrences of value from the container.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   value      Value to remove.
 *  @return  Filtered container as @c result_container .
 *
 *  @note    Use String Manipulators' operators for @c std::string or
 *           @c std::basic_string_view .
 *
 *  @see     cu::filter_out.
 */
template<cu::cu_compatible container>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
inline constexpr auto operator-= (
    container                       &ctr,
    const cu::value_type<container> &value
) -> container &
{
    ctr = ctr - value;
    return ctr;
}

/**
 *  @brief   Repeat container @c n times.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   n          Number of times to repeat.
 *  @return  Repeated container as @c result_container .
 *
 *  @note    Use String Manipulators' operators for @c std::string or
 *           @c std::basic_string_view .
 *
 *  @see     cu::repeat.
 */
template<cu::cu_compatible container, typename count>
requires(!std::is_same_v<container, std::string>
      && !std::is_same_v<container, std::string_view>)
inline constexpr auto operator*= (
    container &ctr,
    count      n
) -> container &
{
    ctr = ctr * n;
    return ctr;
}

} // namespace cu_operators

} // namespace alcelin

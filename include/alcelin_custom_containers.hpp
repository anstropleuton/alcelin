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

#include <array>
#include <concepts>
#include <format>
#include <initializer_list>
#include <span>

#include "alcelin_container_utilities.hpp"

/**
 *  @brief  All Alcelin's contents in this namespace.
 */
namespace alcelin {

/**
 *  @brief  Custom Containers.
 */
namespace cc {

/**
 *  @brief   Compatible container for @c boundless_access.
 *
 *  The container must satisfy @c cu_compatible and it's value type should also
 *  assignable with default constructed value type.
 *
 *  @tparam  container  Container type.
 */
template<typename container>
concept boundless_accessible = cu::cu_compatible<container>
    && requires(cu::value_type<container> value) {
    { value = {} };
    { *(container().begin()) } -> std::same_as<cu::value_type<container> &>;
};

/**
 *  @brief   Return element at index, or a default-constructed instance of the
 *           value type if the index is invalid.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   index      Index specifying element.
 *  @return  Element at index or default constructed instance of type.
 */
template<cu::cu_compatible Container>
[[nodiscard]] inline constexpr auto boundless_access(
    const Container &container,
    std::size_t      index
)
{
    if (index >= container.size()) return cu::value_type<Container>();
    return *(container.begin() + index);
}

/**
 *  @brief   Return element at index, or a default-constructed instance of the
 *           value type if the index is invalid.
 *
 *  @tparam  container  Compatible container type.
 *  @param   ctr        Container.
 *  @param   index      Index specifying element.
 *  @return  Element at index or default constructed instance of type.
 *
 *  @note    Do NOT modify the element if the index is invalid.  The modified
 *           change is not stored and is immediately reset after next function
 *           call of the type.
 */
template<boundless_accessible Container>
[[nodiscard]] inline constexpr auto boundless_access(
    Container  &container,
    std::size_t index
) -> cu::value_type<Container> &
{
    static cu::value_type<Container> value;

    // Always initialize to default every time it is accessed
    value = {};
    if (index >= container.size()) return value;
    return *(container.begin() + index);
}

/**
 *  @brief   Boundless version of std::vector.
 *
 *  Index-access of this vector always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  element_type  Type of element.
 *  @tparam  alloc         Allocator type, defaults to @c std::allocator<T> .
 */
template<typename element_type, typename alloc = std::allocator<element_type>>
requires(std::is_default_constructible_v<element_type>)
struct boundless_vector : std::vector<element_type, alloc> {

    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::vector<element_type, alloc>;

    using base::vector;

    /**
     *  @brief  Creates a vector with no elements.
     */
    inline constexpr boundless_vector() = default;

    /**
     *  @brief  Creates a vector with no elements.
     *
     *  @param  allocator  Allocator.
     *  @see    @c std::vector 's constructor for more details.
     */
    explicit inline constexpr boundless_vector(
        const alloc &allocator
    ) noexcept : base(allocator) {}

    /**
     *  @brief  Creates a vector with default constructed elements.
     *
     *  @param  size       Number of elements to initially create.
     *  @param  allocator  Allocator.
     *  @see    @c std::vector 's constructor for more details.
     */
    explicit inline constexpr boundless_vector(
        std::size_t  size,
        const alloc &allocator = alloc()
    ) : base(size, allocator) {}

    /**
     *  @brief  Creates a vector with copies of an exemplar element.
     *
     *  @param  size       Number of elements to initially create.
     *  @param  value      Element to copy.
     *  @param  allocator  Allocator.
     *  @see    @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(
        std::size_t         size,
        const element_type &value,
        const alloc        &allocator = alloc()
    ) : base(size, value, allocator) {}

    /**
     *  @brief  Vector copy constructor.
     *
     *  @param  vector  Other vector to copy from.
     *  @see    @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(const boundless_vector &vector) = default;

    /**
     *  @brief  Vector move constructor.
     *
     *  @param  vector  Other vector to move from.
     *  @see    @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(boundless_vector &&vector)
    noexcept = default;

    /**
     *  @brief  Copy constructor with alternative allocator.
     *
     *  @param  vector     Other vector to copy from.
     *  @param  allocator  Allocator.
     *  @see    @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(
        const boundless_vector &vector,
        const alloc            &allocator
    ) : base((base)vector, allocator) {}

    /**
     *  @brief  Move constructor with alternative allocator.
     *
     *  @param  vector     Other vector to move from.
     *  @param  allocator  Allocator.
     *  @see    @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(
        boundless_vector &&vector,
        const alloc       &allocator
    ) noexcept : base(std::move((base &) vector, allocator)) {}

    /**
     *  @brief  Creates a vector from an initializer list.
     *
     *  @param  list       An @c std::initializer_list .
     *  @param  allocator  Allocator.
     *  @see    @c std::vector 's constructor for more details.
     */
    inline constexpr boundless_vector(
        std::initializer_list<element_type> list,
        const alloc                        &allocator = alloc()
    ) : base(list, allocator) {}

    /**
     *  @brief   Creates a vector from a range.
     *
     *  @tparam  InputIterator  Type of input iterators.
     *  @param   first          Input iterator.
     *  @param   last           Input iterator.
     *  @param   allocator      Allocator.
     *  @see     @c std::vector 's constructor for more details.
     */
    template<std::input_iterator InputIterator>
    inline constexpr boundless_vector(
        InputIterator first,
        InputIterator last,
        const alloc  &allocator = alloc()
    ) : base(first, last, allocator) {}

    /**
     *  @brief  Copy from base vector.
     *  @param  vector  Base vector.
     */
    inline constexpr boundless_vector(const base &vector) : base(vector) {}

    /**
     *  @brief  Move from base vector.
     *  @param  vector  Base vector.
     */
    inline constexpr boundless_vector(base &&vector)
        : base(std::move(vector)) {}

    /**
     *  @brief  Default destructor.
     *  @see    @c std::vector 's destructor for more details.
     */
    inline constexpr ~boundless_vector() = default;

    /**
     *  @brief   Vector assign operator.
     *
     *  @param   vector  Vector of identical element and allocator types.
     *  @return  Reference to self.
     *  @see     @c std::vector 's @c operator= for more details.
     */
    inline constexpr auto operator= (
        const boundless_vector &vector
    ) -> boundless_vector & = default;

    /**
     *  @brief   Vector move assign operator.
     *
     *  @param   vector  Vector of identical element and allocator types.
     *  @return  Reference to self.
     *  @see     @c std::vector 's @c operator= for more details.
     */
    inline constexpr auto operator= (
        boundless_vector &&vector
    ) -> boundless_vector & = default;

    /**
     *  @brief   Vector list assignment operator.
     *
     *  @param   list  Initializer list.
     *  @return  Reference to self.
     *  @see     @c std::vector 's @c operator= for more details.
     */
    inline constexpr auto operator= (
        std::initializer_list<element_type> list
    ) -> boundless_vector &
    {
        return base::operator= (list);
    }

    /**
     *  @brief   Vector base assignment operator.
     *
     *  @param   vector  Base vector.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (const base &vector) -> boundless_vector &
    {
        return base::operator= (vector);
    }

    /**
     *  @brief   Vector base move assignment operator.
     *
     *  @param   vector  Base vector.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (base &&vector) -> boundless_vector &
    {
        return base::operator= (std::move(vector));
    }

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index) -> element_type &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> element_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) -> element_type &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(
        std::size_t index) const -> element_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get the first element, or a default constructed instance of
     *           the value type when the vector is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() -> element_type &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief   Get the first element, or a default constructed instance of
     *           the value type when the vector is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> element_type
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief   Get the last element, or a default constructed instance of
     *           the value type when the vector is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() -> element_type &
    {
        return boundless_access(*this, this->size() - 1);
    }

    /**
     *  @brief   Get the last element, or a default constructed instance of
     *           the value type when the vector is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> element_type
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief   Template parameter deduction guide for @c boundless_vector .
 *
 *  Deduce types from initializer.
 *
 *  @tparam  input_iterator  Type of input iterator.
 *  @tparam  value_type      Type of elements of vector.
 *  @tparam  alloc           Type of an allocator object.
 */
template<std::input_iterator input_iterator,
    typename value_type = std::iterator_traits<input_iterator>::value_type,
    typename alloc = std::allocator<value_type>>
boundless_vector(input_iterator, input_iterator, alloc = alloc())
                          -> boundless_vector<value_type, alloc>;

/**
 *  @brief   Boundless version of std::array.
 *
 *  Index-access of this array always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  element_type  Type of element.
 *  @tparam  count         Size of array.
 */
template<typename element_type, std::size_t count>
requires(std::is_default_constructible_v<element_type>)
struct boundless_array : std::array<element_type, count> {

    // Woah, std::array has no constructors!

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index) -> element_type &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> element_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index) -> element_type &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(
        std::size_t index) const -> element_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get the first element, or a default constructed instance of
     *           the value type when the array is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() -> element_type &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief   Get the first element, or a default constructed instance of
     *           the value type when the array is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> element_type
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief   Get the last element, or a default constructed instance of
     *           the value type when the array is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() -> element_type &
    {
        return boundless_access(*this, this->size() - 1);
    }

    /**
     *  @brief   Get the last element, or a default constructed instance of
     *           the value type when the array is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> element_type
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief   Template parameter deduction guide for @c boundless_array .
 *
 *  Deduce types from initializer.
 *
 *  @tparam  element_type   Type of elements.
 *  @tparam  elements_type  Type of multiple elements in initializer.
 */
template<typename element_type, typename ... elements_type>
requires(std::is_same_v<element_type, elements_type> && ...)
boundless_array(element_type,
    elements_type ...) -> boundless_array<element_type,
    1 + sizeof... (elements_type)>;

/**
 *  @brief   Boundless version of std::span.
 *
 *  Index-access of this span always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  element_type    Type of element.
 *  @tparam  extents         Number of elements in the sequence, or
 *                           @c std::dynamic_extent if dynamic (default).
 */
template<typename element_type, std::size_t extents = std::dynamic_extent>
requires(std::is_default_constructible_v<element_type>)
struct boundless_span : std::span<element_type, extents> {
    using std::span<element_type, extents>::span;

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (std::size_t index)
    const -> element_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get an element at index, or a default constructed instance of
     *           the value type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Element at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(
        std::size_t index) const -> element_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get the first element, or a default constructed instance of
     *           the value type when the span is empty.
     *  @return  First element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> element_type
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief   Get the last element, or a default constructed instance of
     *           the value type when the span is empty.
     *  @return  Last element or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> element_type
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief   Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from raw array.
 *
 *  @tparam  element_type  Type of array elements.
 *  @tparam  count         Number of array elements.
 */
template<typename element_type, std::size_t count>
boundless_span(element_type(&)[count]) -> boundless_span<element_type, count>;

/**
 *  @brief   Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from @c std::array .
 *
 *  @tparam  element_type  Type of array elements.
 *  @tparam  count         Number of array elements.
 */
template<typename element_type, std::size_t count>
boundless_span(std::array<element_type,
    count> &) -> boundless_span<element_type, count>;

/**
 *  @brief   Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from constant @c std::array.
 *
 *  @tparam  element_type  Type of array elements.
 *  @tparam  count         Number of array elements.
 */
template<typename element_type, size_t count>
boundless_span(const std::array<element_type,
    count> &) -> boundless_span<const element_type, count>;

/**
 *  @brief   Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from iterators.
 *
 *  @tparam  iter  Type of iterator.
 *  @tparam  end   Type of end of the iterator.
 */
template<std::contiguous_iterator iter, typename end>
boundless_span(iter, end) -> boundless_span<
    std::remove_reference_t<std::iter_reference_t<iter>>>;

/**
 *  @brief   Template parameter deduction guide for @c boundless_span .
 *
 *  Deduce type from range.
 *
 *  @tparam  range_type  Range type.
 */
template<std::ranges::contiguous_range range_type>
boundless_span(range_type &&) -> boundless_span<
    std::remove_reference_t<std::ranges::range_reference_t<range_type &>>>;

/**
 *  @brief   Boundless version of std::basic_string.
 *
 *  Index-access of this string always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  char_type  Character type.
 *  @tparam  traits     Character traits type.
 *  @tparam  alloc      Allocator type, defaults to @c std::allocator<char_type> .
 */
template<typename char_type, typename traits = std::char_traits<char_type>,
    typename alloc = std::allocator<char_type>>
requires(std::is_default_constructible_v<char_type>)
struct boundless_basic_string : std::basic_string<char_type, traits, alloc> {

    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::basic_string<char_type, traits, alloc>;

    using base::basic_string;

    /**
     *  @brief  Default constructor creates an empty string.
     */
    inline constexpr boundless_basic_string()
    noexcept (std::is_default_constructible_v<alloc>) = default;

    /**
     *  @brief  Create an empty string using allocator.
     *
     *  @param  allocator  Allocator.
     *  @see    @c std::basic_string 's constructor for more details.
     */
    inline constexpr boundless_basic_string(
        const alloc &allocator
    ) noexcept : base(allocator) {}

    /**
     *  @brief  String copy constructor.
     *
     *  @param  string  Other string to copy from.
     *  @see    @c std::basic_string 's constructor for more details.
     */
    inline constexpr boundless_basic_string(
        const boundless_basic_string &string
    ) = default;

    /**
     *  @brief  Creates a string as a copy of a substring.
     *
     *  @param  string     String to copy from.
     *  @param  pos        Index of first character to copy from.
     *  @param  allocator  Allocator.
     */
    inline constexpr boundless_basic_string(
        const boundless_basic_string &string,
        std::size_t                   pos,
        const alloc                  &allocator = alloc()
    ) : base(string, pos, allocator) {}

    /**
     *  @brief  Creates a string as a copy of a substring.
     *
     *  @param  string     String to copy from.
     *  @param  pos        Index of first character to copy from.
     *  @param  n          Number of characters to copy.
     *  @param  allocator  Allocator.
     */
    inline constexpr boundless_basic_string(
        const boundless_basic_string &string,
        std::size_t                   pos,
        std::size_t                   n,
        const alloc                  &allocator = alloc()
    ) : base(string, pos, n, allocator) {}

    /**
     *  @brief  Creates a string initialized by a character array.
     *
     *  @param  string     Character array.
     *  @param  n          Number of characters to copy.
     *  @param  allocator  Allocator.
     */
    inline constexpr boundless_basic_string(
        const char_type *string,
        std::size_t      n,
        const alloc     &allocator = alloc()
    ) : base(string, n, allocator) {}

    /**
     *  @brief  Creates a string initialized by a character array.
     *
     *  @param  string     Null-terminated character array.
     *  @param  allocator  Allocator.
     */
    inline constexpr boundless_basic_string(
        const char_type *string,
        const alloc     &allocator = alloc()
    ) : base(string, allocator) {}

    /**
     *  @brief  Creates a string with multiple characters.
     *
     *  @param  n          Number of characters.
     *  @param  c          Character to use.
     *  @param  allocator  Allocator.
     */
    inline constexpr boundless_basic_string(
        std::size_t  n,
        char_type    c,
        const alloc &allocator
    ) : base(n, c, allocator) {}

    /**
     *  @brief  String move constructor.
     */
    inline constexpr boundless_basic_string(
        boundless_basic_string &&string
    ) noexcept = default;

    /**
     *  @brief  Creates a string from an initializer list.
     *
     *  @param  list       An @c std::initializer_list of characters.
     *  @param  allocator  Allocator.
     */
    inline constexpr boundless_basic_string(
        std::initializer_list<char_type> list,
        const alloc                     &allocator = alloc()
    ) : base(list, allocator) {}

    /**
     *  @brief  Copy constructor with alternative allocator.
     *
     *  @param  string     Other string to copy from.
     *  @param  allocator  Allocator.
     */
    inline constexpr boundless_basic_string(
        const boundless_basic_string &string,
        const alloc                  &allocator
    ) : base(string, allocator) {}

    /**
     *  @brief  Move constructor with alternative allocator.
     *
     *  @param  string     Other string to move from.
     *  @param  allocator  Allocator.
     */
    inline constexpr boundless_basic_string(
        boundless_basic_string &&string,
        const alloc             &allocator
    ) : base(std::move(string), allocator) {}

    /**
     *  @brief   Creates a string from a range.
     *
     *  @tparam  input_iterator  Type of input iterator.
     *  @param   first           Input iterator.
     *  @param   last            Input iterator.
     *  @param   allocator       Allocator.
     */
    template<std::input_iterator input_iterator>
    inline constexpr boundless_basic_string(
        input_iterator first,
        input_iterator last,
        const alloc   &allocator = alloc()
    ) : base(first, last, allocator) {}

    /**
     *  @brief   Creates a string from a substring of a
     *           @c std::basic_string_view .
     *
     *  @tparam  type       Type convertible to @c std::basic_string_view .
     *  @param   value      String to copy from.
     *  @param   pos        Index of the first character to copy from.
     *  @param   n          Number of characters to copy.
     *  @param   allocator  Allocator.
     */
    template<std::convertible_to<std::basic_string_view<char_type>> type>
    inline constexpr boundless_basic_string(
        const type  &value,
        std::size_t  pos,
        std::size_t  n,
        const alloc &allocator = alloc()
    ) : base(value, pos, n, allocator) {}

    /**
     *  @brief   Creates a string from a @c std::basic_string_view .
     *
     *  @tparam  type       Type convertible to @c std::basic_string_view .
     *  @param   value      String to copy from.
     *  @param   allocator  Allocator.
     */
    template<std::convertible_to<std::basic_string_view<char_type>> type>
    inline constexpr boundless_basic_string(
        const type  &value,
        const alloc &allocator = alloc()
    ) : base(value, allocator) {}

    /**
     *  @brief  Copy from base string.
     *  @param  string  Base string.
     */
    inline constexpr boundless_basic_string(const base &string)
        : base(string) {}

    /**
     *  @brief  Move from base string.
     *  @param  string  Base string.
     */
    inline constexpr boundless_basic_string(base &&string)
        : base(std::move(string)) {}

    /**
     *  @brief  Default destructor.
     */
    inline constexpr ~boundless_basic_string() = default;

    /**
     *  @brief   String assign operator.
     *
     *  @param   string  String of identical char type and allocator.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        const boundless_basic_string &string
    ) -> boundless_basic_string & = default;

    /**
     *  @brief   Copy contents of @c string to this string.
     *
     *  @param   string  String of identical char type and allocator.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        const char_type *string
    ) -> boundless_basic_string &
    {
        base::operator= (string);
        return *this;
    }

    /**
     *  @brief   Set value of string to one character.
     *
     *  @param   c  Character.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (char_type c) -> boundless_basic_string &
    {
        base::operator= (c);
        return *this;
    }

    /**
     *  @brief   String move assign operator.
     *
     *  @param   string  String of identical char type and allocator.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        boundless_basic_string &&string
    ) -> boundless_basic_string & = default;

    /**
     *  @brief   Set value of string using an @c std::initializer_list.
     *
     *  @param   list  An @c std::initializer_list of char type.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        std::initializer_list<char_type> list
    ) -> boundless_basic_string &
    {
        base::operator= (list);
        return *this;
    }

    /**
     *  @brief   Set value of string from a @c std::basic_string_view .
     *
     *  @tparam  tyoe   Type convertible to @c std::basic_string_view .
     *  @param   value  String to copy from.
     *  @return  Reference to self.
     */
    template<std::convertible_to<std::basic_string_view<char_type>> type>
    inline constexpr auto operator= (
        const type &value
    ) -> boundless_basic_string &
    {
        base::operator= (value);
        return *this;
    }

    /**
     *  @brief   String base assignment operator.
     *
     *  @param   string  Base string.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        const base &string
    ) -> boundless_basic_string &
    {
        return base::operator= (string);
    }

    /**
     *  @brief   String base move assignment operator.
     *
     *  @param   string  Base string.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        base &&string
    ) -> boundless_basic_string &
    {
        return base::operator= (std::move (string));
    }

    /**
     *  @brief   Convert to a @c std::basic_string_view .
     *  @return  @c std::basic_string_view of this string.
     */
    [[nodiscard]] inline constexpr operator std::basic_string_view<char_type>()
    const noexcept
    {
        return std::basic_string_view((base) * this);
    }

    /**
     *  @brief   Get a character at index, or a default constructed instance of
     *           the character type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index
    ) -> char_type &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get a character at index, or a default constructed instance of
     *           the character type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index
    ) const -> char_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get a character at index, or a default constructed instance of
     *           the character type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index)
    -> char_type &
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get a character at index, or a default constructed instance of
     *           the character type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index)
    const -> char_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get the first character, or a default constructed instance of
     *           the character type when the string is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() -> char_type &
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief   Get the first character, or a default constructed instance of
     *           the character type when the string is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> char_type
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief   Get the last character, or a default constructed instance of
     *           the character type when the string is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() -> char_type &
    {
        return boundless_access(*this, this->size() - 1);
    }

    /**
     *  @brief   Get the last character, or a default constructed instance of
     *           the character type when the string is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> char_type
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  Boundless version of std::basic_string_view.
 *
 *  Index-access of this string view always returns a default constructed element
 *  when an invalid index is provided.  Requires a default-constructible type.
 *
 *  @tparam  char_type   Character type.
 *  @tparam  traits      Character traits type.
 */
template<typename char_type, typename traits = std::char_traits<char_type>>
requires(std::is_default_constructible_v<char_type>)
struct boundless_basic_string_view : std::basic_string_view<char_type, traits> {

    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::basic_string_view<char_type, traits>;

    using base::basic_string_view;

    /**
     *  @brief  Default constructor.
     */
    inline constexpr boundless_basic_string_view() noexcept = default;

    /**
     *  @brief  String view copy constructor.
     *  @param  string  Other string view to copy from.
     */
    inline constexpr boundless_basic_string_view(
        const boundless_basic_string_view &string
    ) noexcept = default;

    /**
     *  @brief  Creates a string view from a null-terminated character array.
     *  @param  string  Null-terminated character array.
     */
    inline constexpr boundless_basic_string_view(
        const char_type *string
    ) : base(string) {}

    /**
     *  @brief  Creates a string from a character array.
     *
     *  @param  string  Character array of at least @c n length.
     *  @param  n       Number of characters to create a view.
     */
    inline constexpr boundless_basic_string_view(
        const char_type *string,
        std::size_t      n
    ) : base(string, n) {}

    /**
     *  @brief  Creates a string view from a range.
     *
     *  @tparam  input_iterator  Input iterator type.
     *  @param   first           Input iterator.
     *  @param   last            Input iterator.
     */
    template<std::input_iterator input_iterator>
    inline constexpr boundless_basic_string_view(
        input_iterator first,
        input_iterator last
    ) noexcept (noexcept (last - first)) : base(first, last) {}

    /**
     *  @brief  Creates a string view from a C++20 range.
     *
     *  @tparam  range_type  Range type.
     *  @param   range       Range of char type.
     */
    template<std::ranges::range range_type>
    explicit inline constexpr boundless_basic_string_view(
        range_type range
    ) : base(range) {}

    /**
     *  @brief  Copy from base string.
     *  @param  string  Base string.
     */
    inline constexpr boundless_basic_string_view(const base &string)
        : base(string) {}

    /**
     *  @brief   String view assign operator.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (const boundless_basic_string_view &)
    noexcept -> boundless_basic_string_view & = default;

    /**
     *  @brief   String base assignment operator.
     *
     *  @param   string  Base string.
     *  @return  Reference to self.
     */
    inline constexpr auto operator= (
        const base &string
    ) -> boundless_basic_string_view &
    {
        return base::operator= (string);
    }

    /**
     *  @brief   Get a character at index, or a default constructed instance of
     *           the character type when index is invalid.
     *
     *  @param   index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        std::size_t index
    ) const -> char_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get a character at index, or a default constructed instance of
     *           the character type when index is invalid.
     *
     *  @param  index  Index specifying element.
     *  @return  Character at index or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto at(std::size_t index)
    const -> char_type
    {
        return boundless_access(*this, index);
    }

    /**
     *  @brief   Get the first character, or a default constructed instance of
     *           the character type when the string view is empty.
     *  @return  First character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto front() const -> char_type
    {
        return boundless_access(*this, 0);
    }

    /**
     *  @brief   Get the last character, or a default constructed instance of
     *           the character type when the string view is empty.
     *  @return  Last character or default constructed instance.
     */
    [[nodiscard]] inline constexpr auto back() const -> char_type
    {
        return boundless_access(*this, this->size() - 1);
    }
};

/**
 *  @brief  Boundless version of std::string of @c char .
 */
using boundless_string = boundless_basic_string<char>;

/**
 *  @brief  Boundless version of std::string of @c wchar_t .
 */
using boundless_wstring = boundless_basic_string<wchar_t>;

/**
 *  @brief  Boundless version of std::string of @c char16_t .
 */
using boundless_u16string = boundless_basic_string<char16_t>;

/**
 *  @brief  Boundless version of std::string of @c char32_t .
 */
using boundless_u32string = boundless_basic_string<char32_t>;

/**
 *  @brief  Non-owning @boundless_c string .
 */
using boundless_string_view = boundless_basic_string_view<char>;

/**
 *  @brief  Non-owning @c boundless_wstring .
 */
using boundless_wstring_view = boundless_basic_string_view<wchar_t>;

/**
 *  @brief  Non-owning @c boundless_u16string .
 */
using boundless_u16string_view = boundless_basic_string_view<char16_t>;

/**
 *  @brief  Non-owning @c boundless_u32string .
 */
using boundless_u32string_view = boundless_basic_string_view<char32_t>;

/**
 *  @brief   Array with enumerator as index.
 *
 *  @tparam  enum_type     Container Utilities compatible enumerator type.
 *  @tparam  element_type  Type of element.
 */
template<cu::cu_compatible_enum enum_type, typename element_type>
struct enumerated_array : std::array<element_type, cu::enum_max_v<enum_type>> {

    /**
     *  @brief  Base class, template arguments are long.
     */
    using base = std::array<element_type, cu::enum_max_v<enum_type>>;

    /**
     *  @brief   Get the element at enumerator.
     *
     *  @param   enumerator  Enumerator specifying index.
     *  @return  Element at index.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        enum_type e) -> element_type &
    {
        return base::operator[] (std::to_underlying (e));
    }

    /**
     *  @brief   Get the element at enumerator.
     *
     *  @param   enumerator  Enumerator specifying index.
     *  @return  Element at index.
     */
    [[nodiscard]] inline constexpr auto operator[] (
        enum_type e) const -> element_type
    {
        return base::operator[] (std::to_underlying (e));
    }

    /**
     *  @brief   Get the element at enumerator.
     *
     *  @param   enumerator  Enumerator specifying index.
     *  @return  Element at index.
     */
    [[nodiscard]] inline constexpr auto at(enum_type e) -> element_type &
    {
        return base::at(std::to_underlying(e));
    }

    /**
     *  @brief   Get the element at enumerator.
     *
     *  @param   enumerator  Enumerator specifying index.
     *  @return  Element at index.
     */
    [[nodiscard]] inline constexpr auto at(enum_type e) const -> element_type
    {
        return base::at(std::to_underlying(e));
    }
};

/**
 *  @brief  Alias to @c enumerated_array .
 */
template<cu::cu_compatible_enum enum_type, typename element_type>
using erray = enumerated_array<enum_type, element_type>;

} // namespace cc

} // namespace alcelin

namespace std {

/**
 *  @brief   Formatter for @c cc::boundless_basic_string .
 *
 *  @tparam  char_type   Character type.
 *  @tparam  traits  Character traits type.
 *  @tparam  alloc   Allocator type, defaults to @c std::allocator<char_type> .
 */
template<typename char_type, typename traits, typename alloc>
struct formatter<alcelin::cc::boundless_basic_string<char_type,
    traits, alloc>, char_type> {

    /**
     *  @brief   Parse the format specifiers (none).
     *
     *  @tparam  parse_context  Parse context type.
     *  @param   ctx            Parse context.
     *  @return  Iterator to begin of parse context.
     */
    template<typename parse_context>
    [[nodiscard]] inline constexpr auto parse(parse_context &ctx)
    -> parse_context::iterator
    {
        // No format specifiers
        return ctx.begin();
    }

    /**
     *  @brief   Format the string using parsed specifiers (none).
     *
     *  @tparam  format_context  Format context type.
     *  @param   string          String to format.
     *  @param   ctx             Format context.
     *  @return  Iterator to end of format context.
     */
    template<typename format_context>
    [[nodiscard]] inline constexpr auto format(
        const alcelin::cc::boundless_basic_string<char_type, traits,
            alloc>     &string,
        format_context &ctx
    ) const
    {
        return std::ranges::copy(string, ctx.out()).out;
    }
};

/**
 *  @brief   Formatter for @c cc::boundless_basic_string_view .
 *
 *  @tparam  char_type   Character type.
 *  @tparam  traits  Character traits type.
 */
template<typename char_type, typename traits>
struct formatter<alcelin::cc::boundless_basic_string_view<char_type,
    traits>, char_type> {

    /**
     *  @brief   Parse the format specifiers (none).
     *
     *  @tparam  parse_context  Parse context type.
     *  @param   ctx            Parse context.
     *  @return  Iterator to begin of parse context.
     */
    template<typename parse_context>
    [[nodiscard]] inline constexpr auto parse(parse_context &ctx)
    {
        // No format specifiers
        return ctx.begin();
    }

    /**
     *  @brief   Format the string using parsed specifiers (none).
     *
     *  @tparam  format_context  Format context type.
     *  @param   string          String to format.
     *  @param   ctx             Format context.
     *  @return  Iterator to end of format context.
     */
    template<typename format_context>
    [[nodiscard]] inline constexpr auto format(
        const alcelin::cc::boundless_basic_string_view<char_type,
            traits>    &string,
        format_context &ctx
    ) const
    {
        return std::ranges::copy(string, ctx.out()).out;
    }
};

} // namespace std

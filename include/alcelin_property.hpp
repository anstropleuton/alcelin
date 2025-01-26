/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Implement properties in C++, similar to languages like C#.
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

#include <functional>
#include <memory>

/**
 *  @brief  All Alcelin's contents in this namespace.
 */
namespace alcelin {

/**
 *  @brief  Properties.
 */
namespace prop {

/**
 *  @brief   Property with getter.  Variable read operation will call the getter
 *           to retrieve the value.
 *  @tparam  type  Type to work with.
 */
template<typename type>
struct property_readonly {

    /**
     *  @brief  Getter function.
     */
    std::function<type()> getter;

    /**
     *  @brief  Creates a property with provided getter.
     *  @param  getter  Getter function.
     */
    inline constexpr property_readonly(std::function<type()> getter)
        : getter(getter) {}

    // All the below operators call getter

    [[nodiscard]] inline constexpr operator auto () const
    {
        return getter();
    }

    [[nodiscard]] inline constexpr auto operator+ (const type &o) const
    requires requires { std::declval<type>() + std::declval<type>(); }
    {
        return getter() + o;
    }

    [[nodiscard]] inline constexpr auto operator- (const type &o) const
    requires requires { std::declval<type>() - std::declval<type>(); }
    {
        return getter() - o;
    }

    [[nodiscard]] inline constexpr auto operator* (const type &o) const
    requires requires { std::declval<type>() * std::declval<type>(); }
    {
        return getter() * o;
    }

    [[nodiscard]] inline constexpr auto operator/ (const type &o) const
    requires requires { std::declval<type>() / std::declval<type>(); }
    {
        return getter() / o;
    }

    [[nodiscard]] inline constexpr auto operator% (const type &o) const
    requires requires { std::declval<type>() % std::declval<type>(); }
    {
        return getter() % o;
    }

    [[nodiscard]] inline constexpr auto operator^ (const type &o) const
    requires requires { std::declval<type>() ^ std::declval<type>(); }
    {
        return getter() ^ o;
    }

    [[nodiscard]] inline constexpr auto operator& (const type &o) const
    requires requires { std::declval<type>() & std::declval<type>(); }
    {
        return getter() & o;
    }

    [[nodiscard]] inline constexpr auto operator| (const type &o) const
    requires requires { std::declval<type>() | std::declval<type>(); }
    {
        return getter() | o;
    }

    [[nodiscard]] inline constexpr auto operator<< (const type &o) const
    requires requires { std::declval<type>() << std::declval<type>(); }
    {
        return getter() << o;
    }

    [[nodiscard]] inline constexpr auto operator>> (const type &o) const
    requires requires { std::declval<type>() >> std::declval<type>(); }
    {
        return getter() >> o;
    }

    [[nodiscard]] inline constexpr auto operator&& (const type &o) const
    requires requires { std::declval<type>() && std::declval<type>(); }
    {
        return getter() && o;
    }

    [[nodiscard]] inline constexpr auto operator|| (const type &o) const
    requires requires { std::declval<type>() || std::declval<type>(); }
    {
        return getter() || o;
    }

    [[nodiscard]] inline constexpr auto operator~ () const
    requires requires { ~std::declval<type>(); }
    {
        return ~getter();
    }

    [[nodiscard]] inline constexpr auto operator! () const
    requires requires { !std::declval<type>(); }
    {
        return !getter();
    }

    [[nodiscard]] inline constexpr auto operator< (const type &o) const
    requires requires { std::declval<type>() < std::declval<type>(); }
    {
        return getter() < o;
    }

    [[nodiscard]] inline constexpr auto operator<= (const type &o) const
    requires requires { std::declval<type>() <= std::declval<type>(); }
    {
        return getter() <= o;
    }

    [[nodiscard]] inline constexpr auto operator> (const type &o) const
    requires requires { std::declval<type>() > std::declval<type>(); }
    {
        return getter() > o;
    }

    [[nodiscard]] inline constexpr auto operator>= (const type &o) const
    requires requires { std::declval<type>() >= std::declval<type>(); }
    {
        return getter() >= o;
    }

    [[nodiscard]] inline constexpr auto operator== (const type &o) const
    requires requires { std::declval<type>() == std::declval<type>(); }
    {
        return getter() == o;
    }

    [[nodiscard]] inline constexpr auto operator!= (const type &o) const
    requires requires { std::declval<type>() != std::declval<type>(); }
    {
        return getter() != o;
    }

    template<typename ... Args>
    inline constexpr auto operator() (Args &&... args) const
    requires requires { std::declval<type>()(std::forward<Args>(args)...); }
    {
        return getter()(std::forward<Args>(args)...);
    }

    template<typename ... Args>
    inline constexpr auto operator[] (Args &&... args) const
    requires requires { std::declval<type>()[std::forward<Args>(args)...]; }
    {
        return getter()[std::forward<Args>(args)...];
    }

    [[nodiscard]] inline constexpr auto operator-> () const
    requires requires { std::declval<type>().operator-> (); }
    {
        return getter().operator-> ();
    }
};

/**
 *  @brief   Property with getter and setter.  Variable read operation will call
 *           the getter to retrieve the value, and write operation will call the
 *           setter to set the value.
 *  @tparam  type  Type to work with.
 */
template<typename type>
struct property : property_readonly<type> {

    /**
     *  @brief  Setter function.
     */
    std::function<void (const type &)> setter;

    /**
     *  @brief  Creates a property with provided getter and setter.
     *
     *  @param  getter  Getter function.
     *  @param  setter  Setter function.
     */
    inline constexpr property(
        std::function<type()>              getter,
        std::function<void (const type &)> setter
    ) : property_readonly<type>(getter), setter(setter) {}

    // All the below operators call getter and setter

    inline constexpr auto operator= (const type &t) -> property &
    requires requires(type t) { t = std::declval<type>(); }
    {
        setter(t);
        return *this;
    }

    inline constexpr auto operator+= (const type &o) -> property &
    requires requires(type t) { t += std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() + o);
        return *this;
    }

    inline constexpr auto operator-= (const type &o) -> property &
    requires requires(type t) { t -= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() - o);
        return *this;
    }

    inline constexpr auto operator*= (const type &o) -> property &
    requires requires(type t) { t *= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() * o);
        return *this;
    }

    inline constexpr auto operator/= (const type &o) -> property &
    requires requires(type t) { t /= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() / o);
        return *this;
    }

    inline constexpr auto operator%= (const type &o) -> property &
    requires requires(type t) { t %= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() % o);
        return *this;
    }

    inline constexpr auto operator^= (const type &o) -> property &
    requires requires(type t) { t ^= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() ^ o);
        return *this;
    }

    inline constexpr auto operator&= (const type &o) -> property &
    requires requires(type t) { t &= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() & o);
        return *this;
    }

    inline constexpr auto operator|= (const type &o) -> property &
    requires requires(type t) { t |= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() | o);
        return *this;
    }

    inline constexpr auto operator<<= (const type &o) -> property &
    requires requires(type t) { t <<= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() << o);
        return *this;
    }

    inline constexpr auto operator>>= (const type &o) -> property &
    requires requires(type t) { t >>= std::declval<type>(); }
    {
        setter(property_readonly<type>::getter() >> o);
        return *this;
    }

    inline constexpr auto operator++ () -> property &
    requires requires(type t) { ++t; }
    {
        type value = property_readonly<type>::getter();
        ++value;
        setter(value);
        return *this;
    }

    inline constexpr auto operator++ (int)
    requires requires(type t) { t++; }
    {
        type value = property_readonly<type>::getter();
        type copy  = value;
        value++;
        setter(value);
        return copy;
    }

    inline constexpr auto operator-- () -> property &
    requires requires(type t) { --t; }
    {
        type value = property_readonly<type>::getter();
        --value;
        setter(value);
        return *this;
    }

    inline constexpr auto operator-- (int)
    requires requires(type t) { t--; }
    {
        type value = property_readonly<type>::getter();
        type copy  = value;
        value--;
        setter(value);
        return copy;
    }
};

/**
 *  @brief   A property with default getter and setter, and an observer that is
 *           called when the variable is changed (technically, when an operation
 *           is performed on it).
 *  @tparam  type  Type to work with.
 */
template<typename type>
struct observable : property<type> {

    /**
     *  @brief  Internal value of type.
     */
    type value;

    /**
     *  @brief  Observer, called when the value is changed.
     */
    std::function<void (const type &)> observer;

    /**
     *  @brief  Default constructor initializes observer to do nothing.
     */
    inline constexpr observable() : value(type()), observer(),
        property<type>([&]() {
        return this->value;
    }, [&](const type &value) {
        this->value = value;
        if (this->observer) this->observer(this->value);
    }) {}

    /**
     *  @brief  Creates an observable property with default value and observer.
     *  @param  observer  Observer function.
     */
    inline constexpr observable(
        std::function<void (const type &)> observer
    ) : observable()
    {
        this->observer = observer;
    }

    /**
     *  @brief  Creates an observable property with provided value and no
     *          observer (observer does nothing).
     *  @param  value  Initial value.
     */
    inline constexpr observable(
        type value
    ) : observable()
    {
        this->value = value;
    }

    // Explicitly inherit operator= from property due to interference with
    // constructor
    using property<type>::operator=;
};

/**
 *  @brief   A proxy is an observable which modifies external value instead of
 *           internally storing it.  It also has an observer that is called when
 *           an operation is performed.
 *
 *  @tparam  type  Type to work with.
 *  @note    It cannot detect change in external value.
 */
template<typename type>
struct proxy : property<type> {

    /**
     *  @brief  External value to modify.
     */
    type *external;

    /**
     *  @brief  Observer, called when the variable is performed on.
     */
    std::function<void (const type &)> observer;

    /**
     *  @brief  Creates a proxy with default value and observer.
     */
    inline constexpr proxy() : external(nullptr), observer(),
        property<type>([&]() {
        if (!external) return type();
        return *external;
    }, [&](const type &value) {
        if (external) *external = value;
        if (observer) observer(value);
    }) {}

    /**
     *  @brief  Creates a proxy with default value and provided observer.
     *  @param  observer  Observer function.
     */
    inline constexpr proxy(
        std::function<void (const type &)> observer
    ) : proxy()
    {
        this->observer = observer;
    }

    /**
     *  @brief  Creates a proxy with provided value and no observer (observer
     *          does nothing).
     *  @param  value  Link to value.
     */
    inline constexpr proxy(
        type *value
    ) : proxy()
    {
        external = value;
    }

    /**
     *  @brief  Creates a proxy with provided value and observer.
     *  @param  value    Link to value.
     *  @param  observer Observer function.
     */
    inline constexpr proxy(
        type *value,
        std::function<void (const type &)> observer
    ) : proxy()
    {
        external = value;
        this->observer = observer;
    }

    // Explicitly inherit operator= from property due to interference with
    // constructor
    using property<type>::operator=;
};

} // namespace prop

} // namespace alcelin

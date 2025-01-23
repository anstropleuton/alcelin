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

/**
 *  @brief  All Alcelin's contents in this namespace.
 */
namespace alcelin {

/**
 *  @brief  Properties.
 */
namespace prop {

/**
 *  @brief  Property with getter.  Variable read operation will call the getter
 *          to retrieve the value.
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

    // All the below operators call getter.

    [[nodiscard]] inline constexpr operator auto () const {
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
 *  @brief  Property with getter and setter.  Variable read operation will call
 *          the getter to retrieve the value, and write operation will call the
 *          setter to set the value.
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

    // All the below operators call getter and setter.

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

    [[nodiscard]] inline constexpr auto operator++ ()
    requires requires(type t) { ++t; }
    {
        type value = property_readonly<type>::getter();
        ++value;
        setter(value);
        return *this;
    }

    [[nodiscard]] inline constexpr auto operator++ (int)
    requires requires(type t) { t++; }
    {
        type value = property_readonly<type>::getter();
        type copy  = value;
        value++;
        setter(value);
        return copy;
    }

    [[nodiscard]] inline constexpr auto operator-- ()
    requires requires(type t) { --t; }
    {
        type value = property_readonly<type>::getter();
        --value;
        setter(value);
        return *this;
    }

    [[nodiscard]] inline constexpr auto operator-- (int)
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
 *  @brief  A property with default getter and setter, useful to call something
 *          when a variable is changed (technically, doesn't need to be changed
 *          either).
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
     *  @brief  Getter for the property.
     */
    const std::function<void (const type &)> getter = [&]()
    {
        return value;
    };

    /**
     *  @brief  Setter for the property.
     */
    const std::function<void (const type &)> setter = [&](const type &t)
    {
        value = t;
        observer(value);
    };

    /**
     *  @brief  Creates an observable property with default value and observer.
     *  @param  observer  Observer function.
     */
    inline constexpr observable(
        std::function<void (const type &)> observer
    ) : property<type>(getter, setter), value(type()), observer(observer) {}

    /**
     *  @brief  Creates an observable property with provided value and observer.
     *
     *  @param  value     Initial value.
     *  @param  observer  Observer function.
     */
    inline constexpr observable(
        type                               value,
        std::function<void (const type &)> observer
    ) : property<type>(getter, setter), value(value), observer(observer) {}
};

} // namespace prop

} // namespace alcelin

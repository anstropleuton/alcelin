/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   The root header file to include everything.
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

#include <string_view>

// uncrustify:off
#include "alcelin_config.hpp"

#include "alcelin_container_utilities.hpp" // IWYU pragma: keep
#include "alcelin_custom_containers.hpp" // IWYU pragma: keep
#include "alcelin_string_manipulators.hpp" // IWYU pragma: keep
#include "alcelin_ansi_escape_codes.hpp" // IWYU pragma: keep
#include "alcelin_file_utilities.hpp" // IWYU pragma: keep
#include "alcelin_property.hpp" // IWYU pragma: keep
// uncrustify:on

/**
 *  @brief  All Alcelin's contents in this namespace.
 */
namespace alcelin {

/**
 *  @brief  Alcelin version string.
 */
inline constinit std::string_view alcelin_version = ALCELIN_VERSION;
} // namespace alcelin

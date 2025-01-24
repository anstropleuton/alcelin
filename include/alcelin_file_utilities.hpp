/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   General functionality to work with files.
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
#include <cstring>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <vector>

/**
 *  @brief  All Alcelin's contents in this namespace.
 */
namespace alcelin {

/**
 *  @brief  File utilities.
 *
 *  Contains utilities regarding file handling, and functionality to handle
 *  binary file data in SD format.
 *
 *  SD Format is a binary format which consists of chunks.  Each chunk is a pair
 *  of *Size* and *Data*.  The Size part of the data is @c std::size_t bytes and
 *  specifies the size of the chunk to be read to get the entire chunk.
 *
 *  @note   The SD Format does not specify the endianness of the data, neither
 *          does the code to handle this format.  This implies that the binary
 *          file may not be portable for systems with different endianness.
 *  @todo   When C++ introduces a good reflection support, implement automatic
 *          endianness conversion to make the binary file actually be portable.
 *          but for now, this is an impossible task and no plans to support it
 *          with hack codes.
 */
namespace file {

/**
 *  @brief  "SD chunk" is basically a vector of unsigned characters (bytes).
 */
using sd_chunk = std::vector<unsigned char>;

/**
 *  @brief   Read all the file's content at once and return @c std::string
 *           representing the file's content.
 *
 *  @param   filename  Filename.
 *  @return  @c std::string representing all the file's contents.
 *
 *  @note    Large files causes problems.
 */
[[nodiscard]] inline auto read_all(std::string_view filename)
{
    std::ifstream infile((std::string(filename)));
    if (!infile)
    {
        throw std::runtime_error(std::format("Failed to open file {}",
            filename));
    }

    return std::string(std::istreambuf_iterator(infile), {});
}

/**
 *  @brief   Creates a chunk from object @c t .
 *
 *  @tparam  type  Trivially copyable type.
 *  @param   t     Trivially copyable value.
 *  @return  Chunk of size `sizeof (type)` and containing the data from @c t .
 */
template<typename type>
requires(std::is_trivially_copyable_v<type>)
[[nodiscard]] inline constexpr auto to_sd_chunk(const type &t)
{
    auto     t_size = sizeof (type);
    sd_chunk chunk(t_size);

    std::memcpy(chunk.data(), &t, t_size);
    return chunk;
}

/**
 *  @brief   Convert a @c type from chunk.
 *
 *  @tparam  type   Trivially copyable chunk.
 *  @param   chunk  Chunk with size and data of @c type .
 *  @return  Object of type @c type with data of the chunk.
 */
template<typename type>
requires(std::is_trivially_copyable_v<type>)
[[nodiscard]] inline constexpr auto from_sd_chunk(const sd_chunk &chunk)
{
    auto t_size = sizeof (type);

    if (t_size != chunk.size())
    {
        throw std::invalid_argument(std::format(
            "SD chunk size ({}) does not match type size ({})", chunk.size(),
            t_size));
    }

    auto t = type();
    std::memcpy(&t, chunk.data(), t_size);
    return t;
}

/**
 *  @brief   Read a chunk from an input stream.
 *
 *  @param   input  Input stream to read from.
 *  @return  Chunk read from the stream.
 */
[[nodiscard]] inline constexpr auto read_chunk(std::istream &input)
{
    std::size_t size = 0;
    input.read((char *)&size, sizeof (std::size_t));

    sd_chunk chunk(size);
    input.read((char *)chunk.data(), chunk.size());
    return chunk;
}

/**
 *  @brief  Write a chunk to an output stream.
 *
 *  @param  output  Output stream to write to.
 *  @param  chunk   Chunk to write.
 */
[[nodiscard]] inline constexpr auto write_chunk(
    std::ostream   &output,
    const sd_chunk &chunk
)
{
    std::size_t size = chunk.size();
    output.write((char *)&size, sizeof (std::size_t));

    output.write((char *)chunk.data(), chunk.size());
}

/**
 *  @brief   Helper to read a chunk and convert it to type.
 *
 *  @tparam  type    Trivially copyable type.
 *  @param   input   Input stream to read from.
 *  @return  Data converted from chunk read from the stream.
 */
template<typename type>
requires(std::is_trivially_copyable_v<type>)
[[nodiscard]] inline constexpr auto read_data(std::istream &input)
{
    auto chunk = read_chunk(input);
    return from_sd_chunk<type>(chunk);
}

/**
 *  @brief   Helper to convert the type to chunk and write it.
 *
 *  @tparam  type    Trivially copyable type.
 *  @param   output  Output stream to write to.
 *  @param   t       Trivially copyable value.
 */
template<typename type>
requires(std::is_trivially_copyable_v<type>)
[[nodiscard]] inline constexpr auto write_data(
    std::ostream &output,
    const type   &t
)
{
    auto chunk = to_sd_chunk(t);
    write_chunk(output, chunk);
}

} // namespace file

} // namespace alcelin

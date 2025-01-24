/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Test all of File Utilities in Alcelin.
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
#include <exception>
#include <sstream>
#include <string>
#include <string_view>

#include "alcelin_file_utilities.hpp"
#include "alcelin_string_manipulators.hpp"
#include "confer.hpp"

using namespace alcelin;
using namespace std::string_literals;

/**
 *  @brief   Test File' read_all function.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_file_read_all) {
    CT_BEGIN;

    std::string_view filename = "test_file_read_all_file.txt";
    std::string      expected = "Copyright (C) 2024 Anstro Pleuton\n"
                                "\n"
                                "This is a dummy file for testing File "
                                "Utilities's read_all function which reads all "
                                "the file contents at once.\n";

    auto content = file::read_all(filename);

    logln("filename: {}", filename);
    logln("content: {}",  content);
    logln("expected: {}", expected);

    CT_ASSERT_CTR(content, expected);

    CT_END;
}

/**
 *  @brief   Test File' SD chunk conversion functions.
 */
[[nodiscard]] CT_TESTER_FN(test_file_sd_chunk_conversion) {
    CT_BEGIN;

    unsigned int   value         = (unsigned int)-1;
    file::sd_chunk to_sd_chunk   = file::to_sd_chunk<unsigned int>(value);
    unsigned int   from_sd_chunk =
        file::from_sd_chunk<unsigned int>(to_sd_chunk);

    CT_ASSERT(value, from_sd_chunk, "Conversion to chunk and back from chunk "
        "should yield same value");

    std::stringstream stringstream;

    file::write_chunk(stringstream, to_sd_chunk);
    auto read_chunk = file::read_chunk(stringstream);

    CT_ASSERT(to_sd_chunk, read_chunk, "Chunk written to a stream and then read"
        " back should yield same chunk");

    // Reset string stream to reuse
    stringstream.clear();

    file::write_data(stringstream, value);
    unsigned int read_data = file::read_data<unsigned int>(stringstream);

    CT_ASSERT(value, read_data, "Conversion to chunk and written to a stream, "
        "and then read back from stream and conversion back to type should "
        "yield same value");

    CT_END;
}

/**
 *  @brief   Test File.
 *  @return  Number of errors.
 */
[[nodiscard]] CT_TESTER_FN(test_file) try
{
    test_case file_read_all_test_case {
        .title         = "Test File's read_all function",
        .function_name = "test_file_read_all",
        .function      = test_file_read_all
    };

    test_case file_sd_chunk_conversion_test_case {
        .title         = "Test File' SD chunk conversion functions",
        .function_name = "test_file_sd_chunk_conversion",
        .function      = test_file_sd_chunk_conversion
    };

    test_suite suite = {
        .tests       = {
            &file_read_all_test_case,
            &file_sd_chunk_conversion_test_case
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

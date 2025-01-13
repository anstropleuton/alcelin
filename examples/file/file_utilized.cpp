/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   How to use File Utilities functions.
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

#include <fstream>
#include <ios>
#include <print>

#include "alcelin.hpp" // IWYU pragma: export

using namespace alcelin;

// This example is meant to be a kick-starter to start using my library, but
// they do not teach everything.  Refer to the documentation for more details
auto main() -> int
{
    // Write to a binary file and read it back
    int my_very_special_number = 2'189'263;
    int a_copy_of_that_number = my_very_special_number;
    int my_another_very_special_number = 3'786'231;
    int another_copy_of_that_number = my_another_very_special_number;

    std::ofstream outfile("binary_file.bin", std::ios::binary);
    if (!outfile)
    {
        std::println("Failed to write to binary_file.bin");
        return 1;
    }

    file::write_data(outfile, my_very_special_number);
    file::write_data(outfile, my_another_very_special_number);

    outfile.close();

    std::ifstream infile("binary_file.bin", std::ios::binary);
    if (!infile)
    {
        std::println("Failed to read from binary_file.bin");
        return 1;
    }

    my_very_special_number = file::read_data<int>(infile);
    my_another_very_special_number = file::read_data<int>(infile);

    // Compare values with original to see if it worked
    if (my_very_special_number == a_copy_of_that_number
     && my_another_very_special_number == another_copy_of_that_number)
    {
        std::println("Written and read back a number, it works!");
    }
    else
    {
        if (my_very_special_number != a_copy_of_that_number)
        {
            std::println("Written {} but read back {}, it does not work",
                a_copy_of_that_number, my_very_special_number);
        }
        if (my_another_very_special_number != another_copy_of_that_number)
        {
            std::println("Written {} but read back {}, it does not work",
                another_copy_of_that_number, my_another_very_special_number);
        }
        std::println("NOTE: Please build and run tests to ensure functionality,"
            " and report a bug to me (Anstro Pleuton) for this output");
        return 1;
    }
}

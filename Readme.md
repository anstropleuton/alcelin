# Alcelin
Alcelin is a collection of utils for Anstro Pleuton's programs. This library contains several commonly used program artifacts in a simplified functions for ease of use.

# Sections
This library is subdivided into sections:
- **Container Utilities** contains several utilities for container types (i.e., **std::vector**, **std::array**, etc. or custom compatible container types) which includes **appending elements** (combining), **filtering elements out**, etc. And several **operators** for these operations.
- **Custom Containers** contains **boundless** version of standard library containers, in which you can access elements without having to **worry about bounds check**.
- **String Manipulators** contains several utilities for **std::string** (or **std::string_view** as parameters) which includes **converting containers to string**, **word-wrap**, **trimming string**, converting **to lower case**, etc. And several **operators** from Container Utilities applied to string types.
- **ANSI Escape Codes** contains easy handlers for manipulation output using decorator [ANSI Escape Codes](https://en.wikipedia.org/wiki/ANSI_escape_code).
- **Argument Parser** is [removed](#removed-sections).
- **File Utilities** contains file utilities such as function to **read all the file contents**, and other utilities ability to **convert any trivially copyable** type from and to **vector of bytes** (`sd_chunk`) and **read/write to file/generic streams**.
- **Properties**. Yes, properties. The similar one from C#. Properties allow you to define function that **return a value** when a variable is being observed (used its value), or a function that **sets a value** when a variable is assigned to or operated on.

# Removed Sections
- **Argument Parser** contains functionality to parse **Command Line Arguments** and structures to **define options** (or **switches** if you are old and use Microsoft Windows) to easily validate arguments.
  - This is removed from Alcelin, and is now available in [Optrone](https://github.com/anstropleuton/optrone).

# Dependencies
- [Confer](https://github.com/anstropleuton/confer) - Only for testing.

# Prerequisite
- Know to program in C++
- Know to program in C++23 (optional, recommended)
- Know to use third party C++ libraries
- Know to use CMake

# Usage
If you are not Anstro Pleuton, which you probably are, here is a quick and rough guide to use my library:

 1. Setup:
    - Clone this repository.
    ```bash
    git clone https://github.com/anstropleuton/alcelin.git
    cd alcelin
    ```
 2. Initialize dependencies:
    - Clone/update dependencies
    ```bash
    git submodule update --init --recursive
    ```
 3. Build the library:
    - Make build folder:
    ```bash
    mkdir build
    cd build
    ```
    - Build the project:
    ```bash
    cmake ..
    cmake --build .
    ```
 4. Install (optional, Unix/-like only)
    ```
    sudo cmake --install .
    ```
    Note: To uninstall, use `sudo cmake --build . --target uninstall`.
 5. If you are using CMake, you can use `find_package`/`add_subdirectory` or `FetchContent_Declare`/`FetchContent_MakeAvailable`, or manually set `include` and `build` as include directories and link `build/libalcelin.a`.

# Documentations
Assuming you are in root directory of this project and built the project in build directory, generate documentation using:
```bash
cd build
doxygen
```

The documentation is generated as a web-pages. Open the file `build/docs/html/index.html` to read the documentations.
```bash
firefox docs/html/index.html
```

# TODO
- Review all CMake files
- Refactor tests to be less repetitive
- Refactor examples to be more structured

# Changelog
Refer to the [Changelog](Changelog.md) for info about changes in each version.

# Contributing
Check out [Guidelines](Guidelines.md) before you submit your code! Make sure to create a branch with one task with the name of the category of your task (i.e., "features/", "bugfix/", etc.) your task before you change the code.

# Credits
Thanks to [jothepro](https://github.com/jothepro) for the stylesheet [Doxygen Awesome](https://github.com/jothepro/doxygen-awesome-css) for Doxygen.

Thanks to Nuno Pinheiro (can't find link) for the background Elarun. But I did find a [KDE store link](https://store.kde.org/p/1162360/) to the background image. I think you could consider that. If KDE developers are here, I would appreciate your help to find a proper link to the author.

Thanks to GLFW for some code in CMake.

# License
This project is licensed under the terms of MIT License, see [License](License.md).

# Junk folder?
That folder is where I put my useless features. Don't use them please.

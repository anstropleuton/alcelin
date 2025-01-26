# Changelog
## v0.0.0.0 - A history
This project started out as a C header and source file. I think it it was called `aplib.h`/`aplib.c`? I am not sure, I lost the source codes and don't know file names either. It had a really small and really basic argument parser. That's all, or was it?

Later, I started using C++ again, and made an `aplib.hpp`. It is a header-only library. It started out as having a really small collection of stuff. It had `operator+` for adding two vectors and `operator*` for repeating a string. A few string functions like `split`, `merge` (`combined` in Alcelin) and `word_wrap`. It also had a small collection of AECs, which was actually just a collection of strings. I also had ported the argument parser to it.

Even later, I started using raylib and PhysX, and created some helpers.

I was using it by just copying the header file across my source code. It was beautiful, until it wasn't. I did not have any idea which one was the most up-to-date. The solution? Adding comments to it to describe its version. But was it enough? Probably stayed that way for a while. And then I decided to create a repo and split the header files into its own distinct sections.

And that's how it born, *drum roll please*, aplib. Yeah... not Alce yet. But wait, too early have revealed this name. Later I renamed it to Auspicious Library, and Propitious Library. The Auspicious Library was meant to be independent, and Propitious Library was meant to have other things as its dependency (i.e., raylib, physx, and Auspicious Library). Auspicious Library had all the good things from Alcelin, such as CU, SM, AEC and AP (argument parser). and Propitious Library had raylib+PhysX integrations and stuff.

The name did not stuck, and it was changed to Alce Library. Even this name did not stuck, as it was just slightly inconsistent with my super-awkward, highly-unmemorizable, completely-taken-out-of-thin-air naming convention. It was not too long before I rename it to Alcelin.

## v1.0.0.0 - Initial Release
Alce Library is now production ready! (*hopefully*)

## v1.1.0.0 - Extract Tester
The custom testing framework is now in it's own repository, [Confer Tester](https://github.com/anstropleuton/confer)!

## v2.0.0.0 - Project Rename
Rename the project from Alce Library to Alcelin.
Also renamed it's dependency from Confer Tester to Confer.

## v2.1.0.0 - Extract Argument Parser
Alcelin's argument parser is now in it's own repository, [Optrone](https://github.com/anstropleuton/optrone)!
Also, restructure documentations.

## v2.1.0.1 - Make CMake's files more reusable
Few CMake files I use in cmake/ folder are mostly reused throughout my project, so rename them to have generic name and configure them with proper name in CMakeLists.txt itself.
Also fix the uninstall target.

## v2.1.0.2 - Add dependency helper
Added [dependency helpers](cmake/depman.cmake). And removed submodules.

## v2.1.1.0 - Added binary functionality
Added binary functionality to [alcelin_file_utilities.hpp](include/alcelin_file_utilities.hpp), including ability to convert any trivially copyable type from and to vector of bytes (`sd_chunk`) and read/write to file/generic streams.

## v2.2.0.0 - Refactors and container to string formatter
Refactor tests, format files, and several small changes.
Also added `std::formatter` for formatting containers. Automatically works with nested containers too!

## v2.2.1.0 - Add member assignment operators
Added member assignment operators (`operator+=`, `operator-=` and `operator*/`) for CU and member assignment operators (`operator-=` and `operator*=`) for SM.

## v2.3.0.0 - Add properties
Added properties which allows custom getters and setters to be called when a thing changes.

## v2.3.1.0 - Switch template orders for enumerated_array
Swap `enum_type` and `element_type` around to match that of an unordered map.

## v2.4.0.0 - Extract custom containers into its own header
Extract custom containers from CU into its own section (CC).
This is where I `rm -rf`'ed my current working directory... glad I use Git and VS Code omg... Opened files in VS Code, when the file itself is deleted, stays opened in the memmory of VS Code. This, paired with Git, allowed me to recover all the deleted files. Man I hate myself...

## v2.4.0.1 - Upgrade Observables
It can now take only value as an constructor parameter.

## v2.4.1.0 - Add Proxy
Proxy is like an observer but instead of internal value, it control external value.

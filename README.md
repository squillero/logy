LOGY
====

[![License: cc0](https://img.shields.io/badge/license-cc0-brightgreen.svg)](http://creativecommons.org/publicdomain/zero/1.0/)
[![Language: C++11](https://img.shields.io/badge/language-C%2B%2B11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
![Version: 1.02](https://img.shields.io/badge/version-1.02-lightgrey.svg)

Yet another C++ logger, no strings attached. *Logy* is very easy to use (its functions either mirror `printf` or accept a simple list of generic objects), very easy to install (just drop `logy.h` into any existing project), and extremely efficient (everything is done at compile time).

> If you need serious logging, you should use a full-fledged library, such as [*Easylogging++*](https://github.com/muflihun/easyloggingpp) or [*Loguru*](https://github.com/emilk/loguru). A much simpler library, still more complex and powerful than *logy*, is [*plog*](https://github.com/SergiusTheBest/plog).


### Instructions

Add `logy.h` header file to an existing project, and call `Log`, `Debug`, `Info`, and `Warning` with the `printf` syntax. Alternatively, use `LOG_BARE`, `LOG_DEBUG`, `LOG_INFO`, and `LOG_WARNING` with a list of objects that could be streamed to `std::cerr` (i.e., that would be acceptable for the operator `<<`). 

Some messages will be displayed and some will not according to the *verbosity level* set at compile time. In more details, defining these preprocessor macros enables the different *logy*'s messages:

|  | *nil* | VERBOSE | DEBUG |
|---------|:-----:|:-------:|:-----:|
|Log | ✔ | ✔ | ✔ |
|Debug | | |   ✔   |
|Info | | ✔ | ✔ |
|Warning | ✔ | ✔ | ✔ |
|LOG_BARE | ✔ | ✔ | ✔ |
|LOG_DEBUG | | | ✔ |
|LOG_INFO | | ✔ | ✔ |
|LOG_WARNING | ✔ | ✔ | ✔ |

Please note that *logy* is based on [variadic macros](http://en.cppreference.com/w/cpp/preprocessor/replace) and [variadic templates](https://en.cppreference.com/w/cpp/language/parameter_pack), and thus requires a [C++11 compiler](https://en.cppreference.com/w/cpp/compiler_support). 

*VisualStudio* users may need to define `_CRT_SECURE_NO_WARNINGS`.

### Example

```c++
#include "logy.h"

int main() {
    Log("This is version v1.02!");
    Debug("To get debug messages you need to define DEBUG while compiling");
    Info("To get info messages you need to define either DEBUG or VERBOSE");
    Warning("You %s get all warning messages", std::string{"always"}.c_str());
    LOG_INFO("LOG_* macros mirror to std::cerr<<.", std::string{"Just"}, "list the objects...");

    return 0;
}
```

compiling with 

```sh
g++ -std=c++11 -DVERBOSE main.cpp
```

you may get something like

```
[10:26:00] This is version v1.02!
[10:26:00] INFO: To get info messages you need to define either DEBUG or VERBOSE
[10:26:00] WARNING: You always get all warning messages
[10:26:00] INFO: LOG_* macros mirror to std::cerr<<. Just list the objects...
```

### Logy is public domain

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means. See [LICENSE.md](/LICENSE.md) for more details.

LOGY
====

[![License: public domain](https://img.shields.io/badge/license-public%20domain-brightgreen.svg)](https://unlicense.org/)
[![Language: C++11](https://img.shields.io/badge/language-C%2B%2B11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
![Version: 1.0](https://img.shields.io/badge/version-1.0-lightgrey.svg)

Yet another C++ logger, no strings attached. *Logy* is very easy to use (its functions either mirror `printf` or accept a simple list of generic objects), very easy to install (just drop `logy.h` into any existing project), and extremely efficient (everything is done at compile time).

> If you need a powerful, full-fledged logging, you should use a more complex library, such as [Easylogging++](https://github.com/muflihun/easyloggingpp)

### Instructions

Add `logy.h` header file to an existing project, and call `Debug`, `Info`, and `Warning` with the `printf` syntax. Alternatively, use `LOG_DEBUG`, `LOG_INFO`, and `LOG_WARNING` with a list of objects that would be acceptable for `std::cerr`'s `operator<<`. Some messages will be displayed and some will not according to the *verbosity level* set at compile time. In more details, these preprocessor macros enable the different *logy*'s messages:

|  | *nil* | VERBOSE | DEBUG |
|---------|:-----:|:-------:|:-----:|
|Debug | | |   ✔   |
|Info | | ✔ | ✔ |
|Warning | ✔ | ✔ | ✔ |
|LOG_DEBUG | | | ✔ |
|LOG_INFO | | ✔ | ✔ |
|LOG_WARNING | ✔ | ✔ | ✔ |

Please note that *logy* is based on C++11 [variadic templates](https://en.cppreference.com/w/cpp/language/parameter_pack) and requires a [compliant compiler](https://en.cppreference.com/w/cpp/compiler_support).

### Example

```c++
#include "logy.h"

int main() {
    Debug("To get debug messages you need to define DEBUG while compiling");
    Info("To get info messages you need to define either DEBUG or VERBOSE");
    Warning("You %s get all warning messages", std::string{"always"}.c_str());
    LOG_INFO("LOG_* macros mirror to std::cerr<<.", std::string{"Just"}, "list the objects!");

    return 0;
}
```

compiling with 

```sh
g++ -DVERBOSE main.cpp
```

you may get something like

```
[10:26:00] INFO: To get info messages you need to define either DEBUG or VERBOSE
[10:26:00] WARNING: You always get all warning messages
[10:26:00] INFO: LOG_* macros mirror to std::cerr<<. Just list the objects!
```

### Logy is public domain

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means. See [LICENSE.md](/LICENSE.md) for more details.

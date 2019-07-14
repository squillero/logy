LOGY
====

[![License: cc0](https://img.shields.io/badge/license-cc0-brightgreen.svg)](http://creativecommons.org/publicdomain/zero/1.0/)
[![Language: C++11](https://img.shields.io/badge/language-C%2B%2B11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
![Version: 1.2.1](https://img.shields.io/badge/version-1.2.1-lightgrey.svg)

Yet another C++ logger, no strings attached. *Logy* is very easy to use (its functions either mirror `printf` or accept a simple list of generic objects), very easy to install (just drop `logy.h` into any existing project), and extremely efficient (everything is done at compile time).

> If you need serious logging, you should use a full-fledged library.

### Instructions

Add `logy.h` header file to an existing project, and call `Logy`, `Debug`, `Info` and `Warning` with exactly the same syntax as `printf`; alternatively, use `LOGY`, `LOG_DEBUG`, `LOG_INFO` and `LOG_WARNING` with a list of objects. Some messages will be displayed and some will not according to the *verbosity level* set at compile time. 

`LOGY`, `LOG_DEBUG`, `LOG_INFO` and `LOG_WARNING` accept objects that could be streamed directly to `std::cerr` (i.e., that would be acceptable for the operator `<<`), or `std::vectors` and `std::initializer_list` of such objects. Containers are recursively unrolled as `[ e1 e2 ... eN ]` using [SFINAE](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/SFINAE); an alternative implementation, which exploits [tag dispatching](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Tag_Dispatching), is commented out in the code.

Defining these preprocessor macros enables the different *logy*'s messages:

|  | *nil* | VERBOSE | DEBUG |
|---------|:-----:|:-------:|:-----:|
|Logy | ✔ | ✔ | ✔ |
|Debug | | |   ✔   |
|Info | | ✔ | ✔ |
|Warning | ✔ | ✔ | ✔ |
|LOGY | ✔ | ✔ | ✔ |
|LOG_DEBUG | | | ✔ |
|LOG_INFO | | ✔ | ✔ |
|LOG_WARNING | ✔ | ✔ | ✔ |

#### Notes:

* *Logy* is based on [variadic macros](http://en.cppreference.com/w/cpp/preprocessor/replace) and [variadic templates](https://en.cppreference.com/w/cpp/language/parameter_pack), and thus requires a [C++11 compiler](https://en.cppreference.com/w/cpp/compiler_support).

* The alternate tag-dispatching mechanism requires a [C++14 compiler](https://en.cppreference.com/w/cpp/compiler_support), but it could be easily changed to be compatible with C++11.

* *VisualStudio* users may need to define `_CRT_SECURE_NO_WARNINGS` to avoid annoying messages.

### Example

```c++
#include "logy.h"

int main() {
    Logy("This is version v1.2.1!");
    Debug("To get debug messages you need to define DEBUG while compiling");
    Info("To get info messages you need to define either DEBUG or VERBOSE");
    Warning("You %s get all warning messages", std::string{"always"}.c_str());
    LOG_INFO("LOG_* macros mirror to std::cerr<<.", std::string{"Just"}, "list the objects...");
    std::vector<std::vector<std::string>> gx = {{ "foo", "bar", "baz" }, { "Jake", "Elwood" }};
    LOG_INFO("A vector:", gx);

    return 0;
}
```

compiling with 

```sh
g++ -std=c++11 -DVERBOSE main.cpp
```

you may get something like

```
[17:51:57] This is version v1.2.1!
[17:51:57] INFO: To get info messages you need to define either DEBUG or VERBOSE
[17:51:57] WARNING: You always get all warning messages
[17:51:57] INFO: LOG_* macros mirror to std::cerr<<. Just list the objects...
[17:51:57] INFO: A vector: [ [ foo bar baz ] [ Jake Elwood ] ]
```

**Logy is public domain**  
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means. See [LICENSE.md](/LICENSE.md) for more details.

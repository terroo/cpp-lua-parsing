# C++ Parser Lua file config
Just a basic mini library for parsing simple files that only have variables written and with Lua extension.

> Note: At the moment this parser is only for variables, I have not yet implemented the table and metatable parser in Lua.

It is a parser without running Lua, that is, without using the PUC-RIO Lua libraries.

I decided to start this project because I haven't seen any similar without using additional libraries, only C++. If you want to contribute to the implementation of tables and metatables, feel free to modify and send a pull request.

---

### Features and News
- [x] String parser
- [x] Ignore comments on Lua
- [x] Ignore spaces in badly formatted files
- [ ] Variable parser
- [ ] Table parser
- [ ] Metatable parser

---

# Installation
```sh
git clone https://github.com/terroo/cpp-lua-parsing
cd cpp-lua-parsing/
sudo make install
```

> You can also use `cpplua.hpp` file without installing, just copying and including in your project.

---

# Use
Suppose you have a file in Lua with only variable names and values for them.

And that file can be with spaces, comments and blank lines, and want to use as a "mini database", example:

> `cat file.lua`

```lua
-- file configuration for game
position = 18.3
name = "Strike Man The Biggest of The World" -- use name capitalize and spaces
color = #554477
skin = "Dragon"
-- for more configs add here
        after = true
result = 935


news = "information"


```

### Basic use
Print the entire file, but ignoring spaces and comments. This basic code would be:

> `vim main.cpp`

- Include cpp-lua-parsing:
```cpp
#include <cpp-lua-parsing/cpplua.hpp>
```
> If you haven't installed it and want to use it separately, just: `#include cpplua.hpp`.

- Instantiate the `luaparsing` *class* inside the `cpp` *namespace*
```cpp
cpp::luaparsing luapp;
```
- Initialize and declare the `luafile` member for your `.lua` file (must be `.lua`) or the *full path* to it:
```cpp
luapp.luafile = "file.lua";
```
- Print member function `readluafile()`:

Full `main.cpp` code:
```cpp
#include "cpplua.hpp"

int main(){
  cpp::luaparsing luapp;
  luapp.luafile = "file.lua";
  std::cout << luapp.readluafile();
}
```

Compile: `g++ main.cpp -o luaparsing` . After running `./luaparsing` the formatted output of the example file will be:
```lua
position = 18.3
name = Strike Man The Biggest of The World 
color = #554477
skin = Dragon
after = true
result = 935
news = information
```

### Get the value of a specific variable
> Use member function: `get_value_from_key()`

```cpp
#include <cpp-lua-parsing/cpplua.hpp>

int main( int argc , char **argv ){
  cpp::luaparsing luapp;
  luapp.luafile = "./resources/file.lua";
  std::cout << luapp.get_value_from_key("color") << '\n';
}
```
> The output will be: `#554477`

### Knowing which variable has a certain value
> Use member function: `get_key_from_value()`

```cpp
#include "cpplua.hpp"

int main( int argc , char **argv ){
  cpp::luaparsing luapp;
  luapp.luafile = "./resources/file.lua";
  std::cout << luapp.get_key_from_value("Dragon") << '\n';
}
```

> NOTE: get\_**key**\_from_value() `≠` get\_**value**\_from_key()

---

# Uninstall
```sh
sudo make uninstall
```

Contribute! Issues: <https://github.com/terroo/cpp-lua-parsing/issues>

---

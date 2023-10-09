# ch
Simple command-line code generator tool. ch - *Code helper (abbreviation)*

**Note! This tool goes without any guarantee! Use it at your risk without any warranty.**

License: [Apache License, Version 2.0][LicenseURL] - see ``LICENSE`` for more information.

# HOW TO INSTALL

## Debian, Ubuntu, Mint

and other Debian derivatives.

You should have ``c++ +17``, ``cmake 3.22`` ot higher, ``flex-dev``, ``libbison-dev`` packages installed.

### Typical installation path:

* cd to a dir you whant to install ch source code to;
* Clone it from git:
```
git clone git@github.com:valera-vorona/ch.git
```
* Then go a typical simple way to install any project from source code with cmake:
```
cd ch
mkdir build && cd build
cmake ..
cmake --build .
sudo cmake --install .
```
* That's it.
* *If you don't need ``ch`` source code any longer, you can remove the whole directory, all installed binaries and other files required to run ``ch`` will remain.*

## Other OS

### No information yet

* Install ``git`` ``c++ +17``, ``cmake 3.22`` ot higher, ``flex-dev``, ``libbison-dev``;
* Clone the source code from ``git@github.com:valera-vorona/ch.git``;
* Compile and install the project.

# HOW TO USE

* Open your console and ``cd`` to a directory you want to generate source code to;
* Then type:
```
ch cpp create class namespace=mynamespace name=MyClass
```
* ``ls`` and you will see **MyClass.h** and **MyClass.cpp** source code files;
* Note that by default **ch** will not overwrite the files which exist on your disk already. It's safe! If you whant to overwrite them, use **ch** with option ``--force=t``;
* By default **ch** creates files with the same names as you type in the ``name`` variable but you can change it with option ``-o``.

Usage: ``ch commands [options and variables]``

The order of commands is important:
``cpp create class`` - creates a cpp class.

The order of options and variables is not important. They can go and mix with each other.
Options and variables must be followed by ``=`` and a value. If you want to use a false value you should type ``0``, for example, if you what not to overwrite existing files type ``--force=0`` or just don't menthion this option. The same goes with the variables.

Options:
* **--force** - overwrite existing files.
* **-o**, **--out-file-name** - Output file name (without extention. By default it's equal to **name** variable

Variables:
* **name** - class name.
* **namespace** - namespace name.

## Editing template files
After the installation ``ch`` will create a directory ``.ch`` at your home dir. In this directory you will see:
* ``struct.txt`` file, which describes the overall structure of the generated files;
* ``templates`` directory with the templates themselves.

You can edit these files to make your own templates of any programming languages or other text based projects there.
A better practice is that you copy ``.ch`` directory whenever you develop your project and edit the files there, as when you
reinstall ``.ch`` this directory will be rewritten to default.

``ch`` looks for the ``.ch`` directory beginning with the current directory, up to the root directory (excluding the root directory itself),
then it tries to find ``.ch`` in the directories set at CH_HOME, HOME environment variables. It fails to go further with an error message if doesn't find ``.ch`` directory after the above attempts.

### struct.txt

This file describes the overall structure of the generated files.

  *further information goes here.*

### template files

These files hold the templates which ``ch`` generates code from.

  *further information goes here.*

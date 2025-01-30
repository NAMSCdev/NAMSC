[![Actions Status](https://github.com/lighttab2/procedural-visual-novel/workflows/macOS/badge.svg)](https://github.com/lighttab2/procedural-visual-novel/actions/workflows/macos.yml)
[![Actions Status](https://github.com/lighttab2/procedural-visual-novel/workflows/Windows/badge.svg)](https://github.com/lighttab2/procedural-visual-novel/actions/workflows/windows.yml)
[![Actions Status](https://github.com/lighttab2/procedural-visual-novel/workflows/Ubuntu/badge.svg)](https://github.com/lighttab2/procedural-visual-novel/actions/workflows/ubuntu.yml)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/lighttab2/procedural-visual-novel)](https://github.com/lighttab2/procedural-visual-novel/releases)

# Procedural Visual Novels
<!--
(Project logo)

(Cool PNGs to attract people)

(Project usage example GIFs)
-->

Library and Editor for generating **Procedurally Narrated Visual Novels**.


## Install

<details><summary>Prerequisites</summary>

* **[CMake v3.21+](https://cmake.org/)**

* **[Python 3](https://www.python.org/)**
    * **Conan** &ndash; `pip install conan`

* **[Qt 6](https://www.qt.io/)**

* **C++ compiler that can compile Qt6** &ndash; needs to support the **C++17** standard. Lists of viable compilers:
    * [Linux](https://doc.qt.io/qt-6/linux.html)
    * [Windows](https://doc.qt.io/qt-6/windows.html)
    * [macOS](https://doc.qt.io/qt-6/macos.html)

<hr>
</details>

### Install packages using *Conan*:

```bash
conan install conan/ --build=missing --settings=build_type=Debug
conan install conan/ --build=missing --settings=build_type=Release
```

### [Simply run *CMake*:](https://cmake.org/runningcmake/)

<details><summary>Bash</summary>

```bash
cmake . -G [generator] -T [toolset] --build [PathToBuiltProject]
```

Example:

```bash
cmake . -G "Visual Studio 16 2019" -T v143 -Bbuild
```

<hr>
</details>

<details><summary>GUI</summary>

The procedure is the standard one, but there are three things to be way of.

You need to provide **architecture** and **toolkit**. If you leave them blank, project **generation** will likely fail. Also select option to specify the **toolchain file**:

<p align="center">
<img src="pages/cmake2.png" alt="CMake settings screenshot" width="55%"/>
</p>

If you did not tinker with *Conan*, the **toolchain file** should be found at `conan/conan_toolchain.cmake`. 

<p align="center">
<img src="pages/cmake3.png" alt="CMake settings screenshot" width="35%"/>
</p>

<hr>
</details>

### Build the project

You can use your local *IDE* or *CMake* again:

```bash
cmake --build [pathToBuiltProject] --config [configuration] -j4 -DCMAKE_TOOLCHAIN_FILE=[pathToConanToolchainFile]
```

Example:

```bash
cmake --build build --config release -j4 -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake
```
<!--
## Features
[List of features]
-->

## Troubleshooting
<details><summary><i>Qt6</i> is <b>not found</b>, despite being installed</summary>

Ensure that these **environment variables** are set properly:

* **Qt6_DIR** - `[path_to_Qt]/[version]/[compiler]/lib/cmake/Qt6`<br/>Example: `C:/Qt/6.5.1/msvc2019_64/lib/cmake/Qt6`

* **Qt6GuiTools_DIR** - `[path_to_Qt]/[version]/[compiler]/lib/cmake/Qt6GuiTools`<br/>Example: `/usr/lib/x86_64-linux-gnu/6.5.1/clang_64/lib/cmake/Qt6GuiTools`

* **Qt6CoreTools_DIR** - `[path_to_Qt]/[version]/[compiler]/lib/cmake/Qt6CoreTools`<br/>Example: `D:/Qt/6.3/msvc2019_64/lib/cmake/Qt6CoreTools`

<hr>
</details>

<details><summary><b>Missing</b> or <b>wrong architecture</b> libraries | <i>Conan</i> profile errors</summary>

Ensure `conan/conanfile.txt` has listed all the needed libraries under `[requires]` section.
Run:

```bash
conan install conan/ --build=missing --settings=build_type=Debug
conan install conan/ --build=missing --settings=build_type=Release
```

In case of a **wrong architecture** of the libraries and other possible **profile errors**, read: [https://docs.conan.io/2.0/reference/config_files/profiles.html](https://docs.conan.io/2.0/reference/config_files/profiles.html)<br/>
If you don't have a profile, create one:

```bash
conan profile detect
```

or:
```bash
conan profile new default --detect
```

<hr>
</details>

## Contributing

This project follows these [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), and it would be fun if you followed them too. If you don't, someone will correct your code. An ugly contribution is better than no contribution. **Thanks**!

## License

This project is licensed under the [LGPL 2.1](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html#SEC1); see the
[LICENSE](LICENSE) file for details.
It also uses the [Qt](https://www.qt.io/) library and possibly some of its additional modules that are licensed under the [LGPL](https://www.gnu.org/licenses/lgpl-3.0.en.html), but **none** of its code is present in this repository. Also note that *Qt* itself uses [other third-party libraries](https://doc.qt.io/qt-6/licenses-used-in-qt.html) under **different** license terms.

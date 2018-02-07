# The Lyt Library
*Lyt* is a C++ library and command-line tool for rapid prototyping of audio applications. It gives the programmer the ability to utilize the features and speed of C++, without having to go through the usual ceremony of setting up such a project.

*Lyt* comes *batteries included* — many oft used DSP routines are included as well as utilities for reading and writing audio files. Many of these features are not implemented yet, but will in the future.

In addition to the C++ library there is the `lyt` command-line tool which gives you a scripting-language like experience of writing C++ code. Write your C++ program and run `lyt`, and it will take care of all compilation and linking for you.

## Dependencies
To build use *Lyt* you will need the following software

* A C++ compiler (clang preferred).
* Make (preferably GNU Make).
* Python 2.7 or later.

Additionally you will need the following libraries

* [libsndfile](http://www.mega-nerd.com/libsndfile/), easily installed via `apt-get install sndfile` on linux or `brew install sndfile` on mac (via [homebrew](https://brew.sh/)).

Make sure that these are in your *PATH*, otherwise header inclusion and linking wont work.

## Installing on unix-like systems

Fire up your terminal and run the following commands:

```
$ git clone https://github.com/PelleJuul/lyt.git
$ cd lyt
$ make install
```

Which will install Lyt to */usr/local/*. Set the `PREFIX` variable to change the installation location.

## Installing on Windows
Installation and use on Windows is still in **very** early development, but the general steps should be:

* Install [MinGW](http://www.mingw.org/) including MSYS.
* Clone this repository
* Run `make install -D PREFIX=myprefix/` with a suitable prefix in the MSYS shell.
* Make sure that your chosen prefix is in your *PATH*.

The lyt tool is still not compatible with windows. Instead you can try to build the scripts with the command

```
$ g++ --std=c++11 -lsndfil -llyt lyt_file.cpp -o lyt_file.exe
```

## Using Lyt
*Lyt* is used by writing a C++ program and then running or building it using the `lyt` command-line tool. After installing *Lyt* you can test it on one of the examples in
the *examples* directory.

The most basic of the examples is the *test_tone* example. 

```
#include <lyt/lyt.h>
#include <cmath>

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(44100); 
    buf.mapt([&](float t, float v)
    {
        return std::sin(2 * M_PI * t * 440.0);
    });

    buf.writeFile("output.wav");
    return 0;
}
```

When run this will create a one second long wav file, called *output.wav*, containing a *440Hz* sine tone. Lets look at each statement of the code. First

```
auto buf = Buffer::zero(44100); 
```

creates a new audio buffer of *44100* samples. The default sample rate is *44100* so this will be one second of audio. Next statement we have

```
buf.mapt([&](float t, float v)
{
    return std::sin(2 * M_PI * t * 440.0);
});
```

The `mapt` function is a higher order function — it takes another function as its arguemnt. The given function will take the time `t` and value `v` of each sample
and return a resulting sample. In this case we only use the time `t` to compute and return a sine wave.

Lastly we have

```
buf.writeFile("output.wav");
```

Which writes the audio contained in the buffer `buf` to the file *output.wav*.

*Pretty soon there will be a complete reference for all of the functionality contained in lyt. Until then it can be useful to look throgh the header files in the library directory*

## Contributing
Please contribute to *Lyt* and help make it awesome! Some of the ways you can contribute:

* Use *Lyt* for making cool audio apps and give us feedback, suggestions and bug reports using GitHub issues.
* Try to install *Lyt* on new operating systems.
* Try to use lyt combined with other software packages.
* Add new features to the *Lyt* library or tool.

Some features that are *todo* or that could be cool to have are:

* A fractional delay line.
* Spectral analysis tools.
* More oscillators and filters.
* A fractional delay line.
* Tools for physical modelling.
* Real time audio.
* Simple GUI and interactivity tools.
* Add more filter types to the `Biquad` class.
* Implement common audio effects such as echo, flanger, chorus, reverb, distortion and compression as `Processor`s.
* Whatever you'd like that's cool!

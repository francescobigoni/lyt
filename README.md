# The Lyt Library
*Lyt* is a C++ library and command-line tool for rapid prototyping of audio applications. It gives the programmer the ability to utilize the features and speed of C++, without having to go through the usual ceremony of setting up such a project.

Lyt comes *batteries included* --- many oft used DSP routines are included as well as utilities for reading and writing audio files. Many of these features are not implemented yet, but will in the future.

In addition to the C++ library there is the `lyt` command-line tool which gives you a scripting-language like experience of writing C++ code. Write your C++ program and run `lyt`, and it will take care of all compilation and linking for you.

## Building and dependencies
To build use Lyt you will need the following software

* A C++ compiler (clang preferred)
* GNU Make
* Python 2.7 or later

Additionally you will need the following libraries

* [libsndfile](http://www.mega-nerd.com/libsndfile/), easily install via `apt-get install sndfile` or `brew install sndfile`

You install Lyt by running

```
make install
```

Which will install Lyt to */usr/local/*. Set the `PREFIX` variable to change the installation location.

# Examples
This directory contains example *Lyt* applications. To run an example, make sure that *Lyt* is installed and that `lyt` is in your path, then run for example:

```
$ cd test_tone
$ lyt run test_tone.cpp
```

All of the examples are:

* `clarinet` — Physical model of a clarinet
* `echo` — Shows the use of the `Delay` class to create an echo effect.
* `karplus_strong` — Basic Karplus-Strong string synthesis.
* `karplus_strong_triangle` — Basic Karplus-Strong string synthesis with triangular pluck model.
* `karplus_strong_variable_pluck` — Basic Karplus-Strong string synthesis with variable pluck position.
* `test_tone` — Shows the basic use of the `Buffer` class and the `mapt` function.
* `two_tones` — Show the use of the `append` function of the `Buffer` class.

Each example will write a output file called `output.wav`

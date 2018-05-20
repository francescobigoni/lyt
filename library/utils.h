extern double pi;

/** Converts from seconds to number samples.
    
    @param  seconds     The number of seconds to convert to samples.
*/
int samples(float seconds);

/** Convertes from number of samples to seconds

    @param  samples     The number of samples to convert to seconds.
*/
float seconds(int samples);

/** Returns a random float in the range [0:1).
*/
float randNum();

/** Calculates the frequency of the given MIDI note number

    @param  note        The MIDI note to calculate the frequency of.
*/
float noteToFreq(int note);

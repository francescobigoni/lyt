#pragma once

/// A resonator implementation to be used for modal synthesis. It discretizes
/// the mass-spring-damper model
///     
///     u_tt = f/m - g * u_t - w^2 * u
///
/// found in *The Sounding Object, Rocchesso and Fontana* section 8.2. 
/// Discretization was done using methods found in *Numerical Sound Synthesis,
/// Bilbao*.
class Resonator
{
public:
	/// Initializes a resonator with a frequency of 440Hz, a T60 decay of 1.0,
	/// a mass of 0.01 at a samplerate of 44100. This can be changed afterwards
    /// by calling setParams().
	Resonator();

	/// Initializes a new resonator with the given parameters.
	/// @param freq        The frequency of the resonator (in Hz).
	/// @param decay       The T60 decay of the resonator (in seconds).
	/// @param mass        The mass of the resonator (in Kg).
	/// @param samplerRate The sample rate to use.
	Resonator(double freq, double decay, double mass, double sampleRate);

    /// Initializes a new resonator with the given parameters.
    /// @param freq        The frequency of the resonator (in Hz).
    /// @param decay       The T60 decay of the resonator (in seconds).
    /// @param mass        The mass of the resonator (in Kg).
    /// @param samplerRate The sample rate to use.
    void setParams(double freq, double decay, double mass, double sampleRate);

    /// Sets the state of the resonator. This can have a severe impact on the
    /// current simulator. Call only after setParams() as been called.
    /// @param displacement The new displacement of the resonator.
    /// @param velocity     The new velocity of the resonator.
    void setState(double displacement, double velocity);

    /// Sets the force acting on the resonator.
    /// @param force The force to apply (newtons).
    void setForce(double force);

    /// Run one update loop of the model. Returns the current displacement.
    double next();

private:
    double g;           // Dampening
    double m;           // Mass
    double w;           // Angular frequency
    double f;           // External force
    double k;           // Sample period
    double a;           // Model constant
    double b;           // Model constant
    double c;           // Model constant
    double u0;          // State variable one (displacement)
    double u1;          // State variable two
};
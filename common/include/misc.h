#ifndef MISC_H
#define MISC_H
#include <cmath>

float triangle_wave_fast(float t, float period)
{
    // Offset t by period/4 to align it with Sin (starts at 0)
    // instead of Cos (starts at 1)
    float shifted_t = t - (period / 4.0f);

    // Create a sawtooth wave
    float sawtooth = fmod(shifted_t, period);
    if (sawtooth < 0)
        sawtooth += period; // Handle negative inputs

    // Fold the sawtooth into a triangle
    return (2.0f / period) * fabs(sawtooth - (period / 2.0f)) - 0.5f;
}

float random_float(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; // [0, 1.0]
    return min + scale * (max - min);       // [min, max]
}

#endif // MISC_H

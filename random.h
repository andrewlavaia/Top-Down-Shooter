
#ifndef RANDOM_H
#define RANDOM_H

#include <random>
using namespace std;
/*
class Random
{
private:
    // Types
    typedef std::mt19937                                 Engine;
    typedef std::uniform_real_distribution<float>        Distribution;
    //typedef std::variate_generator<Engine, Distribution> Generator;

    // To hold the generator
    Generator* _gen;

public:
    Random( int seed, float minVal, float maxVal )
    {
        _gen = new Generator( Engine( seed ), Distribution( minVal, maxVal ) );
    }

    ~Random()
    {
        delete _gen;
    }

    float next()
    {
        return (*_gen)();
    }
};
*/
#endif


#ifndef HELPERS_H
#define HELPERS_H

#include <sstream> // to_str
#include <iomanip>
#include <random>
#include <chrono>

// converts number to std::string
// needed because current mingw gcc does not support std::to_string()
template <typename T>
std::string to_string(const T& t)
{
  std::ostringstream os;
  os << t;
  return os.str();
}
template <typename T>
std::string to_string(const T& t, unsigned p)
{
  std::ostringstream os;
  os << std::fixed << std::setprecision(p) << t;
  return os.str();
}

// Produce a random value according to a normal distribution
template <typename T>
T rand_normal(const T& mean, const T& sd)
{
  unsigned long seed =
    std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
  std::mt19937 gen(seed);

  std::normal_distribution<> dist(mean, sd);
  return dist(gen);
}

// Produce a random integer according to a uniform distribution (discrete)
template <typename T>
int rand_uniform_int(const T& minimum, const T& maximum)
{
  unsigned long seed =
    std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
  std::mt19937 gen(seed);

  std::uniform_int_distribution<> dist(minimum, maximum);
  return dist(gen);
}

// Produce a random double according to a uniform distribution (continuous)
template <typename T>
double rand_uniform_double(const T& minimum, const T& maximum)
{
  unsigned long seed =
    std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
  std::mt19937 gen(seed);

  std::uniform_real_distribution<> dist(minimum, maximum);
  return dist(gen);
}

#endif

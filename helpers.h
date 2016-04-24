
#ifndef HELPERS_H
#define HELPERS_H

#include <sstream> // to_str
#include <iomanip>

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

#endif

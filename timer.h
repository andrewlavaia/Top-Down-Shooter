#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>
#include <iostream>

class Timer
{
public:
  double PCFreq = 0.0;
  __int64 CounterStart = 0;

  void StartCounter()
  {
      LARGE_INTEGER li;
      if(!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

      PCFreq = double(li.QuadPart)/1000.0; //converts to milliseconds

      QueryPerformanceCounter(&li);
      CounterStart = li.QuadPart;
  }
  double GetCounter()
  {
      LARGE_INTEGER li;
      QueryPerformanceCounter(&li);
      return double(li.QuadPart-CounterStart)/PCFreq;
  }

};


#endif // TIMER_H

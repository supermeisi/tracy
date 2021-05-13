#ifndef TRACE_HH
#define TRACE_HH

#include <iostream>
#include <thread>

#include "TRandom2.h"

#include "sphere.hh"

class Trace
{
public:
    Trace();
    
    void SetNCores(int _n_cores) { n_cores = _n_cores; }
    bool Processing();
    bool Run();

private:
    int n_cores;
    std::thread th[100];
};

#endif //TRACE_HH

#include <iostream>

#include "trace.hh"

int main(int argc, char** argv)
{
    Trace *trace = new Trace();
    
    trace->SetNCores(9);
    trace->Run();

    delete trace;
    
    return 0;
}

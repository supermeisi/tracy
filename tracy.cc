#include <iostream>

#include "trace.hh"

int main(int argc, char** argv)
{
    Trace *trace = new Trace();
    
    trace->Run();
    
    return 0;
}

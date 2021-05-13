#include <iostream>

#include "TApplication.h"

#include "trace.hh"

int main(int argc, char** argv)
{
    TApplication app("tracy", &argc, argv);

    Trace *trace = new Trace();
    
    trace->SetNCores(8);
    trace->Run();

    delete trace;

    app.Run(1);
    
    return 0;
}

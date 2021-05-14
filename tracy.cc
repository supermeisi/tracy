#include <iostream>

#include "TApplication.h"

#include "trace.hh"

int main(int argc, char** argv)
{
    TApplication app("tracy", &argc, argv);

    Trace *trace = new Trace();
    
    trace->SetNCores(4);

    Sphere *sp = new Sphere();
    sp->SetPosition(0., 0., 3.);
    sp->SetRadius(1.);

    trace->AddObject(sp);

    trace->Run();

    delete trace;

    app.Run(1);
    
    return 0;
}

#include <iostream>

#include "TApplication.h"

#include "trace.hh"

int main(int argc, char** argv)
{
    TApplication app("tracy", &argc, argv);

    Trace *trace = new Trace();
    
    trace->SetNCores(1);

    Sphere *sp = new Sphere();
    sp->SetPosition(0., 0., 3.);
    sp->SetRadius(1.);

    Detector *det = new Detector();
    det->SetPosition(0., 0., 5);

    trace->AddObject(sp);
    trace->AddObject(det);

    trace->Run();

    delete trace;

    app.Run(1);
    
    return 0;
}

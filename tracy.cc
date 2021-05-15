#include <iostream>

#include "TApplication.h"

#include "trace.hh"

int main(int argc, char** argv)
{
    TApplication app("tracy", &argc, argv);

    Trace *trace = new Trace();
    
    trace->SetNCores(1);

    Sphere *sp = new Sphere();
    sp->SetPosition(0.2, 0., 6.);
    sp->SetRadius(1.);

    Sphere *sp2 = new Sphere();
    sp2->SetPosition(0.1, 0., 3.);
    sp2->SetRadius(1.);

    Detector *det = new Detector();
    det->SetPosition(0., 0., 9.);

    trace->AddObject(sp);
    trace->AddObject(sp2);
    trace->AddObject(det);

    trace->Run();

    delete trace;

    app.Run(1);
    
    return 0;
}

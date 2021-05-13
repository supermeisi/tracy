#include "trace.hh"

Trace::Trace()
{}

bool Trace::Run()
{
    std::cout << "Start tracing..." << std::endl;

    Sphere *sp = new Sphere();
    sp->SetPosition(0., 0., 10.);
    sp->SetRadius(2.);

    TRandom2 *rand = new TRandom2();

    for(int i = 0; i < 10; i++)
    {
        TVector3 r(-0.5+rand->Rndm()*1.,-0.5+rand->Rndm()*1.,0.);
        TVector3 p(0., 0., 1.);

        double lambda = sp->GetLambda(r, p);

        std::cout << "Lambda: " << lambda << std::endl;
    }

    std::cout << "End tracing..." << std::endl;
}

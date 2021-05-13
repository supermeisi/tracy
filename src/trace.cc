#include "trace.hh"

Trace::Trace()
{
    n_cores = 1;
}

bool Trace::Processing()
{
    Sphere *sp = new Sphere();
    sp->SetPosition(0., 0., 10.);
    sp->SetRadius(2.);

    TRandom2 *rand = new TRandom2();

    TVector3 r, p;

    for(int i = 0; i < 1000000; i++)
    {
        r.SetX(-0.5+rand->Rndm()*1);
        r.SetY(-0.5+rand->Rndm()*1.);
        r.SetZ(0.);

        p.SetX(0.);
        p.SetY(0.);
        p.SetZ(1.);

        double lambda = sp->GetLambda(r, p);

        std::cout << "Lambda: " << lambda << std::endl;
    }

    return true;
}

bool Trace::Run()
{
    std::cout << "Start tracing..." << std::endl;

    for(int i = 0; i < n_cores; i++)
    {
        th[i] = std::thread(&Trace::Processing, this);
    }

    for(int i = 0; i < n_cores; i++)
    {
        th[i].join();
    }

    std::cout << "End tracing..." << std::endl;

    return true;
}

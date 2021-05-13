#include "trace.hh"

Trace::Trace()
{
    n_cores = 1;

    rand = new TRandom2();

    physics = new Physics();

    n_world = 1.; //World refractive index

    sp = new Sphere();
    sp->SetPosition(0., 0., 3.);
    sp->SetRadius(1.);

    det = new Detector();
    det->SetPosition(0., 0., 4.);
}

bool Trace::Processing()
{
    TVector3 r, p, n;

    for(int i = 0; i < 10000; i++)
    {
        r.SetX(-0.5+rand->Rndm()*1.);
        r.SetY(-0.5+rand->Rndm()*1.);
        r.SetZ(0.);

        p.SetX(0.);
        p.SetY(0.);
        p.SetZ(1.);

        for(int j = 0; j < 2; j++)
        {
            double lambda = sp->GetLambda(r, p);

            std::cout << "Lambda: " << lambda << std::endl;

            r  = lambda*p + r; //Propagate ray to object

            n = sp->GetNormal(r); //Get normal vector of object

            //Calculate refraction
            if(p.Dot(n) > 0)
            {
                p = physics->Refraction(p, n, n_world, sp->GetRefIndex());
            }
            else
            {
                p = physics->Refraction(p, -n, sp->GetRefIndex(), n_world);
            }
        }

        double lambda = det->GetLambda(r, p);

        std::cout << "Lambda: " << lambda << std::endl;

        r  = lambda*p + r;

        std::cout << r.X() << " " << r.Y() << " " << r.Z() << std::endl;

        det->Hit(r.X(), r.Y());
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

    det->Display();

    return true;
}

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
    det->SetPosition(0., 0., 4.5);

    verbose = false;

    c1 = new TCanvas("c1", "c1", 500, 500);

    view = TView::CreateView(1);
    view->SetRange(-10.,-10.,-1.,300.,300.,300.);

    man = new TGeoManager();
    top = gGeoManager->MakeBox("TOP",NULL,10,10,10);
    man->SetTopVolume(top);
}

bool Trace::Processing()
{
    TVector3 r, p, n;

    for(int i = 0; i < 10000000; i++)
    {
        double r0 = 0.5*sqrt(rand->Rndm());
        double theta0 = 2*TMath::Pi()*rand->Rndm();

        r.SetX(r0*cos(theta0));
        r.SetY(r0*sin(theta0));
        r.SetZ(0.);

        p.SetX(0.);
        p.SetY(0.);
        p.SetZ(1.);

        for(int j = 0; j < 2; j++)
        {
            double lambda = sp->GetLambda(r, p);

            if(verbose)
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

        r  = lambda*p + r;

        if(verbose)
        {
            std::cout << "Lambda: " << lambda << std::endl;
            std::cout << r.X() << " " << r.Y() << " " << r.Z() << std::endl;
        }

        det->Hit(r.X(), r.Y());

    }

    return true;
}

bool Trace::Run()
{
    std::cout << "Start tracing..." << std::endl;

    top->Draw();

    sp->Draw(*man, *top);

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

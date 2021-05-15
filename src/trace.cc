#include "trace.hh"

Trace::Trace()
{
    n_cores = 1;

    lambda_min_init = 0.;

    rand = new TRandom2();

    physics = new Physics();

    n_world = 1.; //World refractive index

    verbose = true;

    c1 = new TCanvas("c1", "c1", 500, 500);

    view = TView::CreateView(1);
    view->SetRange(-10.,-10.,-1.,300.,300.,300.);

    man = new TGeoManager();
    top = gGeoManager->MakeBox("TOP",NULL,10,10,10);
    man->SetTopVolume(top);
}

int Trace::GetMinimum(const TVector3 &r, const TVector3 &p)
{
    int id = 0;

    double lambda_min = 0.;

    //Find initial value
    for(int k = 0; k < objarr.size(); k++)
    {
        if(objarr[k]->GetLambda(r, p) > 1e-12)
        {
            lambda_min = objarr[k]->GetLambda(r, p);
            break;
        }
    }

    if(lambda_min == lambda_min_init) return 0;

    //Find minimum lambda value
    for(int k = 0; k < objarr.size(); k++)
    {
        double lambda = objarr[k]->GetLambda(r, p);

        if(lambda < lambda_min && lambda > 1e-12)
        {
            lambda_min = lambda;
            id = k;
        }
    }

    return id;
}

bool Trace::Processing()
{
    TVector3 r, p, n;

    int n_rays = 100000;
    int n_draw = 10;
    int modulo = n_rays/n_draw;

    std::vector<TGeoTrack*> track;

    if(verbose)
        std::cout << "Modulo: " << modulo << std::endl;

    for(int i = 0; i < n_rays; i++)
    {
        bool draw = false;

        if(i%modulo == 0)
        {
            draw = true;
            track.push_back(new TGeoTrack());
            track[track.size()-1]->SetLineColor(kRed);
        }

        double r0 = 0.5*sqrt(rand->Rndm());
        double theta0 = 2*TMath::Pi()*rand->Rndm();

        r.SetX(r0*cos(theta0));
        r.SetY(r0*sin(theta0));
        r.SetZ(0.);

        p.SetX(0.);
        p.SetY(0.);
        p.SetZ(1.);

        if(draw) track[track.size()-1]->AddPoint(r.X(), r.Y(), r.Z(), track[track.size()-1]->GetNpoints());

        //Maximum number of intersections
        for(int j = 0; j < 10; j++)
        {
            //Finding minimum line parameter
            int id = GetMinimum(r, p);
            double lambda_min = objarr[id]->GetLambda(r, p);

            //Check if lambda is a real number
            if(lambda_min != lambda_min)
                break;

            if(verbose)
                std::cout << "Lambda: " << lambda_min << std::endl;

            r  = lambda_min*p + r; //Propagate ray to object

            n = objarr[id]->GetNormal(r); //Get normal vector of object

            //Calculate refraction
            if(p.Dot(n) > 0)
            {
                p = physics->Refraction(p, n, n_world, objarr[id]->GetRefIndex());
            }
            else
            {
                p = physics->Refraction(p, -n, objarr[id]->GetRefIndex(), n_world);
            }

            if(draw) track[track.size()-1]->AddPoint(r.X(), r.Y(), r.Z(), track[track.size()-1]->GetNpoints());

            if(objarr[id]->GetKillTrack())
                break;
        }
    }

    return true;
}

bool Trace::Run()
{
    std::cout << "Start tracing..." << std::endl;

    top->Draw();

    for(int i = 0; i < objarr.size(); i++)
    {
        objarr[i]->Draw(*man, *top);
    }

    for(int i = 0; i < n_cores; i++)
    {
        th[i] = std::thread(&Trace::Processing, this);
    }

    for(int i = 0; i < n_cores; i++)
    {
        th[i].join();
    }

    std::cout << "End tracing..." << std::endl;

    //det->Display();

    return true;
}

#include "trace.hh"

Trace::Trace()
{
    n_cores = 1;
    n_draw = 100;

    lambda_min_init = 0.;

    physics = new Physics();

    n_world = 1.; //World refractive index

    verbose = false;

    man = new TGeoManager();
    top = gGeoManager->MakeBox("TOP",NULL,10,10,10);
    man->SetTopVolume(top);
}

int Trace::GetMinimum(const TVector3 &r, const TVector3 &p)
{
    int id = -1;

    double lambda_min = 0.;

    //Find initial value
    for(int k = 0; k < objarr.size(); k++)
    {
        if(objarr[k]->GetLambda(r, p) > 1e-12)
        {
            lambda_min = objarr[k]->GetLambda(r, p);
            id = k;
            break;
        }
    }

    if(lambda_min == lambda_min_init)
        return -1;

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

    //Loop over all sources
    for(int i = 0; i < srcarr.size(); i++)
    {
        int n_rays = srcarr[i]->GetNRays();
        int modulo = n_rays/n_draw;

        if(verbose)
            std::cout << "Modulo: " << modulo << std::endl;

        //Loop over all rays
        for(int j = 0; j < n_rays; j++)
        {
            bool draw = false;

            r = srcarr[i]->GetPosition();
            p = srcarr[i]->GetDirection();

            if(j%modulo == 0)
            {
                draw = true;
                mtx.lock();
                track.push_back(new TPolyLine3D());
                track[track.size()-1]->SetLineColor(kRed);
                mtx.unlock();
            }

            if(draw)
            {
                mtx.lock();
                track[track.size()-1]->SetPoint(0, r.X(), r.Y(), r.Z());
                mtx.unlock();
            }

            if(verbose)
                std::cout << "Ray ID: " << i << std::endl;

            //Maximum number of intersections per light ray
            for(int k = 0; k < 10; k++)
            {
                //Finding minimum line parameter
                int id = GetMinimum(r, p);

                //Kill rays that do not hit any ob1ect
                if(id < 0)
                {
                    if(verbose)
                        std::cout << "Ray finished..." << std::endl;
                    break;
                }

                double lambda_min = objarr[id]->GetLambda(r, p);

                if(verbose)
                {
                    std::cout << "Object ID: " << id << std::endl;
                    std::cout << "Lambda: " << lambda_min << std::endl;
                }

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

                if(draw) track[track.size()-1]->SetPoint(k+1, r.X(), r.Y(), r.Z());

                if(objarr[id]->GetKillTrack())
                {
                    if(verbose) std::cout << "Ray killed..." << std::endl;
                    if(objarr[id]->IsDetector())
                    {
                        mtx.lock();
                        objarr[id]->Hit(r.X(), r.Y());
                        mtx.unlock();
                    }
                    break;
                }
            }
        }
    }

    return true;
}

bool Trace::Run()
{
    std::cout << "Start tracing..." << std::endl;

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

    man->CloseGeometry();
    top->Draw("ogl");

    //Draw rays
    for(int i = 0; i < track.size(); i++)
    {
        track[i]->Draw("same");
    }

    TGLViewer * v = (TGLViewer *)gPad->GetViewer3D();
    v->SetStyle(TGLRnrCtx::kWireFrame);

    //Show detector
    for(int i = 0; i < objarr.size(); i++)
    {
        if(objarr[i]->IsDetector()) objarr[i]->Display();
    }

    return true;
}

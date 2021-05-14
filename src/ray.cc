#include "ray.hh"

Ray::Ray()
{}

Ray::~Ray()
{}

void Ray::Draw()
{
    TGeoTrack *track = new TGeoTrack();
    track->SetLineColor(kRed);
    
    for(Int_t i = 0; i < vtx.size(); i++)
    {
        TVector3 r = vtx[i]->GetPosition();
        track->AddPoint(r.X(), r.Y(), r.Z(), i);
    }
    
    track->Draw();
}

void Ray::Print()
{
    for(Int_t i = 0; i < vtx.size(); i++)
    {
        TVector3 r = vtx[i]->GetPosition();
        TVector3 p = vtx[i]->GetDirection();

        std::cout << "Vertex " << i << std::endl;
        std::cout << "Position: " << "(" << r.X() << ", " << r.Y() << ", " << r.Z() << ")" << std::endl;
        std::cout << "Direction: " << "(" << p.X() << ", " << p.Y() << ", " << p.Z() << ")" << std::endl;
    }
}

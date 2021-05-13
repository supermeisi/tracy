#include "physics.hh"

Physics::Physics()
{}

TVector3 Physics::Refraction(TVector3 e, TVector3 n, double n1, double n2)
{
    double ex = e.X();
    double ey = e.Y();
    double ez = e.Z();

    double nx = n.X();
    double ny = n.Y();
    double nz = n.Z();

    double ax = (nx*sqrt(((ez*ez+ey*ey+ex*ex)*n2*n2+(-ey*ey-ex*ex)*n1*n1)*nz*nz+(2*ey*ez*n1*n1*ny+2*ex*ez*n1*n1*nx)*nz+((ez*ez+ey*ey+ex*ex)*n2*n2+(-ez*ez-ex*ex)*n1*n1)*ny*ny+2*ex*ey*n1*n1*nx*ny+n2*n2*(ez*ez*nx*nx+ey*ey*nx*nx+ex*ex*nx*nx)+n1*n1*(-ez*ez*nx*nx-ey*ey*nx*nx))+ex*n1*nz*nz-ez*n1*nx*nz+ex*n1*ny*ny-ey*n1*nx*ny)/(n2*nz*nz+n2*ny*ny+n2*nx*nx);

    double ay = (ny*(sqrt(((ez*ez+ey*ey+ex*ex)*n2*n2+(-ey*ey-ex*ex)*n1*n1)*nz*nz+(2*ey*ez*n1*n1*ny+2*ex*ez*n1*n1*nx)*nz+((ez*ez+ey*ey+ex*ex)*n2*n2+(-ez*ez-ex*ex)*n1*n1)*ny*ny+2*ex*ey*n1*n1*nx*ny+n2*n2*(ez*ez*nx*nx+ey*ey*nx*nx+ex*ex*nx*nx)+n1*n1*(-ez*ez*nx*nx-ey*ey*nx*nx))-ex*n1*nx)+ey*n1*nz*nz-ez*n1*ny*nz+ey*n1*nx*nx)/(n2*nz*nz+n2*ny*ny+n2*nx*nx);

    double az = -(nz*(-sqrt(((ez*ez+ey*ey+ex*ex)*n2*n2+(-ey*ey-ex*ex)*n1*n1)*nz*nz+(2*ey*ez*n1*n1*ny+2*ex*ez*n1*n1*nx)*nz+((ez*ez+ey*ey+ex*ex)*n2*n2+(-ez*ez-ex*ex)*n1*n1)*ny*ny+2*ex*ey*n1*n1*nx*ny+n2*n2*(ez*ez*nx*nx+ey*ey*nx*nx+ex*ex*nx*nx)+n1*n1*(-ez*ez*nx*nx-ey*ey*nx*nx))+ey*n1*ny+ex*n1*nx)-ez*n1*ny*ny-ez*n1*nx*nx)/(n2*nz*nz+n2*ny*ny+n2*nx*nx);

    TVector3 a(ax, ay, az);

    return a;
}

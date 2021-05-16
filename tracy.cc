#include <iostream>
#include <fstream>
#include <sstream>

#include "TApplication.h"

#include "trace.hh"

int main(int argc, char** argv)
{
    TApplication app("tracy", &argc, argv);

    Trace *trace = new Trace();
    
    std::ifstream is_file;
    is_file.open("config.ini");

    std::string line;

    while(std::getline(is_file, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if(std::getline(is_line, key, '='))
        {
            std::string value;
            if( std::getline(is_line, value))
            {
                if(key == "threads")
                {
                    std::cout << "Number of threads: " << value << std::endl;
                    trace->SetNCores(stoi(value));
                }
                if(key == "verbose")
                {
                    std::cout << "Verbose: " << value << std::endl;
                    trace->SetVerbose(stoi(value));
                }
                if(key == "draw")
                {
                    std::cout << "Maximum shown rays: " << value << std::endl;
                    trace->SetNVisibleRays(stoi(value));
                }
            }
        }
    }

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

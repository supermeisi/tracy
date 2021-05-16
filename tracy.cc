#include <iostream>
#include <fstream>
#include <sstream>

#include "TApplication.h"

#include "trace.hh"

int main(int argc, char** argv)
{
    TApplication app("tracy", &argc, argv);

    Trace *trace = new Trace();
    
    //Reading config file
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

    is_file.close();

    //Reading input file
    std::ifstream input;
    input.open("example.trc");

    while(!input.eof())
    {
        std::string value;
        input >> value;
        if(value == "Sphere")
        {
            std::cout << "Adding sphere" << std::endl;

            Sphere *sp = new Sphere();
            double xm, ym, zm, R;

            input >> xm >> ym >> zm >> R;

            sp->SetPosition(xm, ym, zm);
            sp->SetRadius(R);

            trace->AddObject(sp);
        }
        if(value == "Detector")
        {
            std::cout << "Adding detector" << std::endl;

            Detector *det = new Detector();
            double xm, ym, zm;

            input >> xm >> ym >> zm;

            det->SetPosition(xm, ym, zm);

            trace->AddObject(det);
        }
    }

    input.close();

    trace->Run();

    delete trace;

    app.Run(1);
    
    return 0;
}

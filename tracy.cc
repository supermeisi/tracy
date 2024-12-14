#include <iostream>
#include <fstream>
#include <sstream>

#include "TApplication.h"

#include "tinyxml2.hh"
#include "trace.hh"

int main(int argc, char **argv)
{
    TApplication app("tracy", &argc, argv);

    Trace *trace = new Trace();

    // Reading config file
    std::ifstream is_file;
    is_file.open("config.ini");

    std::string line;

    while (std::getline(is_file, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '='))
        {
            std::string value;
            if (std::getline(is_line, value))
            {
                if (key == "threads")
                {
                    std::cout << "Number of threads: " << value << std::endl;
                    trace->SetNCores(stoi(value));
                }
                if (key == "verbose")
                {
                    std::cout << "Verbose: " << value << std::endl;
                    trace->SetVerbose(stoi(value));
                }
                if (key == "draw")
                {
                    std::cout << "Maximum shown rays: " << value << std::endl;
                    trace->SetNVisibleRays(stoi(value));
                }
            }
        }
    }

    is_file.close();

    // Reading all important parameters of the scene from the config file
    tinyxml2::XMLDocument scene;
    scene.LoadFile("example.xml");

    tinyxml2::XMLElement *db_node = scene.FirstChildElement("config");
    if (!db_node)
    {
        std::cerr << "Error: 'config' element not found." << std::endl;
        return -1;
    }

    // Iterate over all etnries elements
    for (tinyxml2::XMLElement *etnries = db_node->FirstChildElement(); etnries != nullptr; etnries = etnries->NextSiblingElement())
    {
        const char *name = etnries->Name();

        if (name)
        {
            std::cout << "Found child element with name: " << name << std::endl;
        }

        if (strcmp(name, "objects") == 0)
        {
            std::cout << "Scene elements: " << etnries->Name() << std::endl;

            for (tinyxml2::XMLElement *objects = etnries->FirstChildElement(); objects != nullptr; objects = objects->NextSiblingElement())
            {
                const char *type = etnries->Name();

                if (type)
                {
                    std::cout << "Found scene element: " << type << std::endl;
                }

                const char *value = objects->Attribute("name");

                if (value)
                {
                    std::cout << "  Element 'name': " << value << std::endl;
                }
            }
        }
    }

    // Reading input file
    std::ifstream input;
    input.open("example.trc");

    while (!input.eof())
    {
        std::string value;

        double xm, ym, zm; // Center of origin
        double xa, ya, za; // Rotation angles

        input >> value;

        if (value == "Source")
        {
            std::cout << "Adding source" << std::endl;

            Source *src = new Source();

            int nrays;

            input >> xm >> ym >> zm >> nrays;

            src->SetPosition(xm, ym, zm);
            src->SetNRays(nrays);

            trace->AddSource(src);
        }
        if (value == "Sphere")
        {
            std::cout << "Adding sphere" << std::endl;

            Sphere *sp = new Sphere();
            double R;

            input >> xm >> ym >> zm >> R;

            sp->SetPosition(xm, ym, zm);
            sp->SetRadius(R);

            trace->AddObject(sp);
        }
        if (value == "Detector")
        {
            std::cout << "Adding detector" << std::endl;

            Detector *det = new Detector();

            int nx, ny;

            input >> xm >> ym >> zm >> xa >> ya >> za >> nx >> ny;

            det->SetPosition(xm, ym, zm);
            det->SetRotation(xa, ya, za);
            det->SetBins(nx, ny);

            trace->AddObject(det);
        }
    }

    input.close();

    trace->Run();

    app.Run(1);

    return 0;
}

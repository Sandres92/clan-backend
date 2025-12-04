#include <drogon/drogon.h>
#include <iostream>

int main()
{
    std::cout << "11\n"
              << std::flush;

    // Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", 5555);
    std::cout << "22\n"
              << std::flush;

    // Load config file
    // drogon::app().loadConfigFile("../config.json");
    // drogon::app().loadConfigFile("../config.yaml");
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    std::cout << "33\n"
              << std::flush;
    return 0;
}

#include <iostream>
#include "application.hpp"
#include "define.hpp"
#include <filesystem>
int main(){

    const std::string title = "Environnement générator";
    const uint width = 1280;
    const uint height = 720;

    try {
        
        ENV_GEN::Application app(title, width, height);
		return app.run();

    } catch ( const std::exception & e ) {
		std::cerr << "Exception : " << std::endl << e.what() << std::endl;
		return EXIT_FAILURE;
	}

}
#include <catch2/catch.hpp>

#include "../src/User_Input_Strategy.hpp"
#include "../src/Coordinator.hpp"



TEST_CASE("Test Coordinator menus", "[Coordinator]"){

    

    Coordinator c(new GetLine_Strategy(), new Auto_Input_Strategy(std::string("sean")), new Msg_Output_Strategy() );
    try{
        c.Run();
    } catch (MenuStateException const &e){
        std::cerr << "Menu error: " <<e.what() <<std::endl;
        REQUIRE(false);
    }

    REQUIRE(true);
}
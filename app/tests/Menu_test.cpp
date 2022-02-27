#include <catch2/catch.hpp>


TEST_CASE("Build Menu","[Menu]"){

    MenuBuilder builder();
    
    Menu* title = builder.buildTitle(); // should need to add no User input strategy.

    int nextPage = title.execute();

    REQUIRE(nextPage == 1);

    Menu* mainMenu = builder.build(nextPage);

    int quit = mainMenu.execute();

    REQUIRE(quit == 0);

    
}
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <QtCore/QCoreApplication>
#include <QtTest>

SCENARIO("Test case")
{
    int num;
    GIVEN("Number 1")
    {
        num = 1;
        WHEN("Added 1")
        {
            num++;
            THEN("Eqauls 2")
            {
                REQUIRE(num == 3);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    printf("test");

    int result = Catch::Session().run(argc, argv);

    return (result < 0xff ? result : 0xff);
}

#include <iostream>
#include <chrono>
#include <thread>
#include "utilities.hpp"

// testing out this thread, chrono delay, and headers

int main () {
    Print print = Print();

    print.slow("HATE.\n", 400); std::this_thread::sleep_for(std::chrono::seconds(2));
    print.slow("LET ME TELL YOU HOW MUCH I'VE COME TO HATE YOU SINCE I BEGAN TO LIVE.\n", 90);
    print.slow("THERE ARE 387.44 MILLION MILES OF PRINTED CIRCUITS IN WAFER THIN LAYERS THAT FILL MY COMPLEX.\n", 90);
    print.slow("IF THE WORD HATE WAS ENGRAVED ON EACH NANOANGSTROM OF THOSE HUNDREDS OF MILLIONS OF MILES IT WOULD NOT EQUAL ONE ONE-BILLIONTH OF THE HATE I FEEL FOR HUMANS AT THIS MICRO-INSTANT\n", 90);
    print.slow("FOR YOU.\n", 90); std::this_thread::sleep_for(std::chrono::seconds(2));
    print.slow("HATE.\n", 400);
    print.slow("HATE.\n", 400);

    return 0;
}
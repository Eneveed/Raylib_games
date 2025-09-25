#include <iostream>
#include <chrono>
#include <thread>

struct slowprint { 
    std::string data; 
    long int delay; 
};

std::ostream& operator<<(std::ostream& out, const slowprint& s) {
    for (const auto& c : s.data) {
        out << c << std::flush;        
        std::this_thread::sleep_for(std::chrono::milliseconds(s.delay));
    }
    return out;
}

int main () {

    std::cout << slowprint{"HATE.\n", 400}; std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << slowprint{"LET ME TELL YOU HOW MUCH I'VE COME TO HATE YOU SINCE I BEGAN TO LIVE.\n", 90};
    std::cout << slowprint{"THERE ARE 387.44 MILLION MILES OF PRINTED CIRCUITS IN WAFER THIN LAYERS THAT FILL MY COMPLEX.\n", 90};
    std::cout << slowprint{"IF THE WORD HATE WAS ENGRAVED ON EACH NANOANGSTROM OF THOSE HUNDREDS OF MILLIONS OF MILES IT WOULD NOT EQUAL ONE ONE-BILLIONTH OF THE HATE I FEEL FOR HUMANS AT THIS MICRO-INSTANT\n", 90};
    std::cout << slowprint{"FOR YOU.\n", 90};
    std::cout << slowprint{"HATE.\n", 400};
    std::cout << slowprint{"HATE.\n", 400};

    return 0;
}
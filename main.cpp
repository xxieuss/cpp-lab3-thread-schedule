#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

void f(char x, int i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::osyncstream(std::cout) << "Action " << i << " of set " << x << " completed.\n";
}

int main() {
    std::osyncstream(std::cout) << "Computation started.\n";
    auto start = std::chrono::steady_clock::now();

    // temporary check
    std::thread test([] { f('a', 3); });
    test.join();

    std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::osyncstream(std::cout) << "Computation finished. Duration: "
                                << elapsed.count() << " seconds.\n";
}
#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>
#include <latch>

void f(char x, int i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::osyncstream(std::cout) << "Action " << i << " of set " << x << " completed.\n";
}

void run(char x, int first, int last, std::latch& done) {
    for (int i = first; i <= last; ++i) {
        f(x, i);
        done.count_down();
    }
}

int main() {
    std::osyncstream(std::cout) << "Computation started.\n";
    auto start = std::chrono::steady_clock::now();

    std::latch before_j(9 + 8); // a + d
    std::latch before_h(9 + 5); // e + b
    std::latch before_i(5 + 7); // g + c
    std::latch before_f(7 + 9 + 6); // j + h + i

    // temporary check
    std::thread test([&] {
        run('g', 1, 5, before_i);
        run('c', 1, 7, before_i);
        before_i.wait();
        f('i', 1);
    });
    test.join();

    std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::osyncstream(std::cout) << "Computation finished. Duration: " << elapsed.count() << " seconds.\n";
}
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

    std::thread t1([&] {
        run('a', 1, 9, before_j);
        before_j.wait();
        run('j', 1, 4, before_f);
        before_f.wait();
        f('f', 1);
    });
    std::thread t2([&] {
        run('e', 1, 9, before_h);
        before_h.wait();
        run('h', 1, 4, before_f);
        before_f.wait();
        f('f', 2);
    });
    std::thread t3([&] {
        run('d', 1, 8, before_j);
        run('b', 5, 5, before_h);
        before_j.wait();
        run('j', 5, 7, before_f);
        before_h.wait();
        run('h', 9, 9, before_f);
        before_f.wait();
        f('f', 3);
    });
    std::thread t4([&] {
        run('g', 1, 5, before_i);
        run('b', 1, 4, before_h);
        before_h.wait();
        run('h', 5, 8, before_f);
        before_f.wait();
        f('f', 4);
    });
    std::thread t5([&] {
        run('c', 1, 7, before_i);
        before_i.wait();
        run('i', 1, 6, before_f);
        before_f.wait();
        f('f', 5);
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::osyncstream(std::cout) << "Computation finished. Duration: " << elapsed.count() << " seconds.\n";
}
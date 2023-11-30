#include <cassert>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <utility>

int main()
{
    auto div2 = [](auto a, auto b) {
        if (b == 0) {
            throw std::overflow_error("Divide by zero (1)");
        }
        return a / b;
    };

    std::packaged_task<int (int, int)> task { div2 };
    std::future<int> fut = task.get_future();

    std::thread thr(std::move(task), 10, 5);
    thr.detach();

    try {
        auto x = fut.get();
        assert(x == 2);
    } catch (std::exception &e) {
        std::cerr << e.what() << " | " << "Divide by zero (2)" << std::endl;
    }

    return 0;
}

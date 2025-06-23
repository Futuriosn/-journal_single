//
// Created by raffaele on 7/24/23.
//


#include <iostream>
#include <thread>
#include "kungfu/yijinjing/time.h"
#include "kungfu/yijinjing/journal_wrapper.h"

using namespace kungfu::yijinjing;

int main(int argc, char *argv[]) {
    auto wr = journal::create_writer("./tmp", "test", data::page_size::Small, 0, false);

    int i = 0;
    while (true) {
        char data[100]{0};
        sprintf(data, "%d, test++++++++++++++end", i);

        std::cout << "write " << data << std::endl;

        wr->write_bytes_with_time(time::now_in_nano(), 100, data, strlen(data));
        i++;

//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
//
// Created by raffaele on 7/24/23.
//

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include "kungfu/yijinjing/time.h"
#include "kungfu/yijinjing/journal_wrapper.h"


using namespace kungfu::yijinjing;

int main(int argc, char *argv[]) {
    auto rd = journal::create_reader(false);
    journal::reader_join(rd, "./tmp", "test", 0, data::page_size::Small, 0);

    while (true) {
        if (rd->data_available()) {
            auto frame = rd->current_frame();
            if (frame) {
                std::cout << frame->data_as_string() << std::endl;
            }
            rd->next();
        }
    }

    return 0;
}
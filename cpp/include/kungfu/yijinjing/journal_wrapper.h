//
// Created by raffaele on 7/25/23.
//

#ifndef JOURNAL_JOURNAL_H
#define JOURNAL_JOURNAL_H

#include <memory>
#include <kungfu/yijinjing/journal/journal.h>
#include <kungfu/yijinjing/simple_locator.h>


namespace kungfu {
    namespace yijinjing {
        namespace journal {
            using writer_ptr = std::shared_ptr<kungfu::yijinjing::journal::writer>;
            using reader_ptr = std::shared_ptr<kungfu::yijinjing::journal::reader>;

            static writer_ptr create_writer(const std::string &home,
                                     const std::string &name,
                                     data::page_size ps = data::page_size::Small,
                                     uint32_t dest_id = 0,
                                     bool lazy = false) {
                data::locator_ptr locptr = std::make_shared<SimpleLocator>(home);
                data::location_ptr loc = data::location::make(name, ps, locptr);
                auto wr = std::make_shared<kungfu::yijinjing::journal::writer>(loc, dest_id, lazy);
                return wr;
            }
            static reader_ptr create_reader(bool lazy = false) {
                auto rd = std::make_shared<kungfu::yijinjing::journal::reader>(false);
                return rd;
            }

            static uint32_t reader_join(reader_ptr rd,
                             const std::string &home,
                             const std::string &name,
                             const int64_t from_time,
                             data::page_size ps = data::page_size::Small,
                             uint32_t dest_id = 0) {
                data::locator_ptr locptr = std::make_shared<SimpleLocator>(home);
                data::location_ptr loc = data::location::make(name, ps, locptr);
                rd->join(loc, dest_id, from_time);
                return loc->uid;
            }
        }
    }
}
#endif //JOURNAL_JOURNAL_H

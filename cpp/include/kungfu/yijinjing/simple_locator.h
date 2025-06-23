//
// Created by raffaele on 7/25/23.
//

#ifndef JOURNAL_SIMPLE_LOCATOR_H
#define JOURNAL_SIMPLE_LOCATOR_H

#include "kungfu/yijinjing/common.h"
#include "kungfu/yijinjing/journal/journal.h"
#include <vector>
#include <algorithm>
#include <sstream>


namespace kungfu {
    namespace yijinjing {
        class SimpleLocator : public data::locator {
            std::string home_;
        public:
            SimpleLocator(const std::string &home) {
                home_ = home;
            }

            bool has_env(const std::string &name) const {
                return ::getenv(name.c_str()) != 0;
            }

            const std::string get_env(const std::string &name) const {
                return ::getenv(name.c_str());
            }

            const std::string layout_dir(data::location_ptr location) const {
                return layout_dir(home_ + "/" + location->path);
            }

            const std::string layout_dir(const std::string &path) const;

            const std::string layout_file(data::location_ptr location, const std::string &name) const {
                std::vector<std::string> parts{
                        layout_dir(location),
                        name + "." + "journal"
                };
                return join(parts.begin(), parts.end(), "/");
            }

            static std::string to_hex(uint32_t n) {
                std::stringstream ss;
                ss << std::hex << n;
                return "0x" + ss.str();
            }

            const std::vector<int> list_page_id(data::location_ptr location, uint32_t dest_id) const;

        private:
            template<typename FwdIt>
            static std::string join(FwdIt from, FwdIt to, const std::string &delim) {
                std::stringstream s;
                for (; from != to; from++) {
                    s << (*from);
                    if ((from + 1) != to)
                        s << delim;
                }
                return s.str();
            }

            static void replace(std::string &org, const std::string &old_value, const std::string &new_value) {
                size_t pos = 0;
                while ((pos = org.find(old_value, pos)) != std::string::npos) {
                    org.replace(pos, old_value.length(), new_value);
                    pos += new_value.length();
                }
            }
        };

    }
}

#endif //JOURNAL_SIMPLE_LOCATOR_H

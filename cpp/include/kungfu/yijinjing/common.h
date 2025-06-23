/*****************************************************************************
 * Copyright [taurus.ai]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#ifndef KUNGFU_YIJINJING_COMMON_H
#define KUNGFU_YIJINJING_COMMON_H

#include <utility>
#include <typeinfo>
#include <vector>
#include <kungfu/common.h>
#include <kungfu/yijinjing/util/util.h>
#include <stdexcept>

namespace kungfu
{
    namespace yijinjing
    {
        /** size related */
        constexpr int KB = 1024;
        constexpr int MB = KB * KB;

        class yijinjing_error : public std::runtime_error
        {
        public:
            explicit yijinjing_error(const std::string &message) : std::runtime_error(message)
            {}
        };

        class event
        {
        public:

            virtual ~event() = default;

            virtual int64_t gen_time() const = 0;

            virtual int64_t trigger_time() const = 0;

            virtual int32_t msg_type() const = 0;

            virtual uint32_t source() const = 0;

            virtual uint32_t dest() const = 0;

            virtual uint32_t data_length() const = 0;

            virtual const char *data_as_bytes() const = 0;

            virtual const std::string data_as_string() const = 0;

            virtual const std::string to_string() const = 0;

            /**
             * Using auto with the return mess up the reference with the undlerying memory address, DO NOT USE it.
             * @tparam T
             * @return a casted reference to the underlying memory address
             */
            template<typename T>
            inline const T &data() const
            {
                return *(reinterpret_cast<const T *>(data_address()));
            }

        protected:
            virtual const void *data_address() const = 0;
        };

        DECLARE_PTR(event)

        namespace data
        {

            enum class page_size : int8_t
            {
                Big,
                Small
            };

            inline std::string get_page_size_name(page_size ps)
            {
                switch (ps)
                {
                    case page_size::Big:
                        return "Big";
                    case page_size::Small:
                        return "Small";
                    default:
                        return "Big";
                }
            }

            FORWARD_DECLARE_PTR(location)

            FORWARD_DECLARE_PTR(locator)

            class locator
            {
            public:
                locator() = default;

                virtual ~locator() = default;

                virtual bool has_env(const std::string &name) const = 0;

                virtual const std::string get_env(const std::string &name) const = 0;

                virtual const std::string layout_dir(location_ptr location) const = 0;

                virtual const std::string layout_file(location_ptr location, const std::string &name) const = 0;

                virtual const std::vector<int> list_page_id(location_ptr location, uint32_t dest_id) const = 0;
            };

            class location : public std::enable_shared_from_this<location>
            {
            public:
                location(const std::string &path, page_size ps, locator_ptr l) :
                        locator(std::move(l)),
                        path(path),
                        ps(ps),
                        uname(path),
                        uid(util::hash_str_32(uname))
                {}

                virtual ~location() = default;

                const std::string path;
                const page_size ps;
                const std::string uname;
                const uint32_t uid;
                const locator_ptr locator;

                static inline location_ptr make(const std::string &path, page_size ps, locator_ptr l)
                {
                    return std::make_shared<location>(path, ps, l);
                }
            };
        }
    }


}

#endif //KUNGFU_YIJINJING_COMMON_H

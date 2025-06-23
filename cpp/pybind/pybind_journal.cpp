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

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include <kungfu/yijinjing/time.h>
#include <kungfu/yijinjing/journal/journal.h>
#include <kungfu/yijinjing/journal/frame.h>
#include <kungfu/yijinjing/util/os.h>
#include <kungfu/yijinjing/util/util.h>
#include <kungfu/yijinjing/journal_wrapper.h>

namespace py = pybind11;

using namespace kungfu::yijinjing;
using namespace kungfu::yijinjing::journal;
using namespace kungfu::yijinjing::util;


class PyEvent : public event {
public:
    int64_t gen_time() const override {
        PYBIND11_OVERLOAD_PURE(int64_t, event, gen_time,)
    }

    int64_t trigger_time() const override {
        PYBIND11_OVERLOAD_PURE(int64_t, event, trigger_time,)
    }

    int32_t msg_type() const override {
        PYBIND11_OVERLOAD_PURE(int64_t, event, msg_type,)
    }

    uint32_t source() const override {
        PYBIND11_OVERLOAD_PURE(int64_t, event, source,)
    }

    uint32_t dest() const override {
        PYBIND11_OVERLOAD_PURE(int64_t, event, dest,)
    }
};


PYBIND11_MODULE(pyd_journal, m) {
    py::enum_<data::page_size>(m, "page_size", py::arithmetic(), "Kungfu Data page_size")
        .value("Big", data::page_size::Big)
        .value("Small", data::page_size::Small)
        .export_values();
    m.def("get_page_size_name", &data::get_page_size_name);

    py::class_<event, PyEvent, std::shared_ptr<event>>(m, "event")
        .def_property_readonly("gen_time", &event::gen_time)
        .def_property_readonly("trigger_time", &event::trigger_time)
        .def_property_readonly("source", &event::source)
        .def_property_readonly("dest", &event::dest)
        .def_property_readonly("msg_type", &event::msg_type)
        .def_property_readonly("data_length", &event::data_length)
        .def_property_readonly("data_as_bytes", &event::data_as_bytes)
        .def_property_readonly("data_as_string", &event::data_as_string)
        .def("to_string", &event::to_string);

    py::class_<frame, event, frame_ptr>(m, "frame")
        .def_property_readonly("gen_time", &frame::gen_time)
        .def_property_readonly("trigger_time", &frame::trigger_time)
        .def_property_readonly("source", &frame::source)
        .def_property_readonly("dest", &frame::dest)
        .def_property_readonly("msg_type", &frame::msg_type)
        .def_property_readonly("frame_length", &frame::frame_length)
        .def_property_readonly("header_length", &frame::header_length)
        .def_property_readonly("data_length", &frame::data_length)
        .def_property_readonly("address", &frame::address)
        .def_property_readonly("data_as_bytes", [](const frame& f) {
            return py::bytes(f.data_as_bytes(), f.data_length());
        })
        .def_property_readonly("data_as_string", &frame::data_as_string)
        .def("has_data", &frame::has_data)
        .def_property_readonly("data_address", [](const frame& f) { return f.address() + f.header_length(); });

    py::class_<reader, reader_ptr>(m, "reader")
        .def("subscribe", &reader::join)
        .def("current_frame", &reader::current_frame)
        .def("seek_to_time", &reader::seek_to_time)
        .def("data_available", &reader::data_available)
        .def("next", &reader::next)
        .def("join", &reader::join)
        .def("dis_join", &reader::disjoin);

    py::class_<writer, writer_ptr>(m, "writer")
        .def("write_str",
             [](const writer_ptr& w, int32_t msg_type, const std::string& data, int64_t trigger_time) {
                 w->write_bytes(msg_type, data.c_str(), data.length(), trigger_time);
             })
        .def("write_bytes",
             [](const writer_ptr& w, int32_t msg_type, char data[], int32_t length, int64_t trigger_time) {
                 w->write_bytes(msg_type, data, length, trigger_time);
             })
        .def("write_bytes_with_time",
             [](const writer_ptr& w, int64_t gen_time, int32_t msg_type, char data[], int length, int64_t trigger_time) {
                 w->write_bytes_with_time(gen_time, msg_type, data, length, trigger_time);
             })
        .def("current_frame_uid", &writer::current_frame_uid)
        .def("mark", &writer::mark)
        .def("mark_with_time", &writer::mark_with_time);

    m.def("create_writer", create_writer);
    m.def("create_reader", create_reader);
    m.def("reader_join", reader_join);
}

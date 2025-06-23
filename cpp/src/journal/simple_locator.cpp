//
// Created by raffaele on 8/18/23.
//

#include "kungfu/yijinjing/simple_locator.h"
#include <filesystem>
#include <regex>
#include <iostream>


using namespace kungfu::yijinjing;

const std::string SimpleLocator::layout_dir(const std::string &path) const {
    std::filesystem::path file_path(path);
    if (!std::filesystem::exists(file_path)) {
        if (!std::filesystem::create_directories(file_path)) {
            throw std::runtime_error("Cannot create directory " + path);
        }
    }

    return path;
}

const std::vector<int> SimpleLocator::list_page_id(data::location_ptr location, uint32_t dest_id) const {
    std::vector<int> page_ids;

    std::string root_path = layout_dir(location);
    std::string regex_str = to_hex(dest_id).substr(2) + ".(*).journal";

    replace(regex_str, ".", "\\.");
    replace(regex_str, "*", ".*");

    for (std::filesystem::directory_iterator iter(root_path);
         iter != std::filesystem::directory_iterator();
         ++iter) {
        std::regex reg = std::regex(regex_str);
        std::smatch what;
        std::string file_name = iter->path().filename().string();
        if (std::regex_search(file_name, what, reg)) {
            auto page_id = what[1];
            page_ids.push_back(std::stoi(page_id));
        }
    }
    std::sort(page_ids.begin(), page_ids.end());
    return page_ids;
}
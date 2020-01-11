// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#ifndef SPDLOG_HEADER_ONLY
#include <spdlog/details/log_msg.h>
#endif

#include <spdlog/details/os.h>

namespace spdlog {
namespace details {

SPDLOG_INLINE log_msg::log_msg(spdlog::source_loc loc, string_view_t logger_name, spdlog::level::level_enum lvl, std::string tag, spdlog::string_view_t msg)
    : logger_name(logger_name)
    , level(lvl)
    , time(os::now())
#ifndef SPDLOG_NO_THREAD_ID
    , thread_id(os::thread_id())
#endif
    , source(loc)
	, tag(tag)
    , payload(msg)
{}

SPDLOG_INLINE log_msg::log_msg(string_view_t logger_name, spdlog::level::level_enum lvl, std::string tag, spdlog::string_view_t msg)
    : log_msg(source_loc{}, logger_name, lvl, tag, msg)
{}

} // namespace details
} // namespace spdlog
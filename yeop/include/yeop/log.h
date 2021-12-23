#pragma once

#include "spdlog/spdlog.h"

#define YEOP_DEFAULT_LOGGER_NAME "yeoplogger"

#if defined(YEOP_PLATFORM_WINDOWS)
#define YEOP_BREAK __debugbreak();
#elif defined (YEOP_PLATFORM_MACOSX)
#define YEOP_BREAK __builtin_debugtrap();
#else
#define YEOP_BREAK __builtin_trap();
#endif

#ifndef YEOP_CONFIG_RELEASE
#define YEOP_TRACE(...) if (spdlog::get(YEOP_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(YEOP_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
#define YEOP_DEBUG(...)	if (spdlog::get(YEOP_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(YEOP_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);}
#define YEOP_INFO(...)	if (spdlog::get(YEOP_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(YEOP_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
#define YEOP_WARN(...)	if (spdlog::get(YEOP_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(YEOP_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
#define YEOP_ERROR(...)	if (spdlog::get(YEOP_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(YEOP_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
#define YEOP_FATAL(...)	if (spdlog::get(YEOP_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(YEOP_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}
#define YEOP_ASSERT(x, msg) if ((x)) {} else { YEOP_FATAL("ASSERT - {}\n\t{}\n\tin file: {} && on line: {}", #x, msg, __FILE__, __LINE__); YEOP_BREAK }
#else
#define YEOP_TRACE(...)     (void)0
#define YEOP_DEBUG(...)	    (void)0
#define YEOP_INFO(...)		  (void)0
#define YEOP_WARN(...)		  (void)0
#define YEOP_ERROR(...)	    (void)0
#define YEOP_FATAL(...)	    (void)0
#define YEOP_ASSERT(x, msg) (void)0
#endif
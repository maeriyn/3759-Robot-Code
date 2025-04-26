#pragma once

#define FMT_HEADER_ONLY
#include "fmt/core.h"

#include "eternal/logger/buffer.hpp"

namespace eternal {
/**
 * @brief Buffered printing to Stout.
 */
class BufferedStdout : public Buffer {
    public:
        BufferedStdout();

        /**
         * @brief Print a string (thread-safe).
         *
         */
        template <typename... T> void print(fmt::format_string<T...> format, T&&... args) {
            pushToBuffer(fmt::format(format, std::forward<T>(args)...));
        }
};

/**
 * @brief Get the buffered stdout.
 *
 */
BufferedStdout& bufferedStdout();
}
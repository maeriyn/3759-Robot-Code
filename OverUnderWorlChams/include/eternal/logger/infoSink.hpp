#pragma once

#include <deque>

#include "pros/rtos.hpp"
#include "eternal/logger/message.hpp"
#include "eternal/logger/baseSink.hpp"

namespace eternal {


class InfoSink : public BaseSink {
    public:
        /**
         * @brief Construct a new Info Sink object
         */
        InfoSink();
    private:
        /**
         * @brief Log the given message
         *
         * @param message
         */
        void sendMessage(const Message& message) override;
};
} 

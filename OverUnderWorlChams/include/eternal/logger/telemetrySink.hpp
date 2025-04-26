#pragma once

#include "eternal/logger/baseSink.hpp"

namespace eternal {

class TelemetrySink : public BaseSink {
    public:
        /**
         * @brief Construct a new Telemetry Sink object
         */
        TelemetrySink();
    private:
        /**
         * @brief Log the given message
         *
         * @param message
         */
        void sendMessage(const Message& message) override;
};
} 
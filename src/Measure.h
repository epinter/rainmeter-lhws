// Copyright (C) 2022 Emerson Pinter - All Rights Reserved

//
// Created by epinter on 15/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>
#include <chrono>
#include <atomic>
#include <future>
#include <mutex>
#include "lhwservice/HardwareService.h"
#include "Constants.h"
#include "API.h"
#include "BackgroundTimer.h"

namespace LhwsPlugin {
    class Measure {
    private:
        lhws::HardwareService hardwareService{};
        std::wstring sensorIdentifier{};
        std::wstring hardwareName{};
        std::wstring hardwareType{};
        std::wstring sensorName{};
        std::wstring sensorType{};
        std::wstring hwStatusType{};
        std::wstring hwStatusItem{};
        std::wstring stringValue{};
        std::wstring sensorId{};
        std::wstring sensorMetricType{};
        std::wstring fps{};
        double lastValue = -1.0f;
        int staleAfterSecs = VALUE_STALE_SECS;
        Rainmeter::API api;
        std::mutex mtxValue{};
        std::chrono::milliseconds updateInterval{};
        std::chrono::time_point<std::chrono::steady_clock> previousUpdate{std::chrono::steady_clock::now()};

        BackgroundTimer timer{std::chrono::milliseconds(1000), [this]() {
                                  if (!mtxValue.try_lock()) {
                                      return;
                                  }
                                  std::scoped_lock lock(std::adopt_lock, mtxValue);
                                  doUpdate();
                              }};

        void loadOptions();

        double avgSensor(std::vector<lhws::SensorValue> vec);

    public:
        explicit Measure(Rainmeter::API const &rm);

        [[nodiscard]] std::wstring getString() {
            return stringValue;
        }

        void reload(double maxValue);

        double update();

        void logError(std::wstring const &message);

        void logError(std::string const &message);

        double updateSmartAta();

        double updateSmartNvme();

        double updateRtss();

        double updateSensor();

        static long long unixTime();

        void doUpdate();

        void calculateUpdateInterval();

        void setUpdateInterval(std::chrono::milliseconds &aInterval);
    };
}// namespace LhwsPlugin
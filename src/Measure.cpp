// Copyright (C) 2022 Emerson Pinter - All Rights Reserved

//
// Created by epinter on 15/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <string>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <lhwservice/HardwareService.h>
#include "API.h"
#include "Measure.h"
#include "Constants.h"
#include "RtssAppStat.h"
#include "BackgroundTimer.h"

namespace LhwsPlugin {
    Measure::Measure(Rainmeter::API const &rm) : api(rm) {
    }

    void Measure::reload([[maybe_unused]] double maxValue) {
        loadOptions();
    }

    double Measure::update() {
        calculateUpdateInterval();
        return lastValue;
    }

    void Measure::logError(std::wstring const &message) {
        api.log(Rainmeter::API::LogLevel::LOG_ERROR, message);
    }

    void Measure::logError(const std::string &message) {
        logError(boost::locale::conv::utf_to_utf<wchar_t>(message));
    }

    long long Measure::unixTime() {
        std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count();
    }

    long long rawValueToLong(std::vector<unsigned char> const &bytes) {
        long long ret = 0;
        for (auto i = bytes.end() - 1; i >= bytes.begin(); i--) {
            ret |= static_cast<long long>(*i) << ((i - bytes.begin())) * 8;
        }
        return ret;
    }

    double Measure::updateSmartAta() {
        std::vector<lhws::SmartAttribute> smartAttributes{};
        try {
            smartAttributes = hardwareService.getSmartAttributes(
                    boost::locale::conv::utf_to_utf<char>(hardwareName),
                    boost::locale::conv::utf_to_utf<char>(hardwareType));
        } catch (std::exception const &e) {
            logError(e.what());
            return -1.0f;
        }
        bool prefail = false;
        bool advisory = false;
        bool warning = false;
        for (auto const &a: smartAttributes) {
            long long rawValue = rawValueToLong(a.getRawValue());

            if (!a.getRawValue().empty()) {
                if ((a.getId() == 0x05 || a.getId() == 0xC5 || a.getId() == 0xC6) && rawValue > WARNING_THRESHOLD_ATASMART) {
                    warning = true;
                    logError((boost::format("warning: id:'%1%'; name:'%2%';") % a.getId() % a.getName()).str());
                }

                if (a.isPrefail()) {
                    prefail = true;
                    logError((boost::format("prefail: id:'%1%'; name:'%2%';") % a.getId() % a.getName()).str());
                }

                if (a.isAdvisory()) {
                    advisory = true;
                }
            }
        }

        if (boost::iequals(hwStatusItem, SMART_ITEM_STATUS)) {
            if (prefail) {
                stringValue = ATASMART_PREFAIL;
            } else if (advisory) {
                stringValue = ATASMART_ENDOFLIFE;
            } else if (warning) {
                stringValue = ATASMART_WARNING;
            } else {
                stringValue = ATASMART_OK;
            }
        } else {
            for (auto const &a: smartAttributes) {
                if (!a.getRawValue().empty() && boost::iequals(hwStatusItem, a.getName())) {
                    return static_cast<double>(a.getCurrentValue());
                }
            }
        }

        return -1.0f;
    }

    double Measure::updateSmartNvme() {
        try {
            lhws::NvmeSmart nvmeSmart = hardwareService.getNvmeSmart(boost::locale::conv::utf_to_utf<char>(hardwareName),
                                                                     boost::locale::conv::utf_to_utf<char>(hardwareType));
            if (boost::iequals(hwStatusItem, "availableSpare")) {
                return static_cast<double>(nvmeSmart.getAvailableSpare());
            }
            if (boost::iequals(hwStatusItem, "availableSpareThreshold")) {
                return static_cast<double>(nvmeSmart.getAvailableSpareThreshold());
            }
            if (boost::iequals(hwStatusItem, "controllerBusyTime")) {
                return static_cast<double>(nvmeSmart.getControllerBusyTime());
            }
            if (boost::iequals(hwStatusItem, "criticalCompositeTemperatureTime")) {
                return static_cast<double>(nvmeSmart.getCriticalCompositeTemperatureTime());
            }
            if (boost::iequals(hwStatusItem, "criticalWarning")) {
                return static_cast<double>(nvmeSmart.getCriticalWarning());
            }
            if (boost::iequals(hwStatusItem, "dataUnitRead")) {
                return static_cast<double>(nvmeSmart.getDataUnitRead());
            }
            if (boost::iequals(hwStatusItem, "dataUnitWritten")) {
                return static_cast<double>(nvmeSmart.getDataUnitWritten());
            }
            if (boost::iequals(hwStatusItem, "errorInfoLogEntryCount")) {
                return static_cast<double>(nvmeSmart.getErrorInfoLogEntryCount());
            }
            if (boost::iequals(hwStatusItem, "hostReadCommands")) {
                return static_cast<double>(nvmeSmart.getHostReadCommands());
            }
            if (boost::iequals(hwStatusItem, "hostWriteCommands")) {
                return static_cast<double>(nvmeSmart.getHostWriteCommands());
            }
            if (boost::iequals(hwStatusItem, "mediaErrors")) {
                return static_cast<double>(nvmeSmart.getMediaErrors());
            }
            if (boost::iequals(hwStatusItem, "percentageUsed")) {
                return static_cast<double>(nvmeSmart.getPercentageUsed());
            }
            if (boost::iequals(hwStatusItem, "powerCycle")) {
                return static_cast<double>(nvmeSmart.getPowerCycle());
            }
            if (boost::iequals(hwStatusItem, "powerOnHours")) {
                return static_cast<double>(nvmeSmart.getPowerOnHours());
            }
            if (boost::iequals(hwStatusItem, "temperature")) {
                return static_cast<double>(nvmeSmart.getTemperature());
            }
            if (boost::iequals(hwStatusItem, "unsafeShutdowns")) {
                return static_cast<double>(nvmeSmart.getUnsafeShutdowns());
            }
            if (boost::iequals(hwStatusItem, "warningCompositeTemperatureTime")) {
                return static_cast<double>(nvmeSmart.getWarningCompositeTemperatureTime());
            }
            if (boost::iequals(hwStatusItem, SMART_ITEM_STATUS)) {
                if((nvmeSmart.getCriticalWarning() & 0x4) == 4 /*bit 2, media errors*/
                    || (nvmeSmart.getCriticalWarning() & 0x8) == 8 /*bit 3, media readonly*/) {
                        stringValue = NVMESMART_CRITICAL;
                } else if((nvmeSmart.getCriticalWarning() & 0x1) == 1 /*bit 0, availableSpare*/
                    || nvmeSmart.getPercentageUsed() >= 100 //life
                    || nvmeSmart.getAvailableSpare() < nvmeSmart.getAvailableSpareThreshold()) {
                    stringValue = NVMESMART_WARNING;
                } else {
                    stringValue = NVMESMART_OK;
                }
            }
        } catch (std::exception const &e) {
            logError(e.what());
        }
        return -1.0f;
    }

    double Measure::updateRtss() {
        RtssAppStat stat = RtssAppStat::getStatLastForeground();
        if (boost::iequals(sensorType, "framerate")) {
            return stat.getFramerate();
        } else if (boost::iequals(sensorType, "frametime")) {
            return (stat.getFrametime() / 1000.0);
        } else if (boost::iequals(sensorType, "frametimeMax")) {
            return (stat.getFrametimeMax() / 1000.0);
        } else if (boost::iequals(sensorType, "frametimeMin")) {
            return (stat.getFrametimeMin() / 1000.0);
        } else if (boost::iequals(sensorType, "frametimeAvg")) {
            return (stat.getFrametimeAvg() / 1000.0);
        }
        return -1.0f;
    }

    double Measure::updateSensor() {
        bool stale = false;
        try {
            if (staleAfterSecs > 0) {
                int sensorUpdateInterval = hardwareService.getSensorsMetadata().getUpdateInterval();
                long long lastUpdate = hardwareService.getSensorsMetadata().getLastUpdate();
                long long now = unixTime();

                if (lastUpdate < (now - sensorUpdateInterval - staleAfterSecs)) {
                    stale = true;
                }
            } else {
                stale = true;
            }
        } catch (std::exception const &e) {
            logError(e.what());
            return -1.0f;
        }

        try {
            lhws::Sensor sensor;
            if (sensorId.empty()) {
                sensor = hardwareService.getSensorByName(
                        boost::locale::conv::utf_to_utf<char>(sensorName),
                        boost::locale::conv::utf_to_utf<char>(sensorType),
                        boost::locale::conv::utf_to_utf<char>(hardwareName));
            } else {
                sensor = hardwareService.getSensorById(boost::locale::conv::utf_to_utf<char>(sensorId));
            }

            if (boost::iequals(sensorMetricType, "max")) {
                return sensor.getMax();
            } else if (boost::iequals(sensorMetricType, "min")) {
                return sensor.getMin();
            } else {
                return sensor.getValue();
            }
        } catch (std::exception const &e) {
            logError(e.what());
        }
        if (!stale) {
            return lastValue;
        }
        return -1.0f;
    }

    void Measure::doUpdate() {
        double value = -1.0;
        if (!hwStatusType.empty() && !hwStatusItem.empty()) {
            if (boost::iequals(hwStatusType, SMARTTYPE_ATA)) {
                value = updateSmartAta();
            } else if (boost::iequals(hwStatusType, SMARTTYPE_NVME)) {
                value = updateSmartNvme();
            }
        } else if (boost::iequals(sensorName, "rtss")) {
            value = updateRtss();
        } else if ((!sensorName.empty() && !sensorType.empty() && !hardwareName.empty()) || !sensorId.empty()) {
            value = updateSensor();
        } else {
            value = -1.0f;
        }

        Measure::lastValue = value;
    }

    void Measure::calculateUpdateInterval() {
        auto now = std::chrono::steady_clock::now();

        auto realInterval = now - previousUpdate;
        long long realIntervalMs = std::chrono::duration_cast<std::chrono::milliseconds>(realInterval).count();

        if (realIntervalMs < MIN_UPDATE_INTERVAL) {
            realIntervalMs = MIN_UPDATE_INTERVAL;
        }
        if (realIntervalMs > MAX_UPDATE_INTERVAL) {
            realIntervalMs = MAX_UPDATE_INTERVAL;
        }

        auto currentInterval = std::chrono::milliseconds(static_cast<long long>(
                                                                 std::round(static_cast<long double>(realIntervalMs) / 500.0) * 500)
        );

        previousUpdate = std::chrono::steady_clock::now();

        setUpdateInterval(currentInterval);
    }

    void Measure::loadOptions() {
        hwStatusType = api.readString(OPTION_HWSTATUSTYPE, L"");
        hwStatusItem = api.readString(OPTION_HWSTATUSITEM, L"");
        sensorName = api.readString(OPTION_SENSORNAME, L"");
        sensorType = api.readString(OPTION_SENSORTYPE, L"");
        hardwareName = api.readString(OPTION_HARDWARENAME, L"");
        hardwareType = api.readString(OPTION_HARDWARETYPE, L"");
        sensorMetricType = api.readString(OPTION_SENSORMETRICTYPE, L"value");
        sensorId = api.readString(OPTION_SENSORID, L"");
        staleAfterSecs = api.readInt(OPTION_STALEAFTERSECS, VALUE_STALE_SECS);

        if (staleAfterSecs < 0) {
            staleAfterSecs = 0;
        }
    }

    void Measure::setUpdateInterval(std::chrono::milliseconds &aInterval) {
        updateInterval = aInterval;
        timer.setTime(updateInterval);
    }
}

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

#include <memory>
#include <string>

namespace Rainmeter {
    class API {
    public:
        enum LogLevel {
            LOG_ERROR = 1,
            LOG_WARNING = 2,
            LOG_NOTICE = 3,
            LOG_DEBUG = 4
        };

        enum GetType {
            RMG_MEASURENAME = 0,
            RMG_SKIN = 1,
            RMG_SETTINGSFILE = 2,
            RMG_SKINNAME = 3,
            RMG_SKINWINDOWHANDLE = 4
        };

    private:
        void *rm;

        [[maybe_unused]] [[nodiscard]] void *get(GetType type) const;

    public:
        explicit API(void *rainmeter) {
            rm = rainmeter;
        }

        API(API const &aApi) {
            rm = aApi.rm;
        }

        [[maybe_unused]] [[nodiscard]] std::wstring
        readString(std::wstring const &option, std::wstring const &defaultValue, bool const &replaceMeasures = true);

        [[maybe_unused]] [[nodiscard]] double readFormula(std::wstring const &option, double const &defaultValue);

        [[maybe_unused]] [[nodiscard]] std::wstring replaceVariables(std::wstring const &str);

        [[maybe_unused]] [[nodiscard]] std::wstring pathToAbsolute(std::wstring const &relativePath);

        [[maybe_unused]] [[nodiscard]] std::wstring readPath(std::wstring const &option, std::wstring const &defaultValue);

        [[maybe_unused]] [[nodiscard]] int readInt(std::wstring const &option, int const &defaultValue);

        [[maybe_unused]] [[nodiscard]] double readDouble(std::wstring const &option, double const &defaultValue);

        [[maybe_unused]] [[nodiscard]] std::wstring readMeasureName() const;

        [[maybe_unused]] [[nodiscard]] std::wstring getSettingsFile() const;

        [[maybe_unused]] [[nodiscard]] void *getSkin() const;

        [[maybe_unused]] [[nodiscard]] std::wstring getSkinName() const;

        [[maybe_unused]] [[nodiscard]] void *getSkinWindow() const;

        [[maybe_unused]] void log(int level, std::wstring const &message);

        [[maybe_unused]] void logError(std::wstring const &message);

        [[maybe_unused]] void logNotice(std::wstring const &message);

        [[maybe_unused]] void logDebug(std::wstring const &message);

        [[maybe_unused]] void logWarning(std::wstring const &message);
    };
}

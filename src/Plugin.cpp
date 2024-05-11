// Copyright (C) 2022 Emerson Pinter - All Rights Reserved

//
// Created by epinter on 15/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <Windows.h>
#include <string>
#include <algorithm>
#include "API.h"
#include "Measure.h"
#include "RainmeterAPI.h"

namespace LhwsPlugin {
    PLUGIN_EXPORT void Initialize([[maybe_unused]] void **data, [[maybe_unused]] void *rm) {
        Rainmeter::API api(rm);
        auto *measure = new Measure(api);
        *data = measure;
    }

    PLUGIN_EXPORT void Reload([[maybe_unused]] void *data, [[maybe_unused]] void *rm,
                              [[maybe_unused]] double *maxValue) {// NOLINT(readability-non-const-parameter)
        auto *measure = static_cast<Measure *>(data);
        measure->reload(*maxValue);
    }

    PLUGIN_EXPORT double Update([[maybe_unused]] void *data) {
        auto *measure = static_cast<Measure *>(data);
        return measure->update();
    }

    PLUGIN_EXPORT LPCWSTR GetString([[maybe_unused]] void *data) {
        auto *measure = static_cast<Measure *>(data);
        std::wstring wstr = measure->getString();
        if (wstr.empty()) {
            return nullptr;
        }

        int stringSize = static_cast<int>(wstr.size() * sizeof(wchar_t));
        auto *str = new wchar_t[stringSize + 1];
        wcsncpy_s(str, stringSize, wstr.c_str(), stringSize);
        return str;
    }

    PLUGIN_EXPORT void Finalize([[maybe_unused]] void *data) {
        delete (static_cast<Measure *>(data));
    }
}// namespace LhwsPlugin
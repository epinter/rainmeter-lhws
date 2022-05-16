// Copyright (C) 2022 Emerson Pinter - All Rights Reserved

//
// Created by epinter on 28/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>

namespace LhwsPlugin {
    class RtssAppStat {
    private:
        std::string appName{};
        unsigned long processId{};
        unsigned long framerate{};
        unsigned long frametime{};
        unsigned long framerateMin{};
        unsigned long framerateAvg{};
        unsigned long framerateMax{};
        unsigned long frametimeMin{};
        unsigned long frametimeAvg{};
        unsigned long frametimeMax{};
    public:
        RtssAppStat(std::string appName, unsigned long processId, unsigned long framerate, unsigned long frametime,
                    unsigned long framerateMin, unsigned long framerateAvg, unsigned long framerateMax, unsigned long frametimeMin,
                    unsigned long frametimeAvg, unsigned long frametimeMax);

        RtssAppStat() = default;

        static RtssAppStat getStatLastForeground();

        [[nodiscard]] [[maybe_unused]] const std::string &getAppName() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getProcessId() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getFramerate() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getFrametime() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getFramerateMin() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getFramerateAvg() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getFramerateMax() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getFrametimeMin() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getFrametimeAvg() const;

        [[nodiscard]] [[maybe_unused]] unsigned long getFrametimeMax() const;
    };
}
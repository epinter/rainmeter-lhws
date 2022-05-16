// Copyright (C) 2022 Emerson Pinter - All Rights Reserved

//
// Created by epinter on 28/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <cmath>
#include <utility>
#include <Windows.h>
#include <RTSSSharedMemory.h>
#include "RtssAppStat.h"

namespace LhwsPlugin {
    RtssAppStat::RtssAppStat(std::string appName, unsigned long processId, unsigned long framerate, unsigned long frametime,
                             unsigned long framerateMin, unsigned long framerateAvg, unsigned long framerateMax,
                             unsigned long frametimeMin, unsigned long frametimeAvg, unsigned long frametimeMax)
            : appName(std::move(appName)), processId(processId), framerate(framerate), frametime(frametime),
              framerateMin(framerateMin),
              framerateAvg(framerateAvg), framerateMax(framerateMax), frametimeMin(frametimeMin), frametimeAvg(frametimeAvg),
              frametimeMax(frametimeMax) {}

    RtssAppStat RtssAppStat::getStatLastForeground() {
        HANDLE hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, "RTSSSharedMemoryV2");

        if (hMapFile) {
            LPVOID pMapAddr = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
            auto pMem = (LPRTSS_SHARED_MEMORY) pMapAddr;

            if (pMem) {
                if ((pMem->dwSignature == 'RTSS') && (pMem->dwVersion >= 0x00020000)) {
                    auto appEntry =
                            reinterpret_cast<RTSS_SHARED_MEMORY::LPRTSS_SHARED_MEMORY_APP_ENTRY>(
                                    ((LPBYTE) pMem + pMem->dwAppArrOffset + pMem->dwLastForegroundApp * pMem->dwAppEntrySize)
                            );
                    if (appEntry->dwTime0 != 0 && appEntry->dwFrames != 0 &&
                        pMem->dwLastForegroundAppProcessID == appEntry->dwProcessID) {
                        return {appEntry->szName,
                                appEntry->dwProcessID,
                                static_cast<unsigned long>(std::round(
                                        1000.0 * appEntry->dwFrames / (appEntry->dwTime1 - appEntry->dwTime0))),
                                appEntry->dwFrameTime,
                                appEntry->dwStatFramerateMin,
                                appEntry->dwStatFramerateAvg,
                                appEntry->dwStatFramerateMax,
                                appEntry->dwStatFrameTimeMin,
                                appEntry->dwStatFrameTimeAvg,
                                appEntry->dwStatFrameTimeMax
                        };
                    }
                }

                UnmapViewOfFile(pMapAddr);
            }

            CloseHandle(hMapFile);
        }

        return {};
    }

    const std::string &RtssAppStat::getAppName() const {
        return appName;
    }

    unsigned long RtssAppStat::getProcessId() const {
        return processId;
    }

    unsigned long RtssAppStat::getFramerate() const {
        return framerate;
    }

    unsigned long RtssAppStat::getFrametime() const {
        return frametime;
    }

    unsigned long RtssAppStat::getFramerateMin() const {
        return framerateMin;
    }

    unsigned long RtssAppStat::getFramerateAvg() const {
        return framerateAvg;
    }

    unsigned long RtssAppStat::getFramerateMax() const {
        return framerateMax;
    }

    unsigned long RtssAppStat::getFrametimeMin() const {
        return frametimeMin;
    }

    unsigned long RtssAppStat::getFrametimeAvg() const {
        return frametimeAvg;
    }

    unsigned long RtssAppStat::getFrametimeMax() const {
        return frametimeMax;
    }
}
// Copyright (C) 2022 Emerson Pinter - All Rights Reserved

//
// Created by epinter on 30/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <functional>
#include <utility>

namespace LhwsPlugin {
    class BackgroundTimer {
    private:
        std::chrono::milliseconds time{};
        std::mutex mutex{};
        std::function<void(void)> func;
        std::atomic<bool> runThread{true};
        std::condition_variable cv{};

        void timer() {
            std::unique_lock<std::mutex> lock{mutex};
            while (runThread) {
                mutex.unlock();
                func();
                mutex.lock();
                auto now = std::chrono::steady_clock::now();
                cv.wait_until(lock, now + time, [this] { return !runThread.load(); });
            }
        }

        std::thread timerThread{[this]() { timer(); }};

    public:
        explicit BackgroundTimer(std::chrono::milliseconds const &time, std::function<void(void)> function) : time(time),
                                                                                                              func(std::move(
                                                                                                                      function)) {}

        ~BackgroundTimer() {
            runThread = false;
            cv.notify_all();
            timerThread.join();
        }

        void setTime(const std::chrono::milliseconds &aTime) {
            BackgroundTimer::time = aTime;
        }
    };
} // LhwsPlugin

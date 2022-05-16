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
#include <RainmeterAPI.h>
#include "API.h"

std::wstring Rainmeter::API::readString(const std::wstring &option, const std::wstring &defaultValue, const bool &replaceMeasures) {
    return std::wstring{RmReadString(rm, option.c_str(), defaultValue.c_str(), replaceMeasures)};
}

double Rainmeter::API::readFormula(const std::wstring &option, const double &defaultValue) {
    return RmReadFormula(rm, option.c_str(), defaultValue);
}

std::wstring Rainmeter::API::replaceVariables(const std::wstring &str) {
    return std::wstring{RmReplaceVariables(rm, str.c_str())};
}

std::wstring Rainmeter::API::pathToAbsolute(const std::wstring &relativePath) {
    return std::wstring{RmPathToAbsolute(rm, relativePath.c_str())};
}

LPVOID Rainmeter::API::get(Rainmeter::API::GetType type) const {
    return RmGet(rm, type);
}

std::wstring Rainmeter::API::readPath(const std::wstring &option, const std::wstring &defaultValue) {
    std::wstring relativePath = readString(option, defaultValue, true);
    return pathToAbsolute(relativePath);
}

int Rainmeter::API::readInt(const std::wstring &option, const int &defaultValue) {
    return static_cast<int>(readFormula(option, defaultValue));
}

double Rainmeter::API::readDouble(const std::wstring &option, const double &defaultValue) {
    return static_cast<double>(readFormula(option, defaultValue));
}

std::wstring Rainmeter::API::readMeasureName() const {
    return std::wstring{static_cast<LPCWSTR>(get(GetType::RMG_MEASURENAME))};
}

std::wstring Rainmeter::API::getSettingsFile() const {
    return std::wstring{static_cast<LPCWSTR>(get(GetType::RMG_SETTINGSFILE))};
}

void *Rainmeter::API::getSkin() const {
    return static_cast<LPVOID>(get(GetType::RMG_SKIN));
}

std::wstring Rainmeter::API::getSkinName() const {
    return std::wstring{static_cast<LPCWSTR>(get(GetType::RMG_SKINNAME))};
}

void *Rainmeter::API::getSkinWindow() const {
    return static_cast<HWND>(get(GetType::RMG_SKINWINDOWHANDLE));
}

void Rainmeter::API::log(int level, const std::wstring &message) {
    RmLog(rm, level, message.c_str());
}

void Rainmeter::API::logError(const std::wstring &message) {
    log(LogLevel::LOG_ERROR, message);
}

void Rainmeter::API::logNotice(const std::wstring &message) {
    log(LogLevel::LOG_NOTICE, message);
}

void Rainmeter::API::logDebug(const std::wstring &message) {
    log(LogLevel::LOG_DEBUG, message);
}

void Rainmeter::API::logWarning(const std::wstring &message) {
    log(LogLevel::LOG_WARNING, message);
}

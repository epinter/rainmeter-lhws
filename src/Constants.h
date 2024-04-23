// Copyright (C) 2022 Emerson Pinter - All Rights Reserved

//
// Created by epinter on 24/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#define ATASMART_PREFAIL L"Pre-fail"
#define ATASMART_WARNING L"Warning"
#define ATASMART_ENDOFLIFE L"End-of-Life"
#define ATASMART_OK L"OK"

#define NVMESMART_CRITICAL L"Critical"
#define NVMESMART_WARNING L"Warning"
#define NVMESMART_OK L"OK"

#define OPTION_HWSTATUSTYPE L"HwStatusType"
#define OPTION_HWSTATUSITEM L"HwStatusItem"
#define OPTION_SENSORNAME L"SensorName"
#define OPTION_SENSORTYPE L"SensorType"
#define OPTION_HARDWARENAME L"HardwareName"
#define OPTION_HARDWARETYPE L"HardwareType"
#define OPTION_SENSORID L"SensorIdentifier"
#define OPTION_SENSORMETRICTYPE L"SensorMetricType"
#define OPTION_STALEAFTERSECS L"StaleAfterSecs"

#define SMART_ITEM_STATUS "Status"
#define SMARTTYPE_ATA L"storage_smart_ata"
#define SMARTTYPE_NVME L"storage_smart_nvme"

#define WARNING_THRESHOLD_ATASMART 10
#define VALUE_STALE_SECS 5
#define MIN_UPDATE_INTERVAL 1000
#define MAX_UPDATE_INTERVAL 5000
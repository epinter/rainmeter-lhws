# LibreHardwareService plugin for Rainmeter

[![Latest Release](https://img.shields.io/github/release/epinter/rainmeter-lhws.svg)](https://github.com/epinter/rainmeter-lhws/releases/latest)
[![Downloads](https://img.shields.io/github/downloads/epinter/rainmeter-lhws/total.svg)](https://github.com/epinter/rainmeter-lhws/releases/latest)
[![Release Date](https://img.shields.io/github/release-date/epinter/rainmeter-lhws.svg)](https://github.com/epinter/rainmeter-lhws/releases/latest)
[![License](https://img.shields.io/github/license/epinter/rainmeter-lhws.svg)](https://github.com/epinter/rainmeter-lhws/blob/main/LICENSE)

## Introduction

This plugin collects hardware sensors from [LibreHardwareService](https://github.com/epinter/LibreHardwareService), allowing skins to access all hardware sensors exposed by [LibreHardwareMonitor](https://github.com/LibreHardwareMonitor/LibreHardwareMonitor), SMART status, and RTSS framerate and frametime.

## Requirements

- [LibreHardwareService](https://github.com/epinter/LibreHardwareService)
- [Visual C++ Redistributable 2022](https://docs.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist)
- [CMake](https://cmake.org/)
- [vcpkg](https://vcpkg.io/en/)
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/)
- [LibHardwareService](https://github.com/epinter/lhwservice)

## Usage

Copy LibreHardwareService.dll to %APPDATA%/Rainmeter/Plugins and setup measures like the examples below.

## Building

The library [LibHardwareService](https://github.com/epinter/lhwservice) is searched by findpackage in a parent directory or inside extern. Scripts for building can be found in cmake directory.

```
./cmake/build.ps1
```

## Measure Examples

Hardware names are the ones returned by LibreHardwareMonitor or ShowSensors.exe from LibreHardwareService.

Motherboard:
```
[MBTemp]
Measure=Plugin
Plugin=LibreHardwareService
HardwareName=#mbSubhardwareName#
SensorName=Temperature #2
SensorType=Temperature
```

CPU usage:
```
[CPUTotalLoad]
Measure=Plugin
Plugin=LibreHardwareService
HardwareName=#cpuHardwareName#
SensorName=CPU Total
SensorType=Load
MinValue=0
MaxValue=100
```

RTSS fps:
```
[Fps]
Measure=Plugin
Plugin=LibreHardwareService
SensorName=RTSS
SensorType=Framerate
```

RTSS Frametime (milliseconds):
```
[Frametime]
Measure=Plugin
Plugin=LibreHardwareService
SensorName=RTSS
SensorType=frametime
```

Storage activity:
```
[Drive1Load]
Measure=Plugin
Plugin=LibreHardwareService
HardwareName=#drive1HwName#
SensorName=Total Activity
SensorType=Load
```

Storage Temperature:
```
[Drive1Temp]
Measure=Plugin
Plugin=LibreHardwareService
HardwareName=#drive1HwName#
SensorName=Temperature
SensorType=Temperature
```
Storage Temperature:
```
[Drive2Temp]
Measure=Plugin
Plugin=LibreHardwareService
SensorIdentifier=/hdd/1/temperature/0
```

SMART SATA status, returns one of the following strings:
- "Pre-fail" if the smart Prefail bit is set;
- "End-of-Life" if the smart Advisory bit is set;
- "Warning" if smart attributes 0x05, 0xC5, or 0xC6 have raw values above 10
- "OK" if none of above is detected
```
[SmartDrive1]
Measure=Plugin
Plugin=LibreHardwareService
HardwareName=#drive1HwName#
HardwareType=Storage
HwStatusType=storage_smart_ata
HwStatusItem=Status
```

SMART NVME:
```
[SmartDrive2availableSpare]
Measure=Plugin
Plugin=LibreHardwareService
HardwareName=#drive2HwName#
HardwareType=Storage
HwStatusType=storage_smart_nvme
HwStatusItem=availableSpare
```

SMART NVME:
```
[SmartDrive2criticalWarning]
Measure=Plugin
Plugin=LibreHardwareService
HardwareName=#drive2HwName#
HardwareType=Storage
HwStatusType=storage_smart_nvme
HwStatusItem=criticalWarning
```

SMART NVME:
```
[SmartDrive2percentageUsed]
Measure=Plugin
Plugin=LibreHardwareService
HardwareName=#drive2HwName#
HardwareType=Storage
HwStatusType=storage_smart_nvme
HwStatusItem=percentageUsed
```

NVME attributes available:
```
availableSpare
availableSpareThreshold
controllerBusyTime
criticalCompositeTemperatureTime
criticalWarning
dataUnitRead
dataUnitWritten
errorInfoLogEntryCount
hostReadCommands
hostWriteCommands
mediaErrors
percentageUsed
powerCycle
powerOnHours
temperature
unsafeShutdowns
warningCompositeTemperatureTime
```

## License

This software is licensed under the terms of [Mozilla Public License Version 2.0](https://www.mozilla.org/en-US/MPL/2.0/).


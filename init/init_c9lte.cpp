/*
 * Copyright (C) 2017 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
 
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

static int read_file2(const char *fname, char *data, int max_size)
{
    int fd, rc;

    if (max_size < 1)
        return 0;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        ERROR("failed to open '%s'\n", fname);
        return 0;
    }

    rc = read(fd, data, max_size - 1);
    if ((rc > 0) && (rc < max_size))
        data[rc] = '\0';
    else
        data[0] = '\0';
    close(fd);

    return 1;
}

static void init_alarm_boot_properties()
{
    char const *alarm_file = "/proc/sys/kernel/boot_reason";
    char buf[64];

    if (read_file2(alarm_file, buf, sizeof(buf))) {
        /*
         * Setup ro.alarm_boot value to true when it is RTC triggered boot up
         * For existing PMIC chips, the following mapping applies
         * for the value of boot_reason:
         *
         * 0 -> unknown
         * 1 -> hard reset
         * 2 -> sudden momentary power loss (SMPL)
         * 3 -> real time clock (RTC)
         * 4 -> DC charger inserted
         * 5 -> USB charger insertd
         * 6 -> PON1 pin toggled (for secondary PMICs)
         * 7 -> CBLPWR_N pin toggled (for external power supply)
         * 8 -> KPDPWR_N pin toggled (power key pressed)
         */
        if (buf[0] == '3') {
            property_set("ro.alarm_boot", "true");
            property_set("debug.sf.nobootanimation", "1");
        }
        else
            property_set("ro.alarm_boot", "false");
    }
}

void init_target_properties()
{
    char platform[PROP_VALUE_MAX];
    char bootloader[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform, NULL);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.bootloader", bootloader, NULL);

    if (strstr(bootloader, "C900Y")) {
        /* c9ltezt - Taiwan variant  */
        property_override("ro.build.fingerprint", "samsung/c9ltezt/c9lte:6.0.1/MMB29M/C900YZTU1AQC3:user/release-keys");
        property_override("ro.build.description", "c9ltezt-user 6.0.1 MMB29M C900YZTU1AQC3 release-keys");
        property_override("ro.product.model", "SM-C900Y");
        property_override("ro.product.device", "c9lte");
		property_override("ro.product.name", "c9ltezt");
	} else if (strstr(bootloader, "C9000")) {
        /* c9ltezh - China variant  */
        property_override("ro.build.fingerprint", "samsung/c9ltezh/c9ltechn:6.0.1/MMB29M/C9000ZHU1AQG2:user/release-keys");
        property_override("ro.build.description", "c9ltezh-user 6.0.1 MMB29M C9000ZHU1AQG2 release-keys");
        property_override("ro.product.model", "SM-C9000");
        property_override("ro.product.device", "c9lte");
		property_override("ro.product.name", "c9ltezh");
	} else if (strstr(bootloader, "C900F")) {
        /* c9ltedd - Indian variant */
        property_override("ro.build.fingerprint", "samsung/c9ltedd/c9lte:6.0.1/MMB29M/C900FDDU1AQG3:user/release-keys");
        property_override("ro.build.description", "c9ltedd-user 6.0.1 MMB29M C900FDDU1AQG3 release-keys");
        property_override("ro.product.model", "SM-C900F");
        property_override("ro.product.device", "c9lte");
		property_override("ro.product.name", "c9ltedd");
    }

    property_get("ro.product.device", device, NULL);
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found bootloader id %s setting build properties for %s device\n", bootloader, devicename);
}

void vendor_load_properties()
{
    init_target_properties();
    init_alarm_boot_properties();
}
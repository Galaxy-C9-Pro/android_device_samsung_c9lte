#
# Copyright (C) 2016 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# inherit from common msm8976-common
-include device/samsung/msm8976-common/BoardConfigCommon.mk

DEVICE_PATH := device/samsung/c9ltechn

# Assert
TARGET_OTA_ASSERT_DEVICE := c9ltechn

# Board
TARGET_BOARD_INFO_FILE := $(DEVICE_PATH)/board-info.txt

# Telephony
BOARD_RIL_CLASS := ../../../device/samsung/c9ltechn/ril

# RIL
TARGET_RIL_VARIANT := caf
#BOARD_PROVIDES_LIBRIL := true

# Kernel
TARGET_KERNEL_CONFIG := msm8976_sec_defconfig
TARGET_KERNEL_VARIANT_CONFIG := msm8976_sec_c9lte_chn_defconfig
TARGET_KERNEL_SELINUX_CONFIG := selinux_defconfig

# Partitions
BOARD_BOOTIMAGE_PARTITION_SIZE := 33554432
BOARD_CACHEIMAGE_PARTITION_SIZE := 209715200
BOARD_PERSISTIMAGE_PARTITION_SIZE := 33554432
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 33554432
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 4815060992
BOARD_USERDATAIMAGE_PARTITION_SIZE := 57151545344 # 57151565824 - 20480 (footer)
BOARD_FLASH_BLOCK_SIZE := 131072

# Properties
TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop

# inherit from the proprietary version
-include vendor/samsung/gts210velte/BoardConfigVendor.mk

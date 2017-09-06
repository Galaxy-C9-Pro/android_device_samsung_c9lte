$(call inherit-product, device/samsung/c9lte/full_c9lte.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := lineage_c9lte
PRODUCT_BRAND := samsung
PRODUCT_MANUFACTURER := samsung
PRODUCT_DEVICE := c9lte

PRODUCT_GMS_CLIENTID_BASE := android-samsung

# Use the latest approved GMS identifiers
PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_NAME=c9lte \
    BUILD_FINGERPRINT=samsung/c9ltedd/c9lte:6.0.1/MMB29M/C900FDDU1AQG3:user/release-keys \
    PRIVATE_BUILD_DESC="9ltedd-user 6.0.1 MMB29M C900FDDU1AQG3 release-keys"

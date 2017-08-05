$(call inherit-product, device/samsung/c9lte/full_c9lte.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := lineage_c9lte
PRODUCT_BRAND := samsung
PRODUCT_MANUFACTURER := samsung
PRODUCT_DEVICE := c9lte

PRODUCT_GMS_CLIENTID_BASE := android-samsung

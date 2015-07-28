#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# derived from https://github.com/hzeller/gmrender-resurrect.git
#

include $(TOPDIR)/rules.mk

PKG_NAME:=wifi-audio
PKG_VERSION:=2013-12-04
PKG_RELEASE=$(PKG_SOURCE_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/wifi-audio
  SECTION:= sxx
  CATEGORY:= Sxx
  DEPENDS:= +gmediarender +kmod-usb-audio +kmod-usb-core +kmod-usb-ohci +kmod-usb-rt305x-dwc_otg +kmod-usb2 +kmod-rt5350-i2s +kmod-ralink-dma
  TITLE:= Wifi Audio for Sxx
endef

define Package/wifi-audio/description
  Wifi Audio for Sxx
endef

define Package/wifi-audio/install
endef

$(eval $(call BuildPackage,wifi-audio))

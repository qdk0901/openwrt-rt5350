#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libspi
PKG_VERSION:=2015-09-17
PKG_RELEASE=$(PKG_SOURCE_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/libspi
  SECTION:=sxx
  CATEGORY:=Sxx
  DEPENDS:= +kmod-spi-dev +kmod-spi-gpio
  TITLE:=spi lib for dsp
endef

define Package/libspi/description
  spi lib for dsp
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) -r src/. $(PKG_BUILD_DIR)
endef

define Package/libspi/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libspi.so $(1)/lib
	$(CP) $(PKG_BUILD_DIR)/libspi.so $(STAGING_DIR)/lib
endef

$(eval $(call BuildPackage,libspi))

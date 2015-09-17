#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libdsp
PKG_VERSION:=2015-09-17
PKG_RELEASE=$(PKG_SOURCE_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/libdsp
  SECTION:=sxx
  CATEGORY:=Sxx
  DEPENDS:= +libspi
  TITLE:=dsp lib
endef

define Package/libdsp/description
  dsp lib
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) -r src/. $(PKG_BUILD_DIR)
endef

define Package/libdsp/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) ./src/libdsp.so $(1)/lib
	$(CP) ./src/libdsp.so $(STAGING_DIR)/lib
endef

$(eval $(call BuildPackage,libdsp))

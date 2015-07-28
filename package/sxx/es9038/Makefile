#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# derived from https://github.com/hzeller/gmrender-resurrect.git
#

include $(TOPDIR)/rules.mk

PKG_NAME:=es9038
PKG_VERSION:=2013-12-04
PKG_RELEASE=$(PKG_SOURCE_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/es9038
  SECTION:= sxx
  CATEGORY:= Sxx
  DEPENDS:= 
  TITLE:= Codec driver for es9038 on rt5350
endef

define Package/es9038/description
  Codec driver for es9038 on rt5350
endef

define Package/es9038/install
endef

$(eval $(call KernelPackage,es9038))

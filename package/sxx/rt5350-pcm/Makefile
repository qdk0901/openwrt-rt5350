#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# derived from https://github.com/hzeller/gmrender-resurrect.git
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rt5350-pcm
PKG_VERSION:=2013-12-04
PKG_RELEASE=$(PKG_SOURCE_VERSION)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/rt5350-pcm
    TITLE:= PCM on rt5350
    SECTION:= sxx
    CATEGORY:= Sxx
    DEPENDS:= +kmod-sound-core +kmod-sound-soc-core +kmod-ralink-dma
    KCONFIG:=
        
    FILES:=$(PKG_BUILD_DIR)/*.$(LINUX_KMOD_SUFFIX)
    AUTOLOAD:=$(call AutoLoad,50,rt5350-pcm sxx-pcm-codec sxx-pcm-machine)
endef

define KernelPackage/rt5350-pcm/description
  I2S on rt5350
endef


define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) -r src/. $(PKG_BUILD_DIR)
endef

PKG_EXTRA_KCONFIG:= \
    CONFIG_RT5350_PCM=m \
	CONFIG_SXX_PCM_MACHINE=m \
    CONFIG_SXX_PCM_CODEC=m \
    
    
PKG_EXTRA_CFLAGS:= 

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		ARCH="$(LINUX_KARCH)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		SUBDIRS="$(PKG_BUILD_DIR)" \
		$(PKG_EXTRA_KCONFIG) \
        EXTRA_CFLAGS="$(PKG_EXTRA_CFLAGS)" \
		V="$(V)" \
		modules
endef

define KernelPackage/rt5350-pcm/install
endef

$(eval $(call KernelPackage,rt5350-pcm))

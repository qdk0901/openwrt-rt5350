#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

DMA_MENU:=DMA Support

define KernelPackage/ralink-dma
  SUBMENU:=$(DMA_MENU)
  TITLE:=Ralink DMA
  DEPENDS:=
  KCONFIG:= \
    CONFIG_DMADEVICES=y \
    CONFIG_DMA_RALINK
  
  FILES:=$(LINUX_DIR)/drivers/dma/*.ko
  AUTOLOAD:=$(call AutoLoad,00,dmaengine virt-dma ralink-gdma)
endef

define KernelPackage/ralink-dma/description
 Kernel support Ralink DMA
endef

$(eval $(call KernelPackage,ralink-dma))

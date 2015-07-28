#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gmediarender
PKG_VERSION:=2013-12-04
PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_FIXUP:=autoreconf
PKG_INSTALL=1
PKG_REMOVE_FILES:=autogen.sh aclocal.m4

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/gmediarender
  SECTION:=sxx
  CATEGORY:=Sxx
  DEPENDS:= +gstreamer +glib2 +libupnp \
            +gst-mod-alsa \
            +gst-mod-app \
            +gst-mod-audioconvert \
            +gst-mod-audioparsers \
            +gst-mod-audiorate \
            +gst-mod-audioresample \
            +gst-mod-audiotestsrc \
            +gst-mod-autodetect \
            +gst-mod-decodebin \
            +gst-mod-decodebin2 \
            +gst-mod-flac \
            +gst-mod-gio \
            +gst-mod-icydemux \
            +gst-mod-id3demux \
            +gst-mod-isomp4 \
            +gst-mod-mad \
            +gst-mod-ogg \
            +gst-mod-playbin \
            +gst-mod-souphttpsrc \
            +gst-mod-tcp \
            +gst-mod-theora \
            +gst-mod-typefindfunctions \
            +gst-mod-volume \
            +gst-mod-vorbis \
            +gst-plugins-base \
            +gstreamer \
            +libgstapp \
            +libgstaudio \
            +libgstcdda \
            +libgstcheck \
            +libgstcontroller \
            +libgstdataprotocol \
            +libgstfft \
            +libgstinterfaces \
            +libgstnet \
            +libgstnetbuffer \
            +libgstpbutils \
            +libgstreamer \
            +libgstriff \
            +libgstrtp \
            +libgstrtsp \
            +libgstsdp \
            +libgsttag \
            
  TITLE:=A Headless UPnP Renderer
endef

define Package/gmediarender/description
  gmediarender implements the server component that provides UPnP
  controllers a means to render media content (audio, video and images)
  from a UPnP media server.
endef

CONFIGURE_ARGS+= \
	--with-build-cc="$(HOSTCC)" \
	--prefix="\usr"

define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) -r src/. $(PKG_BUILD_DIR)
endef

define Package/gmediarender/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/$(PKG_NAME) $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(CP) 		   $(PKG_BUILD_DIR)/scripts/init.d/$(PKG_NAME)er $(1)/etc/init.d/$(PKG_NAME)
endef

$(eval $(call BuildPackage,gmediarender))

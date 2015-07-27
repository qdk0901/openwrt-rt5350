##1.下载编译源码
```
git clone https://github.com/qdk0901/openwrt-rt5350.git
```
###更新feeds
```
./script/feeds update -a
./script/feeds install -a
```
###选择目标板
![](http://transing.bj.bcebos.com/rt5350-menuconfig.JPG)
###选择uboot
![](http://transing.bj.bcebos.com/rt5350-bootloader.JPG?responseContentDisposition=attachment)
![](http://transing.bj.bcebos.com/rt5350-uboot.JPG?responseContentDisposition=attachment)
###选择wifi audio
![](http://transing.bj.bcebos.com/wifi-audio1.JPG)
![](http://transing.bj.bcebos.com/wifi-audio2.JPG)
###编译源码
```
make -j8 V=s
```
###得到镜像如下
####其中openwrt-ramips-rt305x-sxx-u-boot.bin为uboot
####openwrt-ramips-rt305x-sxx-squashfs-sysupgrade.bin为linux
![](http://transing.bj.bcebos.com/rt5350-images.JPG?responseContentDisposition=attachment)

##2.刷入镜像
####首先，需要刷入uboot，如果你的板已经烧录过uboot，可以用那个uboot的更新方式来更新本源码里的uboot，或者可以用烧录器，
####已经刷了本原码的uboot的板，按照下面的方式刷入linux即可
#####tftp64目录如下
![](http://transing.bj.bcebos.com/rt5350-flash1.JPG?responseContentDisposition=attachment)
#####网卡配置如下
![](http://transing.bj.bcebos.com/rt5350-flash2.JPG?responseContentDisposition=attachment)
#####uboot串口波特率设置为115200,rt5350板用网线根板相连后，在串口输入run ll命令
```
run ll
```
![](http://transing.bj.bcebos.com/rt5350-flash4.JPG?responseContentDisposition=attachment)
等待下载刷写完毕

##3.测试wifi audio
###接入usb声卡，如下图
![](http://transing.bj.bcebos.com/IMG_20150727_222954.jpg?responseContentDisposition=attachment)
###正常的话，/dev/snd下应该有如下设备
![](http://transing.bj.bcebos.com/rt5350-wifi-audio.JPG?responseContentDisposition=attachment)
###执行如下命令
```
gmediarender -f sxx-wifi-audio
```
![](http://transing.bj.bcebos.com/rt5350-wifi-audio2.JPG?responseContentDisposition=attachment)

###手机上播放一首音乐，选择投射到sxx-wifi-audio设备上
![](http://transing.bj.bcebos.com/Screenshot_2015-07-27-22-35-42.png?responseContentDisposition=attachment)

##完毕

更多内容请关注[我的博客](http://transing.xyz)
2012-6-25 Zhang Dong
       1)modified proper ON and OFF of regulator related to MIPI
       Modified files:
       arch/arm/mach-exynos/mach-smdk4x12.c
       drivers/media/video/samsung/tvout/s5p_tvout.c

2012-6-15 Zhang Dong
        1)delete redundant log about max8903
        Modified files:
        drivers/power/max8903.c

2012-6-6: Zhang Dong
        1) modified shutdown threshold of ultra low voltage to be consistent with android setting
        Modified files:
          drivers/power/max17040_battery.c

2012-6-04: Cui Wenpin
	1) Add a sysfs interface to help Android determine whether to  enter ULP
	   mode or not, samsung-rp driver will maintain the status of A2DP device.
	Modified files:
	  sound/soc/samsung/srp_ulp/srp.c

2012-5-28: Sheng Liang
	1) Use timed_output_dev to implement vibrator.
	new file:   arch/arm/mach-exynos/s5p_vibrator.c
	modified:   arch/arm/configs/tc4_dvt_ap11_icecream_defconfig
	modified:   arch/arm/configs/tc4_dvt_ap11_icecream_nfc_defconfig
	modified:   arch/arm/configs/tc4_dvt_icecream_defconfig
	modified:   arch/arm/configs/tc4_dvt_icecream_ion_defconfig
	modified:   arch/arm/mach-exynos/Kconfig
	modified:   arch/arm/mach-exynos/Makefile

2012-5-22: Li Yang
	1) fix sd/mmc trasform error issue.
	Modified files:
	ararch/arm/mach-exynos/setup-sdhci.c
	
2012-5-21: Sheng Liang
	1) Add NFC support, now it can read the tag.

2012-5-21: Lucy 
        1) modify device attribution of busfruq/vib/bt_power due to pass CTS.
        Modified files:
        arch/arm/mach-exynos/busfreq_opp.c
        drivers/gpio/vibrator.c
        drivers/net/wireless/semco_a31.c


2012-5-17: Zhang Dong
        1) improve ultra low voltage shut down 
        Modified files:
        drivers/power/max17040_battery.c

2012-5-14: Cui Wenpin
	1) Disable sysrq: it result some problem on shell
	Modified files:
        arch/arm/configs/tc4_dvt_icecream_defconfig

2012-5-10: Li Yang
	1)Fix mmc driver's bug:  should power off mmc slot and release wake_lock if rescan failed.
	2)Fix touchscreen driver's bug about tp sometimes can't use after sleep/wakeup. 	
	
2012-5-9: Cui Wenpin
	1) Fix a potential risk when reading ts firmware version.
    2) Refine the codes reporting AP version.
	Modified files:
        arch/arm/kernel/setup.c
        drivers/input/touchscreen/egalax_i2c.c

2012-5-8: Cui Wenpin
	1) Add touchscreen firmware version info in /proc/cpuinfo
	Modified files:
        arch/arm/kernel/setup.c
        drivers/input/touchscreen/egalax_i2c.c

2012-5-3: Sheng Liang
	1)Fix the issue that after wakeup, USB Host function is un-usable.
	Modified files:
	arch/arm/mach-exynos/tc4-regulator-consumer.c

2012-5-3:Zhang Dong
        1)fix the problem that LPA cannot enter  
        arch/arm/mach-exynos/cpufreq.c

2012-5-2:lucy
	1)add ion config file.
	arch/arm/configs/tc4_dvt_icecream_ion_defconfig
	


2012-4-28:Li Yang
	1) fix bugs : system crash during reboot.
	Modified:
	arch\arm\configs\
2012-4-27:Zhang Dong
        1) modify LDO enable abnormal
        Modified files:
        arch/arm/mach-exynos/mach-smdk4x12.c
        arch/arm/mach-exynos/tc4-regulator-consumer.c
        drivers/media/video/s5k4ecgx.c
        drivers/media/video/samsung/tvout/s5p_tvout.c

2012-4-25:Zhang Dong
        1) modify cpufreq policy
        Modified files:
        arch/arm/mach-exynos/cpufreq.c
        drivers/cpufreq/cpufreq_ondemand.c

2012-4-24:lucy
	1)add ion related code, supporting 2D/3D/MFC/FIMC/FIMD/TV/ functions
	2)camera(2M) preview/caputre/record
	3)HDMI display(plug-in/out)
	4)use tc4_dvt_icecream_ion_defconfig
	known issues:
	1)there is lag while playing movies with HDMI connected
	2)camera can not be used while HDMI connected
	3)only support 2M camera
	
		arch/arm/mach-exynos/include/mach/videonode-exynos4.h
		arch/arm/mach-exynos/mach-smdk4x12.c
		arch/arm/mach-exynos/setup-fimd0.c
		drivers/media/video/exynos/tv/hdmi_reg_5250.c
		drivers/media/video/exynos/tv/hdmiphy_drv.c
		drivers/media/video/exynos/tv/mixer.h
		drivers/media/video/exynos/tv/mixer_drv.c
		drivers/media/video/s5p-fimc/fimc-capture.c
		drivers/media/video/s5p-fimc/fimc-reg.c
		drivers/media/video/s5p-mfc/s5p_mfc_mem.c
		drivers/media/video/videobuf2-ion.c
		drivers/video/s3c-fb.c


2012-4-20:Ma Jun
	1)set the MMC as DDR mode
	2)fixed the resume bug in ddr mode

2012-4-18:Zhang Dong
        1) reduce sleep current by setting GPC1_0 input pull_none
        Modified files:
        arch/arm/mach-exynos/mach-smdk4x12.c
2012-04-17: Li Yang
	1) fix bugs about panic dump: should only restore uart reg when enable no_console_suspend
	Modefied files:
	drivers/tty/serial/samsung.c
	arch/arm/plat-samsung/pm.c

2012-04-13: Wang Xiebin
	1)The cpu id for exynos4212 is 0x43220xxx,and exynos4412 is 0xe4412xxx.For easy, re-map the exynos4212 cpu id to 0x44212xxx
	2)Disable the modinfo check when insmod ko file
	Modified files:
	arch/arm/kernel/setup.c
	kernel/module.c


2012-04-12: Li Yang
	1) add panic dump reference code. You can enable it by enable CONFIG_KERNEL_PANIC_DUMP in config file. 
	2) if you see "There are 1(or 2,3) valid panic information in memory " in booting msg, you can pull log files run  pull_log.bat with adb connected. Current version can only pull last panic log.
	Modifid files:	 
		arch/arm/kernel/process.c
		arch/arm/mach-exynos/cpu-exynos4.c
		arch/arm/mach-exynos/include/mach/panic-dump.h
		arch/arm/mach-exynos/panic-dump.c
		arch/arm/mach-exynos/setup-mshci-gpio.c
		arch/arm/plat-samsung/include/plat/map-base.h
		arch/arm/plat-samsung/pm.c
		drivers/staging/android/logger.c
		drivers/tty/serial/samsung.c
		init/main.c
		kernel/kallsyms.c
		kernel/panic.c
		kernel/printk.c
2-03-29: Wang Xiebin
        1)Add the cpu id info to /proc/cpuinfo,then android can display the cpu id in the ui.
	2)Adjust the voltage of DVFS,because on board can not work with the default voltage.
        Modified files:
        arch/arm/kernel/setup.c
	arch/arm/mach-exynos/cpufreq-4x12.c

2012-03-27:Cui Wenpin
	1) Remove codes which force DAPM subsystem check power state, These codes were added by shaobo.zhu.
	2) Rewrite DAPM MICBIAS supply method, now take them as a DAPM widget.
	3) Add new widgets namely "HP", "SPK", "MAIN MIC", "SUB MIC".
	Modifided files:
       sound/soc/codecs/wm_hubs.c
       sound/soc/samsung/smdk_wm8994.c
       sound/soc/soc-dapm.c

2012-03-29: Wang Xiebin
	1)Bugfix for: the system enter sleep when hdmi in, there will be ab-normal log info.
	Modified files:
	drivers/media/video/samsung/tvout/s5p_tvif_ctrl.c

2012-03-27:Cui Wenpin
	1) Remove useless self-defined kcontrols, completely using interfaces provided by original codec driver.
	2) Add event functions which will be called back before MIXINL(R) power up or after they power down, we set mic bias here.
	3) Modify some DAPM widgets and interconnections' defination, mainly for voice call.
	Modified files:
	sound/soc/codecs/wm8994.c
	sound/soc/codecs/wm_hubs.c
	
2012-03-27:Li Yang
	1) Resolve 4412 EVT1.1 reboot failed issue
	Modified files:
	arch/arm/mach-exynos/cpu-exynos4.c
	
2012-03-26: Wang Xiebin
	1).Fix the sleep/wakeup issue.
      	Modified files:
	arch/arm/mach-exynos/busfreq_opp_4x12.c
	arch/arm/mach-exynos/cpuidle-exynos4.c
	arch/arm/mach-exynos/mach-smdk4x12.c
	drivers/media/video/samsung/mali_ics/linux/mali_kernel_pm.c


2012-03-23: Sheng Liang
	1). Modify USB PHY code.
	2). Add a config file for AP 1.1.
	3). Now, AP 1.1 can support USB Host and Gadget functions working together.
	Modified files:
		arch/arm/configs/tc4_dvt_ap1.1_icecream_defconfig
		arch/arm/mach-exynos/Kconfig
		arch/arm/mach-exynos/setup-usb-phy.c

2012-03-22: Li Yang
	1) Enable ARM Trustzone
	Modifide files: arch/arm/configs/c4_dvt_icecream_defconfig
2012-03-19: Wang Xiebin
        1)Enable the 3D DVFS.
        Modified files:
        drivers/media/video/samsung/mali_ics/platform/pegasus-m400/mali_platform.c
        arch/arm/configs/tc4_dvt_icecream_defconfig

2012-3-116:yu qingfeng
        1) HDMI busfreq lock/unlock interface change
           the previous interfaces would lead to error report 
           when plug-in and out HDMI cable repeatly during 1080P video is displaying on device.
           Modified files:
           drivers/media/video/samsung/tvout/s5p_tvif_ctrl.c

2012-03-08: Cui Wenpin
	1)Add a new kcontrl "HP Mute" for audio HAL

2012-03-08: Wang Xiebin
	1)Optimize the DVFS policy.
	Modified files:
	arch/arm/mach-exynos/cpufreq.c
	arch/arm/mach-exynos/dynamic-dvfs-nr_running-hotplug.c
	drivers/cpufreq/cpufreq_ondemand.c

2012-03-07: Wang Xiebin
	1)Fix the busfreq bug.
        2)Fix the ACLK_200/ACLK_400 clock error
	3)Set the lcd refresh rate to 60fps
	Modified files:
	arch/arm/mach-exynos/busfreq_opp.c
	arch/arm/mach-exynos/clock-exynos4212.c
	arch/arm/mach-exynos/dev.c
	drivers/media/video/samsung/tvout/s5p_tvif_ctrl.c
	arch/arm/mach-exynos/include/mach/dev.h

2012-03-06 Lucy
        1) Enable vdd_50.
        Modifide files:
        drivers/regulator/s5m8767.c

2012-03-06:Donggeun Baek
	1) The power control frunction is divided into two function
           One is for normal mode operation and the other is for sleep/wakeup
	   In the case of turning ON/OFF the WiFi from the settings, the power
           of A31 and the card detection/removal procedure should be controlled
           together
           In the case of sleep/wakeup, the power of A31 should be only controlled
	modified files:
	arch/arm/mach-exynos/mach-smdk4x12.c
	drivers/mmc/core/sdio.c
	drivers/net/wireless/semco_a31.c

2012-02-21:Zhang Dong
	1)modify sleep gpio setting related to BT to solve BT normal work 
	Modified files:
        arch/arm/mach-exynos/mach-smdk4x12.c
	arch/arm/mach-exynos/tc4-regulator-consumer.c

2012-03-05 Wang Xiebin
	1)In current design, the TP is not cut off when system sleep
	Modifide files:
	arch/arm/mach-exynos/mach-smdk4x12.c

2012-03-02 Wang Xiebin
	1) Disable the TMU tripped function
	2) Upgrade the latest TP driver from EETI
	Modified files:
        arch/arm/mach-exynos/tmu_exynos.c
        drivers/input/touchscreen/egalax_i2c.c
        
2012-02-29 Cui Wenpin
	1) seperate audio codec driver from Meizu BSP driver
	Modified files:
        sound/soc/codecs/Kconfig
        sound/soc/codecs/Makefile
        sound/soc/codecs/wm8994-path.c
        sound/soc/codecs/wm8994.c
        sound/soc/codecs/wm8994.h
        sound/soc/samsung/Kconfig

2012-02-22: Lucy
	1) Turn off dvdd25 and dvdd12, they are not used in TC4.
	2) Move power on/off from tc4-regulator-consumer to each driver.
	Modified files:
		arch/arm/mach-exynos/mach-smdk4x12.c
		arch/arm/mach-exynos/tc4-regulator-consumer.c
		drivers/media/video/samsung/tvout/s5p-tvout.c


2012-02-22: Shengliang
	1) Modify RTC for EVT board without S5M8767
	Modified files:
		drivers/rtc/rtc-s3c.c

2012-02-23: Shengliang
	1) Modify rtc kconfig
	Modified files:
		drivers/rtc/Kconfig

2012-02-23: Shengliang
	1) Modify drivers/rtc/rtc-s3c.c, it has a mistake.
	Modified files:
		drivers/rtc/rtc-s3c.c

2012-02-22: Shengliang
	1) Solve RTC make system crash issue.
	Modified files:
		drivers/rtc/rtc-s3c.c
	
2012-02-22: Shengliang
	1) Some time S5M8767 is not ready when s3c-rtc is register, then system will crash, solved.
	Modified files:
		drivers/rtc/rtc-s3c.c

2012-02-22:Lucy
		1) Turn on/off vdd10_mipi and vdd18_mipi both in camera and hdmi drivers.
		2) Modify runtime pm driver of fimc in order to system could enter lpa mode.

		Modified files:
			drivers/media/video/s5kecgx.c
			drivers/media/video/samsung/fimc/fimc_dev.c
			drivers/media/video/samsung/fimc/fimc_output.c
			drivers/media/video/samsung/tvout/s5p_tvif_ctrl.c
			drivers/media/video/samsung/tvout/s5p_tvout.c
			
2012-02-22: Sheng Liang
	1) RTC function development
	Modified files:
	  drivers/rtc/hctosys.c
	  drivers/rtc/rtc-s3c.c
	  drivers/rtc/rtc-s5m.c
	  include/linux/mfd/s5m87xx/s5m-core.h
	  include/linux/mfd/s5m87xx/s5m-rtc.h

2012-02-20:Wang Xiebin
        1)Reduce the delay according eeti engineer's advice
        Modifided files:
         drivers/input/touchscreen/egalax_i2c.c

2012-02-21:Zhang Dong
	1)modify sleep power related code 
	Modified files:
        arch/arm/mach-exynos/mach-smdk4x12.c
	drivers/regulator/s5m8767.c
2012-02-20:Wang Xiebin
        1)Update TS for Multi-Touch
        Modifided files:
         drivers/input/touchscreen/egalax_i2c.c
         
2012-02-17:Cui Wenpin
		1) Format "wm8994-path.c", "wm8994.c", etc after kernel codingstyle.
		2) Ajust wm8994 register setting when switching between playback and capture
		   playback path won't operate capture related power registers,
		   neither will capture.
		   This can solve the sound loss when switching between the two frequently.
		3) Optimize audio code. Delete useless code, ajust the order of some codes, change macro defination etc.
		4) Add macro "HIGH_VOLUME" in wm8994-path.c, enable it can get higher volume during playback.
		5) This update include previous commit:
			8cb4bc8839e2db8b2364b83fb59e437e60d3f117
		Modified files:
			sound/soc/codecs/wm8994-path.c
			sound/soc/codecs/wm8994-path.h
			sound/soc/codecs/wm8994.c
			sound/soc/samsung/smdk_wm8994.c
			drivers/switch/switch_gpio.c

2012-02-17:Wang Xiebin
        1)Add config for GB2.3.4 @TC4 DVT board
        Modifided files:
         arch/arm/mach-exynos/Kconfig
         arch/arm/configs/tc4_dvt_gingerbread_defconfig

2012-02-16:Wang Xiebin
        1)Bugfix for g2d system mmu kernel panic
        2)Bugfix for system lock 
        Modifided files:
         arch/arm/mach-exynos/busfreq_opp.c
         arch/arm/mach-exynos/cpufreq-4x12.c

2012-02-14:Wang Xiebin
	1)Upgrade the TC4 DVFS code according the HQ 0209 code
	2)Enable the TMU function
	3)Add USB wakelock, when usb in, system don't enter sleep mode.
	Modifided files:
		arch/arm/configs/tc4_dvt_icecream_defconfig
		arch/arm/configs/tc4_evt_icecream_defconfig
		arch/arm/mach-exynos/Kconfig
		arch/arm/mach-exynos/Makefile
		arch/arm/mach-exynos/asv-4210.c
		arch/arm/mach-exynos/asv-4x12.c
		arch/arm/mach-exynos/asv.c
		arch/arm/mach-exynos/busfreq.c
		arch/arm/mach-exynos/busfreq_opp.c
		arch/arm/mach-exynos/busfreq_opp_4x12.c
		arch/arm/mach-exynos/busfreq_opp_5250.c
		arch/arm/mach-exynos/clock-exynos4.c
		arch/arm/mach-exynos/clock-exynos4212.c
		arch/arm/mach-exynos/cpufreq-4x12.c
		arch/arm/mach-exynos/cpufreq.c
		arch/arm/mach-exynos/include/mach/asv.h
		arch/arm/mach-exynos/include/mach/busfreq.h
		arch/arm/mach-exynos/include/mach/cpufreq.h
		arch/arm/mach-exynos/include/mach/dev-sysmmu.h
		arch/arm/mach-exynos/include/mach/dev.h
		arch/arm/mach-exynos/include/mach/exynos-clock.h
		arch/arm/mach-exynos/include/mach/gpio-exynos5.h
		arch/arm/mach-exynos/include/mach/irqs-exynos4.h
		arch/arm/mach-exynos/include/mach/irqs-exynos5.h
		arch/arm/mach-exynos/include/mach/map-exynos4.h
		arch/arm/mach-exynos/include/mach/map-exynos5.h
		arch/arm/mach-exynos/include/mach/media.h
		arch/arm/mach-exynos/include/mach/ppmu.h
		arch/arm/mach-exynos/include/mach/regs-clock.h
		arch/arm/mach-exynos/include/mach/regs-pmu-4212.h
		arch/arm/mach-exynos/include/mach/regs-pmu-5250.h
		arch/arm/mach-exynos/include/mach/regs-pmu5.h
		arch/arm/mach-exynos/include/mach/regs-sysmmu.h
		arch/arm/mach-exynos/include/mach/regs-tmu.h
		arch/arm/mach-exynos/include/mach/secmem.h
		arch/arm/mach-exynos/include/mach/videonode-exynos4.h
		arch/arm/mach-exynos/include/mach/videonode-exynos5.h
		arch/arm/mach-exynos/mach-smdk4x12.c
		arch/arm/mach-exynos/ppmu.c
		arch/arm/mach-exynos/reserve_mem-exynos4.c
		arch/arm/plat-s5p/dev-tmu.c
		arch/arm/plat-s5p/include/plat/s5p-tmu.h
		arch/arm/plat-samsung/pm-gpio.c
		arch/arm/mach-exynos/tmu_exynos.c
		drivers/usb/gadget/s3c_udc_otg.c
		drivers/usb/gadget/s3c_udc_otg_xfer_dma.c 
	
	
2012002-07:Ma Jun
	1):added the factory reset function..
	#       modified:   arch/arm/mach-exynos/cpu-exynos4.c
	#       modified:   arch/arm/plat-s5p/include/plat/reset.h
	#       modified:   arch/arm/plat-s5p/include/plat/system-reset.h
	#       modified:   arch/arm/plat-s5p/reset.c

2012-02-07:Wang Xiebin
	1)Don't Power on the wifi chip, because of there is a sleep/wakeup issue when wifi is on
	Modifided files:
	drivers/regulator/s5m8767.c
	
2012-02-6:Zhang Dong
	1)modify camera power for evt board 
	Modified files:
        drivers/media/video/mt9d115.c
        drivers/media/video/s5k4ecgx.c
        arch/arm/configs/tc4_evt_icecream_defconfig

2012-01-18:Wang Xiebin
	1)Add reserve memory for UXGA preview
	Modified files:
	arch/arm/configs/tc4_dvt_icecream_defconfig
	arch/arm/configs/tc4_evt_icecream_defconfig
	
2012-01-18:Wang Xiebin
	1)Bugfix for Video can't play when wakeup for first time
	2)Support VGA&UXGA preview automatic
	Modified files:
	drivers/media/video/samsung/fimc/fimc_capture.c
	 drivers/media/video/samsung/fimc/fimc_dev.c

2012-01-17:Zhang Dong
	1)modify camera power related code 
	Modified files:
        arch/arm/mach-exynos/mach-smdk4x12.c
        drivers/media/video/mt9d115.c
        drivers/media/video/s5k4ecgx.c

2012-01-13:Wang Xiebin
	1)Fix 2M camera capture issue
        Modified files:
	drivers/media/video/samsung/fimc/fimc_capture.c

2012-01-13:Zhang Dong
	1)add charger function
	Modified files:
	arch/arm/configs/tc4_dvt_icecream_defconfig
	arch/arm/mach-exynos/mach-smdk4x12.c
        drivers/power/max17040_battery.c
        drivers/power/max8903.c
        include/linux/max17040_battery.h

2012-01-13:Cui Wenpin
	1)Roll back previous modification to guarantee SoundRecorder working correct
	Modified files:
	sound/soc/soc-core.c
2012-01-13:Wang Xiebin
	1)Force the BusFreq to 400Mhz when decode/encode the 1080P video stream
	2)When AP is dual core, the busfreq is limited to 400Mhz. Temp solution..
	Modified files:
	drivers/media/video/samsung/mfc5x/mfc_dec.c
	drivers/media/video/samsung/mfc5x/mfc_dev.c
	drivers/media/video/samsung/mfc5x/mfc_dev.h
	drivers/media/video/samsung/mfc5x/mfc_enc.c
	drivers/media/video/samsung/mfc5x/mfc_inst.c
	drivers/media/video/samsung/mfc5x/mfc_inst.h
	arch/arm/mach-exynos/busfreq_opp_4x12.c

2012-01-12:Wang Xiebin
	1)Change the ramp delay (50 -->10),It will help stable voltage change of DVS BUCKs
	Modified files:
	arch/arm/mach-exynos/mach-smdk4x12.c

2012-01-11: Sheng Liang
	1) Modify Kconfig info
	2) Add USB device info
	Modified files:
	  arch/arm/mach-exynos/Kconfig
	  drivers/usb/core/hub.c

2012-01-11:Wang Xiebin
	1)Disable the external GIC wakeup source, in order to fix the wakeup sometimes.
	Modified files:
 	 arch/arm/mach-exynos/include/mach/pm-core.h

2012-01-11: Wang Xiebin
	  1)Enable the S5M8767 RTC function.

	Modified files:
		arch/arm/configs/tc4_dvt_icecream_defconfig
		drivers/rtc/hctosys.c
		drivers/rtc/rtc-s5m.c
	  
2012-01-9 zhangdong
        1) restore disabling voltage scaling of DVFS
        Modified file:
           arch/arm/mach-exynos/busfreq_opp.c
           arch/arm/mach-exynos/busfreq_opp_4x12.c
           arch/arm/mach-exynos/cpufreq.c
           tc4_evt_icecream_defconfig
           
2012-01-06: Lucy
	1) Power on/off vdd33_lcd in lcd driver
	Modified file:
	  arch/arm/mach-exynos/mach-smdk4x12.c
	  arch/arm/mach-exynos/tc4-regulator-consumer.c
	  drivers/regulator/s5m8767.c
	  drivers/video/samsung/s3cfb_main.c

2012-01-05: Sheng Liang
	1) Modify VDD18_HSIC to 1.8V for USB Hub 3503A
	Modified file:
	  arch/arm/mach-exynos/mach-smdk4x12.c

2012-01-05:Cui Wenpin
	1)Remove the codes that limits capture stream sample rate to 44100Hz.
	Modified files:
		sound/soc/soc-core.c
2012-01-05:Wang Xiebin
   	1)Limited the BusFreq to 3 Levels(400Mhz--266Mhz). The LCD display flick is caused by the memory load.
	Modified files:
	arch/arm/mach-exynos/busfreq_opp_4x12.c

2012-01-05: Sheng Liang
	1)Remove I2C6 code for USB HUB of DVT
	Modified file:
	  arch/arm/mach-exynos/mach-smdk4x12.c

<<<<<<< HEAD
2012-01-05: Zhang Dong
	1)Modify busfreq for normal sleep/wakeup
	Modified files:
	  arch/arm/mach-exynos/busfreq_opp.c
	  arch/arm/mach-exynos/busfreq_opp_4x12.c
=======
2012-01-04: Like Yan
	1) Fixed the error of mis booting up of secondary cpus when number of 
           existing CPUs is greater than configured NR_CPUS.
	Modified file:
		arch/arm/mach-exynos/dynamic-dvfs-nr_running-hotplug.c
>>>>>>> 755b8eeee647f21906bbe1b7e6a9a4c985966d78

2012-01-04: Sheng Liang
	1)Modify Sensor data for Landscape mode
	Modified files:
	  arch/arm/mach-exynos/mach-smdk4x12.c

2012-01-04: Lucy
		1)Fixed the error of vdd50 output, hdmi could work well.
		2)Enable 8997 regulator option of tc4_evt_icecream_defconfig. 
	Modified files:
		drivers/regulator/max8997.c
		arch/arm/configs/tc4_evt_icecream_defconfig

2012-01-01: Wang Xiebin
	  1)TC4 Quad-core EVT board, the max.freq is 1.2G,and for DVT, the max.freq is 1.4G.
	  2)Update the Audio SRP's register MINOR number. Because the default MINOR 250 is already used by max8997 evt.So Change MINOR 250 -> 253.
	  3)Fix a compile error when disable the 3D MALI DVFS function. And Disable the MALI DVFS in config file.
	  4)Enable WIRELESS_EXT config,it's for WIFI configuration.
	Modified files:
	  arch/arm/mach-exynos/Kconfig
	  sound/soc/samsung/srp_ulp/srp.c
	  drivers/media/video/samsung/mali_ics/platform/pegasus-m400/mali_platform.c
	  arch/arm/configs/tc4_dvt_icecream_defconfig
	  arch/arm/configs/tc4_evt_icecream_defconfig	 
	  net/wireless/Kconfig 
2012-02-01: Donggeun Baek
	1) Modify the LDO control code for A31 module.
	   Modified files:
		drivers/regulator/s5m8767.c


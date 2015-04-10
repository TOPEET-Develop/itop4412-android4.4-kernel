obj-$(CONFIG_VIDEO_FIMC)	+= fimc/
obj-$(CONFIG_VIDEO_JPEG)	+= jpeg/
obj-$(CONFIG_VIDEO_JPEG_V2X)	+= jpeg_v2x/
obj-$(CONFIG_VIDEO_TVOUT)	+= tvout/
obj-$(CONFIG_VIDEO_MFC5X)	+= mfc5x/
obj-$(CONFIG_VIDEO_FIMG2D3X)	+= fimg2d3x/
obj-$(CONFIG_VIDEO_FIMG2D4X)	+= fimg2d4x/

obj-$(CONFIG_GB_VIDEO_FIMG2D)	+= fimg2d_android/

ifeq ($(CONFIG_TC4_GB),y)
obj-$(CONFIG_GB_VIDEO_UMP)		+= ump_gb/
obj-$(CONFIG_GB_VIDEO_MALI400MP)	+= mali_gb/
endif

ifeq ($(CONFIG_TC4_ICS),y)
#obj-$(CONFIG_VIDEO_UMP)		+= ump_ics/
#obj-$(CONFIG_VIDEO_MALI400MP)	+= mali_ics/
#obj-$(CONFIG_VIDEO_MALI400MP_UMP)       += ump_r3p1/
#obj-$(CONFIG_MALI_400MP_UMP)            += mali_r3p1/
obj-$(CONFIG_MALI400_UMP)       += ump_r4p0/
obj-$(CONFIG_MALI400)           += mali_r4p0/
endif

EXTRA_CFLAGS += -Idrivers/media/video

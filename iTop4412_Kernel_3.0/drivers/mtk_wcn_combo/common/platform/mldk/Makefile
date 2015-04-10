
# WMT DRIVER-platform implementation
mtk_stp_wmt-y += platform/mldk/wmt_plat_mldk.o
# Select desired hw according to project configuration
mtk_stp_wmt-$(CONFIG_MTK_COMBO_CHIP_MT6620) += platform/mldk/mtk_wcn_cmb_hw_6620.o
mtk_stp_wmt-$(CONFIG_MTK_COMBO_CHIP_MT6628) += platform/mldk/mtk_wcn_cmb_hw_6628.o
# WMT stub part (built-in kernel image)
obj-y += platform/mldk/mtk_wcn_cmb_stub_mldk.o


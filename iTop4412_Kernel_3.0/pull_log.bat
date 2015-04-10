@echo off
adb remount
adb shell "rm /data/kmsg_last.txt"
adb shell "rm /data/logger_main_last.txt"
adb shell "rm /data/logger_event_last.txt"
adb shell "rm /data/logger_radio_last.txt"
adb shell "rm /data/logger_system_last.txt"
echo log file generating...
adb shell "echo 6 > /sys/devices/platform/samsung-kmsg/kmsg_ctrl"
echo starting to pull
adb pull /data/kmsg_last.txt
adb pull /data/logger_main_last.txt
adb pull /data/logger_event_last.txt
adb pull /data/logger_radio_last.txt
adb pull /data/logger_system_last.txt
echo pull finished!!
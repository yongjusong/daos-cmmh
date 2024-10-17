#!/bin/sh

sudo umount /mnt/ramdisk0
sudo rm -rf /mnt/ramdisk0

sudo mkdir /mnt/ramdisk0
sudo mount -t tmpfs -o size=16G tmpfs /mnt/ramdisk0
df -h /mnt/ramdisk0

.PHONY: all
all: ../boot.img

../boot.img:
	rm -f $@
	dd if=/dev/zero bs=1M count=0 seek=64 of=$@
	parted -s $@ mklabel gpt
	parted -s $@ mkpart ESP fat32 2048s 100%
	parted -s $@ set 1 esp on
	limine-deploy $@
	sudo losetup -Pf --show $@ >loopback_dev
	sudo mkfs.fat -F 32 `cat loopback_dev`p1
	mkdir -p img_mount
	sudo mount `cat loopback_dev`p1 img_mount
	sudo mkdir -p img_mount/EFI/BOOT
	sudo cp -v ../vmgix limine.cfg ../thirdparty/limine/limine.sys img_mount/
	sudo cp -v ../thirdparty/limine/BOOTX64.EFI img_mount/EFI/BOOT/
	sync
	sudo umount img_mount
	sudo losetup -d `cat loopback_dev`
	rm -rf loopback_dev img_mount

.PHONY: clean
clean:
	rm -rf iso_root

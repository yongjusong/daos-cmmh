
#!/bin/sh                                                                                                                                                                                                           

#Preparing nvme
for SET in $(seq 0 1);
#for SET in 0 1 2 3 9
do
        umount /mnt/nvme${SET}n1
        rm -r /mnt/nvme${SET}n1

        sudo ndctl create-namespace --mode=fsdax
        sleep 1
        mkdir -p /mnt/nvme${SET}n1

        yes | mkfs.ext4 -E lazy_itable_init=0,lazy_journal_init=0 "/dev/nvme${SET}n1"
        tune2fs -O ^has_journal "/dev/nvme${SET}n1"
        e2fsck -f "/dev/nvme${SET}n1"

        #mount -o rw,noatime,nodiratime,block_validity,delalloc,nojournal_checksum,barrier,user_xattr,acl -t ext4 "/dev/nvme${SET}n1" "/mnt/nvme${SET}n1"

        sleep 1
done


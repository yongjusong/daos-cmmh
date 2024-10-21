
#!/bin/sh

ndctl destroy-namespace -f all

#Preparing PMEM
for SET in $(seq 0 0);
do
        umount /mnt/pmem${SET}
        rm -r /mnt/pmem${SET}


        sudo ndctl create-namespace --mode=fsdax

        sleep 1

        mkdir -p /mnt/pmem${SET}

        yes | mkfs.ext4 -E lazy_itable_init=0,lazy_journal_init=0 "/dev/pmem${SET}"
        tune2fs -O ^has_journal "/dev/pmem${SET}"
        e2fsck -f "/dev/pmem${SET}"

        mount -o rw,noatime,nodiratime,block_validity,delalloc,nojournal_checksum,barrier,user_xattr,acl,dax -t ext4 "/dev/pmem${SET}" "/mnt/pmem${SET}"

        #mkdir -p /mnt/pmem${SET}/prism

        sleep 1
done


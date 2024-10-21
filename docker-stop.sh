#/bin/bash

 utils/docker/vcluster/daos-cm.sh stop

sudo  ./format_nvme.sh
sudo  ./format_pmem.sh


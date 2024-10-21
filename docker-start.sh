#/bin/bash

utils/docker/vcluster/daos-cm.sh start 127.0.0.1

docker cp /home/yongju/daos-cmmh/config-daos.ini daos-client:/opt/io500/


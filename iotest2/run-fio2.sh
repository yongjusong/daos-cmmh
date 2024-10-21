#!/bin/bash

# Output Directory
OUTDIR=./fio-output2

# Benchmark Directories
DIRECTORIES=(/mnt/pmem0) #/mnt/nvme0 /mnt/nvme1)

# Block Size for Testing
BLOCK_SIZE=4K

# I/O Depth Values for Testing
IODEPTH=(1) # 2 4 8 16 32) # 64 128 256 512 1024)

# Workloads to Test
WORKLOADS=(read write randread randwrite)

# Number of Jobs to Run
NUM_JOBS=(1 2 4 8 16 32)

# Function to Generate FIO Job File
gen_job_file() {
    local workload=$1
    local block_size=$2
    local iodepth=$3
    local numjobs=$4
    local directory=$5

    cat <<EOF > ${workload}.fio
[global]
bs=$block_size
direct=1
rw=$workload
ioengine=libaio
time_based=1
runtime=60s
[test]
directory=$directory
iodepth=$iodepth
numjobs=$numjobs
size=10g
group_reporting=1
EOF
}

# Cleanup Temporary Files
cleanup() {
    rm -f *.fio
    rm -f *.tmp
    rm -f libaio-irq-*-result-summary.txt
    rm -rf fio-output2/*
}

# Function to Run FIO Test
run_test() {
    local workload=$1
    local block_size=$2
    local iodepth=$3
    local numjobs=$4
    local directory=$5

    local output_file="$OUTDIR/libaio-irq-$workload-$block_size-$iodepth-$numjobs-log"
    local stat_output="libaio-irq-$workload-$block_size-$iodepth-$numjobs-log"

    #./iostat.sh $stat_output &
    #./mpstat.sh $stat_output &

    fio --output="$output_file" ${workload}.fio

    if [ "$workload" == "read" ]; then
        grep ', BW=' "$output_file" >> libaio-irq-bw-result-summary.txt
        grep ' lat (usec): min' "$output_file" >> libaio-irq-lat-result-summary.txt
    elif [ "$workload" == "randread" ]; then
        grep ', BW=' "$output_file" >> libaio-irq-bw-result-summary.txt
        grep ' lat (usec): min' "$output_file" >> libaio-irq-lat-result-summary.txt
    elif [ "$workload" == "write" ]; then
	grep ', BW=' "$output_file" >> libaio-irq-bw-result-summary.txt
    elif [ "$workload" == "randwrite" ]; then
	grep ', BW=' "$output_file" >> libaio-irq-bw-result-summary.txt
    fi

    pkill iostat
    pkill mpstat
}

# Main Execution Starts Here
mkdir -p $OUTDIR

# Remove Previous Output Files
rm -f libaio-irq-*
rm -f $OUTDIR/libaio-irq-*

# Clean Temporary Files Before Starting
cleanup

# Run All Tests
for workload in "${WORKLOADS[@]}"; do
    for directory in "${DIRECTORIES[@]}"; do
        for iodepth in "${IODEPTH[@]}"; do
            for numjobs in "${NUM_JOBS[@]}"; do
                echo "Running libaio $workload on $directory with block size $BLOCK_SIZE, iodepth $iodepth, numjobs $numjobs"
                gen_job_file $workload $BLOCK_SIZE $iodepth $numjobs $directory
                run_test $workload $BLOCK_SIZE $iodepth $numjobs $directory
		sudo ./format_pmem.sh
            done
        done
    done
done


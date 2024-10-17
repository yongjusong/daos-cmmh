#!/bin/bash

sudo vim /etc/init.d/cpufrequtils;
sudo systemctl daemon-reload;
sudo /etc/init.d/cpufrequtils restart;

cpufreq-info

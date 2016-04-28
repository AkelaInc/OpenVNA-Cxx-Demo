#!/bin/bash

cp ../build/vnadll/libvna.so ./
LD_LIBRARY_PATH="/usr/local/qwt-6.1.3-svn/lib:./" ./VNATest
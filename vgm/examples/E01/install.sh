#!/bin/sh
#
# Script for installation for E01 examples

CURDIR=`pwd`

echo "... Installing E01"
./install_sources.sh
. env_setup.sh
cd N03
gmake
echo "... Installing E01 finished"

cd $CURDIR

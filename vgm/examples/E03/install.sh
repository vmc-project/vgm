#!/bin/sh
#
# Script for installation for E03 examples

CURDIR=`pwd`

echo "... Installing E03"
./install_sources.sh
. env_setup.sh
cd N03
gmake
echo "... Installing E03 finished"

cd $CURDIR

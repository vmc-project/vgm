#!/bin/sh
#
# Script for installation for E02 examples

CURDIR=`pwd`

# E02
#
echo "... Installing E02"
./install_sources.sh
. env_setup.sh
cd N03
gmake
echo "... Installing E02 finished"

cd $CURDIR

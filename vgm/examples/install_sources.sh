#!/bin/sh
#
# Script for installation for all examples

CURDIR=`pwd`

cd E01
./install_sources.sh

cd $CURDIR/E02
./install_sources.sh

cd $CURDIR/E03
./install_sources.sh


cd $CURDIR

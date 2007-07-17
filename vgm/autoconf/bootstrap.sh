#! /bin/sh

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see autoconf/COPYING.
# Contact: bv@bnl.gov

set -x
aclocal
libtoolize --force --copy
autoheader
automake --add-missing --copy
autoconf

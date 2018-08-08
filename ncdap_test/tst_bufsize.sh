#!/bin/sh

# This test is intended to be run only manually
# The idea is to gdb ncdump and check that CURLOPT_BUFFERSIZE
# is being set

if test "x$srcdir" = x ; then srcdir=`pwd`; fi
. ../test_common.sh

# Figure our dst server; if none, then just stop
DTS=`${execdir}/findtestserver dap2 dts`
if test "x$DTS" = "x" ; then
echo "WARNING: Cannot locate test server for dts"
exit
fi

URL="[log]${DTS}/test.01"

# Create the .daprc file
rm -f ./.daprc
echo 'HTTP.READ.BUFFERSIZE=max' > ./.daprc
gdb --args ${NCDUMP} "${URL}"

# cleanup
rm -f ./.daprc

exit

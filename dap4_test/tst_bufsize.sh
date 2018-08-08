#!/bin/sh

# This test is intended to be run only manually
# The idea is to gdb ncdump and check that CURLOPT_BUFFERSIZE
# is being set

if test "x$srcdir" = x ; then srcdir=`pwd`; fi
. ../test_common.sh

# Figure our dst server; if none, then just stop
D4TS=`${execdir}/findtestserver4 dap4 d4ts`
if test "x$D4TS" = "x" ; then
echo "WARNING: Cannot locate test server for d4ts"
exit
fi

URL="[log][dap4]${D4TS}/testfiles/test_atomic_types.nc"

# Create the .daprc file
rm -f ./.daprc
echo 'HTTP.READ.BUFFERSIZE=max' > ./.daprc
gdb --args ${NCDUMP} -h "${URL}"

# cleanup
rm -f ./.daprc

exit

#!/bin/bash
set -x
./configure --disable-doxygen --disable-shared --enable-dap --enable-netcdf-4 --enable-diskless CFLAGS="-fno-stack-check -fno-stack-protector -mno-stack-arg-probe -ggdb -O0 -I/c/Users/wfisher/Desktop/hdf5-1.8.9/src -I/c/Users/wfisher/Desktop/hdf5-1.8.9/hl/src -I/c/Users/wfisher/Desktop/curl-7.25.0/build_win32/include/ -DCURL_STATICLIB" LDFLAGS="-ggdb -O0 -L/c/Users/wfisher/Desktop/hdf5-1.8.9/build_win32_static/bin -L/c/Users/wfisher/Desktop/curl-7.25.0/build_win32/lib/.libs -L/c/Users/wfisher/Desktop/szip-2.1/build_win32/bin"

#-L/c/Users/wfisher/Desktop/curl-7.25.0/lib/.libs/libcurl.a"
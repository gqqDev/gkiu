#!/bin/sh

find . -name \*\~ -exec rm {} \;
make distclean
rm -rf autom4te.cache


#!/bin/bash

PREV=$0
ZBASE=${ZEPHYR_BASE}
ERR=0

for ARG in $*; do
	if [ "$PREV" == "-z" ] ; then
		ZBASE=$ARG
	fi
	PREV=$ARG
done

pushd "$ZBASE"
west $*
ERR=$?
popd >/dev/null

exit $ERR

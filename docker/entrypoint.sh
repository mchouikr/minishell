#!/bin/sh

status=0
if [ "$#" -eq 0 ]; then
	/bin/bash
	status=$?
else
	"$@"
	status=$?
fi

if [ "${MSH_AUTO_FCLEAN:-1}" != "0" ] && [ -f /workspace/Makefile ]; then
	(cd /workspace && make fclean) || true
fi

exit $status

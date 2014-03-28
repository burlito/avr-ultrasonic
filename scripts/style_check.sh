#!/bin/bash

perl `dirname $0`/checkpatch.pl --no-tree --terse --file `dirname $0`/../src/*.c

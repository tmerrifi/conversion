#!/bin/bash

cat /proc/$1/maps | grep $2 | head -1 | gawk -F '-' '{print $1 $2}'

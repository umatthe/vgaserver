#!/bin/bash

CPU_OPTS=-T5 

rm *.btl
rm *.tco
rm *.lku
rm *.tga

icc  -FS $CPU_OPTS main
icc  -FS $CPU_OPTS gamedef
icc  -FS $CPU_OPTS gamepic
icc  -FS $CPU_OPTS sokoban

ilink     main.tco gamedef.tco gamepic.tco sokoban.tco -f startup.lnk $CPU_OPTS -o soku.lku -mo soku.map
icollect  soku.lku -t -o soku.btl -p soku.plc

ls -l *.btl





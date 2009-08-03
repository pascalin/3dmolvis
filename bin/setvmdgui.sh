#!/usr/bin/env bash

echo "Linking VMD core binary"
./bin/vmd.py bin/

echo "Compiling translations"
lrelease vmdgui.pro

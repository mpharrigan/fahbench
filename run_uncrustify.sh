#!/bin/bash

find . -name "*.cpp" | uncrustify -c uncrustify.cfg --replace --no-backup -F -

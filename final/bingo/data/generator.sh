#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution bingo.cc

samplegroup
sample 1
sample 2

group 01_group01 20
tc_manual ../manual-tests/g01.in
tc 1
tc 2

group 02_group02 20
tc_manual ../manual-tests/g02.in
tc 1
tc 2

group 03_group03 20
tc_manual ../manual-tests/g03.in
tc 1
tc 2

group 04_group04 20
tc_manual ../manual-tests/g04.in
tc 1
tc 2

group 05_group05 20
tc_manual ../manual-tests/g05.in
tc 1
tc 2

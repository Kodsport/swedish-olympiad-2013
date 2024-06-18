#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution par.cc

# compile gen_random.py
# params: 10000 100 10000

samplegroup
sample 1
sample 2
sample 3


group 01_group01 10
tc_manual ../manual-tests/g01.in
tc 1
tc 2
tc 3

group 02_group02 10
tc_manual ../manual-tests/g02.in
tc 1
tc 2
tc 3

group 03_group03 10
tc_manual ../manual-tests/g03.in
tc 1
tc 2
tc 3

group 04_group04 10
tc_manual ../manual-tests/g04.in
tc 1
tc 2
tc 3

group 05_group05 10
tc_manual ../manual-tests/g05.in
tc 1
tc 2
tc 3

group 06_group06 10
tc_manual ../manual-tests/g06.in
tc 1
tc 2
tc 3

group 07_group07 10
tc_manual ../manual-tests/g07.in
tc 1
tc 2
tc 3

group 08_group08 10
tc_manual ../manual-tests/g08.in
tc 1
tc 2
tc 3

group 09_group09 10
tc_manual ../manual-tests/g09.in
tc 1
tc 2
tc 3

group 10_group10 10
tc_manual ../manual-tests/g10.in
tc 1
tc 2
tc 3
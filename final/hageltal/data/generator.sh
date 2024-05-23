#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution collatz.py

samplegroup
sample 1
sample 2
sample 3
sample 4
sample 5

group 1_group01 20
tc_manual ../manual-tests/g01.in
tc 1
tc 2
tc 3
tc 4
tc 5

group 1_group02 20
tc_manual ../manual-tests/g02.in
tc 1
tc 2
tc 3
tc 4
tc 5

group 1_group03 20
tc_manual ../manual-tests/g03.in
tc 1
tc 2
tc 3
tc 4
tc 5

group 1_group04 20
tc_manual ../manual-tests/g04.in
tc 1
tc 2
tc 3
tc 4
tc 5

group 1_group05 20
tc_manual ../manual-tests/g05.in
tc 1
tc 2
tc 3
tc 4
tc 5

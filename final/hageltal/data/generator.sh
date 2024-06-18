#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution collatz.py

samplegroup
sample 1
sample 2
sample 3
sample 4
sample 5
sample 6

group group1 40
tc_manual a1-1
tc_manual a1-2
tc_manual a1-3
tc_manual a1-4

group group2 60
include_group sample
include_group group1
tc_manual ../manual-tests/g01.in
tc_manual ../manual-tests/g02.in
tc_manual ../manual-tests/g03.in
tc_manual ../manual-tests/g04.in
tc_manual ../manual-tests/g05.in

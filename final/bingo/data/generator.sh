#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution bingo.cc

samplegroup
sample 1
sample 2

group group1 20 # Kinda weak test data, but that's outside of my salary range
tc 1
tc_manual ../manual-tests/g01.in
tc_manual ../manual-tests/g02.in

group group2 40
tc g01
tc g02
tc_manual ../manual-tests/g04.in
tc_manual ../manual-tests/g05.in
tc 2

group group3 40
include_group group1
include_group group2
tc_manual ../manual-tests/g03.in

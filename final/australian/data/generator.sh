#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution tennisprob_dict.py

samplegroup
sample 1
sample 2

group group1 20
tc_manual small1
tc_manual small2
tc_manual small3
tc_manual small4

group group2 80
include_group group1
include_group sample
tc_manual ../manual-tests/g01.in
tc_manual ../manual-tests/g02.in
tc_manual ../manual-tests/g03.in
tc_manual ../manual-tests/g04.in
tc_manual ../manual-tests/g05.in

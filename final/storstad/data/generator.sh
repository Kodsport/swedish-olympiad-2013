#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution par.cc

# compile gen_random.py
# params: 10000 100 10000

samplegroup
sample 1
sample 2
sample 3


group g1 40
include_group sample
tc_manual ../manual-tests/g01.in
tc_manual ../manual-tests/g02.in
tc_manual ../manual-tests/g03.in
tc_manual ../manual-tests/g04.in

group g2 60
include_group g1
tc_manual ../manual-tests/g05.in
tc_manual ../manual-tests/g06.in
tc_manual ../manual-tests/g07.in
tc_manual ../manual-tests/g08.in
tc_manual ../manual-tests/g09.in
tc_manual ../manual-tests/g10.in


#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution rakneord.cpp
compile gen_random.py

samplegroup
sample 1
sample 2
sample 3


group 1_small 15
limits n=2000
tc_manual ../manual-tests/g01.in
tc small-1 gen_random n=2000
tc small-2 gen_random n=2000
tc small-3 gen_random n=2000
tc small-4 gen_random n=2000
tc small-5 gen_random n=2000
tc 1
tc 2
tc 3

group 2_medium 20
limits n=500000
include_group 1_small
tc_manual ../manual-tests/g02.in
tc_manual ../manual-tests/g03.in
tc medium-1 gen_random n=500000
tc medium-2 gen_random n=500000
tc medium-3 gen_random n=500000
tc medium-4 gen_random n=500000
tc medium-5 gen_random n=500000

group 3_large 65
limits n=999999999999
include_group 2_medium
tc_manual ../manual-tests/g04.in
tc_manual ../manual-tests/g05.in
tc_manual ../manual-tests/g06.in
tc_manual ../manual-tests/g07.in
tc_manual ../manual-tests/g08.in
tc_manual ../manual-tests/g09.in
tc_manual ../manual-tests/g10.in
tc large-1 gen_random n=999999999999
tc large-2 gen_random n=999999999999
tc large-3 gen_random n=999999999999
tc large-4 gen_random n=999999999999
tc large-5 gen_random n=999999999999


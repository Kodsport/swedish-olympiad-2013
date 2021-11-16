#!/usr/bin/env bash

PPATH=$(realpath ..)
REQUIRE_SAMPLE_REUSE=0
. ../../../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution skolvag.cpp

compile gen_random.py

samplegroup
limits maxl=1000 
sample 1
sample 2

group group1 40
limits maxl=20
tc 1
tc 2
tc_manual g1
tc_manual g2
tc rand-small-1 gen_random len=20
tc rand-small-2 gen_random len=20
tc rand-small-3 gen_random len=20
tc rand-small-4 gen_random len=20
tc rand-small-5 gen_random len=20
tc rand-small-6 gen_random len=20
tc rand-small-7 gen_random len=20
tc rand-small-8 gen_random len=20

group group2 60
limits maxl=1000
include_group group1
tc_manual g3
tc_manual g4
tc_manual g5
tc rand-1 gen_random len=1000
tc rand-2 gen_random len=1000
tc rand-3 gen_random len=1000
tc rand-4 gen_random len=1000
tc rand-5 gen_random len=1000
tc rand-6 gen_random len=1000
tc rand-7 gen_random len=1000
tc rand-8 gen_random len=1000

#!/usr/bin/env bash

PPATH=$(realpath ..)
REQUIRE_SAMPLE_REUSE=0
. ../../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution skolvag.cpp

samplegroup
limits maxl=1000 
sample 1
sample 2

group group1 20
limits maxl=20
tc_manual g1

group group2 20
limits maxl=20
tc_manual g2

group group3 20
limits maxl=1000
tc_manual g3

group group4 20
limits maxl=1000
tc_manual g4

group group5 20
limits maxl=1000
tc_manual g5

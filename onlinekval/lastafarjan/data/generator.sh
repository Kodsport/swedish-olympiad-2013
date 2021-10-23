#!/usr/bin/env bash

PPATH=$(realpath ..)
REQUIRE_SAMPLE_REUSE=0
. ../../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution par.cpp

samplegroup
limits maxn=20 maxl=40
sample 1
sample 2
sample 3

group group1 40
limits maxn=20 maxl=40
include_group sample
tc_manual ../manual/01.in
tc_manual ../manual/02.in
tc_manual ../manual/03.in
tc_manual ../manual/04.in
tc_manual ../manual/new1.in
tc_manual ../manual/new2.in
tc_manual ../manual/new3.in

group group2 60
limits maxn=200 maxl=60
include_group group1
tc_manual ../manual/05.in
tc_manual ../manual/06.in
tc_manual ../manual/07.in
tc_manual ../manual/08.in
tc_manual ../manual/09.in
tc_manual ../manual/10.in

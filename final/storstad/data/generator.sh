#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh


use_solution joshua.cpp

compile gen_random.py
compile gen_faroptimum.py

samplegroup
limits maxn=10 maxm=10
sample 1
sample 2
sample 3


group g1 40
limits maxn=10000 maxm=100
include_group sample
tc_manual ../manual-tests/g01.in
tc_manual ../manual-tests/g02.in
tc_manual ../manual-tests/g03.in
tc_manual ../manual-tests/g04.in
tc g1-rand-max gen_random n=10000 m=100 a=10000
tc g1-rand-narrow gen_random n=10000 m=100 a=1
tc g1-rand-one-friend gen_random n=1 m=100 a=10000
tc g1-rand-one-house gen_random n=10000 m=1 a=10000

group g2 60
include_group g1
tc_manual ../manual-tests/g05.in
tc_manual ../manual-tests/g06.in
tc_manual ../manual-tests/g07.in
tc_manual ../manual-tests/g08.in
tc_manual ../manual-tests/g09.in
tc_manual ../manual-tests/g10.in
tc g2-rand-max gen_random n=100000 m=100000 a=10000
tc g2-rand-narrow gen_random n=100000 m=100000 a=1
tc g2-rand-many-friends gen_random n=100000 m=1 a=10000
tc g2-rand-many-houses gen_random n=1 m=100000 a=10000
tc faroptimum gen_faroptimum n=100000 m=100000


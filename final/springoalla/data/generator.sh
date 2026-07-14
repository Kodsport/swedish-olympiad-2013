#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh

use_solution js.cpp

compile gen_rand.py
compile gen_manual.py
compile gen_whole.py
compile gen_halves.py

samplegroup
limits maxn=5 maxt=30
sample 1
sample 2
sample 3
sample 4

group subtask1 20
limits maxn=10 maxt=1000
include_group sample
tc s1-rand-a1 gen_rand n=3 t=1000
tc s1-rand-a2 gen_rand n=3 t=1000
tc s1-rand-a3 gen_rand n=3 t=1000
tc s1-rand-b1 gen_rand n=10 t=1000
tc s1-rand-b2 gen_rand n=10 t=1000
tc s1-rand-b3 gen_rand n=10 t=1000
tc s1-m1 gen_manual l=2 t=1000
tc s1-m2 gen_manual l=2,4,8,10 t=1000
tc s1-m3 gen_manual l=10,18 t=991
tc s1-m4 gen_manual l=10,18 t=990
tc s1-m5 gen_manual l=10,18 t=989
tc s1-halves gen_halves m=4 n=10

group subtask2 30
limits onlywhole=1
tc s2-m1 gen_manual l=10000,20000,40000 t=100000
tc s2-m2 gen_manual l=40000 t=40000
tc s2-m3 gen_manual l=40000 t=39999
tc s2-m4 gen_manual l=2,4,6,8,10,30,34,36,38 t=98800
tc s2-big1 gen_whole n=1000 t=100000 maxl=20000
tc s2-big2 gen_whole n=1000 t=100000 maxl=200
tc_manual ../manual-tests/close-1000.in
tc_manual ../manual-tests/close-10000.in

group subtask3 50
include_group subtask1
include_group subtask2
tc s3-m1 gen_manual l=40000 t=40001
tc s3-m2 gen_manual l=40000 t=60000
tc s3-m3 gen_manual l=40000 t=60001
tc s3-m4 gen_manual l=40000 t=59999
tc s3-rand1 gen_rand n=30 t=100000
tc s3-rand2 gen_rand n=30 t=100000
tc s3-rand3 gen_rand n=30 t=100000
tc s3-rand4 gen_rand n=30 t=100000
tc s3-rands1 gen_rand n=30 t=100000 pool=100
tc s3-rands2 gen_rand n=30 t=100000 pool=100
tc s3-big1 gen_rand n=1000 t=100000
tc s3-big2 gen_rand n=1000 t=100000
tc s3-big3 gen_rand n=1000 t=100000
tc s3-halves gen_halves m=8 n=1000

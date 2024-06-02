#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution joshua.cpp


# Sample
samplegroup
sample 1
sample 2
sample 3

group group1 20
include_group sample
tc_manual ../manual_data/01.in
tc_manual ../manual_data/02.in

group group2 80
include_group group1
tc_manual ../manual_data/03.in
tc_manual ../manual_data/04.in
tc_manual ../manual_data/05.in
tc_manual ../manual_data/06.in
tc_manual ../manual_data/07.in
tc_manual ../manual_data/08.in
tc_manual ../manual_data/09.in
tc_manual ../manual_data/10.in

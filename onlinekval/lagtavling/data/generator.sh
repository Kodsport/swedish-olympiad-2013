#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution condorcet.cc


samplegroup
sample 001
sample 002

group group1 100
include_group sample
tc_manual ../manual_data/secret_01.in
tc_manual ../manual_data/secret_02.in
tc_manual ../manual_data/secret_03.in
tc_manual ../manual_data/secret_04.in
tc_manual ../manual_data/secret_05.in
tc_manual ../manual_data/secret_06.in
tc_manual ../manual_data/secret_07.in
tc_manual ../manual_data/secret_08.in
tc_manual ../manual_data/secret_09.in
tc_manual ../manual_data/secret_10.in
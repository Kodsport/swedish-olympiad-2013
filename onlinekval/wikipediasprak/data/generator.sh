#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution arash.cc


samplegroup
sample 01
sample 02


group group1 30
include_group sample
tc_manual ../manual_data/secret_01.in
tc_manual ../manual_data/secret_02.in
tc_manual ../manual_data/secret_03.in

group group2 70
tc_manual ../manual_data/secret_04.in
tc_manual ../manual_data/secret_05.in
tc_manual ../manual_data/secret_06.in
tc_manual ../manual_data/secret_07.in
tc_manual ../manual_data/secret_08.in
tc_manual ../manual_data/secret_09.in
tc_manual ../manual_data/secret_10.in

#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution kangurumamman.py


samplegroup
sample sample


group group1 100
include_group sample
tc_manual ../manual_data/secret1.in
tc_manual ../manual_data/secret2.in
tc_manual ../manual_data/secret3.in
tc_manual ../manual_data/secret4.in
tc_manual ../manual_data/secret5.in

#! /bin/bash

RPATH=/tas/olivito/phase2/output/V00-00-05
#COND=PhaseI_Configuration0_NoPileUp
#COND=PhaseI_Configuration0_140PileUp
COND=PhaseII_Configuration4v2_140PileUp

declare -a Samples=(tt-4p tj-4p Bj-4p BB-4p tB-4p TChiWH)
#declare -a Samples=(tt-4p Bj-4p BB-4p tB-4p TChiWH)
#declare -a Samples=(TChiWH)

for SAMPLE in ${Samples[@]}
  do root -b -q -l makeWHSkim.C\(\"$RPATH\",\"$SAMPLE\"\,\"$COND\"\) &
done
wait

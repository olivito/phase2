#! /bin/bash

RPATH=/tas/olivito/phase2_Jul28/output/V00-00-12_nopujetid
#COND=PhaseI_Configuration0_NoPileUp
#COND=PhaseI_Configuration0_140PileUp
#COND=PhaseII_Configuration4v2_140PileUp
#COND=PhaseII__140PU
COND=PhaseI__50PU

#declare -a Samples=(BB-4p)
#declare -a Samples=(tt-4p tj-4p Bj-4p BB-4p tB-4p TChiWH)
#declare -a Samples=(tt-4p tj-4p Bj-4p BB-4p tB-4p BBB-4p)
#declare -a Samples=(tt-4p tj-4p Bj-4p tB-4p BBB-4p TChiWH)
#declare -a Samples=(TChiWH14Pythia)
#declare -a Samples=(naturalModel2)
declare -a Samples=(tt-4p tj-4p BB-4p tB-4p BBB-4p naturalModel2 TChiWH14Pythia)

for SAMPLE in ${Samples[@]}
  do root -b -q -l makeWHSkim.C\(\"$RPATH\",\"$SAMPLE\"\,\"$COND\"\) &
done
wait

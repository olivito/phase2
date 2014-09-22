#! /bin/bash

RPATH=/tas/olivito/phase2_Jul28_slc6/output/V00-00-12/skim_1lpt30_2b/
#COND=PhaseI_Configuration0_NoPileUp
#COND=PhaseI_Configuration0_140PileUp
#COND=PhaseII_Configuration4v2_140PileUp
COND=PhaseII__140PU
#COND=PhaseI__50PU

OUTPATH=/tas/olivito/phase2_Jul28_slc6/output/V00-00-12/skim_1lpt30_2b_aged/

#declare -a Samples=(BB-4p)
#declare -a Samples=(tt-4p tj-4p Bj-4p BB-4p tB-4p TChiWH)
#declare -a Samples=(tt-4p tj-4p Bj-4p BB-4p tB-4p BBB-4p)
#declare -a Samples=(tt-4p tj-4p Bj-4p tB-4p BBB-4p TChiWH)
#declare -a Samples=(TChiWH14Pythia)
#declare -a Samples=(naturalModel2)
declare -a Samples=(tt-4p tj-4p BB-4p tB-4p BBB-4p naturalModel2 TChiWH14Pythia Bj-4p_WHeavy Bj-4p_WLight)

for SAMPLE in ${Samples[@]}
  do nohup root -b -q -l addAgedVars.C\(\"${RPATH}/${SAMPLE}_${COND}_baby.root\",\"${OUTPATH}/${SAMPLE}_${COND}_baby.root\"\) >& log_aged_${SAMPLE}.txt &
done

#!/bin/bash -f

phase=$1     #PhaseI, PhaseII
config=$2    #Configuration0, Configuration3, Configuration4v2
PU=$3        #NoPileUp, 40PileUp, 140PileUp
sample=$4    #tB-4p-0-500-v1510_14TEV

echo ""
echo "phase" ${phase}
echo "config" ${config}
echo "PU" ${PU}
echo "sample" ${sample}

eoscms ls /eos/cms/store/group/phys_higgs/upgrade/${phase}/${config}/SUSY_SIGNAL/${PU}/${sample}_Jul31/ | grep root > fileLists/${sample}_${phase}__${PU}.txt
# prepend the specific path to the file name
sed -i -e "s/^/phys_higgs\/upgrade\/${phase}\/${config}\/SUSY_SIGNAL\/${PU}\/${sample}_Jul31\//" fileLists/${sample}_${phase}__${PU}.txt

#!/bin/bash -f

phase=$1     #PhaseI, PhaseII
#config=$2    #Configuration0, Configuration3, Configuration4v2
PU=$2        #NoPileUp, 40PileUp, 140PileUp
sample=$3    #tB-4p-0-500-v1510_14TEV

echo ""
echo "phase" ${phase}
#echo "config" ${config}
echo "PU" ${PU}
echo "sample" ${sample}

#eoscms ls /eos/cms/store/group/upgrade/delphes/${phase}_${PU}_ProdJul28/${sample} | grep root > fileLists/${sample}_${phase}__${PU}.txt
## more complicated version to remove files with 0 size..
#eoscms ls -l /eos/cms/store/group/upgrade/delphes/${phase}_${PU}_ProdJul28/${sample} | awk '$5!=0{print $9}' | grep root > fileLists/${sample}_${phase}__${PU}.txt
# prepend the specific path to the file name
#sed -i -e "s/^/upgrade\/delphes\/${phase}_${PU}_ProdJul28\/${sample}\//" fileLists/${sample}_${phase}__${PU}.txt

eoscms ls -l /eos/cms/store/group/upgrade/delphes/${phase}_${PU}_ProdAug6/${sample} | awk '$5!=0{print $9}' | grep root > fileLists/${sample}_${phase}__${PU}.txt
# prepend the specific path to the file name
sed -i -e "s/^/upgrade\/delphes\/${phase}_${PU}_ProdAug6\/${sample}\//" fileLists/${sample}_${phase}__${PU}.txt

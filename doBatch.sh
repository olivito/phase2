#!/bin/bash -f

version=V00-00-12_nopujetid
#version=temp
#version=printout
nfiles=-1

#phase=PhaseI
#config=Conf0
#pu=NoPileUp

phase=PhaseI
config=""
#config=Configuration4v2
pu=50PU

#phase=PhaseII
#config=""
#config=Configuration4v2
#pu=140PU

logdir=${phase}_${config}_${pu}

echo "Version" ${version}

#nohup nice -n 19 root -b -q processBaby.C\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",1,1\) > output/${version}/${logdir}/tW_1.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",1,3\) > output/${version}/${logdir}/ttbar_1.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",1,1\) > output/${version}/${logdir}/boson_1.log 2>&1 &

#nohup nice -n 19 root -b -q processBaby.C\(\"TChiWHTest\",\"${phase}\",\"${config}\",\"${pu}\",0,1\) > output/${version}/${logdir}/TChiWHTest_small.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"TChiWH\",\"${phase}\",\"${config}\",\"${pu}\",0,1\) > output/${version}/${logdir}/TChiWH_small.log 2>&1 &

#nohup nice -n 19 root -b -q processBaby.C\(\"TChiWHTest\",\"${phase}\",\"${config}\",\"${pu}\",0,${nfiles}\) > output/${version}/${logdir}/TChiWHTest.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"TChiWH\",\"${phase}\",\"${config}\",\"${pu}\",0,${nfiles}\) > output/${version}/${logdir}/TChiWH.log 2>&1 &

#nohup nice -n 19 root -b -q processBaby.C\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/ttbar_1.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/ttbar_2.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/ttbar_3.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/ttbar_4.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/ttbar_5.log 2>&1 &

# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/boson_1.log 2>&1 &
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/boson_2.log 2>&1 &
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/boson_3.log 2>&1 &
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/boson_4.log 2>&1 &
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/boson_5.log 2>&1 &
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",6,${nfiles}\) > output/${version}/${logdir}/boson_6.log 2>&1 &
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",7,${nfiles}\) > output/${version}/${logdir}/boson_7.log 2>&1 &

### split large samples into parts
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles},1\) > output/${version}/${logdir}/boson_1_part1.log 2>&1 &
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles},2\) > output/${version}/${logdir}/boson_1_part2.log 2>&1 &
# nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles},3\) > output/${version}/${logdir}/boson_1_part3.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles},1\) > output/${version}/${logdir}/boson_2_part1.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles},2\) > output/${version}/${logdir}/boson_2_part2.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles},3\) > output/${version}/${logdir}/boson_2_part3.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles},4\) > output/${version}/${logdir}/boson_2_part4.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles},5\) > output/${version}/${logdir}/boson_2_part5.log 2>&1 &

#nohup nice -n 19 root -b -q processBaby.C\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/diboson_1.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/diboson_2.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/diboson_3.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/diboson_4.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/diboson_5.log 2>&1 &

#nohup nice -n 19 root -b -q processBaby.C\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/tW_1.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/tW_2.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/tW_3.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/tW_4.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/tW_5.log 2>&1 &

#### need to run these! aug 27
#nohup nice -n 19 root -b -q processBaby.C\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/singletop_1.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/singletop_2.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/singletop_3.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/singletop_4.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/singletop_5.log 2>&1 &

## already done aug 27
#nohup nice -n 19 root -b -q processBaby.C\(\"VH\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/VH_1.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"VH\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/VH_2.log 2>&1 &
#nohup nice -n 19 root -b -q processBaby.C\(\"VH\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/VH_3.log 2>&1 &

#nohup nice -n 19 root -b -q processBaby.C\(\"naturalModel2\",\"${phase}\",\"${config}\",\"${pu}\",0,1\) > output/${version}/${logdir}/naturalModel2_small.log 2>&1 &

#nohup nice -n 19 root -b -q processBaby.C\(\"naturalModel2\",\"${phase}\",\"${config}\",\"${pu}\",0,-1\) > output/${version}/${logdir}/naturalModel2.log 2>&1 &

#nohup nice -n 19 root -b -q processBaby.C\(\"TChiWH\",\"${phase}\",\"${config}\",\"${pu}\",0,-1\) > output/${version}/${logdir}/TChiWH.log 2>&1 &

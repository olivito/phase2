#!/bin/bash -f

#version=V00-00-05
version=temp
nfiles=-1
#nfiles=3
phase=PhaseI
config=Configuration0
pu=NoPileUp
#pu=140PileUp
logdir=${phase}_${config}_${pu}

echo "Version" ${version}

root -b -q simpleLooper.C+\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",1,1\) > output/${version}/${logdir}/ttbar_1.log 2>&1 &

#root -b -q simpleLooper.C+\(\"TChiWHTest\",\"${phase}\",\"${config}\",\"${pu}\",0,1\) > output/${version}/${logdir}/TChiWHTest_small.log 2>&1 &

#root -b -q simpleLooper.C+\(\"TChiWHTest\",\"${phase}\",\"${config}\",\"${pu}\",0,${nfiles}\) > output/${version}/${logdir}/TChiWHTest.log 2>&1 &
#root -b -q simpleLooper.C+\(\"TChiWH\",\"${phase}\",\"${config}\",\"${pu}\",0,${nfiles}\) > output/${version}/${logdir}/TChiWH.log 2>&1 &

# root -b -q simpleLooper.C+\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/ttbar_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/ttbar_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/ttbar_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/ttbar_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"ttbar\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/ttbar_5.log 2>&1 &

# root -b -q simpleLooper.C+\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/boson_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/boson_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/boson_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/boson_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/boson_5.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",6,${nfiles}\) > output/${version}/${logdir}/boson_6.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"${phase}\",\"${config}\",\"${pu}\",7,${nfiles}\) > output/${version}/${logdir}/boson_7.log 2>&1 &

# root -b -q simpleLooper.C+\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/diboson_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/diboson_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/diboson_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/diboson_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"diboson\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/diboson_5.log 2>&1 &

# root -b -q simpleLooper.C+\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/tW_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/tW_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/tW_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/tW_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"tW\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/tW_5.log 2>&1 &

# root -b -q simpleLooper.C+\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",1,${nfiles}\) > output/${version}/${logdir}/singletop_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",2,${nfiles}\) > output/${version}/${logdir}/singletop_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",3,${nfiles}\) > output/${version}/${logdir}/singletop_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",4,${nfiles}\) > output/${version}/${logdir}/singletop_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"singletop\",\"${phase}\",\"${config}\",\"${pu}\",5,${nfiles}\) > output/${version}/${logdir}/singletop_5.log 2>&1 &



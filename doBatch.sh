#!/bin/bash -f

version=V00-00-02
nfiles=-1

echo "Version" ${version}

# root -b -q simpleLooper.C+\(\"ttbar\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",1,${nfiles}\) > output/${version}/ttbar_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"ttbar\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",2,${nfiles}\) > output/${version}/ttbar_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"ttbar\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",3,${nfiles}\) > output/${version}/ttbar_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"ttbar\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",4,${nfiles}\) > output/${version}/ttbar_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"ttbar\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",5,${nfiles}\) > output/${version}/ttbar_5.log 2>&1 &

# root -b -q simpleLooper.C+\(\"diboson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",1,${nfiles}\) > output/${version}/diboson_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"diboson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",2,${nfiles}\) > output/${version}/diboson_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"diboson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",3,${nfiles}\) > output/${version}/diboson_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"diboson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",4,${nfiles}\) > output/${version}/diboson_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"diboson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",5,${nfiles}\) > output/${version}/diboson_5.log 2>&1 &

# root -b -q simpleLooper.C+\(\"boson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",1,${nfiles}\) > output/${version}/boson_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",2,${nfiles}\) > output/${version}/boson_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",3,${nfiles}\) > output/${version}/boson_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",4,${nfiles}\) > output/${version}/boson_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",5,${nfiles}\) > output/${version}/boson_5.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",6,${nfiles}\) > output/${version}/boson_6.log 2>&1 &
# root -b -q simpleLooper.C+\(\"boson\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",7,${nfiles}\) > output/${version}/boson_7.log 2>&1 &

# root -b -q simpleLooper.C+\(\"tW\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",1,${nfiles}\) > output/${version}/tW_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"tW\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",2,${nfiles}\) > output/${version}/tW_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"tW\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",3,${nfiles}\) > output/${version}/tW_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"tW\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",4,${nfiles}\) > output/${version}/tW_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"tW\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",5,${nfiles}\) > output/${version}/tW_5.log 2>&1 &

# root -b -q simpleLooper.C+\(\"singletop\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",1,${nfiles}\) > output/${version}/singletop_1.log 2>&1 &
# root -b -q simpleLooper.C+\(\"singletop\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",2,${nfiles}\) > output/${version}/singletop_2.log 2>&1 &
# root -b -q simpleLooper.C+\(\"singletop\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",3,${nfiles}\) > output/${version}/singletop_3.log 2>&1 &
# root -b -q simpleLooper.C+\(\"singletop\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",4,${nfiles}\) > output/${version}/singletop_4.log 2>&1 &
# root -b -q simpleLooper.C+\(\"singletop\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",5,${nfiles}\) > output/${version}/singletop_5.log 2>&1 &

root -b -q simpleLooper.C+\(\"TChiwh\",\"PhaseI\",\"Configuration0\",\"NoPileUp\",0,${nfiles}\) > output/${version}/TChiwh.log 2>&1 &



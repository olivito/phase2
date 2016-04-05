This package was designed to run analysis on CMS phase 2 upgrade Delphes samples.  These instructions were written later based on memory and may be incomplete / wrong..

check out and compile Delphes, using the information here:

https://twiki.cern.ch/twiki/bin/view/CMS/HiggsWG/Phase2UpgradeStudies#Recommended_tag_and_version

https://github.com/sethzenz/Delphes

check out this package:

git clone https://git@github.com/olivito/phase2.git

cd phase2

make soft links to Delphes in phase2 dir

ln -s [path_to_Delphes]

ln -s [path_to_ExRootAnalysis]

ln -s [path_to_classes]

ln -s [path_to_libDelphes.so]

simpleLooper.C makes a flat ntuple, and is run with processBaby.C

 see doBatch.sh for examples

makeWHSkim.C is an example of applying a skim selection

 see doSkims.sh for running instructions

plotMaker_WH.C is an example of plotting from the flat ntuples


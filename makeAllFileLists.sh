#!/bin/bash -f

# ## boson+jets(+jets)
# Bj-4p-0-300-v1510_14TEV
# Bj-4p-300-600-v1510_14TEV
# Bj-4p-600-1100-v1510_14TEV
# Bj-4p-1100-1800-v1510_14TEV
# Bj-4p-1800-2700-v1510_14TEV
# Bj-4p-2700-3700-v1510_14TEV
# Bj-4p-3700-100000-v1510_14TEV

# ## diboson(+jets)
# BB-4p-0-300-v1510_14TEV
# BB-4p-300-700-v1510_14TEV
# BB-4p-700-1300-v1510_14TEV
# BB-4p-1300-2100-v1510_14TEV
# BB-4p-2100-100000_14TEV

# ## top+boson(+jets)
# tB-4p-0-500-v1510_14TEV
# tB-4p-500-900-v1510_14TEV
# tB-4p-900-1500-v1510_14TEV
# tB-4p-1500-2200-v1510_14TEV
# tB-4p-2200-100000-v1510_14TEV

# ## single top(+jets)
# tj-4p-0-500-v1510_14TEV
# tj-4p-500-1000-v1510_14TEV
# tj-4p-1000-1600-v1510_14TEV
# tj-4p-1600-2400-v1510_14TEV
# tj-4p-2400-100000-v1510_14TEV

# ## ttbar(+jets)
# tt-4p-0-600-v1510_14TEV
# tt-4p-600-1100-v1510_14TEV
# tt-4p-1100-1700-v1510_14TEV
# tt-4p-1700-2500-v1510_14TEV
# tt-4p-2500-100000-v1510_14TEV


# ## boson+jets(+jets)
# source makeFileList.sh PhaseI Configuration0 NoPileUp Bj-4p-0-300-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp Bj-4p-300-600-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp Bj-4p-600-1100-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp Bj-4p-1100-1800-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp Bj-4p-1800-2700-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp Bj-4p-2700-3700-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp Bj-4p-3700-100000-v1510_14TEV

# ## diboson(+jets)
# source makeFileList.sh PhaseI Configuration0 NoPileUp BB-4p-0-300-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp BB-4p-300-700-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp BB-4p-700-1300-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp BB-4p-1300-2100-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp BB-4p-2100-100000_14TEV

# ## top+boson(+jets)
# source makeFileList.sh PhaseI Configuration0 NoPileUp tB-4p-0-500-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tB-4p-500-900-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tB-4p-900-1500-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tB-4p-1500-2200-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tB-4p-2200-100000-v1510_14TEV

# ## single top(+jets)
# source makeFileList.sh PhaseI Configuration0 NoPileUp tj-4p-0-500-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tj-4p-500-1000-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tj-4p-1000-1600-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tj-4p-1600-2400-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tj-4p-2400-100000-v1510_14TEV

# ## ttbar(+jets)
# source makeFileList.sh PhaseI Configuration0 NoPileUp tt-4p-0-600-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tt-4p-600-1100-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tt-4p-1100-1700-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tt-4p-1700-2500-v1510_14TEV
# source makeFileList.sh PhaseI Configuration0 NoPileUp tt-4p-2500-100000-v1510_14TEV

## WH signal
source makeFileListSignal.sh PhaseI Configuration0 NoPileUp TChiWH14Pythia

# test
#source makeFileList.sh PhaseI Configuration0 NoPileUp tB-4p-0-500-v1510_14TEV

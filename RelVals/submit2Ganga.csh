#....
# script to sumit the RelVal jobs to Ganga
#. aosorio@uniandes.edu.co

if ( $# == 0 ) then
    echo "$0 <cmssw>"
    exit(0)
else
    set cmssw=$1
endif

#. list of Samples
set workArea = $HOME/scratch0
set samples  = ("MinBias" "QCD_Pt_3000_3500" "QCD_Pt_80_120" "SingleMuPt10" "SingleMuPt100" "SingleMuPt1000" "ZMM" "TTbar")

set argument = $samples[1]

echo $argument

foreach sample ($samples)
    if ( $sample != $argument ) then
	echo $sample
	set argument = "$sample,$argument"
    endif
end

cd $workArea/$cmssw/src/StudyL1Trigger/L1GtTechTrig/test
ganga submitRelVals.py -v $cmssw -f $argument
cd -

echo "submit> done"

#! /bin/tcsh -f

setenv MYDIR /uscms_data/d2/aosorio/scratch0/CMSSW_5_3_4/run
unsetenv CMS_PATH
source /uscmst1/prod/sw/cms/cshrc prod
pushd $MYDIR
cmsenv
popd

setenv FILE $1
setenv CFGFILE $2
setenv COPY "cp ${FILE} ./input.root"
setenv CMD  "cmsRun $CFGFILE"
echo INFO:  running on file: \"$FILE\"
echo INFO:  launching command: $COPY
$COPY
echo INFO:  launching command: $CMD
$CMD
echo "Removing input.root file"
rm input.root
echo DONE


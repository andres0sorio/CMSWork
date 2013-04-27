#! /bin/tcsh -f

setenv MYDIR /uscms_data/d2/aosorio/scratch0/CMSSW_5_3_4/run
unsetenv CMS_PATH
source /uscmst1/prod/sw/cms/cshrc prod
pushd $MYDIR
cmsenv
popd

setenv CFGFILE $1
setenv CMD  "cmsRun $CFGFILE"
echo INFO:  running on file: \"$CFGFILE\"
echo INFO:  launching command: $CMD
$CMD
echo "Clean up area"
rm -rf tmp
echo DONE


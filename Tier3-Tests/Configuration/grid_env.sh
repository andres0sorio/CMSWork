if [ "X${GLITE_ENV_SET+X}" = "X" ]; then
. /afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/etc/profile.d/grid-env-funcs.sh
gridpath_prepend     "PYTHONPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg/lib64/python2.4/site-packages"
gridpath_prepend     "PYTHONPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg/lib64/python"
gridpath_prepend     "PYTHONPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/lib64/python2.4/site-packages"
gridpath_prepend     "PYTHONPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/lib64/python"
gridpath_prepend     "PERL5LIB" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg/lib64/perl"
gridpath_prepend     "PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg/bin"
gridpath_prepend     "PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/globus/bin"
gridpath_prepend     "PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/bin"
gridpath_prepend     "PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/edg/bin"
gridpath_prepend     "PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/d-cache/srm/bin:/afs/cern.ch/project/gd/LCG-share/3.2.10-1/d-cache/dcap/bin"
gridpath_prepend     "MANPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg/share/man"
gridpath_prepend     "MANPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg/man"
gridpath_prepend     "MANPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/globus/man"
gridpath_prepend     "MANPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/yaim/man"
gridpath_prepend     "MANPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/share/man"
gridpath_prepend     "MANPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/edg/share/man"
gridpath_prepend     "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg/lib64"
gridpath_prepend     "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg/lib"
gridpath_prepend     "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/globus/lib"
gridpath_prepend     "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/lib64"
gridpath_prepend     "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/lib"
gridpath_prepend     "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/d-cache/dcap/lib64"
gridpath_prepend     "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/d-cache/dcap/lib"
gridpath_append      "PYTHONPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/opt/fpconst/lib/python2.4/site-packages"
gridpath_append      "PYTHONPATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/opt/ZSI/lib/python2.4/site-packages"
gridpath_append      "PERLLIB" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/gpt/lib/perl"
gridpath_append      "PERL5LIB" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/gpt/lib/perl"
gridpath_append      "PERL5LIB" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/usr/lib/perl5/vendor_perl/5.8.8"
gridpath_append      "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/usr/lib64"
gridpath_append      "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/usr/lib"
gridpath_append      "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/opt/c-ares/lib"
gridpath_append      "LD_LIBRARY_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/classads/lib64/"
gridenv_setind      "X509_USER_PROXY" "/tmp/x509up_u$(id -u)"
gridenv_set         "X509_VOMS_DIR" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/etc/grid-security/vomsdir/"
gridenv_set         "X509_CERT_DIR" "/afs/cern.ch/project/gd/LCG-share2/certificates"
gridenv_set         "VO_VO_SIXT_CERN_CH_SW_DIR" "/afs/cern.ch/project/gd/apps/sixt"
gridenv_set         "VO_VO_SIXT_CERN_CH_DEFAULT_SE" "srm.cern.ch"
gridenv_set         "VO_VO_GEAR_CERN_CH_SW_DIR" "/afs/cern.ch/project/gd/apps/gear"
gridenv_set         "VO_VO_GEAR_CERN_CH_DEFAULT_SE" "lxdpm104.cern.ch"
gridenv_set         "VO_UNOSAT_SW_DIR" "/afs/cern.ch/project/gd/apps/unosat"
gridenv_set         "VO_UNOSAT_DEFAULT_SE" "lxdpm104.cern.ch"
gridenv_set         "VO_OPS_SW_DIR" "/afs/cern.ch/project/gd/apps/ops"
gridenv_set         "VO_OPS_DEFAULT_SE" "srm.cern.ch"
gridenv_set         "VO_NA48_SW_DIR" "/afs/cern.ch/project/gd/apps/na48"
gridenv_set         "VO_NA48_DEFAULT_SE" "lxdpm104.cern.ch"
gridenv_set         "VO_LHCB_SW_DIR" "/afs/cern.ch/project/gd/apps/lhcb"
gridenv_set         "VO_LHCB_DEFAULT_SE" "srm.cern.ch"
gridenv_set         "VO_ILC_DEFAULT_SE" "classic_SE_host"
gridenv_set         "VO_GEANT4_SW_DIR" "/afs/cern.ch/project/gd/apps/geant4"
gridenv_set         "VO_GEANT4_DEFAULT_SE" "lxdpm104.cern.ch"
gridenv_set         "VO_DTEAM_SW_DIR" "/afs/cern.ch/project/gd/apps/dteam"
gridenv_set         "VO_DTEAM_DEFAULT_SE" "srm.cern.ch"
gridenv_set         "VO_COMPASS_SW_DIR" "/afs/cern.ch/project/gd/apps/compass"
gridenv_set         "VO_COMPASS_DEFAULT_SE" "classic_SE_host"
gridenv_set         "VO_CMS_SW_DIR" "/afs/cern.ch/project/gd/apps/cms"
gridenv_set         "VO_CMS_DEFAULT_SE" "srm.cern.ch"
gridenv_set         "VO_ATLAS_SW_DIR" "/afs/cern.ch/project/gd/apps/atlas"
gridenv_set         "VO_ATLAS_DEFAULT_SE" "srm.cern.ch"
gridenv_set         "VO_ALICE_SW_DIR" "/afs/cern.ch/project/gd/apps/alice"
gridenv_set         "VO_ALICE_DEFAULT_SE" "srm.cern.ch"
gridenv_set         "SRM_PATH" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/d-cache/srm"
gridenv_set         "MYPROXY_SERVER" "myproxy.cern.ch"
gridenv_set         "LCG_LOCATION" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/lcg"
gridenv_set         "LCG_GFAL_INFOSYS" "lcg-bdii.cern.ch:2170"
gridenv_set         "GT_PROXY_MODE" "old"
gridenv_set         "GRID_ENV_LOCATION" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/etc/profile.d"
gridenv_set         "GPT_LOCATION" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/gpt"
gridenv_set         "GLOBUS_TCP_PORT_RANGE" "20000,25000"
gridenv_set         "GLOBUS_LOCATION" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/globus"
gridenv_set         "GLITE_WMS_LOCATION" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite"
gridenv_set         "GLITE_SD_SERVICES_XML" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/etc/services.xml"
gridenv_set         "GLITE_SD_PLUGIN" "file,bdii"
gridenv_set         "GLITE_LOCATION_VAR" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite/var"
gridenv_set         "GLITE_LOCATION" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/glite"
gridenv_set         "EDG_WL_LOCATION" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/edg"
gridenv_set         "EDG_LOCATION" "/afs/cern.ch/project/gd/LCG-share/3.2.10-1/edg"
gridenv_set         "DPNS_HOST" "lxdpm104.cern.ch"
gridenv_set         "DPM_HOST" "lxdpm104.cern.ch"
. /afs/cern.ch/project/gd/LCG-share/3.2.10-1/external/etc/profile.d/clean-grid-env-funcs.sh
fi

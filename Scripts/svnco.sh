#!/bin/bash

if [ $# -lt 1 ];

then
    echo "usage: $0 <package>"
    exit 0
fi 

#if [ -z "$SSH_AUTH_SOCK" ] ; then
#eval `ssh-agent -s`
#fi
#ssh-add ~/.ssh/id_dsa_hepua; ssh-add -l

svnrepo="svn+ssh://svn.cern.ch/reps/cmsuniandes"

package=$1

echo "svn co $svnrepo/$package"

svn co $svnrepo/$package

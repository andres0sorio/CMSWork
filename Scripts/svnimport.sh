#!/bin/bash

if [ $# -lt 1 ];

then
    echo "usage: $0 <package>"
    exit 0
fi 

if [ -z "$SSH_AUTH_SOCK" ] ; then
eval `ssh-agent -s`
fi
ssh-add ~/.ssh/id_rsa_t61; ssh-add -l

svnrepo="svn+ssh://svn.cern.ch/reps/cmsuniandes/Users/aosorio/Code"

package=$1

echo "svn import $package $svnrepo/$package"

svn import $package $svnrepo/$package

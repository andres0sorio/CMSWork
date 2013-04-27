#!/bin/bash

# Transfer files via SRM

VO=cms
JOB="aoscript.jdl"
CE="cale.uniandes.edu.co:8443/cream-pbs-cms"

glite-wms-job-submit -a -r $CE $JOB


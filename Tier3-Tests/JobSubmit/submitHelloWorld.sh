#!/bin/bash

# Hello World example 1

VO=cms
JOB="aoscript.jdl"
CE="cale.uniandes.edu.co:8443/cream-pbs-cms"

glite-wms-job-submit -a --vo $VO -r $CE $JOB


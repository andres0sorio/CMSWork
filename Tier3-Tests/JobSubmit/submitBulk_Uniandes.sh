#!/bin/bash

# Testing the access of files

VO="uniandes.edu.co"
JOB="bulk_submit_ua.jdl"
CE="cale.uniandes.edu.co:8443/cream-pbs-uniandes"

glite-wms-job-submit --debug -a -r $CE --vo $VO $JOB > my_grid_job_ua.log 2>&1



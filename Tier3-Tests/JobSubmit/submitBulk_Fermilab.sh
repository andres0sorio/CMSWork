#!/bin/bash

# Testing the access of files

VO=cms
JOB="bulk_submit.jdl"

glite-wms-job-submit --debug -a --vo $VO $JOB > my_grid_job.log 2>&1



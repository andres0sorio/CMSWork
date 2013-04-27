#...

set data=${1}

rm job_cfg.py

cat ttuanalyzer_cfg.py ${data} > job_cfg.py

echo "running test on ${data}"
cmsRun job_cfg.py

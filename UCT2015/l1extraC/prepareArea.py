#!/usr/bin/python
import os, sys
from optparse import OptionParser

#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-p", type = "string", dest="path",
                  help="new directory" )

(options, args) = parser.parse_args()

if options.path is None:
        parser.error("please give a path")
#--------------------------------------------------------

target = 'results'
path =options.path

types = ['rate','efficiency','turnon','resolution','distributions']
objects = ['Sums','Jets','EG','Taus','Sums']
file_ext = ['eps','png']
studies = ['withPUC/isoStudies', 'noPUC/isoStudies']

for type in types:
    for obj in objects:
        for study in studies:
            for ext in file_ext:
                base = target + '/' + path + '/'
                new_path = base + type + '/' + obj + '/' + study + '/' + ext
                if not os.path.isdir(new_path):
                    os.makedirs( new_path )

sym_link = target + '/' + path

cmd = 'rm slhc-plots; ln -s ' + sym_link + ' slhc-plots'
os.system(cmd)


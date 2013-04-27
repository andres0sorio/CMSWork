#!/usr/bin/python

import string
from time import time
from optparse import OptionParser

#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-e", type = "string", dest="application",
                help="which application", metavar="APP" )

(options, args) = parser.parse_args()

if options.application is None:
      parser.error("please give the application (pythia8, lhapdf)")

#-------------------------------------------------------------------------
#-------------------------------------------------------------------------

import os

if options.application == 'pythia8':
    g1 = 'export PYTHIA8=' + ('/').join(os.environ['PYTHIA8DATA'].split('/')[:-1])
    print g1

if options.application == 'lhapdf':
    g1 = 'export LHAPDFLOCATION=' + ('/').join(os.environ['LHAPATH'].split('/')[:-3])
    print g1



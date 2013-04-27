#!/usr/bin/python

import os,sys
import string

from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------

parser = OptionParser()
parser.add_option("-f", type = "string", dest="indir",
                help="directory with file", metavar="INDIR" )

(options, args) = parser.parse_args()

if options.indir is None:
      parser.error("please provide a directory")

#-------------------------------------------------------------------------

indir = options.indir

cmd = 'ls ' + indir + '/*.txt'

result = os.popen(cmd,'r').readlines()

for file in result:
      title = []
      info  = file.split()
      for item in info:
            if item.find('arXiv') == 1:
                  arxiv_ref = item[1:].split('_')[1]
                  pdf_link = 'http://arxiv.org/pdf/' + arxiv_ref
                  break
            else:
                  title.append(item)

      full_title = ('').join(title)
      init = len(indir)+1
      print arxiv_ref, full_title[init:]
      filename = arxiv_ref + '_autodownload.pdf'
      getpdf_cmd = 'lynx -dump ' + pdf_link + ' > ' + filename
      #...print getpdf_cmd
      os.system(getpdf_cmd)
      



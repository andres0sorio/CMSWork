#!/usr/bin/python

import sys,os

if len(sys.argv) == 1:
    
    print 'Error: Usted debe proveer la clave secreta'

username = os.getenv('USER')

if len(sys.argv) > 1:
    
    print 'Muy bien: Sr ', username, ' usted ha dado la clave ', sys.argv[1]




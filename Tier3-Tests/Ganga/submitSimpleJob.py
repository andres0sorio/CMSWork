import sys,os

CElement='cale.uniandes.edu.co:8443/cream-pbs-cms'

myjob = Job( backend = 'LCG' )
myjob.name = 'hello.test.uniandes.ao'
myjob.backend.CE = CElement

myjob.submit()


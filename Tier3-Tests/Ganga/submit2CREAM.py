import sys,os

CElement='cale.uniandes.edu.co:8443/cream-pbs-cms'
SEpath=''

app = Executable()
app.exe = 'aoscript.csh'
app.args = ['']

myjob = Job( application = app, backend = 'CREAM' )
myjob.name = 'CEtests.uniandes.ao'

myjob.inputsandbox.append( File(name='aoscript.csh') )

#myjob.backend.middleware = 'GLITE'
myjob.backend.CE = CElement

myjob.submit()


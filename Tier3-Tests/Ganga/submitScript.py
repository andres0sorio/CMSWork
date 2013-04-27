import sys,os

CElement='cale.uniandes.edu.co:8443/cream-pbs-cms'

app = Executable()
app.exe = File( name = 'aoscript.sh' )
app.args = ['']

myjob = Job( application = app, backend = 'LCG' )
myjob.name = 'ganga.hello.world'

myjob.backend.middleware = 'GLITE'
myjob.backend.CE = CElement

myjob.submit()


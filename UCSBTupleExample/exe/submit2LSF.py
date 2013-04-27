#. This is a ganga script: submit jobs to LSF batch system at CERN
#. Andres Osorio - aosorio@uniandes.edu.co
#. January 2009

jobname   = 'ucsbanalysis'
sofiles   = []
listfiles = 'short_list_of_files_cern.txt'
sandbox   = [ listfiles ]

#.......
fh = open("list_of_sofiles.dat")
for line in fh.readlines():
    sofiles.append(line[:-1])
    
for k in range(0,len(sofiles)):
    sandbox.append(sofiles[k])
#.......

app         = Root()
app.version ='5.18.00'
app.script  ='analyse.C'
app.args    = [ listfiles, 'Test']

exjob = Job(application = app)
exjob.name          = jobname
exjob.backend       = LSF()
exjob.backend.queue = '1nh'
exjob.inputsandbox  = sandbox

exjob.submit()

print "sub2LSF> Done!"


import sys,os
import ConfigFile

userhome = os.environ.get("HOME")
scratch0 = userhome + '/scratch0/'

filename = scratch0 + 'crab.cfg'

ff = ConfigFile.ConfigFile(filename)

ff.append('CRAB' ,'jobtype=cmssw')
ff.append('CRAB' ,'scheduler=glite')
ff.append('CRAB' ,'server_name=bari')

ff.append('CMSSW','jobs2=myjobs')
ff.append('USER' ,'jobs3=myjobs')
ff.append('EDG'  ,'jobs4=myjobs')
ff.write()


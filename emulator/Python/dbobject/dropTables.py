import os,sys
import cx_Oracle

connection = cx_Oracle.connect("CMS_RPC_COMMISSIONING", "rpc2009xcms", "devdb10")

name    = sys.argv[1]
command = 'DROP TABLE '+name
print command

cursor  = connection.cursor()
cursor.execute(command)
cursor.close()


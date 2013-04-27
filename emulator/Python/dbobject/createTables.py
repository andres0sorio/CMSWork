import cx_Oracle

connection = cx_Oracle.connect("CMS_RPC_COMMISSIONING", "rpc2009xcms", "devdb10")

cmds=[]

fh = open("tables.txt")

cursor = connection.cursor()

while 1:
    line = fh.readline()
    if not line:
        break
    pass
    tableinfo = line.split()
    tablename = tableinfo[0]
    command = 'CREATE TABLE ' + tablename + '( '
    command = command + tableinfo[1] + ' ' + tableinfo[2] + ' primary key, '
    ncols = (len(tableinfo)-1)/2

    for i in range( 0,ncols-1):
        idx= 2*i+3
        command = command + tableinfo[idx] + ' ' + tableinfo[idx+1]
        if idx != (len(tableinfo)-2):
            command = command +', '
        else:
            command = command + ' )'
        
    print command
    cursor.execute(command)

print 'createTable> done.'
cursor.close()


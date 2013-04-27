import cx_Oracle

connection = cx_Oracle.connect("CMS_RPC_COMMISSIONING", "rpc2009xcms", "devdb10")

cursor = connection.cursor()
cursor.execute("DROP TABLE TTUEVENT")

cursor.close()


import cx_Oracle

connection = cx_Oracle.connect("CMS_RPC_COMMISSIONING", "rpc2009xcms", "devdb10")

cursor = connection.cursor()
cursor.execute("CREATE TABLE TTUEVENT( Event_Id_PK number primary key, Run_Id number, RunType varchar2(50))")

cursor.close()


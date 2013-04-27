#!/bin/sh

if [ "$1" = "" ];then
    echo Usted debe ejecutar asi: $0 nombredesucertificado.pfx
else
    
    echo "-----------------------------------------"
    echo "Generando llave Privada"
    echo openssl pkcs12 -in $1 -nocerts -out userkey.pem
    echo "-----------------------------------------"
    echo "Generando certificado de usuario"
    echo openssl pkcs12 -in $1 -clcerts -nokeys -out usercert.pem
    
#...
    
    echo chown $USER.$USER user*
    echo chmod 644 usercert.pem
    echo chmod 400 userkey.pem
    
    if [ ! -d "/home/$USER/.globus" ];then
	mkdir /home/$USER/.globus
    fi
    echo "-----------------------------------------"
    echo mv -iv user* /home/$USER/.globus
    
fi


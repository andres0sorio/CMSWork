#!/bin/sh

if [ "$1" = "" ];then
    echo Usted debe ejecutar asi: $0 nombredesucertificado.pfx
else
    
    echo "-----------------------------------------"
    echo "Generando llave Privada"
    openssl pkcs12 -in $1 -nocerts -out userkey.pem
    echo "-----------------------------------------"
    echo "Generando certificado de usuario"
    openssl pkcs12 -in $1 -clcerts -nokeys -out usercert.pem
    
#...
    
    chown $USER.$USER user*
    chmod 644 usercert.pem
    chmod 400 userkey.pem
    
    if [ ! -d "/home/$USER/.globus" ];then
	mkdir /home/$USER/.globus
    fi
    echo "-----------------------------------------"
    mv -iv user* /home/$USER/.globus
    
fi


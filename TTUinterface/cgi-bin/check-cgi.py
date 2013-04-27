#!/usr/bin/python
import cgi
import cgitb; cgitb.enable()
import cgitb; cgitb.enable(display=0, logdir="/tmp")

from pyspecs.GUIstatus import *

def check():
    #...............
    header= """Content-type: text/html

    <title>TTU Configuration Interface</title>
    <head>
    <style type="text/css">
    """
    #...............
    cssfile = open('ttu_style.css','r')
    #...............
    print header
    print cssfile.read()
    print '</style>'
    #...............

    print '<html>'
    print '<body>'
    print ''
    #...
    print ''
    print '<div id="TopTitle">'
    print '<h1>RPC - Technical Trigger Configuration</h1>'
    print '<p class="top" >'
    print '<a class="top" href="http://www.cern.ch" target="_blank">Wiki-Doc</a>'
    print '<a class="top" href="mailto:aosorio@NOTSPAM.uniandes.edu.co">Contact</a> v.1.0'
    print '</p>'
    print '</div>'
    print ''
    #...
    print '<div id="Status">'
    print '<h3>TTU/RBC status</h3>'
    print '<div id="StatusCode">'
    print '<span class="codeON"> ON</span> <span class="codeNR"> NR <span class="codeOFF"> OFF'
    print '</div>'
    print '<p>'
    target = '/home/aosorio/Work/TTUinterface/status/'
    infile = 'rbc-status.txt'
    drawboxes(infile,target)
    print '</p>'
    print '</div>'
    print '</body>'
    print '</html>'
    
check()


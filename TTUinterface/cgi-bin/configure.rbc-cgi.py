#!/usr/bin/python
import cgi
import cgitb; cgitb.enable()
import cgitb; cgitb.enable(display=0, logdir="/tmp")

form = cgi.FieldStorage()

selrbc  = form['RBCboard'].value
rbcinfo = selrbc.split('.')
ttu = rbcinfo[1]
rbc = rbcinfo[2]

def execute():
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
    print '<div id="Content">'
    print '<h3>Wheel: %s RBC Configuration</h3>' % ttu
    #...
    
    print '<h4>'
    print 'Configuration of sectors %s' % rbc
    print '</h4>'

    print '<form action="http://localhost:5000/configure.exec-cgi.py">'
    print '<p>'
    print '  Mayority Level:'
    print '  <input type="text" name="MayorityLevel" value=%d />' % 6
    print '</p>'
    print ''
    print '<p>'
    print '  Pulse Width:'
    print '  <input type="text" name="PulseWidth" value=%d />' % 20
    print '</p>'
    print ''
    print '<p>'
    print 'Mask:</p>'
    print '<p>'
    print '<input type="checkbox" name="masks1" value="MaskIn1" />'
    print '<input type="checkbox" name="masks2" value="MaskIn2" />'
    print '<input type="checkbox" name="masks3" value="MaskIn3" />'
    print '<input type="checkbox" name="masks4" value="MaskIn4" />'
    print '<input type="checkbox" name="masks5" value="MaskIn5" />'
    print '<input type="checkbox" name="masks6" value="MaskIn6" />'
    print '<input type="checkbox" name="masks7" value="MaskIn7" />'
    print '<input type="checkbox" name="masks8" value="MaskIn8" />'
    print '<input type="checkbox" name="masks9" value="MaskIn9" />'
    print '<input type="checkbox" name="masks10" value="MaskIn10" />'
    print '<input type="checkbox" name="masks11" value="MaskIn11" />'
    print '<input type="checkbox" name="masks12" value="MaskIn12" />'
    print '<input type="checkbox" name="masks13" value="MaskIn13" />'
    print '<input type="checkbox" name="masks14" value="MaskIn14" />'
    print '<input type="checkbox" name="masks15" value="MaskIn15" />'
    print '</p>'
    print ''
    print '<p>'
    print 'Force:</p>'
    print '<p>'
    print '<input type="checkbox" name="force1" value="ForceIn1" />'
    print '<input type="checkbox" name="force2" value="ForceIn2" />'
    print '<input type="checkbox" name="force3" value="ForceIn3" />'
    print '<input type="checkbox" name="force4" value="ForceIn4" />'
    print '<input type="checkbox" name="force5" value="ForceIn5" />'
    print '<input type="checkbox" name="force6" value="ForceIn6" />'
    print '<input type="checkbox" name="force7" value="ForceIn7" />'
    print '<input type="checkbox" name="force8" value="ForceIn8" />'
    print '<input type="checkbox" name="force9" value="ForceIn9" />'
    print '<input type="checkbox" name="force10" value="ForceIn10" />'
    print '<input type="checkbox" name="force11" value="ForceIn11" />'
    print '<input type="checkbox" name="force12" value="ForceIn12" />'
    print '<input type="checkbox" name="force13" value="ForceIn13" />'
    print '<input type="checkbox" name="force14" value="ForceIn14" />'
    print '<input type="checkbox" name="force15" value="ForceIn15" />'
    print ''
    print '</p>'
    print ''
    print '<input type=submit value="Execute" />'
    print '</form>'

    #...
    print '</div>'
    print '</body>'
    print '</html>'
    
execute()


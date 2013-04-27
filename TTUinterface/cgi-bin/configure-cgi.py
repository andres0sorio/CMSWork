#!/usr/bin/python
import cgi
import cgitb; cgitb.enable()
import cgitb; cgitb.enable(display=0, logdir="/tmp")

def configure():
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
    print '<h3>TTU Configuration</h3>'

    print '<form action="http://localhost:5000/configure.preset-cgi.py">'
    print ''
    print '<p>'
    print '  Presets: '
    print '  <select name="Presets">'
    print '    <option value="GlobalCosmic">Cosmic Run</option>'
    print '    <option value="BeamHalo">Beam Halo</option>'
    print '    <option value="Global10TeV">Global Run 10 TeV</option>'
    print '    <option value="Debug">Debug</option>'
    print '  </select>'
    print '<input type=submit value="Send" />'
    print '</p>'
    print ''
    print '</form>'
    #...
    print '</div>'
    print '</body>'
    print '</html>'
    
configure()


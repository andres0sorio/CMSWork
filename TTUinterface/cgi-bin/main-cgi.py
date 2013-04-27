#!/usr/bin/python

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
print '<div id="ActionBar">'
print '<h2>Please select what you want to do:</h2>'
print ''
#...
print '<p>'
print '<form method=POST action="http://localhost:5000/check-cgi.py">'
print '<input type=submit value="Check" />'
print '</form>'

#...
print '<form method=POST action="http://localhost:5000/configure-cgi.py">'
print '<input type=submit value="Configure" />'
print '</form>'

#...
print '<form method=POST action="http://localhost:5000/report-cgi.py">'
print '<input type=submit value="Report" />'
print '</form>'
print '</p>'

#...............
print '</div>'
print '</body>'
print '</html>'

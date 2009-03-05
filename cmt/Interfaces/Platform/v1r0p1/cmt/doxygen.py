

# -*- coding: iso-8859-1 -*-

import os
import sys
import string
import popen2
import stat
import re

from os.path import join


tagfiles = ''

#----------------------------------------------------
def removedirs (top):
    # Delete everything reachable from the directory named in 'top'.
    # CAUTION:  This is dangerous!  For example, if top == '/', it
    # could delete all your disk files.
    if os.path.exists (top):
        for root, dirs, files in os.walk (top, topdown=False):
            for name in files:
                name = root + '/' + name
                os.chmod (name, stat.S_IWRITE)
                #print name
                os.remove (name)
            for name in dirs:
                name = root + '/' + name
                os.chmod (name, stat.S_IWRITE)
                #print name
                os.rmdir (name)
        os.chmod (top, stat.S_IWRITE)
        #print top
        os.rmdir (top)


#----------------------------------------------------
#
# Execution d'une commande du shell
#
def execute (cmd):
    #print '> ' + cmd
    r, w, e = popen2.popen3(cmd)
    lines = []
    for line in r.readlines():
	##print line
        line = string.rstrip (line)
        lines.append (line)
    #for line in e.readlines():
    #    line = string.rstrip (line)
    #    lines.append (line)
    r.close()
    w.close()
    e.close()
    return lines
    #end execute

#----------------------------------------------------
def show_lines (lines):
    for line in lines:
        print line
    # end show_lines

#----------------------------------------------------
class Cmt:
    cmtexe = os.environ ['CMTROOT'] + '/' + os.environ ['CMTBIN'] + '/cmt.exe'
    macros = dict ()
    sets = dict ()
    uses = []
    
    def __init__ (self):
        #lines = execute (self.cmtexe + ' show macros')
        #for line in lines:
        #    w = string.split (line, '=')
        #    name = w[0]
        #    value = re.sub ('^[\']', '', w[1])
        #    value = re.sub ('[\']$', '', value)
        #    self.macros [name] = value
        #lines = execute (self.cmtexe + ' show sets')
        #for line in lines:
        #    w = string.split (line, '=')
        #    name = w[0]
        #    value = re.sub ('^[\']', '', w[1])
        #    value = re.sub ('[\']$', '', value)
        #    self.sets [name] = value
        lines = execute (self.cmtexe + ' show uses')
        for line in lines:
            if line[0] == '#':
                continue
            self.uses.append (line)
    def macro_value (self, name):
        if not self.macros.has_key (name):
            lines = execute (self.cmtexe + ' show macro_value ' + name)
            self.macros[name] = ''
            for line in lines:
                #print 'name=' + name + ' value = ' + line
                self.macros[name] = line
                break
        return self.macros[name]

    def do (self, cmd):
        execute (self.cmtexe + ' ' + cmd)

def filter_doxyfile (doxygen_input, tagfiles, package_tagfile):
    f = open ('Doxyfile')
    lines = f.readlines ()
    f.close ()
    g = open ('Doxyfile', 'w')
    for line in lines:
        w = string.split (line)
        if len (w) > 0:
            if w[0] == 'INPUT':
                line = 'INPUT = ' + doxygen_input + '\n'
            elif w[0] == 'TAGFILES':
                line = 'TAGFILES = ' + tagfiles + '\n'
            elif w[0] == 'GENERATE_TAGFILE':
                line = 'GENERATE_TAGFILE = ' + package_tagfile + '\n'
	# print line
        g.write (line)
    g.close ()

def filter_uses ():
  used_packages = ''
  tagfiles = ''

  for line in cmt.uses:
    w = string.split (line)
    package = w[1]
    version = w[2]
    offset = w[3]
    if offset[0] == '(':
        offset = ''
        
    if package == 'CMT':
        continue
    if offset == 'CMT':
        continue
    if offset != '':
        offset = offset + '/'

    cmtpath = string.replace (line, '(no_auto_imports)', '')
    cmtpath = re.sub ('.*[(]', '', cmtpath)
    cmtpath = re.sub ('[)].*', '', cmtpath)

    inpackage = ''
    path = cmtpath + '/' + offset + '/' + package + '/' + version + '/doc'
    if os.path.isdir (path):
        for f in os.listdir (path):
            if re.search ('[.]tag$', f) == None:
		continue
            inpackage = f

    path = cmtpath + '/InstallArea/doc/' + package + '.tag'
    if os.path.isfile (path):
        print package + '.tag found in InstallArea ' + cmtpath
        tagfiles = tagfiles + ' ' + path
    elif inpackage != '':
        print package + '.tag found in package ' + cmtpath + '/' + offset + package
        tagfiles = tagfiles + ' ' + inpackage

    used_packages = used_packages + ' ' + offset + package

  return used_packages, tagfiles


#----------------------------------------------------
# Main
#----------------------------------------------------

cmt = Cmt ()

#----------------------------------------------------
# Preparation de la configuration

CMTINSTALLAREA       = cmt.macro_value ('CMTINSTALLAREA')
PLATFORMROOT         = cmt.macro_value ('PLATFORMROOT')
package              = cmt.macro_value ('package')
DOXYGEN_INPUT        = cmt.macro_value ('DOXYGEN_INPUT')
DOXYGEN_FILE_PATTERNS    = cmt.macro_value ('DOXYGEN_FILE_PATTERNS')
DOXYGEN_OUTPUT_DIRECTORY = cmt.macro_value ('DOXYGEN_OUTPUT_DIRECTORY')

output = DOXYGEN_OUTPUT_DIRECTORY + 'doc'
print 'output=[' + output + ']'

package_tagfile = CMTINSTALLAREA + '/doc/' + package + '.tag'
DOXYGEN_GENERATE_TAGFILE = package_tagfile

used_packages, tagfiles = filter_uses ()
#print 'used_packages = ' + used_packages
#print 'tagfiles = ' + tagfiles

#----------------------------------------------------
# Preparation de l'output

#print 'output = ' + output

if not os.path.isdir (output):
    os.makedirs (output)

if not os.path.isdir ('../doc'):
    os.makedirs ('../doc')

if not os.path.isfile ('../doc/mainpage.h'):
    f = open ('../doc/mainpage.h', 'w')
    f.write ('/**\n')
    f.write ('\n')
    f.write ('@mainpage\n')
    f.write ('\n')
    f.write ('@htmlinclude used_packages.html\n')
    f.write ('\n')
    f.write ('@include requirements\n')
    f.write ('\n')
    f.write ('*/\n')
    f.close ()

#----------------------------------------------------
# Construction de Doxyfile

#if not os.path.isfile ('../doc/Doxyfile'):
#    cmt.do ('filter ' + PLATFORMROOT + '/cmt/Doxyfile ../doc/Doxyfile')
#cmt.do ('filter ' + PLATFORMROOT + '/cmt/Doxyfile ../doc/Doxyfile')
cmt.do ('filter ' + PLATFORMROOT + '/doc/Doxyfile ../doc/Doxyfile')

ok = False
doxygen_input = ''
for d in string.split (DOXYGEN_INPUT):
    if os.path.isdir (d):
        for p in string.split (DOXYGEN_FILE_PATTERNS):
            lines = execute ('ls ' + d + '/' + p)
            show_lines (lines)
            if len (lines) != 0:
                doxygen_input = doxygen_input + ' ' + d
                break

if doxygen_input == '':
    print 'Empty input for Doxygen'
    exit
else:
    print 'input for Doxygen = ' + doxygen_input

os.chdir ('../doc')

filter_doxyfile (doxygen_input, tagfiles, package_tagfile)

#----------------------------------------------------
# Construction de used_packages.html

f = open ('used_packages.html', 'w')
f.write ('<center><table border="1"><tr><td><center><i>Used packages</i></center></td></tr>\n')
for u in string.split (used_packages):
    p = os.path.basename (u)

    r = cmt.macro_value (p + '_root')

    print '>>> r=' + r
    
    f.write ('<tr><td><a href="' + r + '/doc' + '/html/index.html">' + u + '</a></td></tr>\n')
f.write ('</table></center>\n')
f.close ()

#----------------------------------------------------
# Lancement de doxygen

print 'Now running doxygen'
    
lines = execute ('doxygen') 
show_lines (lines)

##sys.exit (0)

#----------------------------------------------------
# Gestion des tagfiles

print 'Now patching output files'
    
print 'tagfiles = [' + tagfiles + ']'

args = ''

subs = dict ()

if len(tagfiles) > 0:

  for f in string.split (tagfiles):
    filename = os.path.basename (f)
    package = string.replace (filename, '.tag', '')
    d = os.path.dirname (f)
    d = re.sub ('.*/InstallArea/doc', '../../' + package + '/html/', d)
    args = args + ' -l ' + filename + '@' + d
    subs[filename] = d

os.chdir (output + '/html')

files = []
for name in os.listdir ('.'):
  if name == 'tree.js':
    files.append (name)
  elif re.search ('[.]html$', name) != None:
    files.append (name)

if len(files) == 0:
  print 'Warning: No input files given and non found!'

for key in subs:
  if key == '':
    continue
  if key == 'DoxygenInterface.tag':
    continue
  if key == '_doc':
    continue
  if key == '_cgi':
    continue

  print 'Substituting ' + subs[key] + ' for each occurence of tag file ' + key

  pattern1 = r'doxygen="(' + key + r'):([^ \"\t\>\<]*)" (href|src)="'
  repl1    = r'doxygen="' + subs[key] + r'" \3="' + subs[key]

  pattern2 = r'"(' + key + r')\:([^ \"\t\>\<]*)", "'
  repl2 = r'"' + subs[key] + '", "'

  #print 'p1 = ' + pattern1 + ' r = ' + repl1
  #print 'p2 = ' + pattern2 + ' r = ' + repl2

  for f in files:
    #print 'Editing ' + f
    fbak = f + '.bak' + key
    #print 'renaming ' + f + ' into ' + fbak
    if not os.path.isfile (f):
      print 'File ' + f + ' not found '
      continue

    os.rename (f, fbak)
    if f != 'tree.js':
      pattern = pattern1
      repl = repl1
    else:
      pattern = pattern2
      repl = repl2

    g = open (f, 'w')
    gbak = open (fbak)

    for line in gbak:
      line2 = re.sub (pattern, repl, line)
      #if line2 != line:
      #  print line
      #  print '->' + line2
      g.write (line2)

    g.close ()
    gbak.close ()
 
    ##os.rename (fbak, f)


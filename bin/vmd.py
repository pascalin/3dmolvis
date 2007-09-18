#!/usr/bin/env python
"""A simple script to make a custom copy of VMD C-Shell startup
script. It comments some lines and essentially disables the launching
of an xterm previously to VMD booting. The custom copy is created on
cwd or on command line indicated destination."""

import sys, os, re

def _(s):
    return s

if __name__ == "__main__":
    #Detect if we are in a *nix
    if not re.search(r'^(linux|irix).*$', sys.platform):
        sys.stderr.write(_("This script just functions on *nix OSes"))
        sys.exit(1)
    vmdpath = os.popen("whereis vmd").read().split() #Uses the whereis command
    if len(vmdpath)>1: #VMD was found
        vmdpath=vmdpath[1]
    else:
        sys.stderr.write(_("You need to install VMD before you can employ VMDGui"))
        sys.exit(2)

    destpath = len(sys.argv)>1 and sys.argv[1] or "."
    targetfile = os.path.join(destpath,"vmd")
    if os.path.exists(targetfile):
        proceed = ""
        while proceed not in (_("N"), _("Y")):
            proceed = raw_input(_("vmd script exists already on target folder. Overwite? [Y/N]")).strip().upper()
        if proceed == _("N"):
            sys.exit(0)
    target = open(targetfile, "w")
    target.write("#!/bin/csh\n")
    comment = False
    lastline = ""
    #Comment some lines
    for sourceline in [l for l in open(vmdpath) if not l.startswith("#")]:
        if comment:
            if sourceline.strip() == "\"$MASTERVMDDIR/$execname\" $*" and lastline.find("else")!=-1:
                target.write(sourceline+"#\tendif\nendif\n")
                break
            else:
                target.write("#"+sourceline)
        else:
            target.write(sourceline)
        if lastline.find("bpsh $VMDSLAVENODE")!=-1:
            comment = True
        lastline = sourceline
    target.close()
    os.chmod(targetfile, 0755) #Makes the copy executable

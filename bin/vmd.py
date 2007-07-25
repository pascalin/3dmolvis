#!/usr/bin/env python

import sys, os

def _(s):
    return s

if __name__ == "__main__":
    if not sys.platform in ('linux2',):
        sys.exit(0)
    vmdpath = os.popen("whereis vmd").read().split()
    if len(vmdpath)>1:
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
    for sourceline in [l for l in open(vmdpath) if not l.startswith("#")]:
        if comment:
            if sourceline.strip() == "\"$MASTERVMDDIR/$execname\" $*" and "else" in lastline:
                target.write(sourceline+"#\tendif\nendif\n")
                break
            else:
                target.write("#"+sourceline)
        else:
            target.write(sourceline)
        if "bpsh $VMDSLAVENODE" in lastline:
            comment = True
        lastline = sourceline
    target.close()
    os.chmod(targetfile, 0755)

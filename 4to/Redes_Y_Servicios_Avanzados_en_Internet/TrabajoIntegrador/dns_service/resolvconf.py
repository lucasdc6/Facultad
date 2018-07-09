# -*- coding: utf-8 -*- 

# Copyright (c)2013 Raúl Benencia
# See the LICENSE file included in this distribution.

''' Trivial resolvconf updater. A link from /run/resolvconf/resolv.conf to
    /etc/resolv.conf must exists.
'''
from core.service import CoreService, addservice

class ResolvconfService(CoreService):
    ''' Trivial resolvconf updater'''
    # a unique name is required, without spaces
    _name = "resolvconf"
    # you can create your own group here
    _group = "DNS"
    # per-node directories
    _dirs = ('/etc/resolvconf/resolv.conf.d', )
    # generated files (without a full path this file goes in the node's dir,
    #  e.g. /tmp/pycore.12345/n1.conf/)

    _configs = ("/etc/resolvconf/resolv.conf.d/base", "startup.sh")
    _startup = ("sh startup.sh",)

    @classmethod
    def generateconfig(cls, node, filename, services):
        if filename == cls._configs[0]:
            return "nameserver 10.0.4.10\n"
        elif filename == cls._configs[1]:
            cfg = "#!/bin/sh\n"
            cfg += "mkdir -p /run/resolvconf/interface\n"
            cfg += "resolvconf --enable-updates\n"
            cfg += "resolvconf -u\n"
            return cfg
        else:
            return ""     
  
# this line is required to add the above class to the list of available services
addservice(ResolvconfService)

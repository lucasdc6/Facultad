# -*- coding: utf-8 -*- 

# Copyright (c)2013 Raúl Benencia <rbenencia@cert.unlp.edu.ar>
# See the LICENSE file included in this distribution.

''' Custom DNS service.
'''
from core.service import addservice
from core.services.utility import UtilService

class DnsService(UtilService):
    ''' Parent class for all DNS services '''

    domain = "myzone."
    addressv4 = []
    nsv4 = []
    master = True

    # a unique name is required, without spaces
    _name = "GenericDNS"
    _group = "DNS"

    # generated files (without a full path this file goes in the node's dir,
    #  e.g. /tmp/pycore.12345/n1.conf/)
    _configs = ('/etc/bind/named.conf',
                '/etc/bind/named.conf.options',
                '/etc/bind/named.conf.local',
                '/etc/bind/rndc.key',
                '/etc/bind/db.myzone.') # When subclassing replace with the domain db filename

    # per-node directories
    _dirs = ("/etc/bind", "/var/cache/bind", "/var/run/named")

    # list of startup commands, also may be generated during startup
    _startup = ('/etc/init.d/bind9 start',)
    # list of shutdown commands
    _shutdown = ('/etc/init.d/bind9 stop',)
    _validate = ('pidof named',)

    @classmethod
    def generateconfig(cls, node, filename, services):
        ''' Return a string that will be written to filename, or sent to the
            GUI for user customization.
        '''
        if filename == cls._configs[0]:   # named.conf
            return cls.generatenamedconf(node, filename, services)
        elif filename == cls._configs[1]: # named.conf.options
            return cls.generatenamedconfoptions(node, filename, services)
        elif filename == cls._configs[2]: # named.conf.local
            return cls.generatenamedconflocal(node, filename, services)
        elif filename == cls._configs[3]: # rndc.key
            key = ""
            try:
                key = open(filename, "rb").read()
            except e:
                print "Error opening DNS rndc key (%s): %s" % (filename, e)
            return key
        elif filename == cls._configs[4]: # '/etc/bind/db.' + domain
            return cls.generatedominfo(node, filename, services)
        else:
            return ""

    @classmethod
    def generatenamedconf(cls, node, filename, services):
        return """\
// This is the primary configuration file for the BIND DNS server named.
// If you are just adding zones, please do that in /etc/bind/named.conf.local

include "/etc/bind/named.conf.options";
include "/etc/bind/named.conf.local";
"""
    @classmethod
    def generatenamedconfoptions(cls, node, filename, services):
        return "options { \n" + cls.default_options() + cls.custom_options() + "};\n"

    @staticmethod
    def default_options():
        options = [ """directory "/var/cache/bind";"""
                  , "listen-on-v6 { none; };"
                  , "allow-query { any; };"
                  , "allow-query-cache { any; };"
                  ]
        return ''.join(map(lambda s: "\t" + s + "\n", options))

    @staticmethod
    def custom_options():
        options = [ "recursion no;" ]
        return ''.join(map(lambda s: "\t" + s + "\n", options))

    @classmethod
    def generatenamedconflocal(cls, node, filename, services):
        return """\
zone "%s" {
	type %s;
	file "/etc/bind/db.%s";
};
""" % (cls.domain, "master" if cls.master else "hint", cls.filename())

    @classmethod
    def filename(cls):
        return cls.domain

    @classmethod
    def generatedominfo(cls, node, filename, services):
        # Default zone information. Most likely you'll want to change it.
        dom = cls.domain if cls.domain != "." else ""
        return ("""\
$TTL	120
@		SOA	ns.%s  hostmaster.ns.%s ( 1 3600 1200 604800 60 )
		NS	ns
""" % (dom, dom)) + cls.pp_nsv4() + cls.pp_addressv4()
    
    @classmethod
    def pp_addressv4(cls):
        return ''.join(map(lambda (name, ip): name + cls.mid_str() + "A\t" + ip + "\n", cls.addressv4)) + "\n"

    @classmethod
    def pp_nsv4(cls):
        return ''.join(map(lambda (domain, ns): domain + cls.mid_str() + "NS\t" + ns + "\n", cls.nsv4)) + "\n"

    @classmethod
    def mid_str(cls):
        return "\t\t" if cls.master else "\t\t3600000\t"

class RootDnsService(DnsService):
    '''Root DNS service.'''
    domain = "."
    _name = "RootServer"
    _configs = DnsService()._configs[:-1] + ('/etc/bind/db.' + 'root',)

    nsv4 = [ (".", "ns2.")
           , (".", "ns3.")
           , (".", "ns4.")
           , ("com.", "com.")
	   ]

    addressv4 = [ ("ns", "200.51.4.62")
                , ("ns2", "200.52.4.62")
                , ("ns3", "200.53.4.62")  
                , ("ns4", "200.54.4.62")  
                , ("com", "200.55.4.62")  
                ]

    @classmethod
    def filename(cls):
        return "root"

class TldEduDnsService(DnsService):
    '''.edu TLD DNS service.'''
    domain = "edu."
    nsv4 = [ ("unlp.edu.", "ns.unlp.edu.")
           , ("uba.edu.", "ns.uba.edu.")
           ]
    addressv4 = [("ns", "10.0.2.10"), ("ns.unlp.edu.", "10.0.5.10"), ("ns.uba.edu.", "10.0.5.11")]

    _name = "TLD_edu"
    _configs = DnsService()._configs[:-1] + ('/etc/bind/db.' + domain,)

class TldComDnsService(DnsService):
    '''.com TLD DNS service.'''
    domain = "com."
    nsv4 = [ ("google.com.", "ns.google.com.")
           , ("yahoo.com.", "ns.yahoo.com.")]
    addressv4 = [("ns", "10.0.1.10"), ("ns.google.com.", "200.55.4.62"), ("ns.yahoo.com.", "10.0.5.13")]
    _name = "TLD_com"
    _configs = DnsService()._configs[:-1] + ('/etc/bind/db.' + domain,)

class ResolverDnsService(DnsService):
    '''Resolver DNS service.'''
    domain = "."
    master = False

    nsv4 = [ (".", "ns.")
           , (".", "ns2.")
           , (".", "ns3.")
           , (".", "ns4.")
           ]
    addressv4 = [ ("ns.", "200.51.4.62")
                , ("ns2.", "200.52.4.62")
                , ("ns3.", "200.53.4.62")
                , ("ns4.", "200.54.4.62")
                ]

    _name = "Resolver"
    _configs = DnsService()._configs[:-1] + ('/etc/bind/db.' + 'root',)

    @classmethod
    def filename(cls):
        return "root"

    @staticmethod
    def custom_options():
        options = [ "recursion yes;"
                  , "allow-recursion { any; };"
                  ]
        return ''.join(map(lambda s: "\t" + s + "\n", options))

    @classmethod
    def generatedominfo(cls, node, filename, services):
        # Root servers information
        return cls.pp_nsv4() + cls.pp_addressv4() + "\n"
        
# this lines are required to add the above classes to the list of available services
addservice(DnsService)
addservice(RootDnsService)
addservice(TldComDnsService)
addservice(TldEduDnsService)
addservice(ResolverDnsService)

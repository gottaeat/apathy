### security
#### software listed below must be updated:
* [done] ntp | 4.2.8p12 --> 4.2.8p13  
https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-8936
* [done] libpng | 1.6.36 --> 1.6.37  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.369646
* [done] openjpeg | 2.3.0 --> 2.3.1  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.332670
* [done] irssi | 1.2.0 --> 1.2.1  
https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-13045
* [done] bzip2 | 1.0.6 --> 1.0.8  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.423144
* curl  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.424586
* libssh2  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.378113
* wget  
https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-5953
* gnutls  
http://www.slackware.com/security/viewer.php?l=slackware-security&y=2019&m=slackware-security.427640

### planned to be built/set/configured
* [d] rss reader		--> built newsboat
* [d] set up iptables		--> done
* [d] mutt			--> done, ages ago

### dbus removal garbage
#### bin and lib still linked against libdbus:
```
none, as far as i can tell.
```
#### rebuilt without dbus
```
* iftop-1.0pre4
* gtk+-3.24.5
* compton-0.1_beta2
* mpd-0.21.10
* libpcap-1.9.0
```

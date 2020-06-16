##### ToDo:
- Watch out for runnig out of space on / of ams-www-eos
`watch -n1 "ls -la /home/common/ams-event-display-snapshots/ | wc -l"`
- Watch out for running out of space on (should be 1TB of space)
`11:52:23-wwwapash@ams-www-eos:~$ ls -la /eos/project/w/wwwams/www/buffer`

##### Changes:

2020.06.16 Moved `www` into `www/EventDisplay`:
```
16:52:03-wwwapash@ams-www-eos:$ ls -la /eos/project/w/wwwams/www/EventDisplay/
drwxr-xr-x. 1 wwwapash def-cg   4096 Jun 16 16:52 buffer
-rw-------. 1 wwwapash def-cg    226 Jun 16 16:51 index.html
-rw-------. 1 wwwapash def-cg 216199 Jun 16 16:51 Index.js
-rw-------. 1 wwwapash def-cg  59650 Jun 16 16:45 ss_0.png
```

# AMS Event Display web page

The URL of the "AMS Services" website: [https://amsservices.web.cern.ch/](https://amsservices.web.cern.ch/amsservices/)

This website is used for `ams02.space` (the official AMS website). 
[The Event Display page](https://ams02.space/EventDisplay) has an iframe with "https://amsservices.web.cern.ch/amsservices/EventDisplay" inside.

This is a EOS-based web site. The EOS location is owned by wwwapash (which is a service account).
```
The service account `wwwapash` is a member of cernbox-project-wwwams-admins. The owner of this service account can login (using his/her own primary account) to https://e-groups.cern.ch and add other project space administrators to this egroup). More details here: https://cern.service-now.com/service-portal?id=ticket&n=RQF1376416.
There are 2 EOS folder: 
/eos/project/w/wwwams/www/       (folder for hosting an EOS-site-type website)
/eos/project/w/wwwams/public/    (public folder for all CERN authenticated users)
```

- Source code: https://github.com/kowaraj/AMS_EventDisplay_reader2
- From this ticket: https://cern.service-now.com/service-portal/view-request.do?n=RQF1376416

### How it works

The website EOS location is:
```
14:57:29-apashnin@ams-www-eos:/eos/project/a/amstest/www$ ls -la
lrwxrwxrwx. 0 129385 def-cg     11 Jun 15 15:12 buffer -> ./buffer_v1
drwxr-xr-x. 1 129385 def-cg   4096 Jun 15 15:12 buffer_v1
-rw-------. 1 129385 def-cg    232 Jun 15 13:33 index.html
-rw-------. 1 129385 def-cg 216229 Jun 15 14:40 Index.js
```

It takes the images from:
```
14:57:26-apashnin@ams-www-eos:/eos/project/a/amstest/www$ ls -la ./buffer/ | tail
-rw-r--r--. 1 129385 def-cg 22505 Jun 15 14:57 ss_1592218652.png
-rw-r--r--. 1 129385 def-cg 24495 Jun 15 14:57 ss_1592218653.png
-rw-r--r--. 1 129385 def-cg 23316 Jun 15 14:57 ss_1592218654.png
-rw-r--r--. 1 129385 def-cg 23330 Jun 15 14:05 ss_1.png
-rw-r--r--. 1 129385 def-cg 23360 Jun 15 14:07 ss_2.png
```

Which are produced by
```
16:16:46-wwwapash@ams-www-eos:$ ls -la  /home/wwwapash/run/event_display/
-rw-r--r--. 1 wwwapash def-cg 1263 Jun 16 11:48 image-transporter.sh
-rw-------. 1 wwwapash def-cg   60 Jun 16 13:04 wwwapash.keytab7
```

Which is a copy of
```
19:33:24-apashnin@ams-www-eos:/home/apashnin/src/event_display$ ls -la
-rw-r--r--. 1 apashnin va   1416 Jun 15 12:33 image-generator.py
-rw-r--r--. 1 apashnin va    747 Jun 15 19:23 image-transporter.sh
-rw-r--r--. 1 apashnin va    975 Apr 15 20:19 pptimer.py
-rw-r--r--. 1 apashnin va 834452 Apr 15 20:24 times_new_roman.ttf
```

To run a simulation (python generated fake screenshots), source the venv first
```
15:06:30-apashnin@ams-www-eos:/home/apashnin/run/event_display$ . /home/apashnin/src/venv/bin/activate
```

Then run
```
(venv) 15:06:33-apashnin@ams-www-eos:/home/apashnin/run/event_display$ python3 ./image-generator.py
```

Run an Xvnc session with vncserver
```
[vncviewer@ams-www-eos ~]$ vncserver -bs
[vncviewer@ams-www-eos ~]$ ps aux | grep Xvnc
vncview+ 15477  0.9  0.8 251892 65352 pts/12   Sl   14:50   2:44 /bin/Xvnc :1 -auth /home/vncviewer/.Xauthority -desktop ams-www-eos.cern.ch:1 (vncviewer) -fp catalogue:/etc/X11/fontpath.d -geometry 1024x768 -pn -rfbauth /home/vncviewer/.vnc/passwd -rfbport 5901 -rfbwait 30000
Run VLC to produce the screenshots every 1 second
```

Run a VLC to produce the screenshots:
```
[vncviewer@ams-www-eos ~]$ export DISPLAY=:1
[vncviewer@ams-www-eos ams-event-display-snapshots]$ /usr/bin/vlc -I dummy screen:// --rate=1 --video-filter=scene --vout=dummy  --scene-format=png --scene-ratio=24 --scene-prefix=sna --scene-path=/home/common/ams-event-display-snapshots/
```

Run a bash script to rename/move and delete the screenshots:
```
19:38:18-apashnin@ams-www-eos:/home/apashnin/run/event_display$ bash /home/apashnin/run/event_display/image-transporter.sh
```


#### Reauth with a keytab file

1. Create a `keytab`:
```
13:03:23-wwwapash@ams-www-eos:/home/wwwapash/run/event_display$ ktutil
ktutil:  add_entry -password -p wwwapash@CERN.CH -k 1 -e rc4-hmac
Password for wwwapash@CERN.CH:
ktutil:  wkt wwwapash.keytab7
ktutil:  quit
```

2. Check the `keytab`
```
13:04:43-wwwapash@ams-www-eos:/home/wwwapash/run/event_display$ kinit -k -t ./wwwapash.keytab7 wwwapash
```

3. Run `k5reauth` to use the created keytab: 
```
13:07:31-wwwapash@ams-www-eos:/home/wwwapash/run/event_display$ k5reauth -p wwwapash -k /home/wwwapash/run/event_display/wwwapash.keytab7 -- bash ./image-transporter.sh
```

FILES:
```
14:38:05-wwwapash@ams-www-eos:/home/wwwapash/run/event_display$ ls -la
-rw-r--r--. 1 wwwapash def-cg 1263 Jun 16 11:48 image-transporter.sh
-rw-------. 1 wwwapash def-cg   60 Jun 16 13:04 wwwapash.keytab7
```


> This obsoletes the following? what about eosfusebind -g ?
> 14:38:18-apashnin@ams-www-eos:/eos/project/a/amstest/www/v1$ crontab -l
> 19 7 * * * /afs/cern.ch/user/a/apashnin/bin/eos_reauth.cron


### To build for production and deliver:

Build for production
```
[kapashnin@Andreys-MacBook-Pro: ~/src/test/ams/ams-ed-reader-app/ams-ed-reader-app_re ] npm run webpack:production
```

Deliver
```
scp -P60666 -i ~/.ssh/key-ams-www-eos ~/src/test/ams/ams-ed-reader-app/ams-ed-reader-app_re/build/* apashnin@localhost:/eos/project-a/amstest/www/
```

### Summary

| Name         | Account  | URL                                   | EOS path                   | Quota  |   |
| ------------ | -------- | ------------------------------------- | -------------------------- | ------ | - |
| AMS Services | wwwapash | https://amsservices.web.cern.ch       | /eos/project/w/wwwams/www  | 1TB    |   |
| amstest      | apashnin | https://test-apashnin-ams.web.cern.ch | /eos/project/a/amstest/www | 33 GB? |   |
| apashnin     | apashnin | https://apashnin.web.cern.ch          | /eos/user/a/...?           |        |   |


### Hardware and accounts

| Account   | Host        | Type         | Desct                                            |
| --------- | ----------- | ------------ | ------------------------------------------------ |
| vncviewer | www-ams-eos | local        | To run Xvnc and VLC to produce the screenshots   |
| wwwapash  | www-ams-eos | CERN service | To access EOS location of amsservices WWW folder |





2. test-apashnin-ams - The  "real" website
It will be re-named or moved to a production EOS-based website, like ams02eos.space
It is not the same as test-apashnin website (Drupal8 CMS). The test-apashnin will become ams02.space in production.
It is a project website. Project's name is amstest. To be re-named/moved to ams02eos project.

# Development 

It's a frontend written in ReasonReact. Source code is in github: https://github.com/kowaraj/AMS_EventDisplay_reader2
It's compiled with BucketScript and it's bundled with Webpack into 2 static files (index.html and Index.js) which are copied into the apashnin@ams-www-eos:/eos/project-a/amstest/www/ folder.
CORS (for development)
Working of a test website will fail to fetch resources from https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt due to same-origin policy of fetch API.
A workaround is to add a .htaccess file to the buffer/ folder with 
Header set Access-Control-Allow-Origin "http://localhost:3001
(assuming webpack-dev-server is running on port 3001)

# Crontab

18:30:15-apashnin@ams-www-eos:~$ crontab  -l
19 7 * * * /afs/cern.ch/user/a/apashnin/bin/eos_reauth.cron
#* * * * * env > /afs/cern.ch/user/a/apashnin/cronenv
18:30:16-apashnin@ams-www-eos:~$ cat /afs/cern.ch/user/a/apashnin/bin/eos_reauth.cron
#!/bin/bash

/afs/cern.ch/user/a/apashnin/bin/eos_reauth.sh > /afs/cern.ch/user/a/apashnin/eos_reauth.log 2>&1
18:30:22-apashnin@ams-www-eos:~$ cat /afs/cern.ch/user/a/apashnin/bin/eos_reauth.sh
#!/bin/bash



# EOS access credentials

`apashnin` account (do kinit + eosfusebind -g) has access to both EOS spaces:
- /eos/project/a/amstest/www/
- /eos/project/w/wwwams/www/
```
11:06:21-apashnin@ams-www-eos:~$ ls -la /eos/project/a/amstest/www/
total 283
drwx------. 2 129385 def-cg   4096 Jun 15 20:22 .
drwx------. 2 129385 def-cg   4096 Jun 15 12:06 ..
lrwxrwxrwx. 1 129385 def-cg     11 Jun 15 13:12 buffer -> ./buffer_v1
drwxr-xr-x. 2 129385 def-cg   4096 Jun 16 09:49 buffer_v1
-rw-------. 1 129385 def-cg    226 Jun 15 20:22 index.html
-rw-------. 1 129385 def-cg 216054 Jun 15 20:22 Index.js
-rw-------. 1 129385 def-cg  59650 Jun 15 20:10 ss_0.png
11:06:25-apashnin@ams-www-eos:~$ ls -la /eos/project/w/wwwams/www/
total 9
drwx------. 2 wwwapash def-cg 4096 Jun 15 11:39 .
drwx------. 2 wwwapash def-cg 4096 Jun 15 11:45 ..
-rw-r--r--. 1 wwwapash def-cg  214 Jun 15 11:39 index.htmln
```

# Versions

### v.0.2.1 

Started from scratch. It's the simplest functionality. 

The SPA updates by a timer every 1 second and gets a new URL for the image to show (based on the linux epoch time in seconds). 
The server is fake for now - a python script that is generating a fake image every second. 
Naming convention for the image files is 'ss_1500600700.png'.

List of actors: 
- `Version1.re` - the shown component
- `TimerV1.re` - a timer which triggers the image URL update every 1 second
- `image-generator.py` - a python script that generates fake images every 1 second
- `PrecisionPeriodicTimer` - a python class for the precision timer (no drift)

# History 

2020.04.15: Version1.re works fine with TimerV1.re and image-generator.py
```
[kapashnin@Andreys-MBP: ~/src/test/ams/ams-ed-reader-app/ams-ed-reader-app_re/python-scripts ] python3 ./image-generator.py ./buffer/
```

# Run 

1. Build for production
```
[kapashnin@Andreys-MacBook-Pro: ~/src/test/ams/ams-ed-reader-app/ams-ed-reader-app_re ] npm run webpack:production
[kapashnin@Andreys-MacBook-Pro: ~/src/test/ams/ams-ed-reader-app/ams-ed-reader-app_re ] ls -la ./build/
total 440
drwxr-xr-x   5 kapashnin  staff     170 Apr 15 14:28 .
drwxr-xr-x  17 kapashnin  staff     578 Apr 15 14:29 ..
-rw-r--r--   1 kapashnin  staff  216004 Apr 15 20:51 Index.js
lrwxr-xr-x   1 kapashnin  staff      25 Apr 15 14:23 buffer -> ../python-scripts/buffer/
-rw-r--r--   1 kapashnin  staff     226 Apr 15 20:51 index.html
```
2. Copy to a production host (ams-www-eos:/)


# Install 

```
bsb -init ams-ed-reader-app_re -theme react-hooks
npm install
```


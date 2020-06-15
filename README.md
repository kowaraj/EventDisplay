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


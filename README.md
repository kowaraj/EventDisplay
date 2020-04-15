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

# Install 
```
bsb -init ams-ed-reader-app_re -theme react-hooks
npm install

```


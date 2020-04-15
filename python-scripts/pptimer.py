import threading
import time
class PrecisionPeriodicTimer():
    '''
    Triggers a callback every second without a drift. 
    The drift is compensated by the next time_interval to run. 
    '''
    def __init__(self, callback, interval=1.0):
        self.callback = callback
        self.interval = interval
        self.dt = interval
        if (interval > 1.0):
            raise ValueError('Value larger 1 second is not supported yet. Fix __callback function!')

    def start(self):
        t = threading.Timer(self.dt, self.__callback)
        t.start()

    def __callback(self):
        self.callback()
        ms = int(round(time.time() * 1000)) % 1000
        dt = (1000 - ms)/1000.
        print('dt = ', dt)
        self.dt = dt
        # if dt < 0.8:
        #     raise ValueError('Timer callback is longer than 0.8 seconds.')
        self.start()
        print('timer callback, current ms: ', ms)


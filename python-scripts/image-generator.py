from PIL import Image, ImageDraw, ImageFont
import datetime
from time import sleep 
import sys

def make_image(label, path="./buffer"):
    img = Image.new('RGB', (1680, 1050), color = (73, 109, 137))
    fnt = ImageFont.truetype('times_new_roman.ttf', 120)
    d = ImageDraw.Draw(img)
    d.text((300,400), label, font=fnt, fill=(255, 255, 0))
    img.save(path + '/ss_' + label + '.png')

def generate_sequential():
    for i in range(100):
        print(str(i))
        make_image(str(int(i/100)) + '_' + str(int(i/10)) + '_' + str(i%10))

def generate_realtime(delta_sec):
    print(sys.argv[1])
    while True:
        # instead of: ts_str = datetime.datetime.utcnow().strftime("%s")
        # use:
        ts_str = datetime.datetime.now(datetime.timezone.utc).strftime("%s")
        ts = int(ts_str)
        ts_mod = ts + delta_sec
        ts_str_mod = str(ts_mod)
        print(ts_str, ts_str_mod)
        make_image(ts_str_mod, path=sys.argv[1])
        sleep(1)

if __name__ == "__main__":
    generate_realtime(5)
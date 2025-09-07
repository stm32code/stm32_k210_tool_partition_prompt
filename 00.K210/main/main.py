import sensor, image, time, lcd, gc, cmath
from maix import KPU
from maix import GPIO
from fpioa_manager import fm
from machine import UART,Timer

lcd.init()                          # Init lcd display
lcd.clear(lcd.RED)                  # Clear lcd screen.

#注册IO和构建LED对象
fm.register(35, fm.fpioa.GPIO0)
LED_B = GPIO(GPIO.GPIO0, GPIO.OUT)
#计数变量
Counter=0
ls = 0  # 根据你的需求初始化ls
lm = 0  # 根据你的需求初始化lm
kind=0
 
 

while(True):
    gc.collect()

    clock.tick()
    img = sensor.snapshot()

    kpu.run_with_output(img)
    dect = kpu.regionlayer_yolo2()

    fps = clock.fps()

    if len(dect) > 0:
        for l in dect :
            a = img.draw_rectangle(l[0],l[1],l[2],l[3],color=(0,255,0))

            info = "%s %.1f" % (labels[l[4]], l[5])
            if labels[l[4]] == '1':
                ls = 1
            if labels[l[4]] == '2':
                lm = 2

            del info

    #计算色块数量并在LCD显示
    img.draw_string(0, 0, 'Kind: '+str(kind), color = (255, 255,255), scale = 3,mono_space = False)

    lcd.display(img)



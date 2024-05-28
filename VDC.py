import cv2

import numpy as np

from time import sleep

import serial
import struct
import time

largura_min = 80

altura_min = 80

offset = 6

pos_linha = 200


# FPS to vídeo

delay = 60



detec = []

carros = 0

carros2 = 0

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)

def write_read(x):
    arduino.write(bytes(x))
    time.sleep(0.05)
    
	

def pega_centro(x, y, w, h):

    x1 = int(w / 2)

    y1 = int(h / 2)

    cx = x + x1

    cy = y + y1

    return cx, cy



# video source input

cap = cv2.VideoCapture('http://192.168.26.197:4747/video')
cap2 = cv2.VideoCapture('http://192.168.26.196:4747/video')
#cap = cv2.VideoCapture(0)


subtracao = cv2.bgsegm.createBackgroundSubtractorMOG()


while True:

    ret, frame1 = cap.read()        

    tempo = float(1/delay)         

    sleep(tempo)         

    grey = cv2.cvtColor(frame1, cv2.COLOR_BGR2GRAY)         

    blur = cv2.GaussianBlur(grey, (3, 3), 5)          

    img_sub = subtracao.apply(blur)          

    dilat = cv2.dilate(img_sub, np.ones((5, 5)))           

    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))           


    dilatada = cv2.morphologyEx(dilat, cv2. MORPH_CLOSE, kernel)          

    dilatada = cv2.morphologyEx(dilatada, cv2. MORPH_CLOSE, kernel)          



    contorno, h = cv2.findContours(dilatada, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)          



 

    cv2.line(frame1, (25, pos_linha), (1200, pos_linha), (176, 130, 39), 2)            

    for(i, c) in enumerate(contorno):            

        (x, y, w, h) = cv2.boundingRect(c)                

        validar_contorno = (w >= largura_min) and (h >= altura_min)                 

        if not validar_contorno:                 

            continue                      


        cv2.rectangle(frame1, (x, y), (x+w, y+h), (0, 255, 0), 2)                    

        centro = pega_centro(x, y, w, h)                    

        detec.append(centro)                     

        cv2.circle(frame1, centro, 4, (0, 0, 255), -1)                    


        for (x, y) in detec:                 

            if (y < (pos_linha + offset)) and (y > (pos_linha-offset)):                         

                carros += 1                         

                cv2.line(frame1, (25, pos_linha), (1200, pos_linha), (0, 127, 255), 3)                         

                detec.remove((x, y))                        

                print("No. of cars detected1 : " + str(carros))                        


    ret, frame2 = cap2.read()
    
       

    grey2 = cv2.cvtColor(frame2, cv2.COLOR_BGR2GRAY)         

    blur2 = cv2.GaussianBlur(grey2, (3, 3), 5)          

    img_sub2 = subtracao.apply(blur2)          

    dilat2 = cv2.dilate(img_sub2, np.ones((5, 5)))
    
               


    dilatada2 = cv2.morphologyEx(dilat2, cv2. MORPH_CLOSE, kernel)          

    dilatada2 = cv2.morphologyEx(dilatada2, cv2. MORPH_CLOSE, kernel)          



    contorno2, h2 = cv2.findContours(dilatada2, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)          



 

    cv2.line(frame2, (25, pos_linha), (1200, pos_linha), (176, 130, 39), 2)            

    for(i, c) in enumerate(contorno2):            

        (x2, y2, w2, h2) = cv2.boundingRect(c)                

        validar_contorno2 = (w2 >= largura_min) and (h2 >= altura_min)                 

        if not validar_contorno2:                 

            continue                      


        cv2.rectangle(frame2, (x2, y2), (x2+w2, y2+h2), (0, 255, 0), 2)                    

        centro2 = pega_centro(x2, y2, w2, h2)                    

        detec.append(centro2)                     

        cv2.circle(frame2, centro2, 4, (0, 0, 255), -1)                    


        for (x2, y2) in detec:                 

            if (y2 < (pos_linha + offset)) and (y2 > (pos_linha-offset)):                         

                carros2 += 1                         

                cv2.line(frame2, (25, pos_linha), (1200, pos_linha), (0, 127, 255), 3)                         

                detec.remove((x2, y2))                        

                print("No. of cars detected2 : " + str(carros2)) 


    cv2.putText(frame1, "VEHICLE COUNT1 : "+str(carros), (120, 80),cv2.FONT_HERSHEY_COMPLEX, 1, (0, 0, 255), 4)
    cv2.putText(frame2, "VEHICLE COUNT2 : "+str(carros2), (120, 80),cv2.FONT_HERSHEY_COMPLEX, 1, (0, 0, 255), 4)
    cv2.imshow("Video Original2", frame2)

    cv2.imshow("Video Original1", frame1)
    value = write_read(struct.pack('>BBBB',carros,carros2,0,0))
    data = arduino.readline()
    dataa = str(data[0:len(data)].decode("utf-8"))
    print("test"+dataa)
    if (dataa == "1"):
        print("1111111111111")
        carros = 0
    elif(dataa == "2"):
        print("222222222222222")
        carros2 = 0
    elif(dataa == "3"):
        print("3333333333333")
        carros2 = 0
    elif(dataa == "4"):
        print("444444444444")
        carros2 = 0

   # cv2.imshow(" Detectar ", dilatada)


    if cv2.waitKey(1) == 27:

        break        

    

cv2.destroyAllWindows()

cap.release()

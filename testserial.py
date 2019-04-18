from serial import Serial

com = Serial('COM1',9600)

while(com.inWaiting() != 0):
    car = com.read() #on lit un caractère
    print(car) #on l'affiche

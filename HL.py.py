from tkinter import *
from tkinter.colorchooser import *
from functools import partial

class LED: #definition of the led objects
    def __init__(self,pos,R,G,B): #each led is defined by it's number attributed in the matrix following the arduino adafruit neomatrix standard
        self.pos = pos
        self.R = R
        self.G = G
        self.B = B

class MATRIX: #definition of the matrix object
    def __init__(self, size):
        self.size = size

    def color(self, posi, Rcolor,Gcolor,Bcolor,HEXcolor): #the function called by pressing a button and selecting a button
        print(posi)
        for i in range(len(LEDLIST)): #check if the defined LED already exists in the list of all the leds

            if LEDLIST[i].pos == posi :
                print(posi) #debug
                LEDLIST[i].pos = str(posi)
                LEDLIST[i].R = str(Rcolor)
                LEDLIST[i].G = str(Gcolor)
                LEDLIST[i].B = str(Bcolor)
                #if it exists, we are redefining the RGB attributes of the concerned object as str elements in order to write them in a txt file
                buttonlist[posi].configure(bg = HEXcolor)
                return

        LEDLIST.append(LED(str(posi),str(Rcolor),str(Gcolor),str(Bcolor)))# if it doesn't already exists, we are defining it
        buttonlist[posi].configure(bg = HEXcolor)

    def writefile(self): #the function called when the WRITE button is pressed
      fil = open("map.txt", "w")
      fil.write("START\n\n") #the sart marker for the arduino
      for i in range(len(LEDLIST)): #for each element

        fil.write(LEDLIST[i].pos+"\n")
        fil.write(LEDLIST[i].R+"\n")
        fil.write(LEDLIST[i].G+"\n")
        fil.write(LEDLIST[i].B+"\n\n")

      fil.write("\nEND")# the end marker for the arduino
      fil.close()




def hex_to_rgb(value): #function converting hex to rgb value
    value = value.lstrip('#')
    lv = len(value)
    return tuple(int(value[i:i + lv // 3], 16) for i in range(0, lv, lv // 3))


def interface(): #function building the user's interface
    win=Tk()
    row = 0
    column = 0

    for i in range(40): #creation of the wanted number of button matrix
        button=Button(win,text='o', command=partial(GetPosColor,i)) #button that lets the user select a color
        button.grid(column=column, row=row) #displaying the buttons in a grid
        buttonlist.append(button)


        if column == 7 : #the parameters that define the shape of the grid
            column = 0
            row+=1
        else:
            column+=1
    writebutton = Button(win, text = "WRITE", command=MAIN.writefile) #the button that write the text file
    writebutton.grid(column = 9, row = 0) # /!\ if you are trying to change the parameters, the position of this button could be problematic, try to augment the column argument
    win.mainloop()#initialization of the interface

def GetPosColor(n): #function returning the color picked by the user and the position of the selected led

    button_pos = n #we define the position of the position by the value if i when it was created (in order to fit the norm of the arduino adafruit neomatrix)
    hexa = str(askcolor()[1]) #color contains a string that the hex value of the color chosen by the user
    rgb = hex_to_rgb(hexa) #color contains now a tuple of strings that are the RGB values of the chosen color

    R=(rgb[0])
    G=(rgb[1])
    B=(rgb[2])

    MAIN.color(button_pos,R,G,B,hexa)
    print(R,G,B)#debug

    #posrgb = ([button_pos,R,G,B])
    #return(posrgb) #may need it later

buttonlist = []
MAIN = MATRIX(40)
LEDLIST = []
datatowrite=[]

interface()

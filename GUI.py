from Tkinter import *
from tkFileDialog import *
from subprocess import call

myopen = "NO Filename YET"
def mOpen():
   myopen = askopenfilename()
   return

def CSVmagic(filename):
   call(["Midicsv", filename])
   return

def Hmagic():
   call(["Echo","Hello"])
   return

root = Tk()
w = Label(root, text="Solenoise")

midiCSVTitle = Label(root, text="Convert MIDI to CSV")

MIDIChoiceButton = Button(root, text="Browse file ", command=mOpen)

convertToCSVButton = Button(root, text="Magic", command= lambda: CSVmagic(myopen))

CSVHTitle = Label(root, text="Convert CSV to dot H")

CSVChoiceButton = Button(root, text="Browse file", command=mOpen)

convertToHButton = Button(root, text="Magic", command=Hmagic)

w.pack()
midiCSVTitle.pack()
MIDIChoiceButton.pack()
convertToCSVButton.pack()
CSVHTitle.pack()
CSVChoiceButton.pack()
convertToHButton.pack()

root.mainloop()
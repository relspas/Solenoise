from Tkinter import *
from tkFileDialog import *
from subprocess import call

class Window(Frame):

   def __init__(self, parent):
      Frame.__init__(self, parent)

      self.parent = parent
      self.initUI()

   def initUI(self):
      self.parent.title("Solenoise")
      self.pack(fill=BOTH, expand=1)
      
      w = Label(self, text="Solenoise Converter\n")
      # midiCSVTitle = Label(self, text="\nConvert MIDI to CSV")
      MIDIChoiceButton = Button(self, text="Browse file ", command=self.mOpen)
      convertToCSVButton = Button(self, text="MIDI->CSV", command= self.CSVmagic)
      # CSVHTitle = Label(self, text="\nConvert CSV to dot H")
      # CSVChoiceButton = Button(self, text="Browse file", command=self.mOpen)
      convertToHButton = Button(self, text="CSV->H", command=self.Hmagic)
      convertToCompressedHButton = Button(self, text="H->COMPRESSED H", command=self.CompHmagic)
      self.txt = Text(self)

      w.pack()
      # midiCSVTitle.pack()
      MIDIChoiceButton.pack()
      convertToCSVButton.pack()
      # CSVHTitle.pack()
      # CSVChoiceButton.pack()
      convertToHButton.pack()
      convertToCompressedHButton.pack()

      self.txt.pack(fill=BOTH, expand=1)

   def mOpen(self):
      self.midiFileLocation = askopenfilename()
      if self.midiFileLocation == "":
         self.midiFileLocation = "<NO FILE>"
      self.txt.insert(END, self.midiFileLocation + " selected\n")
      return

   def CSVmagic(self):

      filenameSplit = self.midiFileLocation.split('/')
      filenameParsed = str(filenameSplit[len(filenameSplit)-1])
      filenameExtensionRemoved = filenameParsed[:-4]

      call(["Midicsv", self.midiFileLocation, "csv/"+filenameExtensionRemoved+".txt"])

      self.txt.insert(END, filenameParsed + " converted to CSV. \nNew location: "+\
         "csv/"+filenameExtensionRemoved+".txt\n")
      return

   def Hmagic(self):
      filenameSplit = self.midiFileLocation.split('/')
      filenameParsed = str(filenameSplit[len(filenameSplit)-1])
      self.txt.insert(END, filenameParsed)
      call(["python8.py", "csv/"+filenameParsed, "-1"])
      return

   def CompHmagic(self):
      filenameSplit = self.midiFileLocation.split('/')
      filenameParsed = str(filenameSplit[len(filenameSplit)-1])
      self.txt.insert(END, filenameParsed)
      call(["compress_v2.py", "csv/"+filenameParsed])
      return

def main():
   root = Tk()
   win = Window(root)
   root.mainloop()

if __name__ == '__main__':
   main()
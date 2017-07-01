# Solenoise
midi to embedded system compressed file format converter for windows

Solenoise was a project I made over the summer of 2016 that could robotically play a piano using an Arduino mega and an array of 60 solenoids.
Part of this project required a song to be stored on imbedded hardware, and to be playable by robot fingers. 

This program converts:

+ midi --> csv
+ csv  --> .h
+ .h   --> compressed .h

There is a batch script that performs all of these tasks and places each file that it creates in it's respective folder.

### Convert all on Windows

1. Place music file to convert in folder titled `midi/`
2. Run [`MIDItoCompH.bat`](https://github.com/spacerafe/Solenoise/blob/master/MIDItoCompH.bat)
3. When Prompted, enter name of midi file without .mid extension
4. File will be converted. Csv will reside in `csv/`. h file will be in `H/`. Compressed h file will be in `compressed_h/`.

### midi to csv

midi to csv is done by the included midicsv.exe found [here](http://www.fourmilab.ch/webtools/midicsv/).
This file is included in the source here so it does not need to be downloaded again.

### csv to .h

To use: `python10.py [csv file] [tracks to convert (-1 converts all tracks)]`

Example: `python10.py furelise.csv 2 3 4`

Example: `python10.py furelise.csv -1`

The track numbers are imbedded into the midi/csv file and usually separate instruments.
This feature is handy for removing drums or only selecting piano. Use -1 to select all the tracks.
Other python files are outdated versions of the csv to .h converter.

### .h to compressed .h

To use: `compress_v2.py [dot h file you want to convert]`

The output file will be stored as the same file name with
"\_compressed.h" appended to it                            
                                                           
Example: `compress_v2.py csv/furelise.h`
New file name would be furelise_compressed.h              


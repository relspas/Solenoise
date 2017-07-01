@ECHO off
SET /p midi_file_name="Enter file name you would like to convert (without .mid extension): "
Midicsv midi/%midi_file_name%.mid csv/%midi_file_name%.txt
python10.py csv/%midi_file_name%.txt -1
MOVE /Y csv\%midi_file_name%.h H\
compress_v2.py H\%midi_file_name%.h
MOVE /Y H\%midi_file_name%_compressed.h compressed_h\
PAUSE
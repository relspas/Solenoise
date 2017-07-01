# Raphael Elspas
# Project Solenoise

###################################################################
# This file compresses our Binary format to remove repeted lines. #
###################################################################

#############################################################
# How to use                                                #
# compress.py [dot h file you want to convert]              #
#                                                           #
# The output file will be stored as the same file name with #
# "_compressed.h" appended to it                            #
#                                                           #
# Example                                                   #
# compress.py csv/furelise.h                                #
# New file name would be furelise_compressed.h              #
#############################################################

#################################################################
# Updates: adapts to new dot h format with 5 lines before music #
# array instead of 4. Change the songlength variable at the top #
# to the length of the new music array.                         #
#################################################################

import csv
import sys

uncompressed_file = sys.argv[1]
compressed_file = uncompressed_file[:-2] + "_compressed.h" #removes last 4 chars and appends .h

open_file = open(uncompressed_file, 'r')
write_file = open(compressed_file, 'w')
file_array = []
row_count = 0
past_row = ""
music_array_string = ""
number_of_lines = 0
for curr_row in open_file:
    # Copy first few 4 lines to write file
    row_count = row_count + 1
    if row_count <= 5:
        # write_file.write(curr_row)
        music_array_string += curr_row

    # End of line is semicolon
    elif '}};' in curr_row:
        if row_count == 6:
             # write_file.write(curr_row)
             music_array_string += curr_row
             number_of_lines += 1
        else:
            # If different, write
            if curr_row[:-7] != past_row[:-7]:
                # write_file.write(past_row)
                # write_file.write(curr_row)
                music_array_string += past_row
                music_array_string += curr_row
                number_of_lines += 2

            else: # If the same, change
                multiplicity = past_row[-7:-3]
                
                # Increment multiplicity
                multiplicity_int = int(multiplicity,2) + 1

                # Catching overflow
                if multiplicity_int < 16:
                    multiplicity = "{0:04b}".format(multiplicity_int)
                    # print multiplicity
                    # Chop end off row
                    prepared_row = past_row[:-7]
                    
                    # print prepared_row + multiplicity + "};"
                    # write_file.write(prepared_row + multiplicity + "}};")
                    music_array_string += prepared_row + multiplicity + "}};"
                    number_of_lines += 1
                else:
                    # write_file.write(prepared_row + "1111},")
                    # write_file.write(prepared_row + "0000}};")
                    music_array_string += prepared_row + "1111},"
                    music_array_string += prepared_row + "0000}};"
                    number_of_lines += 2
                

    # End of line is NOT semicolon
    else:
        if row_count == 6:
            past_row = curr_row
        else:
            # If different, write
            if curr_row[:-7] != past_row[:-7]:
                # write_file.write(past_row)
                music_array_string += past_row
                number_of_lines += 1
                past_row = curr_row

            else: # If the same, change

                # Record past multiplicity
                multiplicity = past_row[-7:-3]
                # print multiplicity
                # Increment multiplicity
                multiplicity_int = int(multiplicity,2) + 1
                
                # Catching overflow
                if multiplicity_int < 16:
                    multiplicity = "{0:04b}".format(multiplicity_int)
                    # print multiplicity
                    # Chop end off row
                    prepared_row = past_row[:-7]
                    # print prepared_row + multiplicity + "};"
                    past_row = prepared_row + multiplicity + "},\n"
                    # print past_row
                else:
                    # write_file.write(past_row)
                    music_array_string += past_row
                    number_of_lines += 1
                    past_row = past_row[:-7] + "0000},\n"


before_songlength = music_array_string[:96]
after_songlength = music_array_string[music_array_string.find(";", 96):]
write_file.write(before_songlength + str(number_of_lines) + after_songlength)

#Printed Stats 
print "Old number of rows: "+str(row_count)
print "New number of rows: "+str(number_of_lines)
print "Compression rate: "+("%.0f" % ((1-float(number_of_lines)/float(row_count))*100))+"%"
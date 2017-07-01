import csv
import sys


# duration in midi clocks
duration = 300

# time divisor how fast track is printed
divisor = 10
# range of notes used 48 = C3, 72 = C5
# Inclusive range
lower_range = 70
upper_range = 90

past_note_list = [0] * (upper_range - lower_range + 1)
note_list = [None] * (upper_range - lower_range + 1)

file = open('Beetovenout.txt', 'r')
csv_f = csv.reader(file)
csv_array = []
for row in csv_f:
    csv_array.append(row)

write_file = open('outputBeet.txt', 'w')

for time in range(0, duration):

    for note in range(lower_range, upper_range + 1): 

        for row in csv_array:
        
            # writing new notes
            if (row[2] == " Note_on_c") and (int(row[1])/divisor == int(time)) \
                and (int(row[4]) == note):
                note_list[note - lower_range] = 1
                break
            # removing old note
            elif (row[2] == " Note_off_c") and (int(row[1])/divisor == int(time)) \
                and (int(row[4]) == note):
                note_list[note - lower_range] = 0
                break
            # Holding past notes
            elif past_note_list[note - lower_range] == 0:
                note_list[note - lower_range] = 0
            elif past_note_list[note - lower_range] == 1:
                note_list[note - lower_range] = 1
            else:
                print "strange error"
        # comment out next line to stop after each row
        # raw_input("Press Enter to exit")
    past_note_list = list(note_list)

    # write to screen
    # print "".join(map(str, note_list))
    
    # write to file
    write_file.write(str("".join(map(str, note_list))) + '\n')
    
    # print note_list
    # sys.stdout.write('\n') 
    
file.close()
write_file.close()
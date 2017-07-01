import random
def notePlacement(noteArray):
    arr = []
    for i in range(len(noteArray)):
        if noteArray[i] == 1:
            arr.append(i)
    return arr

print notePlacement([1,0,0,1])

def removeRandom(noteArray, notePlace):
   noteArray[random.choice(notePlace)] = 0
   return noteArray

print removeRandom([1,0,0,1],[0])
# 1 0 0 0 0 0 0 0 0 0 0 0 1
# 0                       12
# C   D   E F   G   A   B C

# 0 1 0 0 0 0 0 0 0 0 0 0 0 1
#   1                       13
# 0 C   D   E F   G   A   B C

# [1,13]
# 13 - 1 = 12 == 12

# [a,b,c,d]
# a - b % 12 == 0

print -(-13)  % 12

# def reduceOctave(noteArray):
#    count = [0] * (12)
#    for x in range(12):
#       while 


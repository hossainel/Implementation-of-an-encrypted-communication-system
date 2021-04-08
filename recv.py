import sys
import string
import time

# TODO implement fonctions uncaesar et recv here

#This function takes an encrypted message and the shift information as a parameter, and returns the message in the clear.
def uncaesar(right_shift, shift, ENCODED_MESSAGES):#{ #the function that will decode the string or the message
    KEY_STRING = string.ascii_uppercase #+' ' # remove the previous hash for adding a space with the decoder.
    TRANSLATED = "" #Decoded Text will save here.
    for i in ENCODED_MESSAGES:#{ #for loop for decoding strings character by character
        j = KEY_STRING.find(i.upper())
        if j==(-1): TRANSLATED = TRANSLATED + i.upper() #returns the previous char if not exixsts at $KEY_STRING
        else:#{ 
            if right_shift: KEY = j+shift #shifting formula
            else: KEY = j-shift
            if KEY>=len(KEY_STRING): KEY = KEY-len(KEY_STRING) #reduce the value if it is greater than the total quantity of alphabets
            TRANSLATED = TRANSLATED + KEY_STRING[KEY]
        #}
    #}
    return TRANSLATED
#}

#This function reads the new messages received in a file.
def recv(right_shift, shift, filename):#{ #The functing that will read message
    r1=0
    if filename[0] == '/': r1 = 1 #Make this line a comment if you got a error
    else: r1 = 0                  #This line too. 
    #with open(filename, "r") as fob:#{ #use hash if you want to remove the following
    with open(filename[r1:], "r") as fob:#{ #opens the file tmp/f105 not /tmp/f105
        while True:#{
            MESSAGES = fob.readline() 
            TRANSLATED = uncaesar(right_shift, shift, MESSAGES) #calls the uncaesar function
            if MESSAGES: print(f"New message: {MESSAGES[:-1].upper()} -> {TRANSLATED[:-1]}")
            time.sleep(1)
        #}
        fob.close()
    #}
#}

#This is the main function
def main():#{
    if len(sys.argv) < 4:#{
        print("Utilization: python recv.py G|D shift file.", file=sys.stderr)
        sys.exit(1)
    #}
    if sys.argv[1] not in ("G", "D"): #{
        print(f"The first argument must be G ou D, {sys.argv[1]} is incorrect", file=sys.stderr)
        sys.exit(1)
    #}
    right_shift: bool = sys.argv[1] == "D"
    shift: int = int(sys.argv[2])
    filename: str = sys.argv[3]
    # TODO the program begins here 
    print(f"Encrypted communication with  Ceasar {sys.argv[1]} {shift} via {filename}")
    recv(right_shift, shift, filename) #the function that will recieve message
#}
if __name__ == "__main__":#{
    main()
#}

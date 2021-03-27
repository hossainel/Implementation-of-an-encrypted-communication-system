import sys
import string
import time

# TODO implement fonctions uncaesar et recv here
def run_decoder(right_shift, shift, filename):#{
    KEY_STRING = string.ascii_uppercase #+' ' # remove the previous hash for adding a space with the decoder.
    TRANSLATED = "" #Decoded Text will save here.
    if filename[0] == '/': r1 = 1 #Check if / included on the first char
    else: r1 = 0
    
    #with open(filename, "r") as fob:#{ #use hash if you want to remove the following
    with open(filename[r1:], "r") as fob:#{ #opens the file tmp/f105 not /tmp/f105
        while True:#{
            MESSAGES = fob.readline() 
            for i in MESSAGES:#{ #for loop for decoding strings
                j = KEY_STRING.find(i.upper())
                if j==(-1): TRANSLATED = TRANSLATED + i.upper() #returns the previous char if not exixsts at $KEY_STRING
                else:#{ 
                    if right_shift: KEY = j+shift
                    else: KEY = j-shift
                    if KEY>=len(KEY_STRING): KEY = KEY-len(KEY_STRING) #reduce the value if it is greater than the total quantity of alphabets
                    TRANSLATED = TRANSLATED + KEY_STRING[KEY]
                #}
            #}
            if MESSAGES: print(f"New message: {MESSAGES[:-1].upper()} -> {TRANSLATED[:-1]}")
            TRANSLATED = "" #Clears the translated string for a new line
            time.sleep(1)
        #}
        fob.close()
    #}
#}
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
    run_decoder(right_shift, shift, filename) #the functing that i added
#}
if __name__ == "__main__":#{
    main()
#}

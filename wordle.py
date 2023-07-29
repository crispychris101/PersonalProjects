import random    # these are the packages that such as random
import sys # this helps with teh actual formating and spacing 
from termcolor import colored # making our words colored
import nltk # we use this for a data set of words to take our wordle guess from 
nltk.download('words')
from nltk import  words
def print_menu():
    print("Hello we are gonna play wordle:")
    print("Type a five letter word and hit enter\n")

def read_random_word(): # # there are two ways we can use a text file or just use the nltk to import a huge databases worth of words
    with open("words.txt") as f:
        words=f.read().splitlines()
        return random.choice(words)
    

nltk.data.path.append('/work/words') # from the data base that contains the words.
word_list=words.words()
words_five=[word for word in word_list if len(word)==5] # this way we make sure that any word we take from teh database is only 5 letters

print_menu()
play_again=""
while play_again != 'q': #q is quit here so if teh user hits q then it exits the program

    #guess=read_random_word()
    guess=random.choice(words_five)# calls that database
    for attempt in range(1,7):
        choice=input().lower()# all lowercase
        sys.stdout.write('\x1b[1a')
        sys.stdout.write('\x1b[2K')  # this erases our prevous guess 

        for i in range(min(len(choice),5)):
            if choice[i]==guess[i]: # if the index at a certain point are the same
                print(colored(guess[i],'green'),end='')
            elif choice[i] in guess: # if its in the word
                print(colored(guess[i],'yellow'),end='')
            else:
                print(choice[i],end='')
        print()
        if choice==guess: # finnaly if they match
            print(colored(f"Congrats you got the wordle in {attempt}",'green'))
            break
        elif attempt==6: # if you try more than  5 times to get the word
            print(f"Sorry the wordle was {guess}")
    play_again=input("want to play again?, otherwise type q to exit:)") # to play again 

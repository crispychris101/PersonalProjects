# here I will make a short program that will make decsions for you, feeling unsure? just ask!
from random import choice
# create a short anime list
action_anime =['Naruto', 'Atack on titan', 'Dragonball', 'Vinland saga']

# print a random anime list 
user_input=input('Whats up, Ill help you pick an anime, you ready(yes/no)?')
if user_input=='yes':
    print('you will watch....', choice(action_anime),"!")
    print(choice(action_anime))
else:
    print('Aw mane that sucks, come back again when you wanna watch one!')




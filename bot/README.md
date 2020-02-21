This is a script for a Discord bot that correct the user they make a bad usage of the homonyms 'sa' or 'ça'

For each message the bot checks if the sentence contains a 'sa' if it does, it will use a function to check if
the next word is a noum.
To check that I made use of HTML parsing; the script will get the HTML code of the web page on the larousse dictionnary
coresponding to the word. With the parsing I am able to be sure if the word is a noum or not and then, return true or false
accordingly.

Commentary in the code are in french.
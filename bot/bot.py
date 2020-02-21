from bs4 import BeautifulSoup
import urllib.request
import os
import discord
import unidecode
import datetime
from dotenv import load_dotenv

TOKEN = #Remplacer par le token du bot

load_dotenv()
client = discord.Client()

def exist(mot):
    mot = unidecode.unidecode(mot)
    strUrl = "https://www.larousse.fr/dictionnaires/francais/" + mot #Accède à la page du dictionaire larousse du mot passé en paramètre
    page = urllib.request.urlopen(strUrl).read() #Récupère le code HTML de la page
    soup = BeautifulSoup(page,'html.parser')
    nom = soup.find('p', {"class": "CatgramDefinition"}) #Regarde en fonction du code HTML si le mot est un nom
    try :
        nom.text
        if nom.text.find('nom') >= 0 : #Retourne vrai ou faux si le mot est un nom commun
            return True
        else :
            return False
    except :
        return False
    return False

@client.event
async def on_message(message):
    if message.author == client.user:
        return
    if 'sa ' in message.content: #Vérifie si 'sa' se trouve dans le message
        text = message.content.split(' ')
        if ( ('sa' in text) & (exist(text[text.index('sa') + 1]))) : #On regarde si le mot suivant le 'sa' est un nom commun ou nom
            return
        await message.channel.send("Sauf erreur de ma part, tu as la mauvaise utilisation de \"sa\".")
        return 
    if message.author == client.user : #Permet au bot de ne pas réagir a ses propres messages
        return

print("Bot en fonction !") 
client.run(TOKEN)
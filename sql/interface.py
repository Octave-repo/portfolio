import tkinter as tk
from tkinter import messagebox
from tkinter import ttk
import tkinter.filedialog
import sqlite3

#DELETE FROM Customers WHERE CustomerName='Alfreds Futterkiste';
class Fichier :
    nom = "base.db"

    def fetch (self, **kw):
        try :
            tab = locals()
            firstTime = True
            tab = tab['kw']
            liste = tab['liste']
            req = "SELECT * FROM " + tab['table']
            for i in tab :
                if (tab[i] != "") & (i != "liste") & (i != "table") & (i != "self"):
                    if (firstTime) :
                        req = req + " WHERE " + tab['table'] + "." + str(i) + " = '" + tab[i] + "'"#On construit la requête avec WHERE, le nom de la variable et sa valeur
                        firstTime = False #Il ne s'agira plus de la première fois
                    else : #Sinon
                        req = str(req) + " AND " + tab['table'] + "." + str(i) + " = '" + tab[i] + "'"
            sqliteConnection = sqlite3.connect(self.nom)
            curseur = sqliteConnection.cursor()
            curseur.execute(req)
            test = curseur.fetchall()
            sqliteConnection.close()
            liste.delete(0, tk.END)
            for i in test :
                print(i)
                liste.insert(tk.END, i)
        except sqlite3.Error as error:
            messagebox.showerror("Error", "Request error " + str(error))
        
    def addClient(self, entClient, liste, nom, prenom, telephone) :
        if (nom == "") | (prenom == "") | (telephone == "") :
            messagebox.showerror("Error", "Toute les cases doivent contenir des données.")
            return
        sqliteConnection = sqlite3.connect(self.nom)
        curseur = sqliteConnection.cursor()
        curseur.execute("SELECT * FROM Client WHERE Client.Telephone = '" + telephone + "'")
        test = curseur.fetchall()
        if test != [] :
            messagebox.showerror("Error", "Numéro de telephone déjà existant")
            return
        curseur.execute("INSERT INTO `Client` ('Nom', 'Prenom', 'Telephone') VALUES ('" + nom + "', '" + prenom + "', '" + telephone + "')")
        sqliteConnection.commit()
        sqliteConnection.close()
        for i in range (0, 3) :
            entClient[i].delete(0, tk.END)
        self.fetch(liste=liste,table = "client", nom="", prenom="", telephone="")

    def delClient(self, liste) :
        try :
            temp = liste.get(liste.curselection())
            sqliteConnection = sqlite3.connect(self.nom)
            curseur = sqliteConnection.cursor()
            curseur.execute("DELETE FROM Client WHERE Client.Nom='" + temp[0] + "' AND Client.Prenom='" + temp[1] + "' AND Client.Telephone ='" + str(temp[2]) + "'")
            sqliteConnection.commit()
            sqliteConnection.close()
            liste.delete(tk.ACTIVE)
        except :
            return    

    def openFile (self) :
        self.nom = tkinter.filedialog.askopenfile( title="Base de donnée ...", filetypes=[('DB','.db')]).name
        #ajouter la création des tables


    def createFile(self) :
        tkinter.filedialog.asksaveasfile(title="Base de donnée ...", filetypes=[('DB','.db')])

root = tk.Tk()
 
style = ttk.Style(root)

#Instancie le fichier
f = Fichier()

#Instancie le notebook
style.configure("uptab.TNotebook", tabposition="wn")
notebook = ttk.Notebook(root, style="lefttab.TNotebook")
 
#Gère le notebook
client = tk.Frame(notebook, width=600, height=500)
commande = tk.Frame(notebook, width=600, height=500)
stock = tk.Frame(notebook, width=600, height=500)

notebook.add(client, text="Client")
notebook.add(commande, text="Commande")
notebook.add(stock, text="Stock")
notebook.grid(row=0, column=0, sticky="nw")

#Gère les menus
menubar = tk.Menu(root)
root.config(menu=menubar)
menufichier = tk.Menu(menubar,tearoff=0)

menubar.add_cascade(label="Fichier", menu=menufichier)
menufichier.add_command(label="Ouvrir",command = lambda: f.openFile())
menufichier.add_command(label="Nouveau",command = lambda: f.createFile())
#menufichier.add_command(label="Afficher", command=lambda:f.fetchClient(listeClient,"", "", ""))

#Gère la frame client
entClient = []
tk.Label(client, text="Nom").grid(row = 0, column = 0)
tk.Label(client, text="Prenom").grid(row = 0, column = 1)
tk.Label(client, text="Telephone").grid(row = 0, column = 2)
for i in range (0, 3) :
        ent = tk.Entry(client)
        ent.grid(row = 1, column = i)
        entClient.append((ent))

listeClient = tk.Listbox(client)
listeClient.grid(row = 3, column = 1)

butt = tk.Button(client, text="Chercher", command = lambda : f.fetch(liste=listeClient,table = "Client", Nom=entClient[0].get(), Prenom=entClient[1].get(), Telephone=entClient[2].get()))
butt.grid(row = 4, column = 1)
butt = tk.Button(client, text="Ajouter", command = lambda : f.addClient(entClient, listeClient, entClient[0].get(), entClient[1].get(), entClient[2].get()))
butt.grid(row = 4, column = 0)
butt = tk.Button(client, text = "Supprimer", command = lambda : f.delClient(listeClient))
butt.grid(row = 4, column = 2)
#mylistbox.get(mylistbox.curselection())

#gère la frame commande

entComCl = []
tk.Label(commande, text="Nom").grid(row = 0, column = 0)
tk.Label(commande, text="Prenom").grid(row = 1, column = 0)
tk.Label(commande, text="Telephone").grid(row = 2, column = 0)
for i in range (0, 3) :
        ent = tk.Entry(commande)
        ent.grid(row = i, column = 1)
        entComCl.append((ent))

listeComCl = tk.Listbox(commande)
listeComCl.grid(row = 4, column = 1)

entComJeu = []
tk.Label(commande, text="Nom").grid(row = 0, column = 3)
tk.Label(commande, text="Prix").grid(row = 1, column = 3)
tk.Label(commande, text="Id").grid(row = 2, column = 3)
for i in range (0, 3) :
        ent = tk.Entry(commande)
        ent.grid(row = i, column = 4)
        entComJeu.append((ent))

listeComJeu = tk.Listbox(commande)
listeComJeu.grid(row = 4, column = 4)

butt = tk.Button(commande, text="Chercher", command = lambda : (f.fetch(liste=listeComCl,table = "Client", Nom=entComCl[0].get(), Prenom=entComCl[1].get(), Telephone=entComCl[2].get()), f.fetch(liste=listeComJeu,table = "Jeu", NomJeu=entComJeu[0].get(), Prix=entComJeu[1].get(), IdJeu=entComJeu[2].get())))
butt.grid(row = 1, column = 2)
root.mainloop()
# MINI FILE SERVER IN C++

## Présentation
Ce projet est un mini serveur de fichiers en C++ utilisant **Boost.Asio**.  
Il sert de projet d’entraînement à la programmation réseau et à la manipulation de fichiers et dossiers en C++ moderne.

## Fonctionnement

Le projet est organisé en plusieurs classes C++ avec chacune son utilité :  

- **Server**  
  C’est l’une des classes fondamentales du projet. Elle gère la connexion des clients sur le serveur Asio.  
  À chaque nouvelle connexion, la classe crée une instance de `Session` pour servir le client connecté et se réarme pour accepter une nouvelle connexion.

- **Session**  
  Cette classe assure la communication (réception et émission) avec un client spécifique.  
  Chaque client connecté possède sa propre session, associée via la classe `Server`.

- **Parser**  
  Cette classe est chargée de décoder les messages envoyés par le client et d’encoder les données à renvoyer.  
  Les messages sont actuellement encodés au format JSON, en utilisant la librairie [nlohmann/json](https://github.com/nlohmann/json).  
  Elle exécute également la commande spécifique demandée par le client en appelant la classe `FileManager`.

- **FileManager**  
  La classe principale pour les opérations sur fichiers et dossiers.  
  Elle reçoit les commandes de `Parser` et effectue les actions correspondantes sur le système de fichiers local.

## Prérequis

Avant de tester le projet, assurez-vous d’avoir les outils suivants installés :  
- **CMake** (pour générer le Makefile)  
- **Compilateur C/C++** (ex : GCC/G++)  
- **Boost.System** (librairie)

## Installation et compilation

1. Cloner le dépôt :  
   ```bash
   git clone https://github.com/Ferdinaelectro1/Mini-File-Server.git
   cd https://github.com/Ferdinaelectro1/Mini-File-Server.git
   ```

2. Créer le dossier de build et se déplacer dedans :  
   ```bash
   mkdir build && cd build
   ```

3. Générer le Makefile avec CMake :  
   ```bash
   cmake ..
   ```

4. Compiler le projet complet :  
   ```bash
   make
   ```

5. Démarrer le serveur :  
   ```bash
   ./mini_file_server
   ```

## Utilisation

Vous pouvez tester les commandes via un client `nc` (netcat) :  

1. Se connecter au serveur :  
   ```bash
   nc 127.0.0.1 12345
   ```

2. Envoyer une commande JSON. Par exemple, pour créer un dossier `testDir` :  
   ```json
   {"cmd" : "createDir","args" : ["testDir"]}
   ```  
   Le dossier sera créé dans le répertoire d’exécution actuel (généralement `build`).

## Contributions

Si vous souhaitez contribuer au projet :  
- Vous pouvez m’écrire directement en DM ou créer une issue sur le dépôt.  
- Plusieurs méthodes de certaines classes ne sont pas encore implémentées. Vous pouvez participer à leur implémentation.



import pandas as pd
import os
import shutil

# Chemin absolu vers le fichier Excel
excel_file_path = r'C:/Users/Geo/Desktop/TABLEAU_XENO3.xlsx'
sheet_name = 'ch020304 (Forms, Heros, Story)'

# Lire la feuille spécifique du fichier Excel avec les en-têtes
df = pd.read_excel(excel_file_path, sheet_name=sheet_name)

# Afficher les premières lignes du DataFrame pour vérifier
print(df.head(10))

# Remplacer les caractères non pris en charge par §
def sanitize_name(name):
    return name.replace('/', '§').replace('\\', '§').replace(':', '§').replace('*', '§').replace('?', '§').replace('"', '§').replace('<', '§').replace('>', '§').replace('|', '§')

# Chemin vers le dossier contenant les fichiers à trier
source_folder = r'C:/Users/Geo/3D Objects/Xenoblade 3 modified/chr/ch - Characters/'

# Fonction pour créer des dossiers et déplacer les fichiers
def create_and_move_files(main_folder_name, col1, col2):
    main_folder_path = os.path.join(source_folder, main_folder_name)

    # Créer le dossier principal s'il n'existe pas
    if not os.path.exists(main_folder_path):
        os.makedirs(main_folder_path)

    for index, row in df.iterrows():
        # Vérifier si les cellules contiennent des données
        if pd.isna(row[col1]) or pd.isna(row[col2]):
            continue  # Passer à la ligne suivante si une des valeurs est manquante

        # Créer le nom du sous-dossier
        sub_folder_name = sanitize_name(f"{row[col1]} ({row[col2]})")
        sub_folder_path = os.path.join(main_folder_path, sub_folder_name)

        # Créer le sous-dossier s'il n'existe pas
        if not os.path.exists(sub_folder_path):
            os.makedirs(sub_folder_path)
            print(f"Dossier créé : {sub_folder_path}")

        # Parcourir tous les fichiers dans le dossier source
        for file_name in os.listdir(source_folder):
            # Vérifier si le nom du fichier contient le texte de la cellule
            if row[col1] in file_name:
                file_path = os.path.join(source_folder, file_name)
                # Déplacer le fichier s'il existe
                if os.path.isfile(file_path):
                    shutil.move(file_path, os.path.join(sub_folder_path, file_name))
                    print(f"Déplacé : {file_name} -> {sub_folder_path}")
                else:
                    print(f"Fichier non trouvé : {file_name}")

# Appeler la fonction pour chaque paire de colonnes
create_and_move_files('Forms', 0, 1)  # Colonnes Forms et Heroes sous le dossier 'Forms'
create_and_move_files('Heroes', 2, 3)  # Colonnes Heroes et Story sous le dossier 'Heroes'
create_and_move_files('Story', 4, 5)  # Colonnes Story et Forms sous le dossier 'Story'
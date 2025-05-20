import pandas as pd
import os
import shutil

EXCEL_PATH = r"C:/Users/Geo/Desktop/TABLEAU_XENO3.xlsx"

# Configuration centrale pour tous les traitements
CONFIGURATIONS = [
    # Configuration for "SORT Main Six (Chx1).py"
    {
        'sheet': 'Main Six (Chx1)',
        'usecols': 'A:L',
        'skiprows': None,
        'source_folder': r'C:/Users/Geo/3D Objects/Xenoblade 3 modified/Xenoblade 3 test/chr/ch - Characters',
        'tasks': [
            {'main_folder': 'Noah', 'cols': [0, 1], 'format': '{0} ({1})'},
            {'main_folder': 'Mio', 'cols': [2, 3], 'format': '{0} ({1})'},
            {'main_folder': 'Eunie', 'cols': [4, 5], 'format': '{0} ({1})'},
            {'main_folder': 'Taion', 'cols': [6, 7], 'format': '{0} ({1})'},
            {'main_folder': 'Lanz', 'cols': [8, 9], 'format': '{0} ({1})'},
            {'main_folder': 'Sena', 'cols': [10, 11], 'format': '{0} ({1})'},
        ]
    },
    
    # Configuration pour "Base Game - Weapons.py"
    {
        'sheet': 'Base Game - wp, en, oj, Maps',
        'usecols': 'E:G',
        'skiprows': [1],
        'source_folder': r'C:/Users/Geo/3D Objects/Xenoblade 3 modified/Xenoblade 3 test/chr/wp - Weapons',
        'tasks': [
            {'main_folder': 'Weapons', 'cols': [4, 5, 6], 'format': '{0} ({1} - {2})'}
        ]                                  # E=4, F=5, G=6 (0-based)
    },
    
    # Configuration pour "TRI ch020304 (Forms, Heros, Story).py"
    {
        'sheet': 'ch020304 (Forms, Heros, Story)',
        'usecols': None,
        'skiprows': None,
        'source_folder': r'C:/Users/Geo/3D Objects/Xenoblade 3 modified/Xenoblade 3 test/chr/ch - Characters',
        'tasks': [
            {'main_folder': 'Forms', 'cols': [0, 1], 'format': '{0} ({1})'},
            {'main_folder': 'Heroes', 'cols': [2, 3], 'format': '{0} ({1})'},
            {'main_folder': 'Story', 'cols': [4, 5], 'format': '{0} ({1})'}
        ]
    }
]

def sanitize_name(name):
    """Nettoie les noms de dossier des caractères spéciaux"""
    replace_chars = ['/', '\\', ':', '*', '?', '"', '<', '>', '|']
    for char in replace_chars:
        name = name.replace(char, '§')
    return name

def process_configurations():
    for config in CONFIGURATIONS:
        try:
            # Lecture du DataFrame
            df = pd.read_excel(EXCEL_PATH, sheet_name=config['sheet'], usecols=config['usecols'], skiprows=config['skiprows'], header=0 if config['skiprows'] is None else None)
            
            print(f"\nProcessing sheet: {config['sheet']}")
            print(df.head(10))

            # Traitement pour chaque tâche dans la configuration
            for task in config['tasks']:
                main_folder = os.path.join(config['source_folder'], task['main_folder'])
                
                # Création du dossier principal
                os.makedirs(main_folder, exist_ok=True)
                
                # Parcours des lignes du DataFrame
                for _, row in df.iterrows():
                    # Vérification des valeurs manquantes
                    if any(pd.isna(row.iloc[col]) for col in task['cols']):
                        continue
                    
                    # Création du nom du sous-dossier
                    parts = [str(row.iloc[col]) for col in task['cols']]
                    sub_name = sanitize_name(task['format'].format(*parts))
                    sub_folder = os.path.join(main_folder, sub_name)
                    
                    # Création du sous-dossier
                    os.makedirs(sub_folder, exist_ok=True)
                    
                    # Déplacement des fichiers correspondants
                    for file in os.listdir(config['source_folder']):
                        file_path = os.path.join(config['source_folder'], file)
                        if os.path.isfile(file_path):
                            if any(str(row.iloc[col]) in file for col in task['cols']):
                                try:
                                    shutil.move(file_path, os.path.join(sub_folder, file))
                                    print(f"Déplacé : {file} -> {sub_folder}")
                                except shutil.Error as e:
                                    print(f"Erreur lors du déplacement de {file}: {e}")
        except Exception as e:
            print(f"Erreur lors du traitement de la configuration {config['sheet']}: {str(e)}")
            continue

if __name__ == '__main__':
    process_configurations()
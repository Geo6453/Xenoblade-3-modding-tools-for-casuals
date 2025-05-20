import pandas
import os
import shutil
import pathlib

config = [
    # Configuration for "Main Six (Chx1)"
    {
        'sheet': 'Main Six (Chx1)',
        'usecols': 'A:L',
        'skiprows': None,
        'location_path': r'chr\\ch',
        'tasks':
        [
            {'new_folder': 'Noah',     'cols': [0, 1], 'format': '{0} ({1})'},
            {'new_folder': 'Mio',      'cols': [2, 3], 'format': '{0} ({1})'},
            {'new_folder': 'Eunie',    'cols': [4, 5], 'format': '{0} ({1})'},
            {'new_folder': 'Taion',    'cols': [6, 7], 'format': '{0} ({1})'},
            {'new_folder': 'Lanz',     'cols': [8, 9], 'format': '{0} ({1})'},
            {'new_folder': 'Sena',     'cols': [10, 11], 'format': '{0} ({1})'},
        ]
    },

    # Configuration for "ch02/03/04 (Forms, Heros, Story)"
    {
        'sheet': 'ch020304 (Forms, Heros, Story)',
        'usecols': 'A:E',
        'skiprows': None,
        'location_path': r'chr\\ch',
        'tasks':
        [
            {'new_folder': 'Forms',    'cols': [0, 1], 'format': '{0} ({1})'},
            {'new_folder': 'Heroes',   'cols': [2, 3], 'format': '{0} ({1})'},
            {'new_folder': 'Story',    'cols': [4, 5], 'format': '{0} ({1})'}
        ]
    },

    # Configuration for "Base Game - wp, en, oj, Maps"
    {
        'sheet': 'Base Game - wp, en, oj, Maps',
        'usecols': 'E:G',
        'skiprows': [1, 2],
        'location_path': r'chr\\wp',
        'tasks':
        [
            #{'new_folder': 'Enemies', 'cols': [0, 1, 2], 'format': '{0} ({1} - {2})'},
            {'new_folder': 'Weapons', 'cols': [4, 5, 6], 'format': '{0} ({1} - {2})'},
            #{'new_folder': 'Objects', 'cols': [8, 9, 10], 'format': '{0} ({1} - {2})'}
        ]
    },
]

def sanitize_name(name):
    # Clean folder's name of special characters and replace by "§"
    replace_chars = ['/', '\\', ':', '*', '?', '"', '<', '>', '|']
    for char in replace_chars:
        name = name.replace(char, '§')
    return name

def process_configurations():
    try:
        df = pandas.read_excel(
            excel_path,
            sheet_name=config['sheet'],
            usecols=config['usecols'],
            skiprows=config['skiprows'],
            header=0)
        print(f"\nProcessing sheet: {config['sheet']}")
        print(df.head(10))

        for task in config['tasks']:
            created_folder = os.path.join('game_path', 'location_path', task['new_folder'])
            os.makedirs(created_folder, exist_ok=True)
            
            # Read DataFrame's lines
            for _, row in df.iterrows():
                # Check empty cells
                if any(pandas.isna(row.iloc[col]) for col in task['cols']):
                    continue
                
                # Create subfolders
                parts = [str(row.iloc[col]) for col in task['cols']]
                sub_name = sanitize_name(task['format'].format(*parts))
                sub_folder = os.path.join(created_folder, sub_name)
                os.makedirs(sub_folder, exist_ok=True)
                
                # Move the files
                for file in os.listdir(config['game_path']):
                    file_path = os.path.join(config['game_path'], file)
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

game_chosen = input("Which game did you want to sort ? (XB1, XB1:DE, XBX, XBX:DE, XB2, XB3) : ")
print("Download the followed files where you want.")
print("https://docs.google.com/spreadsheets/d/12wgzG4gIgd8iY6GyYw_ObsUTDjE0ZvE2CMNtX5WrWzs")
print("Where did you stored the sheet ?")

excel_path = input("Copy & Paste the absolute excel path here like this (C:\\Users\\Geo\\Downloads\\Xenoblade 3 Models - Spoilers.xlsx) : ")
path = pathlib.Path(excel_path)
print("Sheet is found ? :", path.exists())

game_path = input("Where is {} that you have extracted with Xbtool ? (by exemple : C:\\Users\\Geo\\Downloads\\Xenoblade 3 extracted) : ".format(game_chosen))
path = pathlib.Path(game_path)
print("Game is found ? :", path.exists())

process_configurations()
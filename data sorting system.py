import pandas
import os
import shutil
import pathlib

CONFIGURATIONS = [
    # Configuration for "Main Six (Chx1)"
    {
        'sheet': 'Main Six (Chx1)',
        'usecols': 'A:L',
        'skiprows': None,
        'location_path': r'chr\ch',
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
        'location_path': r'chr\ch',
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
        'location_path': r'chr\wp',
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

def process(config, excel_path, game_path):
    try:
        df = pandas.read_excel(
            excel_path,
            sheet_name=config['sheet'],
            usecols=config['usecols'],
            skiprows=config['skiprows'],
            header=0 if config['skiprows'] is None else None)
        print(f"\nProcessing sheet: {config['sheet']}")
        print(df.head(5)) # Show first 5 rows for preview

        for task in config['tasks']:
            created_folder = os.path.join(game_path, config['location_path'], task['new_folder'])
            os.makedirs(created_folder, exist_ok=True)
            
            # Read DataFrame's lines
            for _, row in df.iterrows():
                # Check empty cells
                if any(pandas.isna(row.iloc[col]) for col in task['cols']):
                    continue
                
                # Create subfolders
                parts = [str(row.iloc[col]) for col in task['cols']]
                        # Take value of cell        Use columns pecified on 'task'
                        # If the Excel's line contain ["Noah" | "Hero"] and task['cols'] = [0, 1], then parts = ["Noah", "Hero"]
                sub_name = sanitize_name(task['format'].format(*parts))
                        # If parts = ["Noah", "Hero"] and format = "{0} ({1})", then sub_name = "Noah (Hero)"
                sub_folder = os.path.join(created_folder, sub_name)
                os.makedirs(sub_folder, exist_ok=True)

                # Move matching files
                for file in os.listdir(game_path):
                    file_path = os.path.join(game_path, file)
                    if os.path.isfile(file_path):
                        if any(str(row.iloc[col]) in file for col in task['cols']): # Check if the file is the one expected
                            try:
                                shutil.move(file_path, os.path.join(sub_folder, file))
                                print(f"Déplacé : {file} -> {sub_folder}")
                            except shutil.Error:
                                print(f"Erreur lors du déplacement de {file}: {shutil.Error}")
    except Exception as e:
        print(f"Error processing {config['sheet']}: {str(e)}")

def main():
    game_chosen = input("Which game did you want to sort ? (XB1, XB1:DE, XBX, XBX:DE, XB2, XB3) : ")
    print("Download the following file wherever you want.")
    print("https://docs.google.com/spreadsheets/d/12wgzG4gIgd8iY6GyYw_ObsUTDjE0ZvE2CMNtX5WrWzs")
    print("Where did you stored the sheet ?")

    print("By exemple : C:\\Users\\Geo\\Downloads\\Xenoblade 3 Models - Spoilers.xlsx")
    excel_path = input("Excel file path: ")
    if not pathlib.Path(excel_path).exists():
        print("Error: Excel file not found!")
        return
    
    print("By exemple : C:\\Users\\Geo\\Downloads\\Xenoblade 3 extracted")
    game_path = input(f"Extracted game files path for {game_chosen}: ")
    if not pathlib.Path(game_path).exists():
        print("Error: Game folder not found!")
        return
    
    for config in CONFIGURATIONS:
        process(config, excel_path, game_path)
    
    print("\nFile organization completed!")

if __name__ == "__main__":
    main()
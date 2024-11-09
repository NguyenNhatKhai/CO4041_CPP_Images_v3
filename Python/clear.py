#

import os

folders = ['./Channel', './Decoder', './Encoder', './Image', './Output', './Sink', './Source']
files_to_exclude = ['image_0.png']

for folder_path in folders:
    if not os.path.isdir(folder_path):
        continue
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            if file not in files_to_exclude:
                file_path = os.path.join(root, file)
                os.remove(file_path)
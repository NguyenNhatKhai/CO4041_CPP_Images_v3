#

import sys
from PIL import Image
from constant import *
            
def txt_to_png(txt_path, png_path):
    png_file = Image.new('RGB', (IMAGE_WIDTH, IMAGE_HEIGHT))
    pixels = []
    with open(txt_path + '.txt', 'r') as txt_file:
        content = txt_file.read()
        for i in range(0, len(content), 24):
            r = int(content[i : i + 8], 2)
            g = int(content[i + 8 : i + 16], 2)
            b = int(content[i + 16 : i + 24], 2)
            pixels.append((r, g, b))
    png_file.putdata(pixels)
    png_file.save(png_path + '.png')

if __name__ == "__main__":
    txt_to_png(sys.argv[1], sys.argv[2])
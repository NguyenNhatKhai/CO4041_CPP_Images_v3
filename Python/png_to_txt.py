#

import sys
from PIL import Image
from constant import *

def png_to_txt(png_path, txt_path):
    png_file = Image.open(png_path + '.png').convert('RGB')
    with open(txt_path + '.txt', 'w') as txt_file:
        for i in range(IMAGE_HEIGHT):
            for j in range(IMAGE_WIDTH):
                r, g, b = png_file.getpixel((j, i))
                txt_file.write(f'{format(r, '08b')}{format(g, '08b')}{format(b, '08b')}')

if __name__ == "__main__":
    png_to_txt(sys.argv[1], sys.argv[2])
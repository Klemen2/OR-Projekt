from PIL import Image, ImageFont, ImageDraw
import argparse
import math
import re
import time
import textwrap
import regex

source_file = True

font_include = "fonts.h"

# Greyscale threshold from 0 - 255
THRESHOLD = 128
# Font Character Set
CHAR_SET = '↑↓←→'

font_file = "Danfo.ttf"
font_height = 32
output_file_name = "arrows" # None

x_offset = 0
y_offset = 10


def get_charset_perceived():
    # https://stackoverflow.com/questions/6805311/playing-around-with-devanagari-characters
    return regex.findall(r'\X', CHAR_SET)


def get_max_width(font):
    max_width = 0
    for ch in get_charset_perceived():  # Assuming get_charset_perceived() returns characters you want to measure
        # Use the getmask method to get the rendered size of the character
        mask = font.getmask(ch)
        width, _ = mask.size
        if width > max_width:
            max_width = width
    return max_width


def bin_to_c_hex_array(bin_text, bytes_per_line, lsb_padding=0, msb_padding=0):
    # create comment with preview of line
    comment = bin_text.replace('0', ' ').replace('1', '#')

    # pad the top or bottom remaining bits with 0's
    bin_text = ("0" * msb_padding) + bin_text + ("0" * lsb_padding)
    # ensure the length matches the number of bytes
    assert len(bin_text) == (bytes_per_line * 8)

    # split up into 8 digits each of bytes
    bin_list = re.findall('.{8}', bin_text)
    # convert to hex representation
    bin_list = map(lambda a: "0x{:02X}".format(int(a, 2)), bin_list)
    array = ', '.join(bin_list)

    return f'{array}, /* |{comment}| */\r\n'


def generate_font_data(font, x_size, y_size):
    data = ''

    # find bytes per line needed to fit the font width
    bytes_per_line = math.ceil(x_size / 8)
    empty_bit_padding = (bytes_per_line * 8 - x_size)

    for i, ch in enumerate(get_charset_perceived()):
        # the starting array index of the current char
        array_offset = i * (bytes_per_line * y_size)
        assert data.count('0x') == array_offset

        # comment separator for each char
        data += '\r\n'
        data += f"// @{array_offset} '{ch}' ({font_width} pixels wide)\r\n"

        mask = font.getmask(ch)
        w, h = mask.size
        x_margin = (x_size - (w + x_offset)) // 2
        y_margin = (y_size - (h + y_offset)) // 2
        margin = (x_margin, y_margin)
        im_size = (x_size, y_size)

        # create image and write the char
        im = Image.new("RGB", im_size)
        drawer = ImageDraw.Draw(im)
        drawer.text(margin, ch, font=font)
        del drawer

        # for each row, convert to hex representation
        for y in range(y_size):
            # get list of row pixels
            x_coordinates = range(x_size)
            pixels = map(lambda x: im.getpixel((x, y))[0], x_coordinates)
            # convert to bin text
            bin_text = map(lambda val: '1' if val > THRESHOLD else '0', pixels)
            bin_text = ''.join(bin_text)
            # convert to c-style hex array
            data += bin_to_c_hex_array(bin_text, bytes_per_line,
                                       lsb_padding=empty_bit_padding)
    return data


def output_files(font, font_width, font_height, font_data, font_name, filename):
    generated_time = time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime())

    if not filename:
    # create filename, remove invalid chars
        filename = f'Font{font_name}{font_height}'
        filename = ''.join(c if c.isalnum() else '' for c in filename)

    if source_file:
        ext = "c"
        extras = f'#include "{font_include}"'
    else:
        ext = "h"
        extras = f'#pragma once\n#include "{font_include}"\n#define {filename}_Name ("{font_name} {font_height}px")'
    
    # C file template
    output = f"""/**
 * This file provides '{font_name}' [{font_height}px] text font
 * for STM32xx-EVAL's LCD driver.
 *
 * Generated on {generated_time} UTC
 *
 * Generated with https://github.com/Klemen2/OR-Projekt/tree/main/STM32-LCD_Font_Generator
 * Based on: https://github.com/zst-embedded/STM32-LCD_Font_Generator
 */
{extras}

// {font_data.count('0x')} bytes
const uint8_t {filename}_Table [] = {{{font_data}}};

sFONT {filename} = {{
    {filename}_Table,
    {font_width}, /* Width */
    {font_height}, /* Height */
}};
"""
        
    with open(f'{filename}.{ext}', 'w') as f:
        f.write(output)

    mask = font.getmask(CHAR_SET)
    size = tuple(sum(v) for v in zip(mask.size, (x_offset, y_offset)))
    im = Image.new("RGB", size)
    drawer = ImageDraw.Draw(im)
    drawer.text((0, 0), CHAR_SET, font=font)
    im.save(f'{filename}.png')
    

def str2bool(v):
    if isinstance(v, bool):
        return v
    if v.lower() in ('yes', 'true', 't', 'y', '1'):
        return True
    elif v.lower() in ('no', 'false', 'f', 'n', '0'):
        return False
    else:
        raise argparse.ArgumentTypeError('Boolean value expected.')

if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='Generate text font for STM32xx-EVAL\'s LCD driver')

    parser.add_argument('-f', '--font',
                        type=str,
                        help='Font type [filename]',
                        required=False)
    parser.add_argument('-s', '--size',
                        type=int,
                        help='Font size in pixels [int]',
                        required=False)
    parser.add_argument('-n', '--name',
                        type=str,
                        help='Custom font name [str]',
                        required=False)
    parser.add_argument('-c', '--charset',
                        type=str,
                        help='Custom charset from file [filename]',
                        required=False)
    parser.add_argument('-x', '--offsetx',
                        type=int,
                        help='Character x offset',
                        required=False)
    parser.add_argument('-y', '--offsety',
                        type=int,
                        help='Character y offset',
                        required=False)
    parser.add_argument('-sf', '--source_file',
                        type=str2bool,
                        help='Generate source file (.c)',
                        default=None,
                        required=False)
    args = parser.parse_args()

    if args.charset:
        with open(args.charset) as f:
            CHAR_SET = f.read().splitlines()[0]

    if args.font:
        font_file = args.font
    if args.size:
        font_height = args.size    
    if isinstance(args.offsety,int):
        y_offset = args.offsety
    if isinstance(args.offsetx, int):
        x_offset = args.offsetx
    if args.name:
        output_file_name = args.name
    if args.source_file != None:
        source_file = args.source_file
    

    myfont = ImageFont.truetype(font_file, size=font_height)
    font_width = get_max_width(myfont)

    font_name = myfont.font.family

    # generate the C file data
    font_data = generate_font_data(myfont, font_width, font_height)
    font_data = textwrap.indent(font_data, ' ' * 4)

    # output everything
    output_files(font=myfont,
                 font_width=font_width,
                 font_height=font_height,
                 font_data=font_data,
                 font_name=font_name, 
                 filename=output_file_name)
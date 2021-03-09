# this script is meant to be run on its own
# virtual environment where Pillow is installed

from hsvRainbow import *
from PIL import Image, ImageDraw

rainbowHeight = 100
drawSpace = 10
graphHeight = 255

def drawR1(draw):
    y = 0
    for i in range(len(r1)):
        x = i
        draw.line((x, y, x, y + rainbowHeight), fill=(r1[i], g1[i], b1[i]), width=1)

    y = rainbowHeight + drawSpace - 1
    for i in range(len(r1) - 1):
        x = i
        draw.line((x, y + 255 - r1[i], x, y + 255 - r1[i + 1]), fill=(255, 0, 0), width=1)
        draw.line((x, y + 255 - g1[i], x, y + 255 - g1[i + 1]), fill=(0, 255, 0), width=1)
        draw.line((x, y + 255 - b1[i], x, y + 255 - b1[i + 1]), fill=(0, 0, 255), width=1)

def drawR2(draw):
    y = 0
    for i in range(len(r3)):
        x = i
        draw.line((x, y, x, y + rainbowHeight), fill=(r3[i], g3[i], b3[i]), width=1)

    y = rainbowHeight + drawSpace - 1
    for i in range(len(r3) - 1):
        x = i
        draw.line((x, y + 255 - r3[i], x, y + 255 - r3[i + 1]), fill=(255, 0, 0), width=1)
        draw.line((x, y + 255 - g3[i], x, y + 255 - g3[i + 1]), fill=(0, 255, 0), width=1)
        draw.line((x, y + 255 - b3[i], x, y + 255 - b3[i + 1]), fill=(0, 0, 255), width=1)

def drawR3(draw):
    y = 0
    for i in range(len(r1)):
        x = i
        draw.line((x, y, x, y + rainbowHeight), fill=(r1[i], g1[i], b1[i]), width=1)

    y += rainbowHeight + drawSpace
    for i in range(len(r2)):
        x = i
        draw.line((x, y, x, y + rainbowHeight), fill=(r2[i], g2[i], b2[i]), width=1)

    y += rainbowHeight + drawSpace
    for i in range(len(r3)):
        x = i
        draw.line((x, y, x, y + rainbowHeight), fill=(r3[i], g3[i], b3[i]), width=1)

    y += rainbowHeight + drawSpace
    for i in range(len(r4)):
        x = i
        draw.line((x, y, x, y + rainbowHeight), fill=(r4[i], g4[i], b4[i]), width=1)

    y += rainbowHeight + drawSpace
    for i in range(len(gg)):
        x = 3 * i - 1
        draw.line((x, y + 255, x, y + 255 - gg[i]), fill=(0, 0, 0xFF), width=2)

imgWidth = 765
imgHeight = rainbowHeight + drawSpace + graphHeight

img = Image.new("RGB", (imgWidth, imgHeight), (16, 16, 16))
draw = ImageDraw.Draw(img)
drawR1(draw)
img.save("hsvRainbow.png")
del draw
del img

img = Image.new("RGB", (imgWidth, imgHeight), (16, 16, 16))
draw = ImageDraw.Draw(img)
drawR2(draw)
img.save("hsvRainbowCL.png")
del draw
del img

imgHeight = 4 * (rainbowHeight + drawSpace) + 255
img = Image.new("RGB", (imgWidth, imgHeight), (16, 16, 16))
draw = ImageDraw.Draw(img)
drawR3(draw)
img.save("hsvRainbowGamma.png")
del draw
del img

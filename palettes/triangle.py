import imgen
import math


class Palette(imgen.Palette):
    def __init__(self):
        super().__init__()

        base = imgen.random_hsl()
        hues = [
            base[0],
            base[0] + 0.33,
            base[0] - 0.33
        ]

        for hue in hues:
            if hue < 0.0 or hue > 1.0:
                hue -= math.floor(hue)

            self.colors.append(
                imgen.hsl2rgb(imgen.hsl(hue, base[1], base[2]))
            )

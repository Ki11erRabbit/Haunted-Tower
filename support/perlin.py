import math
import random

def gradient(h):
    """Generate random gradient vector."""
    return math.cos(h), math.sin(h)

def lerp(a, b, x):
    """Linear interpolation."""
    return a + x * (b - a)

def fade(t):
    """Smoothstep interpolation."""
    return t * t * t * (t * (t * 6 - 15) + 10)

def perlin(x, y, grid_size, seed):
    """Compute Perlin noise for coordinates (x, y)."""
    x0, y0 = int(x // grid_size), int(y // grid_size)
    x1, y1 = x0 + 1, y0 + 1

    dx, dy = x / grid_size - x0, y / grid_size - y0

    random.seed(seed)
    gradients = {}
    gradients[(x0, y0)] = gradient(random.random() * 2 * math.pi)
    gradients[(x1, y0)] = gradient(random.random() * 2 * math.pi)
    gradients[(x0, y1)] = gradient(random.random() * 2 * math.pi)
    gradients[(x1, y1)] = gradient(random.random() * 2 * math.pi)

    dot00, dot10 = gradients[(x0, y0)][0]*dx + gradients[(x0, y0)][1]*dy, gradients[(x1, y0)][0]*(dx-1) + gradients[(x1, y0)][1]*dy
    dot01, dot11 = gradients[(x0, y1)][0]*dx + gradients[(x0, y1)][1]*(dy-1), gradients[(x1, y1)][0]*(dx-1) + gradients[(x1, y1)][1]*(dy-1)

    u, v = fade(dx), fade(dy)

    return lerp(lerp(dot00, dot10, u), lerp(dot01, dot11, u), v)



def print_source(suffix, seed):
    print(f"const int8_t perlin_noise{suffix}[] = {{")
    for y in range(0, 16):
        print("    ", end="")
        for x in range(0, 8):
            result = perlin(x, y, 127, seed)
            result = int(result * 1000)
            if result > 127:
                result = result % 127
            elif result < -128:
                result = result % -128
            end = ","
            if y == 15 and x == 7:
                end = ""
            print(f"{result}".rjust(4), end=end)
        print()
    print("};")
    return f"perlin_noise{suffix}"

print_source(0, 0)

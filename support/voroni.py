import math
import random
import argparse

def euclidean_distance(x1, y1, x2, y2):
    """Calculate Euclidean distance between two points."""
    dx = x2 - x1
    dy = y2 - y1
    return math.sqrt(dx * dx + dy * dy)

def voronoi(x, y, grid_size, num_points, seed):
    """Compute Voronoi noise for coordinates (x, y)."""
    random.seed(seed)
    
    # Generate random points
    points = []
    for i in range(num_points):
        px = random.uniform(0, grid_size)
        py = random.uniform(0, grid_size)
        points.append((px, py))
    
    # Wrap coordinates for tiling
    x_wrapped = x % grid_size
    y_wrapped = y % grid_size
    
    # Find minimum distance considering tiling (check 9 tiles)
    min_dist = float('inf')
    second_min_dist = float('inf')
    
    for tile_x in [-grid_size, 0, grid_size]:
        for tile_y in [-grid_size, 0, grid_size]:
            for px, py in points:
                dist = euclidean_distance(x_wrapped, y_wrapped, px + tile_x, py + tile_y)
                if dist < min_dist:
                    second_min_dist = min_dist
                    min_dist = dist
                elif dist < second_min_dist:
                    second_min_dist = dist
    
    # Return F1 (closest distance) or F2-F1 (edge distance)
    # Using F2-F1 gives cell edge emphasis
    return second_min_dist - min_dist

def print_source(suffix, seed, num_points=8, use_edges=True):
    """Generate C code for Voronoi noise map."""
    print(f"const int8_t voronoi_noise{suffix}[] = {{")
    
    # Pre-calculate max value for normalization
    max_val = 0
    values = []
    for y in range(32):
        row = []
        for x in range(32):
            result = voronoi(x, y, 32, num_points, seed)
            row.append(result)
            max_val = max(max_val, result)
        values.append(row)
    
    # Generate C array
    for y in range(32):
        print("    ", end="")
        for x in range(32):
            result = values[y][x]
            # Normalize to -128 to 127 range
            normalized = int((result / max_val) * 127) if max_val > 0 else 0
            
            end = ","
            if y == 31 and x == 31:
                end = ""
            print(f"{normalized}".rjust(4), end=end)
        print()
    
    print("};")
    return f"voronoi_noise{suffix}"

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        prog="Tiled Voronoi Noise",
        description="Generates a C file that contains a Voronoi noise map for use in GBDK"
    )
    parser.add_argument("suffix", help="Suffix for the array name")
    parser.add_argument("-s", "--seed", help="Random seed for generation")
    parser.add_argument("-p", "--points", type=int, default=8, 
                       help="Number of Voronoi points (default: 8)")
    
    args = parser.parse_args()
    
    seed = args.seed
    if seed is None:
        seed = random.randrange(2 ** 64)
    else:
        seed = int(seed)
    
    print_source(args.suffix, seed, args.points)

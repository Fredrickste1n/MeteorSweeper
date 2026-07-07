# generate_resources.py
import os
import sys

def sanitize_name(filename):
    """Turn 'player.png' into 'player_png' for use as a C variable name"""
    name = os.path.splitext(filename)[0]
    ext = os.path.splitext(filename)[1].replace('.', '')
    safe = ''.join(c if c.isalnum() else '_' for c in name)
    return f"{safe}_{ext}"

def generate_header(folder, output_file):
    with open(output_file, 'w') as out:
        out.write("// Auto-generated file - do not edit manually\n")
        out.write("#pragma once\n\n")

        for filename in sorted(os.listdir(folder)):
            filepath = os.path.join(folder, filename)
            if not os.path.isfile(filepath):
                continue
            if not filename.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp')):
                continue

            varname = sanitize_name(filename)
            with open(filepath, 'rb') as f:
                data = f.read()

            out.write(f"static unsigned char {varname}[] = {{\n")
            out.write(",".join(str(b) for b in data))
            out.write("\n};\n")
            out.write(f"static unsigned int {varname}_size = {len(data)};\n\n")

        print(f"Generated {output_file}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python generate_resources.py <textures_folder> <output_header.h>")
        sys.exit(1)

    generate_header(sys.argv[1], sys.argv[2])

# run this line in ssh: python generate_resources.py textures/ resources.h
import os
import shutil

# Define source and destination directories
source_dir = "build"
destination_dir = "build/eDepMaps"

# Loop through all files in the source directory
for filename in os.listdir(source_dir):
    if filename.endswith(".txt") and "gamma_25GeV" in filename:
        parts = filename.split('_')  # Split filename by underscore
        number = parts[0]  # Extract the number part from the filename
        i, j = parts[-1].split('.')[0].split(',')  # Extract the i and j values

        # Create destination directory if it doesn't exist
        dest_folder = os.path.join(destination_dir, f"{i},{j}")
        os.makedirs(dest_folder, exist_ok=True)

        # Copy the file to the destination folder
        shutil.move(os.path.join(source_dir, filename), dest_folder)

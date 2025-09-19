#!/usr/bin/env python3

# Read the file
with open('src/backend/vm.cpp', 'r') as f:
    lines = f.readlines()

# Find the end of the original methods (around line 4577)
# Look for the line that contains "Cannot access property" and the closing brace
end_line = -1
for i, line in enumerate(lines):
    if "Cannot access property" in line and "on non-object value" in line:
        # Look for the closing brace after this line
        for j in range(i, min(i + 10, len(lines))):
            if lines[j].strip() == '}':
                end_line = j + 1
                break
        break

if end_line == -1:
    print("Could not find the end of original methods")
    exit(1)

print(f"Found end of original methods at line {end_line + 1}")

# Write the file up to that point
with open('src/backend/vm.cpp', 'w') as f:
    f.writelines(lines[:end_line])

print("Removed duplicate methods")
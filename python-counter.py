import time
from collections import defaultdict

filename = input("Enter the file name: ")
print(filename)

# Initialize the tournament counts dictionary
tournament_counts = defaultdict(int)
tournament_counts.update({
    "Blitz_tournaments": 0,
    "Bullet_tournaments": 0,
    "Rapid_tournaments": 0,
    "UltraBullet_tournaments": 0,
    "Classical_tournaments": 0,
    "Blitz_non_tournaments": 0,
    "Bullet_non_tournaments": 0,
    "Rapid_non_tournaments": 0,
    "UltraBullet_non_tournaments": 0,
    "Classical_non_tournaments": 0
})

number_of_tournaments = 0

# Open the input and output files
with open(filename, 'r') as file, open("out-p.txt", 'w') as outfile:
    start = time.time()  # Start the timer
    line_count = 0

    # Process each line in the file
    for line in file:
        line_count += 1
        if len(line) > 6 and line[1:6] == "Event":
            if "tournament" in line:
                number_of_tournaments += 1
                if "Blitz" in line:
                    tournament_counts["Blitz_tournaments"] += 1
                elif " Bullet" in line:
                    tournament_counts["Bullet_tournaments"] += 1
                elif "Rapid" in line:
                    tournament_counts["Rapid_tournaments"] += 1
                elif "UltraBullet" in line:
                    tournament_counts["UltraBullet_tournaments"] += 1
                elif "Classical" in line:
                    tournament_counts["Classical_tournaments"] += 1
            else:
                if "Blitz" in line:
                    tournament_counts["Blitz_non_tournaments"] += 1
                elif " Bullet" in line:
                    tournament_counts["Bullet_non_tournaments"] += 1
                elif "Rapid" in line:
                    tournament_counts["Rapid_non_tournaments"] += 1
                elif "UltraBullet" in line:
                    tournament_counts["UltraBullet_non_tournaments"] += 1
                elif "Classical" in line:
                    tournament_counts["Classical_non_tournaments"] += 1

    end = time.time()  # End the timer

    # Write line count to the output file
    outfile.write(str(line_count))

# Print results
print(f"Number of lines in the file: {line_count}")
print(f"Number of tournaments in the file: {number_of_tournaments}")
for key, value in tournament_counts.items():
    print(f"{key} : {value}")

print(f"Time taken: {end - start} seconds")

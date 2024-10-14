import time

filename = input("Enter the file name: ")


start_time = time.time()
line_count=0
with open(filename, 'r') as file:
    for i in file:
        if("[Event" in i):
            if("tournament" in i):
                line_count = line_count +1

end_time = time.time()
with open("out-p.py","w") as file:
    file.write(str(line_count))


print(f"Number of lines in the file: {line_count}")
print(f"Time taken: {end_time - start_time} seconds")

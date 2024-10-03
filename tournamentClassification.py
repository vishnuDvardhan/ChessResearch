import io
import sys
import re
import time
import numpy as np
file = open('out.txt','w')
def tournament_counter():
    counts={"Blitz":0,"Bullet":0,"Rapid":0,"UltraBullet":0,"Classical":0}
    tournamentcount=0
    start = time.time()
    pattern1 = re.compile(r'^\[Event\s+".*tournament.*"\]$')
    pattern2 =re.compile(r"(\w+)\s+tournament")
    for line in sys.stdin:
        if (pattern1.match(line)):
            tournamentcount=tournamentcount+1
            type=pattern2.search(r"(\w+)\s+tournament",line).group(1)
            counts[type]+=1
            file.write(f"Blitz:{counts['Blitz']},Bullet:{counts['Bullet']},Rapid:{counts['Rapid']},UltraBullet:{counts['UltraBullet']},Classical:{counts['Classical']},")
            file.write(f"{line} ,{tournamentcount}\n")
    end = time.time()
    file.write(f" time taken is {end-start}\n")
    file.write(f"{counts}")
    file.write(tournamentcount)


tournament_counter()

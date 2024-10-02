import io
import sys
import re
import time
import numpy as np


def tournament_counter():
    tournamentcount=0
    start = time.time()
    pattern = re.compile(r'^\[Event\s+".*tournament.*"\]$')
    for line in sys.stdin:
        if (pattern.match(line)):
            tournamentcount=tournamentcount+1
            print(line , tournamentcount)
    end = time.time()
    print(" time taken is ",end-start)
    print(tournamentcount)


tournament_counter()

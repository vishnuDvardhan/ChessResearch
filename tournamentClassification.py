import io
import sys
import threading
import chess.pgn
import time
import numpy as np

tournamentcount = 0
lock = threading.Lock()
lock1 = threading.Lock()
chessgamedata = sys.stdin.read()
reader=io.StringIO(chessgamedata)

def tournament_counter():
    global tournamentcount
    global reader
    lock.acquire()
    game = chess.pgn.read_game(reader)
    lock.release()
    while True:
        if game is None:
            break
        if "tournament" in game.headers.get("Event"):
            tournamentcount=tournamentcount+1
        print(game.headers.get("Event"),tournamentcount)


threadPool=[]
num_threads=4
start = time.time()

for i in range(num_threads):
    threadPool.append(threading.Thread(target=tournament_counter))
for thread in threadPool:
    thread.start()
for thread in threadPool:
    thread.join()
end = time.time()
print(" time taken is ", end - start)
print(tournamentcount)

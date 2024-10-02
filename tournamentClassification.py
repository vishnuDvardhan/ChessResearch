import io
import sys
import threading
import chess.pgn
import time
import numpy as np

tournamentcount = 0
lock = threading.Lock()
chessgamedata = sys.stdin.read()
reader=io.StringIO(chessgamedata)

def tournament_counter():
    global tournamentcount
    with lock:
        while True:
            game = chess.pgn.read_game(reader)
            if game is None:
                break
            if "tournament" in game.headers.get("Event"):
                tournamentcount=tournamentcount+1
            print(game.headers.get("Event"),tournamentcount)


threadPool=[]
num_threads=16
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

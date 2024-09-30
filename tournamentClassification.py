import io
import sys
import chess.pgn
import time
import numpy as np


def tournament_counter():
    all_games_states = np.array([])
    chessgamedata = sys.stdin.read()
    reader=io.StringIO(chessgamedata)
    tournamentcount=0
    start = time.time()
    is_present = lambda x : "tournament" in x.headers.get("Event")
    vec_is_present = np.vectorize(is_present)
    while True:
        game = chess.pgn.read_game(reader)
        if game is None:
            break
        if "tournament" in game.headers.get("Event"):
            tournamentcount=tournamentcount+1
        np.append(all_games_states,game)
    end = time.time()
    print(" time taken is ",end-start)
    print(tournamentcount)
    start = time.time()


tournament_counter()

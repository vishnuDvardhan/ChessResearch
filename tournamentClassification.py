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
    while True:
        game = chess.pgn.read_game(reader)
        if game is None:
            break
        if "tournament" in game.headers.get("Event"):
            tournamentcount=tournamentcount+1
            print(game.headers.get("Event"),tournamentcount)

        np.append(all_games_states,game)
    end = time.time()
    print(" time taken is ",end-start)
    print(tournamentcount)


tournament_counter()

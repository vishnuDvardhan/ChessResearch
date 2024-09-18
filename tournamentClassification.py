import io
import sys
import chess.pgn
import time
import numpy as np


def tournament_counter(pgn_file):
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


pgn_file = "/Users/vishnudvardhan/Downloads/lichess_db_antichess_rated_2024-08.pgn"
tournament_counter(pgn_file)

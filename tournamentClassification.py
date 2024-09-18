import io
import sys

import chess.pgn
import time


def pgn_to_numpy_multiple_games(pgn_file):
    all_games_states = []
    chessgamedata = sys.stdin.read()
    reader=io.StringIO(chessgamedata)
    all_games_states=[]
    tournamentcount=0
    start = time.time()

    while True:
        game = chess.pgn.read_game(reader)
        if game is None:
            break
        if "tournament" in game.headers.get("Event"):
            tournamentcount=tournamentcount+1
    end = time.time()
    print("time taken is ",end-start)
    print(tournamentcount)

pgn_file = "/Users/vishnudvardhan/Downloads/lichess_db_antichess_rated_2024-08.pgn"
pgn_to_numpy_multiple_games(pgn_file)

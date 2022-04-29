import math
import random, sys, copy
from abc import ABC, abstractmethod
from exceptions import AgentException
from heuristics import simple_score
from connect4 import Connect4


class Agent(ABC):
    def __init__(self, my_token='o', **kwargs):
        self.my_token = my_token

    @abstractmethod
    def decide(self, connect4):
        pass

    def __str__(self):
        return f"{self.my_token} ({self.__class__.__name__})"


class RandomAgent(Agent):
    def __init__(self, my_token='o', **kwargs):
        super().__init__(my_token, **kwargs)

    def decide(self, connect4):
        if connect4.who_moves != self.my_token:
            raise AgentException('not my round')
        return random.choice(connect4.possible_moves())


class MinMaxAgent(Agent):
    def __init__(self, my_token='o', depth=4, heuristic_fun=simple_score):
        super().__init__(my_token)
        self.depth=depth
        self.heuristic_fun=heuristic_fun

    def decide(self, connect4):
        if connect4.who_moves != self.my_token:
            raise AgentException('not my round')

        best_move, best_score = self.minmax(connect4, depth=self.depth)
        return best_move

    def minmax(self, connect4: Connect4, depth=4, maximizing=True):
        if depth == 0:
            return None, self.heuristic_fun(connect4, self.my_token)

        moves = connect4.possible_moves()
        best_move = moves[0]

        if maximizing:
            value = -math.inf
            for move in moves:
                temp_move, temp_value = self.minmax(copy.deepcopy(connect4), depth-1, False)
                if temp_value > value:
                    best_move = move
                    value = temp_value
            return best_move, value
        else:
            value = math.inf
            for move in moves:
                temp_move, temp_value = self.minmax(copy.deepcopy(connect4), depth-1, True)
                if temp_value < value:
                    best_move = move
                    value = temp_value
            return best_move, value

        #raise NotImplementedError


class AlphaBetaAgent(Agent):
    def __init__(self, my_token='o', depth=4, heuristic_fun=simple_score):
        super().__init__(my_token)
        self.depth=depth
        self.heuristic_fun=heuristic_fun

    def decide(self, connect4):
        if connect4.who_moves != self.my_token:
            raise AgentException('not my round')

        best_move, best_score = self.alphabeta(connect4, depth=self.depth)
        return best_move

    def alphabeta(self, connect4: Connect4, depth=4, maximizing=True, alpha=-sys.maxsize, beta=sys.maxsize):

        # TODO

        raise NotImplementedError

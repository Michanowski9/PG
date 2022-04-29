from maze import Maze, NodeType


def bfs(maze):
    start_node = maze.find_node(NodeType.START)
    q = [start_node]
    counter = 0
    while len(q) > 0:
        counter += 1
        node = q.pop(0)  # FIFO
        node.visited = True
        if node.type == NodeType.GOAL:
            return Maze.path_from(node), counter

        for child in maze.get_possible_movements(node):
            if not child.visited and child.parent is None:
                child.parent = node
                q.append(child)

        maze.draw()

    return None, counter


def dfs(maze):
    start_node = maze.find_node(NodeType.START)
    q = [start_node]
    counter = 0
    while len(q) > 0:
        counter += 1
        node = q.pop(0)  # FIFO
        node.visited = True
        if node.type == NodeType.GOAL:
            return Maze.path_from(node), counter

        for child in maze.get_possible_movements(node):
            if not child.visited and child.parent is None:
                child.parent = node
                q.insert(0, child)

        maze.draw()

    return None, counter


def dijkstra(maze):
    raise NotImplementedError()   #TODO


def a_star(maze):
    start_node = maze.find_node(NodeType.START)
    start_node.cost = 0

    q = [start_node]

    counter = 0
    while len(q) > 0:
        counter += 1
        node = q.pop(0)  # FIFO
        node.visited = True
        if node.type == NodeType.GOAL:
            return Maze.path_from(node), counter

        for child in maze.get_possible_movements(node):
            if not child.visited and child.parent is None:
                goal_node = maze.find_node((NodeType.GOAL))
                g = node.cost
                h = abs(goal_node.x - child.x) + abs(goal_node.y - child.y)
                f = g + h

                if f < child.cost:
                    child.parent = node
                    child.cost = node.cost + Maze.move_cost(node, child)
                    q.insert(0, child)

        maze.draw()

    return None, counter


algos_mapping={'a_star': a_star, 'bfs': bfs, 'dfs': dfs, 'dijkstra': dijkstra}

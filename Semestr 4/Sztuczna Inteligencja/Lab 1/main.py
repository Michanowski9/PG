import argparse
from maze import Maze
from search_algos import algos_mapping


def print_result_info(maze, steps_required):
    print("Path:", end=" ")
    for node in maze.path:
        print(f'({node.x}, {node.y})', end=' ')
    print()
    print(f"Path found in: {steps_required} steps.")
    print(f"Path length: {len(maze.path)}")


def main_cli(algo, mazefile):
    maze = Maze.from_file(mazefile)
    maze.draw()
    maze.path, n_steps = algo(maze)
    print()
    maze.draw()
    print_result_info(maze, n_steps)


def main_gui(algo, mazefile):
    from gui import PyGameMaze, wait_for_quit
    maze = PyGameMaze.from_file(mazefile)
    maze.draw()
    maze.path, n_steps = algo(maze)
    maze.draw()
    print_result_info(maze, n_steps)
    wait_for_quit()


if __name__=='__main__':
    parser = argparse.ArgumentParser()
    required_args = parser.add_argument_group("required named arguments")
    required_args.add_argument("algo", help="Required, possible values: [bfs, dfs, dijkstra, a_star]")
    required_args.add_argument("maze", help="Required, path to a file with maze specs, e.g. maze1.txt")
    parser.add_argument('--gui', action='store_true')
    args = parser.parse_args()
    if args.algo not in algos_mapping.keys():
        raise ValueError("Bad algorithm: should be one of: [bfs, dfs, dijkstra, a_star]")
    if args.gui:
        main_gui(algos_mapping[args.algo], args.maze)
    else:
        main_cli(algos_mapping[args.algo], args.maze)


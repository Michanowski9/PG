from matplotlib import pyplot
import numpy as np


def input_from_file(filename):
    f = open(filename, "r")
    result_input = f.read().split("\n")
    result = []
    for elem in result_input:
        temp = elem.split(" ")
        result.append([float(temp[0]), float(temp[1])])
    return result


def draw_original_plot(data, space):
    x_values = [x[0] for x in data]
    y_values = [y[1] for y in data]
    space.plot(x_values, y_values, zorder=1)


def draw_interpolated_plot(data_input, data_results, space):
    x_values = [x[0] for x in data_input]
    space.plot(x_values, data_results, c='tab:orange', zorder=2)


def draw_chosen_points(data, space):
    x_values = [x[0] for x in data]
    y_values = [y[1] for y in data]
    space.scatter(x_values, y_values, s=20, c='tab:green', zorder=3)


def draw_plot(data_input, data_samples, data_results, space, title):
    draw_original_plot(data_input, space)

    bottom, top = space.get_ylim()      # save scale

    draw_interpolated_plot(data_input, data_results, space)
    draw_chosen_points(data_samples, space)

    space.set_ylim(bottom, top)         # load scale
    space.set_ylabel("y")
    space.set_xlabel("x")
    space.set_title(title)


def make_plots(data_input, data_samples, lagrange_output, splines_output, filename):
    figure, (ax1, ax2) = pyplot.subplots(1, 2)
    figure.set_figwidth(10)
    figure.set_figheight(5)

    figure.suptitle(filename + "\nNumber of Samples: " + str(len(data_samples)))

    draw_plot(data_input, data_samples, lagrange_output, ax1, "Lagrange")
    draw_plot(data_input, data_samples, splines_output, ax2, "Splines")

    result_filename = 'Results/' + filename.split(".")[0] + "_samples_" + str(len(data_samples)) + '.png'

    print(result_filename)
    pyplot.savefig(result_filename)
    pyplot.show()


def get_input():
    global original

    print("podaj nazwę pliku z danymi: ")
    filename = str(input())
    # filename = "chelm.txt"
    # filename = "ostrowa.txt"
    # filename = "rozne_wzniesienia.txt"
    # filename = "stale.txt"
    # filename = "tczew_starogard.txt"

    print("podaj ilość próbek: ")
    sample_amount = int(input())
    # sample_amount = 10

    original = input_from_file("InputData/" + filename)
    samples_result = []

    for i in range(len(original)):
        if i % int(len(original) / (sample_amount - 1)) == 0:
            samples_result.append(original[i])
    if len(samples_result) < sample_amount:
        samples_result.append(original[-1])

    return original, samples_result, filename


def lagrange(data, x_list):
    result = []
    for x in x_list:
        result.append(lagrange_value(data, x))
    return result


def lagrange_value(data, x):
    result = 0

    for i in range(len(data)):
        nominator = 1
        for j in range(len(data)):
            if i != j:
                nominator *= (x - data[j][0])

        denominator = 1
        for j in range(len(data)):
            if i != j:
                denominator *= (data[i][0] - data[j][0])

        result += data[i][1] * nominator / denominator

    return result


def splines(data, x_list):
    matrix_size = (len(data) - 1) * 4
    A = np.zeros((matrix_size, matrix_size))
    b = np.zeros(matrix_size)

    row = 0

    # S_j(x_j) = f(x_j)
    for i in range(len(data) - 1):
        A[row][i * 4 + 0] = 1               # a0
        b[row] = data[i][1]
        row += 1

    # S_j(x_j+1) = f(x_j+1)
    for i in range(len(data) - 1):
        h = data[i + 1][0] - data[i][0]
        A[row][i * 4 + 0] = 1               # a0
        A[row][i * 4 + 1] = 1 * pow(h, 1)   # b0
        A[row][i * 4 + 2] = 1 * pow(h, 2)   # c0
        A[row][i * 4 + 3] = 1 * pow(h, 3)   # d0
        b[row] = data[i + 1][1]
        row += 1

    # S'_j-1(x_j) = S'_j(x_j)
    for i in range(1, len(data) - 1):
        h = data[i + 1][0] - data[i][0]
        A[row][i * 4 - 3] = 1               # b0
        A[row][i * 4 - 2] = 2 * pow(h, 1)   # c0
        A[row][i * 4 - 1] = 3 * pow(h, 2)   # d0

        A[row][i * 4 + 1] = -1              # b1

        row += 1

    # S''_j-1(x_j) = S''_j(x_j)
    for i in range(1, len(data) - 1):
        h = data[i + 1][0] - data[i][0]
        A[row][i * 4 - 2] = 2               # c0
        A[row][i * 4 - 1] = 6 * pow(h, 1)   # d0

        A[row][i * 4 + 2] = -2              # c1

        row += 1

    # S''_0(x_0) = 0
    A[row][2] = 1
    row += 1

    # S''_n(x_n) = 0
    h = data[-1][0] - data[-2][0]
    A[row][-2] = 2
    A[row][-1] = 6 * pow(h, 1)

    factors = np.linalg.solve(A, b)

    result = []
    temp = 0
    for elem in x_list:
        for i in range(len(data) - 1):
            if data[i][0] <= elem <= data[i + 1][0]:
                temp = 0
                for j in range(4):
                    h = elem - data[i][0]
                    temp += factors[4 * i + j] * pow(h, j)
        result.append(temp)

    return result


if __name__ == '__main__':
    original, samples, file = get_input()

    domain = [x[0] for x in original]

    results_lagrange = lagrange(samples, domain)
    results_splines = splines(samples, domain)

    make_plots(original, samples, results_lagrange, results_splines, file)

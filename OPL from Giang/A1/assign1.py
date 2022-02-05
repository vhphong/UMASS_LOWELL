from itertools import combinations


def print_combination(n, k):
    """
    Prints the combination of n and k
    """

    # Conveniently enough python has a function to get the combinations
    combination_list = list(combinations(range(1, k), n))

    # Print the combinations list from the elements in the form of a tuple
    for tup in combination_list:
        for element in tup:
            print("{} ".format(element), end="")
        print("")


def main():
    """
    Obtains an n and a k integer to use to
    print the combination
    """
    # Obtain n and k inputs
    n_input = int(input("Insert an integer for n: "))
    k_input = int(input("Insert an integer for k: "))

    # Prints the combination 
    print_combination(n_input, k_input)


main()

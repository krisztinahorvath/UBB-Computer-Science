def validation_of_pos(x, y):
    """
    Verifies if the input given by the user is valid
    :param x: the row
    :param y: the column
    :return: if it is valid: nothing, otherwise raises error
    """

    try:
        x = int(x)
        y = int(y)

        if x < 0 or x > 2 or y < 0 or y > 0:
            raise ValueError("Invalid input!")
    except ValueError as ve:
        raise ve

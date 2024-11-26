class PieceInfo:
    def __init__(self, material, debug_letter):
        self.material = material
        self.debug_letter = debug_letter


def print_bit_board(board):
    for i in range(64):
        pos = 1 << i

        if board & pos:
            print(" x ", end='')
        else:
            print(" . ", end='')

        if (i + 1) % 8 == 0:
            print()


PIECE_INFOS = []


def init_bit_board():
    pass
